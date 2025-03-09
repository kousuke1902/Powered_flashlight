#pragma once
#include <Siv3D.hpp>
#include "base_particle.hpp"
#include "scatter.hpp"
#include "water_ripple.hpp"
#include "water_ripple.hpp"
#include "bubble.hpp"
#include "wind.hpp"

// パーティクル処理関連の操作クラス
class ParticleSystem final
{
private:

	ParticleSystem() = default; // コンストラクタ
	~ParticleSystem() = default; // デストラクタ
	Array<BaseParticle*> particles; // パーティクル管理

public:

	ParticleSystem(const ParticleSystem&) = delete; // コピーコンストラクタを削除
	ParticleSystem& operator = (const ParticleSystem&) = delete; // コピー代入演算子の削除
	ParticleSystem(ParticleSystem&&) = delete; // ムーブコンストラクタの削除
	ParticleSystem& operator = (ParticleSystem&&) = delete; // ムーブ代入演算子の削除

	// インスタンス情報の入手
	static ParticleSystem& getInstance()
	{
		static ParticleSystem inst; // プライベートなコンストラクタ
		return inst;
	}

	// パーティクル追加
	int AddParticle(BaseParticle* add_particle)
	{
		particles << add_particle;
		return 0;
	}

	// パーティクル動作更新
	int Update()
	{
		// パーティクルの走査
		for (auto it = particles.begin(); it != particles.end();)
		{
			BaseParticle*  particle = *it;

			// 寿命の確認
			if (particle->CheckLife())
			{
				// 削除処理
				delete particle;
				it = particles.erase(it);
			}

			else
			{
				// 寿命処理
				particle->ReduceLifeSpan();
				// パーティクル移動
				particle->Move();
				// パーティクル描画
				particle->Draw();

				++it;
			}

		}

		return 0;

	}

};
