#pragma once
#include <Siv3D.hpp>
#include "base_particle.hpp"

// 水紋が広がっていくパーティクル
class WaterRipple : public BaseParticle 
{

private:

	Color color;
	double start_time;

public:

	// コンストラクタ
	WaterRipple(double set_life_span, Vec2 set_graph,double set_speed, Color set_color) : BaseParticle(set_life_span, set_graph, set_speed)
	{
		color = set_color;
		start_time = set_life_span;
	}

	// デストラクタ
	~WaterRipple(){}

	// パーティクル移動
	int Move() override
	{
		vector.x += deltatime.ShowDeltaTime() * speed;
		color.a = Sin(90_deg * life_span / start_time) * 100.0;
		return 0;
	}

	// パーティクル描画
	int Draw() override
	{
		Circle{ graph, vector.x }.drawFrame(1.0, color);

		return 0;
	}

};
