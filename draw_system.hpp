#pragma once
#include <Siv3D.hpp>
#include "action_system.hpp"
#include "particle_system.hpp"
#include "game_input.hpp"
#include "energy_sphre.hpp"
#include "tachometer.hpp"
#include "piston_engine.hpp"
#include "chart.hpp"
#include "drive_car.hpp"
#include "wind_up.hpp"

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
	WindUp wind; // ねじ巻き 

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
		counter_font = Font{ 50 };
		distance_font = Font{ 30 };
		sub_font = Font{ 20 };


		return 0;
	}

	// 随時更新
	int Update()
	{
		// 表示
		counter_font(action.ShowPower(), U"巻き").drawAt(400.0, 200.0);

		// 車両
		carts.Draw(400.0, 500.0);
		
		// ねじ巻き
		double x = 420.0 - carts.Width() / 1.5;
		double y = 500.0 - carts.Height() / 3.0;
		double dist = action.ShowWindUpVolume();
		wind.Draw(x + dist * 15.0, y, action.ShowPower() * 12_deg, dist);

		// ねじ巻きパーティクル
		if (action.ShowPowerFlag())particle.AddParticle(new WaterRipple(1.0, Vec2(x - 60.0, y), 50.0, Palette::Blueviolet));

		// モード移行
		if (RectF{ Arg::center(400.0, 550.0), 60 }.draw().mouseOver() && MouseL.down()) action.SwitchingWindUpFlag();

		return 0;
	}

};
