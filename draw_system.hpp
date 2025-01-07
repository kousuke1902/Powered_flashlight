#pragma once

#include "energy_sphre.hpp"
#include "tachometer.hpp"

// 描画処理関連の操作クラス
class DrawSystem final
{

private:

	DrawSystem() = default; // コンストラクタ
	~DrawSystem() = default; // デストラクタ

	EnergySphre sphre{ 300.0,300.0 };
	Tachometer tacho{ 400.0, 400.0 };

public:

	DrawSystem(const DrawSystem&) = delete; // コピーコンストラクタを削除
	DrawSystem& operator = (const DrawSystem&) = delete; // コピー代入演算子の削除
	DrawSystem(DrawSystem&&) = delete; // ムーブコンストラクタの削除
	DrawSystem& operator = (DrawSystem&&) = delete; // ムーブ代入演算子の削除

	// インスタンス情報の入手
	static DrawSystem& getInstance()
	{
		static DrawSystem inst; // プライベートなコンストラクタ
		return inst;
	}

	// エネルギー球の描画処理 x=ボタン押し数
	int DrawEnergySphre(int x)
	{
		sphre.MovementPoints(x);
		sphre.Draw();
		return 0;
	}

	// タコメーターの描画処理 x=針の振れ幅
	int DrawTachometer(double x)
	{
		tacho.Draw(x);
		return 0;
	}

	// 初期化設定
	int StartUp()
	{
		

		return 0;
	}

};
