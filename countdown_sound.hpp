#pragma once
#include "base_sound.hpp"

// リセットカウントダウン音
class CountdownSound : public BaseSound
{

public:

	// コンストラクタ
	CountdownSound() : BaseSound(Resource(U"countdown.mp3"), Loop::No, U"Result", false)
	{

	}

	// デストラクタ
	~CountdownSound() {}

};
