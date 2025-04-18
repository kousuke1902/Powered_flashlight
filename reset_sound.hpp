#pragma once
#include "base_sound.hpp"

// リセット音
class ResetSound : public BaseSound
{

public:

	// コンストラクタ
	ResetSound() : BaseSound(Resource(U"reset.mp3"), Loop::No, U"Result", false)
	{

	}

	// デストラクタ
	~ResetSound() {}

};
