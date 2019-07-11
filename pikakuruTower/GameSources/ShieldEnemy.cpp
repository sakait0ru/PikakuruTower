/*!
@file ShieldEnemy.cpp
@brief 敵
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// 盾持ちゾンビ
	//--------------------------------------------------------------------------------------
	ShieldEnemy::ShieldEnemy(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position,
		const shared_ptr<StageCellMap>& CellMap
	) :
		Enemy(stagePtr, scale, rotation, position, CellMap)
	{
	}
	ShieldEnemy::ShieldEnemy(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position,
		const shared_ptr<StageCellMap>& CellMap,
		const int& captainNumber
	) :
		Enemy(stagePtr, scale, rotation, position, CellMap, captainNumber)
	{
	}

	void ShieldEnemy::OnCreate() {
		Enemy::OnCreate();
		// 盾ゾンビのメッシュにする
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"Shield_Walk.bbmf");
		m_Sex = EnemySex::Man;

		auto ptrShadow = AddComponent<Shadowmap>();

		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Shield_Walk.bbmf");

		//避けるスピード
		m_EscapeSpeed = 0.4f;
		//HP
		m_MaxHp = 280;
		m_Hp = m_MaxHp;
		//名前
		m_Name = EnemyName::ShieldEnemy;
	}

	void ShieldEnemy::AwayMove() {
		//よけない
		WalkMove();
	}
}