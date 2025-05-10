#pragma once
#include <Siv3D.hpp>
#include "base_sound.hpp"
#include "click_sound.hpp"
#include "countdown_sound.hpp"
#include "insert_sound.hpp"
#include "mini1_sound.hpp"
#include "mini2_sound.hpp"
#include "mini3_sound.hpp"
#include "pull_sound.hpp"
#include "reset_sound.hpp"
#include "result_sound.hpp"
#include "run_sound.hpp"
#include "wind_up_sound.hpp"

// 効果音の操作に対する処理クラス
class SoundSystem
{
private:

	SoundSystem() = default; // コンストラクタ
	~SoundSystem() = default; // デストラクタ

	Array<BaseSound*>  sounds; // 効果音管理


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

		if (Window::GetState().focused == false) GlobalAudio::FadeVolume(0.0, 0.25s);
		else if (Window::GetState().focused == true)GlobalAudio::FadeVolume(1.0, 0.25s);

		// 効果音の走査
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

	// サウンド終了
	int Finish(String id)
	{
		// 効果音の走査
		for (auto it = sounds.begin(); it != sounds.end();)
		{
			BaseSound* sound = *it;

			// 効果音の確認
			if (sound->ShowID() == id)
			{
				sound->FadeoutSound();
			}

			++it;
			

		}

		return 0;
	}

};
