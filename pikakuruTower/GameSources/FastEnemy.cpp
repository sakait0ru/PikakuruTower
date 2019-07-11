/*!
@file FastEnemy.cpp
@brief 敵
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// 速いゾンビ
	//--------------------------------------------------------------------------------------
	FastEnemy::FastEnemy(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position,
		const shared_ptr<StageCellMap>& CellMap
	) :
		Enemy(stagePtr, scale, rotation, position, CellMap)
	{
	}

	FastEnemy::FastEnemy(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position,
		const shared_ptr<StageCellMap>& CellMap,
		const int& captainNumber
	) :
		Enemy(stagePtr, scale, rotation, position, CellMap, captainNumber)
	{
	}
	void FastEnemy::OnCreate() {
		Enemy::OnCreate();
		//テクスチャ
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"Runner_Zombie.bbmf");

		//避けるスピード
		m_EscapeSpeed = 2.0f;
		//動くスピード
		m_MoveSpeed = 4.0f;
		//HP
		m_MaxHp = 120;
		m_Hp = m_MaxHp;
		//名前
		m_Name = EnemyName::FastEnemy;

		ptrDraw->AddAnimation(L"Walk", 0, 60, true, 250.0f);
	}
}