#pragma once
#include "base_sound.hpp"
#include "action_system.hpp"

// クリック音
class RunSound : public BaseSound
{
private:

	Audio audio1; // 走行音
	Audio audio2; // 走行音

	ActionSystem& action = ActionSystem::getInstance();

public:

	// コンストラクタ
	RunSound() : BaseSound(U"run1.mp3", Loop::No, U"Run", false)
	{
		audio1 = Audio{ Audio::Stream, U"run2.mp3" };
		audio2 = Audio{ Audio::Stream, U"run3.mp3" };
	}

	// デストラクタ
	~RunSound() {}

	// 再生
	int PlaySound() override
	{

		audio.playOneShot();
		return 0;
	}

	// 削除フラグ
	bool CheckDeleteFlag() override
	{
		if (action.ShowScene() != _RUN_SCENE_) return true;
		return false;

	}

};
