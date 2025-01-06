#pragma once
#include "action_system.hpp"
#include "draw_system.hpp"
#include "game_input.hpp"


// 初期設定実行用関数
const int StartUp()
{
	GameInput& input = GameInput::getInstance();
	ActionSystem& action = ActionSystem::getInstance();
	DrawSystem& draw = DrawSystem::getInstance();

	input.Startup();
	action.Startup();
	draw.StartUp();

	return 0;
}
