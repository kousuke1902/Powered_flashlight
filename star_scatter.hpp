#pragma once
#include <Siv3D.hpp>
#include "base_particle.hpp"

class StarScatter : public BaseParticle
{
private:
	Texture icon; // パーティクルの柄

public:

	// コンストラクタ
	StarScatter(double set_life_span, Vec2 set_graph) : BaseParticle(set_life_span, set_graph, Vec2(Random(-1.0, 1.0), Random(-1.0, 1.0)).setLength(1.0), 50.0)
	{
		icon = Texture{ 0xf005_icon, Random(10)};
	}

	// デストラクタ
	~StarScatter(){}

	// パーティクル描画
	int Draw() override
	{
		icon.drawAt(graph);
		return 0;
	}

};
