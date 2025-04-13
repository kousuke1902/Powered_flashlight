#pragma once
#include "base_sound.hpp"

// クリック音
class ClickSound : public BaseSound
{

public:

	// コンストラクタ
	ClickSound() : BaseSound(U"click.mp3", Loop::No, U"Click", false)
	{

	}

	// デストラクタ
	~ClickSound() {}

};
