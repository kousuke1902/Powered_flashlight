#pragma once
#include <Siv3D.hpp>
#include "delta_time.hpp"

// ねじ巻きのアニメーションクラス
class WindUp
{

private:

	double time;
	Texture wind_up; // ねじ巻き

	DeltaTime& deltatime = DeltaTime::getInstance();

public:

	// コンストラクタ
	WindUp()
	{
		wind_up = Texture{ 0xF1C23_icon, 50 };

	}

	// デストラクタ
	~WindUp(){}

	// 描画
	int Draw(double x, double y, double count)
	{

		time += deltatime.ShowDeltaTime();

		wind_up.scaled(1.0, Cos(time)).draw(Arg::rightCenter(x, y));
		wind_up.uv(0.8, 0.0, 0.2, 1.0).draw(Arg::rightCenter(x, y));
		wind_up.uv(0.0, 0.43, 1.0, 0.15).draw(Arg::rightCenter(x, y));

		return 0;
	}

};
