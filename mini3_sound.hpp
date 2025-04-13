#pragma once
#include "base_sound.hpp"

// クリック音
class Mini3Sound : public BaseSound
{

public:

	// コンストラクタ
	Mini3Sound() : BaseSound(U"mini3.mp3", Loop::No, U"Mini3", false)
	{

	}

	// デストラクタ
	~Mini3Sound() {}

};
