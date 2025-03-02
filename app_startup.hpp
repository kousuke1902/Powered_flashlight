#pragma once
#include "action_system.hpp"
#include "draw_system.hpp"
#include "game_input.hpp"


// 初期設定実行用関数
const int StartUp()
{
	GameInput::getInstance().Startup();
	ActionSystem::getInstance().Startup();
	DrawSystem::getInstance().Startup();


	return 0;
}
