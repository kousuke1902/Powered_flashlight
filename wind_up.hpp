#pragma once
#include <Siv3D.hpp>

// ねじ巻きのアニメーションクラス
class WindUp
{

private:

	Texture wind_up; // ねじ巻き


public:

	// コンストラクタ
	WindUp()
	{
		wind_up = Texture{ 0xF1C23_icon, 150 };

	}

	// デストラクタ
	~WindUp(){}

	// 描画
	int Draw(double x, double y, double deg, double alpha)
	{
		ColorF color{ 1.0, alpha };

		wind_up.scaled(1.0, Cos(deg)).draw(Arg::rightCenter(x, y), color);
		wind_up.uv(0.79, 0.0, 0.21, 1.0).draw(Arg::rightCenter(x, y), color);
		wind_up.uv(0.0, 0.41, 1.0, 0.17).draw(Arg::rightCenter(x, y), color);

		return 0;
	}

};
