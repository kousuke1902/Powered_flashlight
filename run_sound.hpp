#pragma once
#include "base_sound.hpp"

// 走行音
class RunSound : public BaseSound
{
private:


public:

	// コンストラクタ
	RunSound() : BaseSound(Resource(U"run.mp3"), Loop::No, U"Run", false)
	{
		
	}

	// デストラクタ
	~RunSound() {}
	

	// 再生
	int PlaySound() override
	{
		audio.play(MixBus1);
		audio.setSpeed(0.5);
		GlobalAudio::BusSetPitchShiftFilter(MixBus1, 0, -12.0);

		return 0;
	}

	// 削除フラグ
	bool CheckDeleteFlag() override
	{
		time += deltatime.ShowDeltaTime();
		if (time >= audio.lengthSec() * 2.0) return true;
		return false;

	}

};
