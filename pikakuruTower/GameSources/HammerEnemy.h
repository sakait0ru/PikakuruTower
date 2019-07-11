/*!
@file HammerEnemy.h
@brief 敵
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// ハンマーゾンビ
	//--------------------------------------------------------------------------------------
	class HammerEnemy :public Enemy {
	private:
		//壁に到達したか
		bool m_BarriHit = false;
	public:
		HammerEnemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const shared_ptr<StageCellMap>& CellMap
		);
		~HammerEnemy() {}
		virtual void OnCreate() override;

		//光に当たってもよけない動き
		Vec3 LightIgnore();
		//メインの動き
		void WalkMove()override;
		//ライトから逃げる処理
		void AwayMove()override;
		//バリケードを壊すアクション
		void BarricadeBrekeAction();
		//壁に対する攻撃
		virtual void AttackBehavior()override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

	};

}