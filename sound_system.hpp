#pragma once
#include <Siv3D.hpp>

// 効果音の操作に対する処理クラス
class SoundSystem
{
private:

	SoundSystem() = default; // コンストラクタ
	~SoundSystem() = default; // デストラクタ

	Audio wind_up_sound; // ねじまき音
	Audio click_sound; // クリック音
	Audio minigame_sound; // ミニゲーム音
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



};
