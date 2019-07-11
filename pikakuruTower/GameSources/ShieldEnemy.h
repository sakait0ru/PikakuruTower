/*!
@file ShieldEnemy.h
@brief “G
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// ‚‚¿ƒ]ƒ“ƒr
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
		//ƒ‰ƒCƒg‚©‚ç“¦‚°‚éˆ—
		void AwayMove()override;
	};

}