﻿#pragma once
#include <Siv3D.hpp>
#include "action_system.hpp"
#include "particle_system.hpp"
#include "sound_system.hpp"
#include "game_input.hpp"
#include "delta_time.hpp"
#include "energy_sphre.hpp"
#include "tachometer.hpp"
#include "piston_engine.hpp"
#include "chart.hpp"
#include "drive_car.hpp"
#include "wind_up.hpp"
#include "button.hpp"


// 描画処理関連の操作クラス
class DrawSystem final
{

private:

	DrawSystem() = default; // コンストラクタ
	~DrawSystem() = default; // デストラクタ

	Font counter_font; // 文字描画
	Font distance_font; // 移動距離描画
	Font sub_font; // 補助文字

	DriveCar carts; // 車描写
	WindUp wind; // ねじ巻き

	Button action_button; // 操作ボタン
	Button reset_button; // データ初期化ボタン

	double wind_interval; // 走行パーティクルの時間間隔
	double tree_interval; // 走行パーティクルの時間間隔

	ActionSystem& action = ActionSystem::getInstance();
	ParticleSystem& particle = ParticleSystem::getInstance();
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
		counter_font = Font{ FontMethod::MSDF, 50 };
		distance_font = Font{ FontMethod::MSDF, 30 };
		sub_font = Font{ FontMethod::MSDF, 20 };
		action_button = Button{ RectF{ Arg::center(400.0, 500.0), 300.0, 70.0 }, Palette::White };
		reset_button = Button{ RectF{Arg::center(90.0, 30.0), 150.0, 30.0 }, Palette::White };
		wind_interval = 0.0;
		tree_interval = 0.0;

