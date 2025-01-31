#pragma once
#include <Siv3D.hpp>
#include "delta_time.hpp"

class BaseParticle
{
private:

	double life_span; // 時間的寿命
	DeltaTime& deltatime = DeltaTime::getInstance(); // 差分時間取得

protected:

	Vec2 graph; // 座標位置
	double speed; // 速度

public:

	// コンストラクタ
	BaseParticle()
	{
		life_span = 5.0;
		graph = Vec2(300.0, 300.0);
		speed = 100.0;
	}

	// コンストラクタ
	BaseParticle(double set_life_span, Vec2 origin_graph, double set_speed)
	{

		life_span = set_life_span;
		graph = origin_graph;
		speed = set_speed;
	}

	// デストラクタ
	~BaseParticle(){}


	// 寿命処理
	int ReduceLifeSpan()
	{
		life_span -= deltatime.ShowDeltaTime();
		return 0;
	}

	// 寿命確認
	bool CheckLife()
	{
		if (life_span <= 0.0) true;
		return false;
	}

	// パーティクル移動
	virtual int Move()
	{
		graph.moveBy(Vec2(0.0, 1.0) * speed * deltatime.ShowDeltaTime());

		return 0;
	}

	// パーティクル描画
	virtual int Draw()
	{
		Circle{ graph, 1.0 }.draw();

		return 0;
	}

};
