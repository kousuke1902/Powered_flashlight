#pragma once
#include "base_sound.hpp"

// ねじまき音
class WindUpSound : public BaseSound
{
public:

	// コンストラクタ
	WindUpSound() : BaseSound(Resource(U"wind-up.mp3"), Loop::No, U"WindUp", false)
	{


	}

	// デストラクタ
	~WindUpSound(){}

};
