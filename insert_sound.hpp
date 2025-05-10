#pragma once
#include "base_sound.hpp"

// ねじ巻き差し込み音
class InsertSound : public BaseSound
{

public:

	// コンストラクタ
	InsertSound() : BaseSound(Resource(U"insert.mp3"), Loop::No, U"Insert", false)
	{

	}

	// デストラクタ
	~InsertSound() {}

};
