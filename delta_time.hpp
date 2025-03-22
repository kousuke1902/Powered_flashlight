#pragma once
#include <Siv3D.hpp>

class DeltaTime
{

private:

	DeltaTime() = default; // コンストラクタ
	~DeltaTime() = default; // デストラクタ

	double delta_time;

public:

	DeltaTime(const DeltaTime&) = delete; // コピーコンストラクタを削除
	DeltaTime& operator = (const DeltaTime&) = delete; // コピー代入演算子の削除
	DeltaTime(DeltaTime&&) = delete; // ムーブコンストラクタの削除
	DeltaTime& operator = (DeltaTime&&) = delete; // ムーブ代入演算子の削除

	// インスタンス情報の入手
	static DeltaTime& getInstance()
	{
		static DeltaTime inst; // プライベートなコンストラクタ
		return inst;
	}

	// シーン間の経過時間の確認
	int CatchDeltaTime()
	{
		delta_time = Scene::DeltaTime();

		return 0;
	}

	// シーン間経過時間の閲覧
	double ShowDeltaTime()
	{

		return delta_time;
	}

};
