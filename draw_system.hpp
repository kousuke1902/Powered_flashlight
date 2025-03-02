#pragma once
#include <Siv3D.hpp>
#include "action_system.hpp"
#include "game_input.hpp"
#include "energy_sphre.hpp"
#include "tachometer.hpp"
#include "piston_engine.hpp"
#include "chart.hpp"
#include "drive_car.hpp"

// 描画処理関連の操作クラス
class DrawSystem final
{

private:

	DrawSystem() = default; // コンストラクタ
	~DrawSystem() = default; // デストラクタ

	Font counter_font; // 文字描画
	Font distance_font; // 移動距離描画
	Font sub_font; // 補助文字

	Chart chart; // チャートグラフ管理
	DriveCar carts; // 車描写

	ActionSystem& action = ActionSystem::getInstance();
	GameInput& input = GameInput::getInstance();


public:

	DrawSystem(const DrawSystem&) = delete; // コピーコンストラクタを削除
	DrawSystem& operator = (const DrawSystem&) = delete; // コピー代入演算子の削除
	DrawSystem(DrawSystem&&) = delete; // ムーブコンストラクタの削除
	DrawSystem& operator = (DrawSystem&&) = delete; // ムーブ代入演算子の削除

	// インスタンス情報の入手
	static DrawSystem& getInstance()
	{
		static DrawSystem inst; // プライベートなコンストラクタ
		return inst;
	}

	// 初期化設定
	int Startup()
	{
		counter_font = Font{ 50 };
		distance_font = Font{ 30 };
		sub_font = Font{ 20 };

		return 0;
	}

	// 随時更新
	int Update()
	{
		const Vec4 trigger = input.TriggerDetect(); // トリガー押し込み計測
		// タコメーター
		Tachometer().Draw(Vec2{ 207.0, 500.0 }, trigger.x);
		Tachometer().Draw(Vec2{ 583.0, 500.0 }, trigger.y);

		// チャート
		chart.Draw(Vec2{ 500.0, 200.0 }, (int)input.MouseWheelAbsDetect());

		// ピストンエンジン
		PistonEngine().Draw(Vec2{ 20.0, 450.0 }, action.ShowMouseCursorCount());

		// モニター
		RoundRect{ Arg::center(400.0, 100.0), 400.0, 140.0, 5.0 }.draw(Palette::Olivedrab);

		int phase = action.ShowPhase();

		// フェーズ0 カウンター表示
		if (phase == 0)
		{
			counter_font(action.ShowPower(), U"mosh").draw(Arg::rightCenter(590.0, 100.0));

		}

		// フェーズ1 ミニゲーム1
		else if (phase == 1)
		{
			distance_font(U"Charge 1").drawAt(400.0, 60.0);
			sub_font(U"Max").drawAt(550.0, 145.0);
			sub_font(U"Min").drawAt(250.0, 145.0);

			RectF(250.0, 100.0, 300.0, 30.0).draw().drawFrame(0.0, 5.0, Palette::Black);
			RectF(250.0, 100.0, 300.0 * action.ShowVolume1(), 30.0).draw(Palette::Orange);

			Circle(370.0, 150.0, 10.0).draw();
			Circle(400.0, 150.0, 10.0).draw(Palette::Black);
			Circle(430.0, 150.0, 10.0).draw(Palette::Black);

		}

		// フェーズ2 ミニゲーム2
		else if (phase == 2)
		{
			distance_font(U"Charge 2").drawAt(400.0, 60.0);
			sub_font(U"Max").drawAt(550.0, 145.0);
			sub_font(U"Min").drawAt(250.0, 145.0);

			RectF(250.0, 100.0, 300.0, 30.0).draw().drawFrame(0.0, 5.0, Palette::Black);
			RectF(250.0, 100.0, 300.0 * action.ShowVolume2(), 30.0).draw(Palette::Orangered);

			Circle(370.0, 150.0, 10.0).draw();
			Circle(400.0, 150.0, 10.0).draw();
			Circle(430.0, 150.0, 10.0).draw(Palette::Black);

		}

		// フェーズ3 ミニゲーム3
		else if (phase == 3)
		{
			distance_font(U"Charge 3").drawAt(400.0, 60.0);
			sub_font(U"Max").drawAt(550.0, 145.0);
			sub_font(U"Min").drawAt(250.0, 145.0);

			RectF(250.0, 100.0, 300.0, 30.0).draw().drawFrame(0.0, 5.0, Palette::Black);
			RectF(250.0, 100.0, 300.0 * action.ShowVolume3(), 30.0).draw(Palette::Red);

			Circle(370.0, 150.0, 10.0).draw();
			Circle(400.0, 150.0, 10.0).draw();
			Circle(430.0, 150.0, 10.0).draw();

		}

		// フェーズ4 エンジン始動
		else if (phase == 4)
		{
			distance_font(U"0cm").draw(Arg::rightCenter(580.0, 60.0));
			sub_font(U"クリックしてエンジン始動").drawAt(400.0, 80.0);

			carts.Draw(Vec2{ 400.0,150.0 }, false);
		}
		
		// フェーズ5 走行
		else if (phase == 5)
		{
			distance_font(action.ShouMovement(), U"cm").draw(Arg::rightCenter(580.0, 60.0));

			carts.Draw(Vec2{ 400.0,150.0 }, true);
		}

		RoundRect{ Arg::center(400.0, 100.0), 400.0, 140.0, 5.0 }.drawFrame(5.0, Palette::Black);

		return 0;
	}

};
