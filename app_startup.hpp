#pragma once
#include "action_system.hpp"
#include "draw_system.hpp"
#include "game_input.hpp"
#include "iosave_system.hpp"


// 初期設定実行用関数
const int StartUp()
{
	
	GameInput::getInstance().Startup();
	ActionSystem::getInstance().Startup(IOsaveSystem::getInstance().DataLoad());
	DrawSystem::getInstance().Startup();
	
	return 0;
}
