#pragma once
#include <Siv3D.hpp>
#include "delta_time.hpp"

#define _MAX_SPHRE_POINTS_ 128
#define _SPHRE_SIZE_ 50

// 暴れて動く円系のアニメーションを描画処理する
class EnergySphre
{

private:

	Array<double> lengths; // 動かした点群の移動距離
	double piece; // 1角度の大きさ
	DeltaTime& delta_time = DeltaTime::getInstance();

public:

	// コンストラクタ
	EnergySphre()
	{
		// 個数分初期値の幅を作成する
		lengths = Array<double>(_MAX_SPHRE_POINTS_, 0.0);
		// 1角の大きさを確定する
		piece = 360_deg / _MAX_SPHRE_POINTS_;
	}

	// デストラクタ
	~EnergySphre(){}

	// 点群移動距離処理
	int MovementPoints(int x)
	{

		for (int step = 0; step < _MAX_SPHRE_POINTS_; ++step)
		{
			// 時間ごとに減少する
			lengths[step] -= delta_time.ShowDeltaTime() * 50.0;

			// 0以下の場合0へ修正する
			if (lengths[step] < 0.0) lengths[step] = 0.0;
		}

		// ランダムな距離を増やす
		if(Periodic::Square0_1(0.5s))	lengths[Random<size_t>(_MAX_SPHRE_POINTS_ - 1)] += Random(20.0);

		// ボタン入力時ランダムな距離を増やす
		for (int step = 0; step < x; ++step)
		{
			lengths[Random<size_t>(_MAX_SPHRE_POINTS_ - 1)] = 50.0;

		}

		return 0;
	}

	// origin座標にスフィアを形成する
	int Draw(Vec2 origin)
	{
		Array<Vec2> sphre_points; // 合算したスフィアの点群形状

		// 有限個の点群を円形状に配置する
		for (int step = 0; step < _MAX_SPHRE_POINTS_; ++step)
		{
			const double theta = (step * piece);

			sphre_points << OffsetCircular{ origin, _SPHRE_SIZE_ + lengths[step], theta};

		}

		const Polygon sphre{ sphre_points };

		sphre.draw(Palette::Orange);

		return 0;
	}

};
