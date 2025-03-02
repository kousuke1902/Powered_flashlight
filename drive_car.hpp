#pragma once
#include <Siv3D.hpp>
#include "delta_time.hpp"


// 車のアニメーションクラス
class DriveCar
{
private:

	Font counter_font; // 文字描画
	Font distance_font; // 移動距離描画
	Texture car; // アイコン
	DeltaTime& deltatime = DeltaTime::getInstance();

	int distance;

public:

	DriveCar()
	{
		counter_font = Font{ 50 };
		distance_font = Font{ 30 };

		distance = 0;

		int num = Random(16);

		if (num == 0)car = Texture{ 0xF07AB_icon, 50 }; // 乗用車
		else if (num == 1)car = Texture{ 0xF07A9_icon, 50 }; // ハッチバック車
		else if (num == 2)car = Texture{ 0xF07A8_icon, 50 }; // エステート車
		else if (num == 3)car = Texture{ 0xF07A7_icon, 50 }; // オープンカー
		else if (num == 4)car = Texture{ 0xF07AA_icon, 50 }; // ピックアップトラック
		else if (num == 5)car = Texture{ 0xF152D_icon, 50 }; // リフトアップピックアップトラック
		else if (num == 6)car = Texture{ 0xF07AC_icon, 50 }; // スポーツカー
		else if (num == 7)car = Texture{ 0xF053D_icon, 50 }; // トラック
		else if (num == 8)car = Texture{ 0xF1891_icon, 50 }; // フラットヘッドトラック
		else if (num == 9)car = Texture{ 0xF11D4_icon, 50 }; // RVトラック
		else if (num == 10)car = Texture{ 0xF0C67_icon, 50 }; // ダンプカー
		else if (num == 11)car = Texture{ 0xF0FE5_icon, 50 }; // タンク車
		else if (num == 12)car = Texture{ 0xF08AB_icon, 50 }; // 消防車
		else if (num == 13)car = Texture{ 0xF0D3A_icon, 50 }; // 戦車
		else if (num == 14)car = Texture{ 0xF11A4_icon, 50 }; // ゴルフカート
		else if (num == 15)car = Texture{ 0xF15EB_icon, 50 }; // レジカート
		else if (num == 16)car = Texture{ 0xF0D79_icon, 50 }; // ゴーカート
		else if (num == 17)car = Texture{ 0xF1677_icon, 50 }; // カタツムリ

	}

	~DriveCar(){}


	// 描画
	int Draw(Vec2 graph, bool accel_flag)
	{

		car.draw(Arg::bottomCenter(graph));


		return 0;
	}

};
