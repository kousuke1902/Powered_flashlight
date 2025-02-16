#pragma once
#include <Siv3D.hpp>
#include "delta_time.hpp"


// 数値とロケットのアニメーションクラス
class Monitor
{
private:

	int phase; // 状態
	double phase_timer; // フェーズ遷移用タイマー
	bool timer_flag; // カウント可能フラグ
	Font counter_font; // 文字描画
	Font distance_font; // 移動距離描画
	Texture car; // アイコン
	DeltaTime& deltatime = DeltaTime::getInstance();

	int distance;

public:

	Monitor()
	{
		phase = 1;
		phase_timer = 0.0;
		timer_flag = true;
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

	~Monitor(){}

	// フェーズ遷移状態
	int PhaseCheck(bool flag)
	{

		// フェーズ0 カウンターの場合
		if (phase == 0)
		{
			if (flag == true)
			{
				timer_flag = true;
				phase++;
			}

		}

		// フェーズ1 遷移アニメーション
		if (phase == 1)
		{
			if (phase_timer > 180_deg)
			{
				timer_flag = false;
				phase_timer = 0.0;
				phase++;
			}

		}

		// フェーズ2 車走行
		if (phase == 2)
		{


		}


		return 0;
	}

	// フェーズ間時間計測
	int PhaseTimer()
	{
		if(timer_flag == true)phase_timer += deltatime.ShowDeltaTime();
		return 0;
	}

	// 描画する距離の設定
	int DistanceSet()
	{

		return 0;
	}

	// 描画
	int Draw(Vec2 graph, int count)
	{

		RoundRect{ Arg::center(graph), 400.0, 140.0, 5.0 }.draw(Palette::Olivedrab);
		

		// フェーズ0 カウンター表示フェーズ
		if (phase == 0)counter_font(count, U" mosh").draw(Arg::rightCenter(graph + Vec2(190.0, 0.0)));

		// フェーズ1 遷移アニメーションフェーズ
		else if (phase == 1)
		{

			// Sin 90度まで右へ拡大
			if (phase_timer < 90_deg)
			{
				double line = Sin(phase_timer);
				RoundRect{ graph + Vec2{-200.0, -70.0},line * 400.0, 140.0, 5.0 }.draw();
				counter_font(count, U" mosh").draw(Arg::rightCenter(graph + Vec2(190.0, 0.0)));
			}
			// Sin 90度以降から左から縮小
			else if (phase_timer >= 90_deg)
			{
				double line = Sin(phase_timer - 90_deg);
				car.draw(Arg::bottomCenter(graph + Vec2{ -160 + line * 160.0, 50.0 }));
				Line{ graph + Vec2{-200.0, 50.0}, graph + Vec2{200.0, 50.0} }.draw(4.0);
				distance_font(distance, U"cm").draw(Arg::rightCenter(graph + Vec2{ 190.0, -50.0 }));
				RoundRect{ graph + Vec2{-200.0 + line * 400.0, -70.0},400.0 - line * 400.0, 140.0, 5.0 }.draw();
			}

		}

		// フェーズ2 車走行
		else if (phase == 2)
		{
			car.draw(Arg::bottomCenter( graph + Vec2{0.0, 50.0}));
			distance_font(distance, U"cm").draw(Arg::rightCenter(graph + Vec2{ 190.0, -50.0 }));
			Line{ graph + Vec2{-200.0, 50.0}, graph + Vec2{200.0, 50.0} }.draw(4.0);
		}


		RoundRect{ Arg::center(graph), 400.0, 140.0, 5.0 }.drawFrame(5.0, Palette::Black);

		return 0;
	}

};
