/*!
@file ShieldEnemy.h
@brief 敵
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// 盾持ちゾンビ
	//--------------------------------------------------------------------------------------
	class ShieldEnemy :public Enemy {
	public:
		ShieldEnemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const shared_ptr<StageCellMap>& CellMap
		);
		ShieldEnemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const shared_ptr<StageCellMap>& CellMap,
			const int& captainNumber
		);

		~ShieldEnemy() {}
		virtual void OnCreate() override;
		//ライトから逃げる処理
		void AwayMove()override;
	};

}