#pragma once
#include <Siv3D.hpp>
#include "delta_time.hpp"

// パーティクルの基礎クラス
class BaseParticle
{



protected:

	double life_span; // 時間的寿命
	Vec2 graph; // 座標位置
	Vec2 vector; // 移動方向
	double speed; // 速度
	DeltaTime& deltatime = DeltaTime::getInstance(); // 差分時間取得

public:

	// コンストラクタ
	BaseParticle()
	{
		life_span = 1.0;
		graph = Vec2(300.0, 300.0);
		vector = Vec2(0.0, 1.0);
		speed = 10.0;
	}

	// コンストラクタ
	BaseParticle(double set_life_span, Vec2 set_graph, Vec2 set_vector, double set_speed = 0.0)
	{

		life_span = set_life_span;
		graph = set_graph;
		vector = set_vector;
		speed = set_speed;
	}

	// コンストラクタ
	BaseParticle(double set_life_span, Vec2 set_graph, double set_speed = 0.0)
	{

		life_span = set_life_span;
		graph = set_graph;
		vector = Vec2(0.0, 0.0);
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
		if (life_span > 0.0) return false;
		return true;
	}

	// パーティクル移動
	virtual int Move()
	{
		graph.moveBy(vector * speed * deltatime.ShowDeltaTime());

		return 0;
	}

	// パーティクル描画
	virtual int Draw()
	{
		Circle{ graph, 1.0 }.draw();

		return 0;
	}

};
