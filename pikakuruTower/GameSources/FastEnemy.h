/*!
@file FastEnemy.h
@brief “G
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// ‘¬‚¢ƒ]ƒ“ƒr
	//--------------------------------------------------------------------------------------
	class FastEnemy :public Enemy {
	public:
		FastEnemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const shared_ptr<StageCellMap>& CellMap
		);
		FastEnemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const shared_ptr<StageCellMap>& CellMap,
			const int& captainNumber
		);

		~FastEnemy() {}
		virtual void OnCreate() override;
	};

}