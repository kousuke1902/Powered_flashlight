﻿#include <Siv3D.hpp>
#include "action_system.hpp"
#include "particle_system.hpp"
#include "delta_time.hpp"
#include "app_startup.hpp"



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


	ActionSystem& action = ActionSystem::getInstance();
	DrawSystem& draw = DrawSystem::getInstance();
	ParticleSystem& particle = ParticleSystem::getInstance();
	DeltaTime& delta_time = DeltaTime::getInstance();

	StartUp();

	while (System::Update())
	{
		delta_time.CatchDeltaTime();
		ClearPrint();
		Print(action.ShowWindUpVolume());
		Print(delta_time.ShowDeltaTime());

		action.Update();
		draw.Update();
		particle.Update();
	}
}
