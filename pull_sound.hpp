#pragma once
#include "base_sound.hpp"

// ねじ巻きの引き抜き音
class PullSound : public BaseSound
{

public:

	// コンストラクタ
	PullSound() : BaseSound(Resource(U"pull.mp3"), Loop::No, U"Pull", false)
	{

	}

	// デストラクタ
	~PullSound() {}

};
