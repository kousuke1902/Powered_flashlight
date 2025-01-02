# pragma once
# include <Siv3D.hpp>

// ゲーム内での入力に関する処理クラス
class GameInput final
{

private:

	GameInput() = default; // コンストラクタ
	~GameInput() = default; // デストラクタ

	Vec2 before_mouse_pos; // 前フレーム時のマウス座標
	Vec2 before_trigger; // 前回トリガー状態 (L=X, R=Y)
	Vec4 thumb_pos; // スティック座標 (LX=X, LY=Y, RX=Z, RY=W)
	Vec4 before_thumb_pos; // 前回のスティック座標 (L=X, R=Y)

public:

	GameInput(const GameInput&) = delete; // コピーコンストラクタを削除
	GameInput& operator = (const GameInput&) = delete; // コピー代入演算子の削除
	GameInput(GameInput&&) = delete; // ムーブコンストラクタの削除
	GameInput& operator = (GameInput&&) = delete; // ムーブ代入演算子の削除

	// インスタンス情報の入手
	static GameInput& getInstance()
	{
		static GameInput inst; // プライベートなコンストラクタ
		return inst;
	}



	// 各種ボタン押し検知
	int ButtonDetect()
	{
		// ボタン押し回数の集計
		int count = 0;
		// XInputコントローラーの情報
		auto controller = XInput(0);
		
		// XInputボタン押しの集計
		count = controller.buttonA.down() +controller.buttonB.down() + controller.buttonX.down() + controller.buttonY.down() // ABXY
			+ controller.buttonBack.down() + controller.buttonStart.down() // START BACK
			+ controller.buttonUp.down() + controller.buttonDown.down()	+ controller.buttonLeft.down() + controller.buttonRight.down() // 十字キー
			//+ controller.buttonLThumb.down() + controller.buttonRThumb.down() // スティック押し込み
			+ controller.buttonLB.down() + controller.buttonRB.down(); // LR

		// 全てのキーボードの入力情報
		const Array<Input> allkeys = Keyboard::GetAllInputs();

		// キーボードのボタン押しを集計
		for (const auto& key : allkeys)
		{
			if (key.down())count++;
		}

		// 全てのマウスボタンの入力情報
		const Array<Input> allbuttons = Mouse::GetAllInputs();

		// マウスボタン押しを集計
		for (const auto& button : allbuttons)
		{
			if (button.down())count++;
		}

		return count;
	}

	// スティック押し込み検知 (L=X, R=Y)
	Vec2 ButtonThumbDetect()
	{

		return Vec2(XInput(0).buttonLThumb.down(), XInput(0).buttonRThumb.down());
	}

	// トリガー押し込み検知 (L=X, R=Y, δL=Z, δR=W)
	Vec4 TriggerDetect()
	{
		Vec2 trigger = Vec2(XInput(0).leftTrigger, XInput(0).rightTrigger);
		Vec2 delta_trigger = trigger - before_trigger;

		before_trigger = trigger;

		return Vec4(trigger, Abs(delta_trigger.x), Abs(delta_trigger.y));
	}

	// スティックの座標 (LX=X, LY=Y, RX=Z, RY=W)
	Vec4 ThumbPos()
	{
		thumb_pos = Vec4(XInput(0).leftThumbX, XInput(0).leftThumbY, XInput(0).rightThumbX, XInput(0).rightThumbY);

		return thumb_pos;
	}

	// スティックの相対距離 (MomentL=X, MomentR=Y)
	Vec2 ThumbDeltaMovement()
	{
		Vec4 delta_thumble_pos = thumb_pos - before_thumb_pos;

		before_thumb_pos = thumb_pos;

		Vec2 moment_L(delta_thumble_pos.x, delta_thumble_pos.y);
		Vec2 moment_R(delta_thumble_pos.z, delta_thumble_pos.w);

		return Vec2(moment_L.length(), moment_R.length());
	}


	// マウスホイール相対移動量検知
	int MouseWheelAbsDetect()
	{

		return Abs(Mouse::Wheel()) + Abs(Mouse::WheelH());
	}

	// マウスカーソル相対移動量検知
	int MouseDeltaMovement()
	{
		Vec2 mouse_pos = Cursor::Pos();
		Vec2 delta_pos = mouse_pos - before_mouse_pos;

		before_mouse_pos = mouse_pos;

		return delta_pos.length();

	}


	// 初期設定
	int Startup()
	{
		before_mouse_pos = Cursor::Pos();
		before_trigger = Vec2(0, 0);
		before_thumb_pos = Vec4(0, 0, 0, 0);

		auto controller = XInput(0);

		controller.setLeftThumbDeadZone();
		controller.setRightThumbDeadZone();

		return 0;
	}

};
