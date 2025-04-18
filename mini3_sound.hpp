#pragma once
#include "base_sound.hpp"

// ミニゲーム3音
class Mini3Sound : public BaseSound
{

public:

	// コンストラクタ
	Mini3Sound() : BaseSound(Resource(U"mini3.mp3"), Loop::No, U"Mini3", false)
	{

	}

	// デストラクタ
	~Mini3Sound() {}

};
