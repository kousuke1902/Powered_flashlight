#pragma once
#include <Siv3D.hpp>
#include "game_input.hpp"
#include "particle_system.hpp"

#define _MOUSE_POINT_SIZE_  1000.0

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
	int wheel_count; // マウスホイールの累計移動量
	double mouse_count; // マウス移動量
	double mouse_buffer; // マウス移動量差分
	int phase; // モニターのフェーズ

	GameInput& input = GameInput::getInstance();
	ParticleSystem& particle = ParticleSystem::getInstance();



	// ボタン押しアクション
	int PushAction()
	{
		const int count = input.ButtonDetect(); // ボタン押し計測

		push_count += count; // ボタン押し計測
		power += count; // 電力充電

		// 描画処理
		//draw.DrawEnergySphre(Vec2{ 400.0, 300.0 }, count);
		if (count > 0)particle.AddParticle(new Bubble(3.0, Vec2{ 400.0, 300.0 }, 100.0, 120.0));

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

		return 0;
	}

	// スティック動作アクション
	int ThumbAction()
	{
		const Vec4 thumb_pos = input.ThumbPos(); // スティック位置
		const Vec2 delta_thumb = input.ThumbDeltaMovement(); // スティック移動差分
		const Vec2 thumb_button = input.ButtonThumbDetect(); // スティック押し込み

		thumb_buffer += delta_thumb; // スティックの移動量を足しこみ
		thumb_count += delta_thumb; // スティックの移動量を足しこみ

		if (thumb_buffer.x >= 1.0) // 規定量を越えたか
		{
			// 電力へ変える
			power++;
			thumb_buffer.x--;

			// 描画
			particle.AddParticle(new Scatter(1.0, Vec2(400.0, 300.0), Vec2(thumb_pos.x, -thumb_pos.y)));
		}

		if (thumb_buffer.y >= 1.0) // 規定量を越えたか
		{
			// 電力へ変える
			power++;
			thumb_buffer.y--;

			// 描画
			particle.AddParticle(new Scatter(1.0, Vec2(400.0, 300.0), Vec2(thumb_pos.z, -thumb_pos.w)));
		}

		if (thumb_button.x == 1.0) // スティックボタン押しこみの検知
		{
			// 電力へ変える
			power++;

			// 描画
			particle.AddParticle(new WaterRipple(3.0, Vec2(500.0, 200.0), 100.0, Palette::Red));
		}

		if (thumb_button.y == 1.0) // スティックボタン押しこみの検知
		{
			// 電力へ変える
			power++;

			// 描画
			particle.AddParticle(new WaterRipple(3.0, Vec2(500.0, 400.0), 100.0, Palette::Red));
		}

		return 0;
	}

	// マウスホイール操作アクション
	int WheelAction()
	{
		int count = int(input.MouseWheelAbsDetect());

		power += count; // 電力加算
		wheel_count += count;// 累計移動量に足しこみ

		return 0;
	}

	// マウス移動アクション
	int MouseAction()
	{
		double count = input.MouseDeltaMovement();
		mouse_count += count; // マウス移動量加算
		mouse_buffer += count; // マウス移動量差分加算

		// 差分計算
		if (mouse_buffer >= _MOUSE_POINT_SIZE_)
		{
			double ratio = mouse_buffer / _MOUSE_POINT_SIZE_;
			mouse_buffer -= ratio * _MOUSE_POINT_SIZE_;
			power += int(ratio);
		}

		return 0;
	}

	// モニター処理
	int MonitorAction()
	{
		

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
	int ShowPower() const
	{
		return power;
	}

	// ボタン押し数の閲覧
	int ShowPushCount() const
	{
		return push_count;
	}

	// トリガー総押し込み量
	Vec2 ShowTriggerCount() const
	{

		return trigger_count;
	}

	// トリガーの累積差分量
	Vec2 ShowTriggerBuffer() const
	{

		return trigger_buffer;
	}

	// スティックの累計移動量
	Vec2 ShowThumbCount() const
	{

		return thumb_count;
	}

	// スティックの累計移動差分
	Vec2 ShowThumbBuffer() const 
	{

		return thumb_buffer;
	}

	// マウスホイールの累計移動量
	int ShowMouseWheelCount() const
	{

		return wheel_count;
	}

	// マウスの累計移動量
	double ShowMouseCursorCount() const
	{

		return mouse_count;
	}

	// 初期設定
	int Startup()
	{
		// 初期化作業
		power = 0; // 貯めこんだ電力
		push_count = 0; // ボタン押し回数
		trigger_buffer = Vec2{ 0.0, 0.0 }; // トリガー押し込みの累積差分
		trigger_count = Vec2{ 0.0, 0.0 }; // 総トリガーの押し込み
		thumb_buffer = Vec2{ 0.0, 0.0 }; // スティック累計移動差分
		thumb_count = Vec2{ 0.0, 0.0 }; // スティック累計移動量
		wheel_count = 0; // マウスホイールの累計移動量
		mouse_count = 0.0; // マウス移動量
		mouse_buffer = 0.0; // マウス移動量差分
		phase = 0; // 遷移フェーズ

		return 0;
	}

	// 随時更新
	int Update()
	{
		PushAction();
		TriggerAction();
		ThumbAction();
		WheelAction();
		MouseAction();
		MonitorAction();

		return 0;
	}

};
