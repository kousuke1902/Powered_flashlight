#pragma once
#include <Siv3D.hpp>
#include "game_input.hpp"
#include "particle_system.hpp"
#include "delta_time.hpp"

#define _MOUSE_POINT_SIZE_  1000.0
#define _WINDUP_SCENE_ 0 // ねじ巻き
#define _MINIGAME_SCENE_ 1 // ミニゲーム
#define _RUN_SCENE_ 2 // 走行
#define _RESULT_SCENE_ 3 // 結果発表

// 様々な操作に対する処理クラス
class ActionSystem final
{
private:

	ActionSystem() = default; // コンストラクタ
	~ActionSystem() = default; // デストラクタ

	int power; // 貯めこんだ力
	bool power_flag; // 力の発生の検知
	int push_count; // ボタン押し回数
	Vec2 trigger_buffer; // トリガー押し込みの累積差分
	Vec2 trigger_count; // 総トリガーの押し込み
	Vec2 thumb_buffer; // スティック累計移動差分
	Vec2 thumb_count; // スティック累計移動量
	int wheel_count; // マウスホイールの累計移動量
	double mouse_count; // マウス移動量
	double mouse_buffer; // マウス移動量差分

	int scene; // ゲームの描画状態

	int minigame_step; // ミニゲーム段階
	double bar1_volume; // ミニゲームの数値
	double bar2_volume; // ミニゲームの数値
	double bar3_volume; // ミニゲームの数値

	double movement; // 移動距離
	double max_movement; // 最大移動距離

	double wind_up_volume; // ねじ巻き遷移度(位置，透過度)

	



	GameInput& input = GameInput::getInstance();
	DeltaTime& deltatime = DeltaTime::getInstance();


	// ボタン押しアクション
	int PushAction()
	{
		const int count = input.ButtonDetect(); // ボタン押し計測

		push_count += count; // ボタン押し計測
		power += count; // 電力充電

		if (0 < count)power_flag = true;

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
			power_flag = true;
			trigger_buffer.x--;
		}

		if (trigger_buffer.y >= 1.0) // 規定量を越えた際に電力へ変える
		{
			power++;
			power_flag = true;
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
			power_flag = true;
			thumb_buffer.x--;

		}

		if (thumb_buffer.y >= 1.0) // 規定量を越えたか
		{
			// 電力へ変える
			power++;
			power_flag = true;
			thumb_buffer.y--;

		}

		if (thumb_button.x == 1.0) // スティックボタン押しこみの検知
		{
			// 電力へ変える
			power++;
			power_flag = true;

		}

		if (thumb_button.y == 1.0) // スティックボタン押しこみの検知
		{
			// 電力へ変える
			power++;
			power_flag = true;

		}

		return 0;
	}

	// マウスホイール操作アクション
	int WheelAction()
	{
		int count = int(input.MouseWheelAbsDetect());

		power += count; // 電力加算
		wheel_count += count;// 累計移動量に足しこみ

		// 力の発生
		if (0 < count)power_flag = true;

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
			power_flag = true;
		}

		return 0;
	}

	// ねじ巻きモードのON/OFF時の処理
	int WindUpVolumeAction()
	{
		// ねじ巻きON -> 透過OFF,ねじ巻き差し込み 
		if (scene == 1)
		{
			if (wind_up_volume < 1.0)wind_up_volume += deltatime.ShowDeltaTime();
			else if (1.0 < wind_up_volume)wind_up_volume = 1.0;
		}

		// ねじ巻きOFF -> 透過ON，ねじ巻き抜きだし
		else if (scene != 1)
		{
			if (wind_up_volume > 0.0)wind_up_volume -= deltatime.ShowDeltaTime();
			else if (0.0 > wind_up_volume) wind_up_volume = 0.0;

		}

		return 0;
	}

	// ミニゲームのゲーム処理
	int MiniGameAction()
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

	// ボタン押し検知
	bool ShowPowerFlag() const
	{
		return power_flag;
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

	// ミニゲームのサイズ確認
	double ShowVolume() const
	{

		if (minigame_step == 1)return bar1_volume;
		else if (minigame_step == 2)return bar2_volume;
		else if (minigame_step == 3)return bar3_volume;

		return 0;

	}


	// 移動距離の参照
	double ShouMovement() const
	{

		return movement;
	}

	// ねじ巻き遷移度(位置，透過度用)参照
	double ShowWindUpVolume() const
	{
		return wind_up_volume;
	}


	// ミニゲームの状態
	int nextMiniGameStep()
	{
		if (minigame_step != 3)	minigame_step++;
		else if (minigame_step == 3)
		{
			minigame_step = 0;
			
		}
		return 0;
	}

	// 初期設定
	int Startup()
	{
		// 初期化作業
		power = 0; // 貯めこんだ電力
		push_count = 0; // ボタン押し回数
		power_flag = false; // ボタン押し検知
		trigger_buffer = Vec2{ 0.0, 0.0 }; // トリガー押し込みの累積差分
		trigger_count = Vec2{ 0.0, 0.0 }; // 総トリガーの押し込み
		thumb_buffer = Vec2{ 0.0, 0.0 }; // スティック累計移動差分
		thumb_count = Vec2{ 0.0, 0.0 }; // スティック累計移動量
		wheel_count = 0; // マウスホイールの累計移動量
		mouse_count = 0.0; // マウス移動量
		mouse_buffer = 0.0; // マウス移動量差分
		wind_up_volume = 1.0; // ねじ巻き遷移度(位置，透過度)


		return 0;
	}

	// 随時更新
	int Update()
	{
		power_flag = false;
		WindUpVolumeAction();

		if (scene == _WINDUP_SCENE_)
		{
			
			PushAction();
			TriggerAction();
			ThumbAction();
			WheelAction();
			MouseAction();
			
		}

		else if (scene == _MINIGAME_SCENE_)
		{


		}
		return 0;
	}

};
