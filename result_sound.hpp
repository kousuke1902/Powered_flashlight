#pragma once
#include "base_sound.hpp"

// クリック音
class ResultSound : public BaseSound
{

public:

	// コンストラクタ
	ResultSound() : BaseSound(U"result.mp3", Loop::No, U"Result", false)
	{

	}

	// デストラクタ
	~ResultSound() {}

};
