#pragma once
#include "base_particle.hpp"

class TreeView : public BaseParticle
{
private:

	Texture icon;

public:

	// コンストラクタ
	TreeView(double set_life_span, Vec2 set_graph, double set_speed, int size):BaseParticle(set_life_span, set_graph, Vec2(-1.0, 0.0), set_speed)
	{
		icon = Texture{ 0xF1C73_icon, size };

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
