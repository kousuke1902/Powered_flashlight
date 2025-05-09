﻿#pragma once
#include <Siv3D.hpp>
#include "base_particle.hpp"

// 散らばるパーティクルのアニメーションクラス
class Scatter : public BaseParticle
{
private:


	Texture icon; // パーティクルの柄

public:

	// コンストラクタ
	Scatter(double set_life_span, Vec2 set_graph, Vec2 set_vector): BaseParticle(set_life_span, set_graph, set_vector.setLength(1.0), Random<double>(50.0, 100.0))
	{
		icon = Texture{ 0xf5d2_icon, 10 };
	}

	// デストラクタ
	~Scatter(){}



	// パーティクル描画
	int Draw() override
	{

		icon.drawAt(graph);
		return 0;
	}
};
