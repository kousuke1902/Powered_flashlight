#pragma once
#include<Siv3D.hpp>

#define _CIRCLE_RADIUS_ 10.0
#define _FIRST_SHAFT_SIZE_ 50.0

class PistonEngine
{

private:



public:

	PistonEngine()
	{


	}

	~PistonEngine(){}

	int Draw(Vec2 origin, double x)
	{
		// 角度算出
		double theta = x * 0.5_deg;
		Vec2 first_fastener = OffsetCircular(origin, _FIRST_SHAFT_SIZE_, theta);
		Vec2 second_fastener = origin + Vec2{ 0.0, -100.0 - Cos(theta) * _FIRST_SHAFT_SIZE_ };

		// 第一シャフト
		Line{ origin, first_fastener }.draw(LineStyle::RoundCap, 40.0, Palette::Orange);
		Circle{ origin, _CIRCLE_RADIUS_ }.draw();
		// ピストンヘッド
		RectF{ Arg::center(second_fastener), 100.0, 50.0 }.draw(Palette::Blue);
		// 第二シャフト
		Line{ first_fastener, second_fastener }.draw(LineStyle::RoundCap, 40.0, Palette::Green);
		Circle{ first_fastener, _CIRCLE_RADIUS_ }.draw();

		Circle{ second_fastener, _CIRCLE_RADIUS_ }.draw();

		return 0;
	}

};
