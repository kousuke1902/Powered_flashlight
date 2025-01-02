# include <Siv3D.hpp>
# include "game_input.hpp"
# include "action_system.hpp"


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
	ActionSystem& action = ActionSystem::getInstance();

	input.Startup();
	action.Startup();

	while (System::Update())
	{
		ClearPrint();
		Print(action.ShowPower());
		Print(action.ShowThumbCount());
		Print(action.ShowThumbBuffer());
		action.Update();
	}
}
