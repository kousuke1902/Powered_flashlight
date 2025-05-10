#pragma once
#include "action_system.hpp"
#include "draw_system.hpp"
#include "game_input.hpp"
#include "iosave_system.hpp"


// 初期設定実行用関数
const int StartUp()
{

	LicenseManager::AddLicense({ .title = U"Programer", .copyright = U"(C)kousuke1902", .text = U"He made this computer game" });
	LicenseManager::AddLicense({ .title = U"Sound Efeect", .copyright = U"(C)2025 SHIKUMI DESIGN Inc.", .text = U"Springin' Sound Stock" });
	LicenseManager::AddLicense({ .copyright = U"(C)2013 効果音ラボ" , .text = U"" });

	GameInput::getInstance().Startup();
	ActionSystem::getInstance().Startup(IOsaveSystem::getInstance().DataLoad());
	DrawSystem::getInstance().Startup();

	return 0;
}
