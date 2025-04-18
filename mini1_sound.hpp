#pragma once
#include "base_sound.hpp"

// ミニゲーム1音
class Mini1Sound : public BaseSound
{

public:

	// コンストラクタ
	Mini1Sound() : BaseSound(Resource(U"mini1.mp3"), Loop::No, U"Mini1", false)
	{

	}

	// デストラクタ
	~Mini1Sound() {}

};
