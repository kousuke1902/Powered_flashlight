#pragma once
#include "base_sound.hpp"

// 結果発表音
class ResultSound : public BaseSound
{

public:

	// コンストラクタ
	ResultSound() : BaseSound(Resource(U"result.mp3"), Loop::No, U"Result", false)
	{

	}

	// デストラクタ
	~ResultSound() {}

};
