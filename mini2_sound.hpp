#pragma once
#include "base_sound.hpp"

// クリック音
class Mini2Sound : public BaseSound
{

public:

	// コンストラクタ
	Mini2Sound() : BaseSound(U"mini2.mp3", Loop::No, U"Mini2", false)
	{

	}

	// デストラクタ
	~Mini2Sound() {}

};
