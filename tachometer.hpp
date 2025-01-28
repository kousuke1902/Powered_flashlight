#pragma once
#include <Siv3D.hpp>

#define _METER_SIZE_ 50
#define _LAMP_SIZE_ 5
#define _POINTER_SIZE_ 40
#define _SCALE_SIZE_ 30

// 出力に対して動くタコメーターのアニメーションクラス
class Tachometer
{
private:



public:

	// コンストラクタ
	Tachometer()
	{

	}

	// タコメーターの描画 origin=原点 X=針の振れ幅
	int Draw(Vec2 origin, double x)
	{
		// ベース
		Circle{ origin, _METER_SIZE_ }.draw(Palette::Black).drawFrame(7.0, Palette::Slategray);

		// 目盛り
		for (int step = 0; step < 11; ++step)
		{
			double theta = 22_deg * step - 110_deg;
			Line{ OffsetCircular{origin, _SCALE_SIZE_, theta}, OffsetCircular{origin, _POINTER_SIZE_, theta} }.draw(5.0, Palette::White);

		}

		// 針
		Line{ origin, OffsetCircular{origin, _POINTER_SIZE_, 220_deg * x - 110_deg} }.draw(LineStyle::RoundCap,10, Palette::Red);

		// ランプ
		Circle{ origin.x, origin.y + 20, _LAMP_SIZE_ }.draw(HSV(0.0, x >= 0.85 ? 1.0 : 0.0, 1.0));

		return 0;
	}

};
