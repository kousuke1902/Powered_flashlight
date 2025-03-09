#pragma once
#include <Siv3D.hpp>
#include "action_system.hpp"
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

	Texture wind_up; // ねじ巻き

	Chart chart; // チャートグラフ管理
	DriveCar carts; // 車描写
	WindUp wind; // 

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

		wind_up = Texture{ 0xF1C23_icon, 50 };

		return 0;
	}

	// 随時更新
	int Update()
	{


		carts.Draw(400.0, 400.0, false);
		
		// wind_up.scaled(1.0, 1.0).draw(Arg::bottomCenter(400.0 - carts.Width() / 1.5, 400.0 - carts.Height() / 3.0));

		wind.Draw(420.0 - carts.Width() / 1.5, 400.0 - carts.Height() / 3.0, 0);

		return 0;
	}

};
