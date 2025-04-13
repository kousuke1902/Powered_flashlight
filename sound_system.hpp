#pragma once
#include <Siv3D.hpp>
#include "base_sound.hpp"
#include "wind_up_sound.hpp"
#include "click_sound.hpp"
#include "mini1_sound.hpp"
#include "mini2_sound.hpp"
#include "mini3_sound.hpp"
#include "result_sound.hpp"

// 効果音の操作に対する処理クラス
class SoundSystem
{
private:

	SoundSystem() = default; // コンストラクタ
	~SoundSystem() = default; // デストラクタ

	Array<BaseSound*>  sounds; // 効果音管理

	Audio click_sound; // クリック音
	Audio minigame1_sound; // ミニゲーム音1
	Audio minigame2_sound; // ミニゲーム音2
	Audio minigame3_sound; // ミニゲーム音3
	Audio drive_sound; // 走行音
	Audio result_sound; // 結果発表音

public:

	SoundSystem(const SoundSystem&) = delete; // コピーコンストラクタを削除
	SoundSystem& operator = (const SoundSystem&) = delete; // コピー代入演算子の削除
	SoundSystem(SoundSystem&&) = delete; // ムーブコンストラクタの削除
	SoundSystem& operator = (SoundSystem&&) = delete; // ムーブ代入演算子の削除

	// インスタンス情報の入手
	static SoundSystem& getInstance()
	{
		static SoundSystem inst; // プライベートなコンストラクタ
		return inst;
	}

	// 効果音追加
	int AddSound(BaseSound* add_sound)
	{
		// 効果音を重複して使用するか確認
		if (add_sound->ShowOverlapping() == false)
		{
			// 重複して使用しない場合，登録を確認する
			for (const auto& sound : sounds)
			{
				if (add_sound->ShowID() == sound->ShowID())
				{
					return 1;
				}

			}
		}
		sounds << add_sound;
		sounds.back()->PlaySound();

		return 0;
	}

	// 効果音動作更新
	int Update()
	{
		// パーティクルの走査
		for (auto it = sounds.begin(); it != sounds.end();)
		{
			BaseSound* sound = *it;

			// 効果音の確認
			if (sound->CheckDeleteFlag())
			{
				// 削除処理
				delete sound;
				it = sounds.erase(it);
			}

			else
			{
				++it;
			}

		}

		return 0;

	}


};