		return 0;
	}

	// 随時更新
	int Update()
	{
		
		// ねじ巻き
		double x = 420.0 - carts.Width() / 1.5;
		double y = 440.0 - carts.Height() / 3.0;
		double dist = action.ShowWindUpVolume();
		wind.Draw(x + dist * 15.0, y, action.ShowPower() * 12_deg, dist);

		// ボタン
		//データ初期化

		reset_button.Draw();
		sub_font(U"データリセット").drawAt(90.0, 30.0, Palette::Black);

		if (reset_button.mouseOver() && MouseL.down())
		{
			reset_button.Click();
			action.DataResetAction();
			particle.AddParticle(new WaterRipple(1.0, Cursor::PosF(), 50.0, Palette::Blueviolet));

		}

		// モード移行
		if (action_button.mouseOver() && MouseL.down())
		{
			action_button.Click();
			action.nextGameStep();
			particle.AddParticle(new WaterRipple(1.0, Cursor::PosF(), 50.0, Palette::Blueviolet));
			
		}

		action_button.Draw();

		// 表示
		int current_scene = action.ShowScene();

		// 車両
		carts.Draw(400.0, 450.0, current_scene == _RUN_SCENE_);

		if (current_scene == _WINDUP_SCENE_)
		{
			distance_font(U"ねじを巻こう").drawAt(400.0, 50.0);
			counter_font(action.ShowPower(), U"巻き").drawAt(400.0, 150.0);
			counter_font(U"出発").drawAt(400.0, 500.0, Palette::Black);

			// ねじ巻きパーティクル
			if (action.ShowPowerFlag())
			{
				for (size_t time = 0; time < 2; ++time)
				{
					particle.AddParticle(new StarScatter(Random(1.0, 3.0), Vec2(x - 50, y)));
				}
			}
		}

		// ミニゲーム
		else if (current_scene == _MINIGAME_SCENE_)
		{
			distance_font(U"気合いを注入").drawAt(400.0, 50.0);
			sub_font(U"ゲージが右に行ったらボタンを押そう").drawAt(400.0, 90.0);
			
			Rect{ Arg::center(400, 170), 400, 50 }.draw(Palette::White);
			Rect{ Arg::center(400, 170), 370, 40 }.draw(Palette::Black);

			current_scene = action.ShowMiniGameStep();
			if (current_scene == 0)
			{
				RectF{ Arg::leftCenter(215.0, 170.0), action.ShowVolume(0) * 370.0, 40.0 }.draw(Palette::Orange);
				sub_font(U"1回目 --- 倍  2回目 --- 倍  3回目 --- 倍").drawAt(400.0, 120.0);
			}

			else if (current_scene == 1)
			{
				RectF{ Arg::leftCenter(215.0, 170.0), action.ShowVolume(1) * 370.0, 40.0 }.draw(Palette::Orangered);
				sub_font(U"1回目 {:.2f} 倍  2回目 --- 倍  3回目 --- 倍"_fmt(action.ShowVolume(0))).drawAt(400.0, 120.0);
			}

			else if (current_scene == 2)
			{
				RectF{ Arg::leftCenter(215.0, 170.0), action.ShowVolume(2) * 370.0, 40.0 }.draw(Palette::Mediumvioletred);
				sub_font(U"1回目 {:.2f} 倍  2回目 {:.2f} 倍  3回目 --- 倍"_fmt(action.ShowVolume(0), action.ShowVolume(1))).drawAt(400.0, 120.0);
			}

			counter_font(U"ストップ").drawAt(400.0, 500.0, Palette::Black);

		}

		// 走行
		else if (current_scene == _RUN_SCENE_)
		{
			counter_font(U"{:.1f}"_fmt(action.ShowMovement()), U"cm").drawAt(400.0, 80.0);
			sub_font(U"1回目 {:.2f} 倍  2回目 {:.2f} 倍  3回目 {:.2f} 倍"_fmt(action.ShowVolume(0), action.ShowVolume(1), action.ShowVolume(2))).drawAt(400.0, 120.0);
			counter_font(U"スキップ").drawAt(400.0, 500.0, Palette::Black);

			if (wind_interval <= 0.0)
			{
				wind_interval = Random(0.5, 1.5);
				x = carts.Width() / 2.0;
				y = carts.Height() / 3.0;
				particle.AddParticle(new Wind(3.0, Vec2(Random(400.0 - x, 400.0 + x), Random(380.0 - y, 380.0 + y))));
			}

			if (tree_interval <= 0.0)
			{
				tree_interval = Random(1.0, 2.0);
				particle.AddParticle(new TreeView(10.0, Vec2(810.0, 300.0 + Random(-50.0, 50.0))));
			}

			double deltatime = DeltaTime::getInstance().ShowDeltaTime();

			wind_interval -= deltatime;
			tree_interval -= deltatime;
		}

		// 結果
		else if (current_scene == _RESULT_SCENE_)
		{
			counter_font(U"{:.1f}"_fmt(action.ShowMovement()), U"cm").drawAt(400.0, 100.0);

			counter_font(U"ネジを巻く").drawAt(400.0, 500.0, Palette::Black);
		}

		// 総移動距離
		sub_font(U"走行距離").draw(Arg::rightCenter(770.0, 70.0));
		sub_font(U"{:.1f}"_fmt(action.ShowTotalMovement()), U"cm").draw(Arg::rightCenter(770.0, 90.0));

		// カーソル距離
		sub_font(U"カーソル総距離").draw(Arg::rightCenter(770.0, 290.0));
		sub_font(U"{:.1f}"_fmt(action.ShowMouseCursorCount() / 1000.0), U"kドット").draw(Arg::rightCenter(770.0, 310.0));

		// ホイール数
		// sub_font(U"ホイール回転").draw(Arg::rightCenter(770.0, 340.0));
		// sub_font(U"{}"_fmt(action.ShowMouseWheelCount()), U"行").draw(Arg::rightCenter(770.0, 360.0));

		// ボタン押し
		sub_font(U"累計ボタン押し").draw(Arg::rightCenter(770.0, 340.0));
		sub_font(U"{}"_fmt(action.ShowPushCount()), U"回").draw(Arg::rightCenter(770.0, 360.0));

		// スティック距離LR
		sub_font(U"スティック総距離").draw(Arg::rightCenter(770.0, 390.0));
		sub_font(U"{:.1f}"_fmt(action.ShowThumbCount().x), U"").draw(Arg::rightCenter(770.0, 410.0));
		sub_font(U"{:.1f}"_fmt(action.ShowThumbCount().y), U"").draw(Arg::rightCenter(770.0, 430.0));

		// トリガー距離
		sub_font(U"トリガー総距離").draw(Arg::rightCenter(770.0, 460.0));
		sub_font(U"{:.1f}"_fmt(action.ShowTriggerCount().x), U"").draw(Arg::rightCenter(770.0, 480.0));
		sub_font(U"{:.1f}"_fmt(action.ShowTriggerCount().y), U"").draw(Arg::rightCenter(770.0, 500.0));

		return 0;
	}

};
