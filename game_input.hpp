#pragma once
#include <Siv3D.hpp>

// ゲーム内での入力に関する処理クラス
class GameInput final
{

private:

	GameInput() = default; // コンストラクタ
	~GameInput() = default; // デストラクタ


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
		count = controller.buttonA.down() +controller.buttonB.down() + controller.buttonX.down() + controller.buttonY.down()
			+ controller.buttonBack.down() + controller.buttonView.down() + controller.buttonStart.down() + controller.buttonMenu.down()
			+ controller.buttonUp.down() + controller.buttonDown.down()	+ controller.buttonLeft.down() + controller.buttonRight.down()
			+ controller.buttonLThumb.down() + controller.buttonRThumb.down()
			+ controller.buttonLB.down() + controller.buttonRB.down();

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


};
