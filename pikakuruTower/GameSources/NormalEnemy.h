/*!
@file NormalEnemy.h
@brief ìG
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// ïÅí ÇÃÉ]ÉìÉr
	//--------------------------------------------------------------------------------------
	class NormalEnemy :public Enemy {
	public:
		NormalEnemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const shared_ptr<StageCellMap>& CellMap
		);
		NormalEnemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const shared_ptr<StageCellMap>& CellMap,
			const int& captainNumber
		);

		~NormalEnemy() {}

		void OnCreate();
	};

}