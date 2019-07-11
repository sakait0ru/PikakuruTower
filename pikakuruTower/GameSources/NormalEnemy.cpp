/*!
@file NormalEnemy.cpp
@brief ìG
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// ïÅí ÇÃÉ]ÉìÉr
	//--------------------------------------------------------------------------------------
	NormalEnemy::NormalEnemy(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position,
		const shared_ptr<StageCellMap>& CellMap
	) :
		Enemy(stagePtr, scale, rotation, position, CellMap)
	{
	}

	NormalEnemy::NormalEnemy(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position,
		const shared_ptr<StageCellMap>& CellMap,
		const int& captainNumber
	) :
		Enemy(stagePtr, scale, rotation, position, CellMap, captainNumber)
	{
	}

	void NormalEnemy::OnCreate() {
		Enemy::OnCreate();

	}

}