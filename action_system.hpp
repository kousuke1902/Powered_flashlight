﻿#pragma once
#include <Siv3D.hpp>
#include "game_input.hpp"
#include "sound_system.hpp"
#include "particle_system.hpp"
#include "delta_time.hpp"

#define _MOUSE_POINT_SIZE_ 1000.0
#define _WHEEL_POINT_SIZE_ 8
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

	unsigned int power; // 貯めこんだ力
	unsigned int buf_power; // 力の一時保存
	bool power_flag; // 力の発生の検知
	unsigned int push_count; // ボタン押し回数
	Vec2 trigger_buffer; // トリガー押し込みの累積差分
	Vec2 trigger_count; // 総トリガーの押し込み
	Vec2 thumb_buffer; // スティック累計移動差分
	Vec2 thumb_count; // スティック累計移動量
	unsigned int wheel_count; // マウスホイールの累計移動量
	unsigned int wheel_buffer; // マウスホイールの一時保存
	double mouse_count; // マウス移動量
	double mouse_buffer; // マウス移動量差分

	int scene; // ゲームの描画状態

	int minigame_step; // ミニゲーム段階
	double bar1_volume; // ミニゲームの数値
	double bar2_volume; // ミニゲームの数値
	double bar3_volume; // ミニゲームの数値

	double movement; // 移動距離
	double max_movement; // 最大移動距離
	double total_movement; // 総移動距離

	double wind_up_volume; // ねじ巻き遷移度(位置，透過度)

	unsigned int reset_count; // データ初期化カウント

	SoundSystem& sound = SoundSystem::getInstance();
	GameInput& input = GameInput::getInstance();
	DeltaTime& deltatime = DeltaTime::getInstance();


	// ボタン押しアクション
	int PushAction()
	{
		const int count = input.ButtonDetect(); // ボタン押し計測

		push_count += count; // ボタン押し計測
		power += count; // 電力充電

		if (0 < count)	power_flag = true;
		
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
			push_count++;
			power_flag = true;

		}

		if (thumb_button.y == 1.0) // スティックボタン押しこみの検知
		{
			// 電力へ変える
			power++;
			push_count++;
			power_flag = true;

		}

		return 0;
	}

	// マウスホイール操作アクション
	int WheelAction()
	{
		int count = int(input.MouseWheelAbsDetect());

		
		wheel_count += count;// 累計移動量に足しこみ
		wheel_buffer += count; // 一時保存に足しこみ

		// 力の発生
		if (wheel_buffer >= _WHEEL_POINT_SIZE_)
		{
			power++; // 電力加算
			power_flag = true;
			wheel_buffer -= _WHEEL_POINT_SIZE_;
		}

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
			mouse_buffer -= _MOUSE_POINT_SIZE_;
			power++;
			power_flag = true;
		}

		return 0;
	}

	// ねじ巻きモードのON/OFF時の処理
	int WindUpVolumeAction()
	{
		// ねじ巻きON -> 透過OFF,ねじ巻き差し込み 
		if (scene == _WINDUP_SCENE_)
		{
			if (wind_up_volume < 1.0)wind_up_volume += deltatime.ShowDeltaTime();
			else if (1.0 < wind_up_volume)wind_up_volume = 1.0;
		}

		// ねじ巻きOFF -> 透過ON，ねじ巻き抜きだし
		else if (scene != _WINDUP_SCENE_)
		{
			if (wind_up_volume > 0.0)wind_up_volume -= deltatime.ShowDeltaTime();
			else if (0.0 > wind_up_volume) wind_up_volume = 0.0;

		}

		return 0;
	}

	// ミニゲームのゲーム処理
	int MiniGameAction()
	{
		// 1回目
		if (minigame_step == 0)
		{
			bar1_volume += deltatime.ShowDeltaTime() / 2.0;
			if (bar1_volume >= 1.0) bar1_volume--;

		}

		// 2回目
		else if (minigame_step == 1)
		{
			bar2_volume += deltatime.ShowDeltaTime();
			if (bar2_volume >= 1.0) bar2_volume--;

		}

		// 3回目
		else if (minigame_step == 2)
		{
			bar3_volume += deltatime.ShowDeltaTime() * 2;
			if (bar3_volume >= 1.0) bar3_volume--;

		}

		return 0;
	}

	// 移動処理
	int MovementAction()
	{
		if (movement < max_movement)
		{
			movement += deltatime.ShowDeltaTime();
		}

		else if (movement >= max_movement)
		{
			movement = max_movement;
			total_movement += max_movement;
			scene = _RESULT_SCENE_;
			sound.Finish(U"Run");
			sound.AddSound(new ResultSound());
		}

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
		if (power_flag) sound.AddSound(new WindUpSound());
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
	double ShowVolume(int x) const
	{

		if (x == 0)return bar1_volume;
		else if (x == 1)return bar2_volume;
		else if (x == 2)return bar3_volume;

		return 0;

	}

	// ミニゲームの段階
	int ShowMiniGameStep() const
	{
		return minigame_step;
	}

	// 移動距離の参照
	double ShowMovement() const
	{
		return movement;
	}

	// 総移動距離の参照
	double ShowTotalMovement() const
	{
		return total_movement;
	}

	// ねじ巻き遷移度(位置，透過度用)参照
	double ShowWindUpVolume() const
	{
		return wind_up_volume;
	}


	// ゲームの遷移処理
	int nextGameStep()
	{
		// ねじ回し
		if (scene == _WINDUP_SCENE_)
		{
			// 遷移
			scene = _MINIGAME_SCENE_;
			buf_power = power;
			power = 0;
			minigame_step = 0;
			bar1_volume = 0.0;
			bar2_volume = 0.0;
			bar3_volume = 0.0;
			sound.AddSound(new PullSound());
		}

		// ミニゲーム
		else if (scene == _MINIGAME_SCENE_)
		{
			// ミニゲームを進める
			if (minigame_step == 0)
			{
				minigame_step++;
				sound.AddSound(new Mini1Sound());
			}

			else if (minigame_step == 1)
			{
				minigame_step++;
				sound.AddSound(new Mini2Sound());
			}

			else if (minigame_step == 2)
			{
				scene = _RUN_SCENE_;
				max_movement = buf_power * bar1_volume * bar2_volume * bar3_volume;
				sound.AddSound(new Mini3Sound());
			}
		}

		// 走行
		else if (scene == _RUN_SCENE_)
		{
			movement = max_movement;
			total_movement += max_movement;
			scene = _RESULT_SCENE_;
			sound.Finish(U"Run");
			sound.AddSound(new ResultSound());
			
		}

		// 結果
		else if (scene == _RESULT_SCENE_)
		{
			scene = _WINDUP_SCENE_;
			sound.AddSound(new InsertSound());
		}


		return 0;
	}

	// 現在の遷移状態
	int ShowScene() const
	{

		return scene;
	}

	// データ初期化アクション
	int DataResetAction()
	{
		
		if (reset_count != 0)
		{
			reset_count--;
			sound.AddSound(new CountdownSound());
		}

		// カウント0で初期化
		else if (reset_count == 0)
		{
			reset_count = 3;
			power = 0;
			buf_power = 0;
			push_count = 0;
			trigger_count = Vec2{ 0.0, 0.0 };
			trigger_buffer = Vec2{ 0.0, 0.0 };
			thumb_count = Vec2{ 0.0, 0.0 };
			thumb_buffer = Vec2{ 0.0, 0.0 };
			wheel_count = 0;
			wheel_buffer = 0;
			mouse_count = 0.0;
			mouse_buffer = 0.0;
			total_movement = 0.0;
			sound.AddSound(new ResetSound());

		}

		return 0;
	}

	// 初期化カウント閲覧
	int ShowResetCount() const
	{
		return reset_count;
	}

	// 初期設定
	int Startup(JSON json)
	{
		// 初期化作業
		power = json[U"power"].get<int>(); // 貯めこんだ電力
		buf_power = 0; // 力の一時保存
		push_count = json[U"push"].get<int>(); // ボタン押し回数
		power_flag = false; // ボタン押し検知
		trigger_buffer = Vec2{ 0.0, 0.0 }; // トリガー押し込みの累積差分
		trigger_count = json[U"trigger"].get<Vec2>(); // 総トリガーの押し込み
		thumb_buffer = Vec2{ 0.0, 0.0 }; // スティック累計移動差分
		thumb_count = json[U"thumb"].get<Vec2>(); // スティック累計移動量
		wheel_count = json[U"wheel"].get<int>(); // マウスホイールの累計移動量
		wheel_buffer = 0; // マウスホイールの一時保存
		mouse_count = json[U"mouse"].get<double>(); // マウス移動量
		mouse_buffer = 0.0; // マウス移動量差分
		total_movement = json[U"movement"].get<double>(); // 総移動距離
		wind_up_volume = 1.0; // ねじ巻き遷移度(位置，透過度)
		reset_count = 3; // データ初期化のカウント

		return 0;
	}

	// 随時更新
	int Update()
	{
		power_flag = false;
		WindUpVolumeAction();

		// ねじ巻き
		if (scene == _WINDUP_SCENE_)
		{
			
			PushAction();
			TriggerAction();
			ThumbAction();
		//	WheelAction();
			MouseAction();
			
		}

		// ミニゲーム
		else if (scene == _MINIGAME_SCENE_)
		{
			MiniGameAction();

		}

		// 走行
		else if (scene == _RUN_SCENE_)
		{
			MovementAction();
			sound.AddSound(new RunSound);
		}

		return 0;
	}

};
