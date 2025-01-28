#pragma once
#include <Siv3D.hpp>

#define _CHART_SIZE_ 100
#define _SPACE_SIZE_ 2

// 入力情報の経過を描画するチャートグラフのアニメーションクラス
class Chart
{
private:

	Array<int> points;

public:

	Chart()
	{

		points = Array<int>(_CHART_SIZE_, 0);

	}

	~Chart(){}

	// 描画 origin=描画座標起点, x=高さ
	int Draw(Vec2 origin, int x)
	{
		// 末尾に数値を追加
		points << x;
		// 先頭から要素を削除
		points.pop_front();

		Array<Vec2> position;

		for (int step = 0; step < _CHART_SIZE_; ++step)
		{
			position << origin + Vec2(step * _SPACE_SIZE_, -points[step] * 30.0);

		}

		LineString{ position }.draw(6, Palette::Orange);

		return 0;
	}

};
