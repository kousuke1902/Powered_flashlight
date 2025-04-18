#pragma once
#include "base_sound.hpp"

// ミニゲーム2音
class Mini2Sound : public BaseSound
{

public:

	// コンストラクタ
	Mini2Sound() : BaseSound(Resource(U"mini2.mp3"), Loop::No, U"Mini2", false)
	{

	}

	// デストラクタ
	~Mini2Sound() {}

};
