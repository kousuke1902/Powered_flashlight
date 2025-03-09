#pragma once
#include <Siv3D.hpp>
#include "base_particle.hpp"

// 風を切るパーティクル
class Wind : public BaseParticle
{

private:

	Texture wind;

public:


	// コンストラクタ
	Wind(double set_life_span, Vec2 graph) : BaseParticle(set_life_span, graph + RandomVec2(Circle{ 0.0, 0.0, 50.0 }), Vec2(-1.0, 0.0), 100.0)
	{
		wind = Texture{ 0xF059D_icon, 50 };

	}

	// デストラクタ
	~Wind(){}


	// パーティクル描画
	int Draw() override
	{
		wind.mirrored().drawAt(graph);

		return 0;
	}

};
