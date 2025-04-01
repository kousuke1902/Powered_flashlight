#pragma once
#include <Siv3D.hpp>
#include "delta_time.hpp"

#define _CAR_SIZE_ 250

// 車のアニメーションクラス
class DriveCar
{
private:

	Texture car; // アイコン
	DeltaTime& deltatime = DeltaTime::getInstance();

public:

	DriveCar()
	{
		int num = Random(17);

		// num = 15;

		if (num == 0)car = Texture{ 0xF07AB_icon, _CAR_SIZE_ }; // 乗用車
		else if (num == 1)car = Texture{ 0xF07A9_icon, _CAR_SIZE_ }; // ハッチバック車
		else if (num == 2)car = Texture{ 0xF07A8_icon, _CAR_SIZE_ }; // エステート車
		else if (num == 3)car = Texture{ 0xF07A7_icon, _CAR_SIZE_ }; // オープンカー
		else if (num == 4)car = Texture{ 0xF07AA_icon, _CAR_SIZE_ }; // ピックアップトラック
		else if (num == 5)car = Texture{ 0xF152D_icon, _CAR_SIZE_ }; // リフトアップピックアップトラック
		else if (num == 6)car = Texture{ 0xF07AC_icon, _CAR_SIZE_ }; // スポーツカー
		else if (num == 7)car = Texture{ 0xF053D_icon, _CAR_SIZE_ }; // トラック
		else if (num == 8)car = Texture{ 0xF1891_icon, _CAR_SIZE_ }; // フラットヘッドトラック
		else if (num == 9)car = Texture{ 0xF11D4_icon, _CAR_SIZE_ }; // RVトラック
		else if (num == 10)car = Texture{ 0xF0C67_icon, _CAR_SIZE_ }; // ダンプカー
		else if (num == 11)car = Texture{ 0xF0FE5_icon, _CAR_SIZE_ }; // タンク車
		else if (num == 12)car = Texture{ 0xF08AB_icon, _CAR_SIZE_ }; // 消防車
		else if (num == 13)car = Texture{ 0xF0D3A_icon, _CAR_SIZE_ }; // 戦車
		else if (num == 14)car = Texture{ 0xF11A4_icon, _CAR_SIZE_ }; // ゴルフカート
		else if (num == 15)car = Texture{ 0xF15EB_icon, _CAR_SIZE_ }; // レジカート
		else if (num == 16)car = Texture{ 0xF0D79_icon, _CAR_SIZE_ }; // ゴーカート
		else if (num == 17)car = Texture{ 0xF1677_icon, _CAR_SIZE_ }; // カタツムリ

	}

	~DriveCar(){}

	// 高さサイズ
	const int Height()
	{
		return car.height();
	}

	// 幅サイズ
	const int Width()
	{
		return car.width();
	}

	// 描画
	int Draw(Vec2 graph, bool accel_flag)
	{
		car.draw(Arg::bottomCenter(graph));

		return 0;
	}

	// 描画
	int Draw(double x, double y)
	{

		car.draw(Arg::bottomCenter(x, y));

		return 0;
	}

};
