#pragma once
#include <Siv3D.hpp>
#include "delta_time.hpp"

class Button
{

private:

	double scale; // ボタンスケール
	RectF button; // 描画ボタン
	Color color; // ボタン色

public:

	// コンストラクタ
	Button()
	{
		scale = 1.0;
		button = RectF{ 50.0 };
		color = Palette::White;
	}

	// コンストラクタ
	Button(RectF button_shape, Color set_color)
	{
		scale = 1.0;
		button = button_shape;
		color = set_color;
	}

	// デストラクタ
	~Button(){}

	// ボタン押し
	int Click()
	{
		scale = 1.5;

		return 0;
	}

	// 描画
	int Draw()
	{
		
		button.scaled(scale).draw(color);

		if (scale > 1.0) scale -= DeltaTime::getInstance().ShowDeltaTime() * 2.0;
		else if (scale < 1.0) scale = 1.0;

		return 0;
	}

	// マウスカーソルが重なっているか
	bool mouseOver()
	{
		return button.mouseOver();
	}

};
