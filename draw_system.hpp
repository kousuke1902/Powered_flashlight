#pragma once
#include <Siv3D.hpp>
#include "action_system.hpp"
#include "game_input.hpp"
#include "energy_sphre.hpp"
#include "tachometer.hpp"
#include "piston_engine.hpp"
#include "chart.hpp"
#include "monitor.hpp"

// 描画処理関連の操作クラス
class DrawSystem final
{

private:

	DrawSystem() = default; // コンストラクタ
	~DrawSystem() = default; // デストラクタ

	Chart chart;
	Monitor monitor;

	ActionSystem& action = ActionSystem::getInstance();
	GameInput& input = GameInput::getInstance();


	// モニターの描画
	int DrawMonitor(Vec2 graph, int count)
	{
		RoundRect{ Arg::center(graph), 400.0, 140.0, 5.0 }.draw(Palette::Olivedrab);


		monitor.DrawCounter(graph, count);

		RoundRect{ Arg::center(graph), 400.0, 140.0, 5.0 }.drawFrame(5.0, Palette::Black);

		return 0;
	}

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
	int StartUp()
	{
		

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
		DrawMonitor(Vec2{ 400.0, 100.0 }, action.ShowPower());
		return 0;
	}

};
