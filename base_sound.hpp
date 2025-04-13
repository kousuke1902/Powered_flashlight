#pragma once
#include <Siv3D.hpp>
#include "delta_time.hpp"

// 効果音の基礎クラス
class BaseSound
{
private:

	String id; // 番号割り当て
	bool overlapping; // 同じ音源での重複可否

protected:

	Audio audio; // 効果音
	double time; // 経過時間

	DeltaTime& deltatime = DeltaTime::getInstance();

public:

	// コンストラクタ
	BaseSound(FilePath filename, Loop loop_flag, String set_id, bool overlapping_posibility)
	{
		audio = Audio{ Audio::Stream, filename, loop_flag };
		id = set_id;
		overlapping = overlapping_posibility;
		time = 0.0;
	}

	// デストラクタ
	~BaseSound(){}

	// 再生
	virtual int PlaySound()
	{
		audio.playOneShot();
		return 0;
	}

	// 割り当て番号閲覧
	String ShowID()
	{
		return id;
	}

	// 重複可否閲覧
	bool ShowOverlapping()
	{
		return overlapping;
	}

	// 削除フラグ
	virtual bool CheckDeleteFlag() 
	{
		time += deltatime.ShowDeltaTime();
		if (time >= audio.lengthSec()) return true;
		return false;

	}

};
