# include <Siv3D.hpp>
# include "game_input.hpp"


void Main()
{
	// ESCキーでアプリケーション終了を行わない
	System::SetTerminationTriggers(UserAction::CloseButtonClicked);

	// 全画面表示を行わない
	Window::SetToggleFullscreenEnabled(false);

	// IMEを無効化
	Platform::Windows::TextInput::DisableIME();

	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	GameInput& input = GameInput::getInstance();

	while (System::Update())
	{
		ClearPrint();
		Print(input.ButtonDetect());

	}
}
