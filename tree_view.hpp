#pragma once
#include "base_particle.hpp"

class TreeView : public BaseParticle
{
private:

	Texture icon;

public:

	// コンストラクタ
	TreeView(double set_life_span, Vec2 set_graph ):BaseParticle(set_life_span, set_graph, Vec2(-1.0, 0.0), 300.0)
	{
		icon = Texture{ 0xF1C73_icon, 100 };

	}

	//デストラクタ
	~TreeView(){}

	// 描画
	int Draw() override
	{

		icon.drawAt(graph);
		return 0;
	}

};
