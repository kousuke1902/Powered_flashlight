# pragma once
# include <Siv3D.hpp>
# include "game_input.hpp"

// 様々な操作に対する処理クラス
class ActionSystem final
{
private:

	ActionSystem() = default; // コンストラクタ
	~ActionSystem() = default; // デストラクタ

	int power; // 貯めこんだ電力
	int push_count; // ボタン押し回数
	Vec2 trigger_buffer; // トリガー押し込みの累積差分


	GameInput& input = GameInput::getInstance();

	// ボタン押しアクション
	int PushAction()
	{
		const int count = input.ButtonDetect(); // ボタン押し計測

		// 描画処理

		push_count += count; // ボタン押し計測
		power += count; // 電力充電

		return 0;
	}

	// トリガー押し込みアクション
	int TriggerAction()
	{
		Vec4 trigger = input.TriggerDetect();

		return 0;
	}

public:

	ActionSystem(const ActionSystem&) = delete; // コピーコンストラクタを削除
	ActionSystem& operator = (const ActionSystem&) = delete; // コピー代入演算子の削除
	ActionSystem(ActionSystem&&) = delete; // ムーブコンストラクタの削除
	ActionSystem& operator = (ActionSystem&&) = delete; // ムーブ代入演算子の削除

	// インスタンス情報の入手
	static ActionSystem& getInstance()
	{
		static ActionSystem inst; // プライベートなコンストラクタ
		return inst;
	}

	// 電力の閲覧
	const int ShowPower()
	{
		return power;
	}

	// ボタン押し数の閲覧
	const int ShowPushCount()
	{
		return push_count;
	}

	// 初期設定
	int Startup()
	{
		// 初期化作業
		power = 0;


		return 0;
	}

	// 随時更新
	int Update()
	{
		

		return 0;
	}

};
