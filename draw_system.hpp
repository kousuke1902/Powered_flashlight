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

	EnergySphre sphre;
	Tachometer tacho;
	PistonEngine engine;
	Chart chart;
	Monitor monitor;

	ActionSystem& action = ActionSystem::getInstance();
	GameInput& input = GameInput::getInstance();

	// エネルギー球の描画処理 x=ボタン押し数
	int DrawEnergySphre(Vec2 origin, int x)
	{
		sphre.MovementPoints(x);
		sphre.Draw(origin);
		return 0;
	}

	// タコメーターの描画処理 x=針の振れ幅
	int DrawTachometer(Vec2 origin, double x)
	{
		tacho.Draw(origin, x);
		return 0;
	}

	// ピストンエンジンの描画
	int DrawPistonEngine(Vec2 origin, double x)
	{
		engine.Draw(origin, x);
		return 0;
	}

	// チャートグラフの描画
	int DrawChart(Vec2 origin, int x)
	{
		chart.Draw(origin, x);
		return 0;
	}

	// モニターの描画
	int DrawMonitor(Vec2 graph, int count, bool flag)
	{
		RoundRect{ Arg::center(graph), 400.0, 140.0, 5.0 }.draw(Palette::Olivedrab);

		monitor.PhaseCheck(flag);
		monitor.PhaseTimer();
		monitor.Draw(graph, count);

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
		DrawTachometer(Vec2{ 207.0, 500.0 }, trigger.x);
		DrawTachometer(Vec2{ 583.0, 500.0 }, trigger.y);

		// チャート
		DrawChart(Vec2{ 500.0, 200.0 }, (int)input.MouseWheelAbsDetect());

		// ピストンエンジン
		DrawPistonEngine(Vec2{ 20.0, 450.0 }, action.ShowMouseCursorCount());

		// モニター
		DrawMonitor(Vec2{ 400.0, 100.0 }, action.ShowPower(), false);
		return 0;
	}

};
