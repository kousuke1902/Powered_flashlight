#pragma once
#include <Siv3D.hpp>
#include "game_input.hpp"
#include "draw_system.hpp"

// 様々な操作に対する処理クラス
class ActionSystem final
{
private:

	ActionSystem() = default; // コンストラクタ
	~ActionSystem() = default; // デストラクタ

	int power; // 貯めこんだ電力
	int push_count; // ボタン押し回数
	Vec2 trigger_buffer; // トリガー押し込みの累積差分
	Vec2 trigger_count; // 総トリガーの押し込み
	Vec2 thumb_buffer; // スティック累計移動差分
	Vec2 thumb_count; // スティック累計移動量

	GameInput& input = GameInput::getInstance();
	DrawSystem& draw = DrawSystem::getInstance();

	// ボタン押しアクション
	int PushAction()
	{
		const int count = input.ButtonDetect(); // ボタン押し計測

		push_count += count; // ボタン押し計測
		power += count; // 電力充電

		// 描画処理
		draw.DrawEnergySphre(count);

		return 0;
	}

	// トリガー押し込みアクション
	int TriggerAction()
	{
		const Vec4 trigger = input.TriggerDetect(); // トリガー押し込み計測

		trigger_buffer += trigger.zw(); // トリガー押し込み差分足しこみ
		trigger_count += trigger.zw(); // トリガー押し込み差分足しこみ

		if (trigger_buffer.x >= 1.0) // 規定量を越えた際に電力へ変える
		{
			power++;
			trigger_buffer.x--;
		}

		if (trigger_buffer.y >= 1.0) // 規定量を越えた際に電力へ変える
		{
			power++;
			trigger_buffer.y--;
		}

		// 描画処理



		return 0;
	}

	// スティック動作アクション
	int ThumbAction()
	{
		const Vec4 thumb_pos = input.ThumbPos(); // スティック位置
		const Vec2 delta_thumb = input.ThumbDeltaMovement(); // スティック移動差分
		const Vec2 thumb_button = input.ButtonThumbDetect();

		thumb_buffer += delta_thumb; // スティックの移動量を足しこみ
		thumb_count += delta_thumb; // スティックの移動量を足しこみ

		if (thumb_buffer.x >= 1.0) // 規定量を越えた際に電力へ変える
		{
			power++;
			thumb_buffer.x--;
		}

		if (thumb_buffer.y >= 1.0) // 規定量を越えた際に電力へ変える
		{
			power++;
			thumb_buffer.y--;
		}

		if (thumb_button.x == 1.0) // スティックボタン押しこみの検知
		{
			power++;

		}

		if (thumb_button.y == 1.0) // スティックボタン押しこみの検知
		{
			power++;

		}


		// 描画処理  



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

	// トリガー総押し込み量
	const Vec2 ShowTriggerCount()
	{

		return trigger_count;
	}

	// トリガーの累積差分量
	const Vec2 ShowTriggerBuffer()
	{

		return trigger_buffer;
	}

	// スティックの累計移動量
	const Vec2 ShowThumbCount()
	{

		return thumb_count;
	}

	// スティックの累計移動差分
	const Vec2 ShowThumbBuffer()
	{

		return thumb_buffer;
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
		PushAction();
		TriggerAction();
		ThumbAction();

		return 0;
	}

};
