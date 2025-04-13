#pragma once
#include "base_sound.hpp"

// クリック音
class Mini1Sound : public BaseSound
{

public:

	// コンストラクタ
	Mini1Sound() : BaseSound(U"mini1.mp3", Loop::No, U"Mini1", false)
	{

	}

	// デストラクタ
	~Mini1Sound() {}

};
