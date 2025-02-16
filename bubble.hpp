#pragma once
#include <Siv3D.hpp>
#include "base_particle.hpp"

// 泡のパーティクルクラス
class Bubble : public BaseParticle
{

private:
	double time; // 変化時間

public:

	// コンストラクタ
	Bubble(double set_life_span, Vec2 set_graph, double min_speed, double max_speed) : BaseParticle(set_life_span, set_graph, Vec2(0.0, -1.0), Random<double>(min_speed, max_speed))
	{
		time = Random<double>(360_deg);

	}

	// デストラクタ
	~Bubble(){}

	// パーティクル移動
	int Move() override
	{
		time += deltatime.ShowDeltaTime();
		vector.x = Sin(time) / 8.0;
		graph.moveBy(vector * deltatime.ShowDeltaTime() * speed);
		return 0;
	}

	// パーティクル描画
	int Draw() override
	{
		Circle{ graph, 4.0 }.draw();
		return 0;
	}

};
