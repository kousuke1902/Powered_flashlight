#pragma once
#include <Siv3D.hpp>

#define _METER_SIZE_ 50
#define _LAMP_SIZE_ 5
#define _POINTER_SIZE_ 40
#define _SCALE_SIZE_ 30

class Tachometer
{
private:

	Circle base; // メーター土台
	double pointer ; // メーター針終点

public:

	// コンストラクタ
	Tachometer()
	{
		base = Circle{300.0, 300.0, _METER_SIZE_ };
		pointer =0.0;
	}

	// コンストラクタ
	Tachometer(double x, double y)
	{
		base = Circle{ x, y, _METER_SIZE_ };
		pointer = 0.0;
	}

	// タコメーターの描画 X=針の振れ幅
	int Draw(double x)
	{
		// ベース
		base.draw(Palette::Black).drawFrame(7.0, Palette::Slategray);

		// 目盛り
		for (int step = 0; step < 11; ++step)
		{
			double theta = 22_deg * step - 110_deg;
			Line{ OffsetCircular{base.center, _SCALE_SIZE_, theta}, OffsetCircular{base.center, _POINTER_SIZE_, theta} }.draw(5.0, Palette::White);

		}

		// 針
		Line{ base.center, OffsetCircular{base.center, _POINTER_SIZE_, 220_deg * x - 110_deg} }.draw(LineStyle::RoundCap,10, Palette::Red);

		// ランプ
		if(x >= 0.8)Circle{ base.x, base.y + 20, _LAMP_SIZE_ }.draw(HSV(0.0, 1.0, 1.0));
		else Circle{ base.x, base.y + 20, _LAMP_SIZE_ }.draw(HSV(0.0, 0.0, 1.0));

		return 0;
	}

};
