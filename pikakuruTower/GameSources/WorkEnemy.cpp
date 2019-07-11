/*!
@file WorkEnemy.cpp
@brief 敵
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// 工作ゾンビ
	//--------------------------------------------------------------------------------------
	WorkEnemy::WorkEnemy(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position,
		const shared_ptr<StageCellMap>& CellMap
	) :
		Enemy(stagePtr, scale, rotation, position, CellMap)
	{
	}
	WorkEnemy::WorkEnemy(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position,
		const shared_ptr<StageCellMap>& CellMap,
		const int& captainNumber
	) :
		Enemy(stagePtr, scale, rotation, position, CellMap, captainNumber)
	{
	}

	void WorkEnemy::OnCreate() {
		Enemy::OnCreate();

		// 工作ゾンビのメッシュにする
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"Zombie_Work_Walk-Attack.bbmf");
		m_Sex = EnemySex::Man;

		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Zombie_Work_Walk-Attack.bbmf");

		//避けるスピード
		m_EscapeSpeed = 0.8f;
		//HP
		m_MaxHp = 120;
		m_Hp = m_MaxHp;
		//名前
		m_Name = EnemyName::WorkEnemy;

	}

	void WorkEnemy::InformationGetCell() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		auto wallPos = GetStage()->GetSharedGameObject<Wall>(L"Wall")->GetComponent<Transform>()->GetPosition();
		auto dis = pos.z - wallPos.z;
		if (dis > 5.0f) {
			{
				auto Bari = GetStage()->AddGameObject<Barricade>(Vec3(1.0f, 1.0f, 1.0f), Vec3(0, 0, 0), Vec3(pos.x, 0.8f, pos.z));
				float  PieceSize = 1.0f;
				m_CelMap.lock()->RefleshCellMap(Vec3(-20.0f, 0.0f, -10.0f), PieceSize, 40, 25);
				dynamic_pointer_cast<MainStage>(GetStage())->SetCellMapCost();
				CellIndex retcellindex;
				if (m_CelMap.lock()->FindCell(Vec3(pos.x, 0, pos.z), retcellindex)) {
					auto& vec = m_CelMap.lock()->GetCellVec();
					vec[retcellindex.x][retcellindex.z].m_Cost = -1;

					AABB aabb;
					m_CelMap.lock()->FindAABB(retcellindex, aabb);
					auto newpos = aabb.GetCenter();
					newpos.y = 0.8f;
					Bari->GetComponent<Transform>()->SetPosition(newpos);

				}
				else {
					throw BaseException(
						L"エラー",
						L"エラー",
						L"エラー"
					);
				}
			}
		}
	}

	void WorkEnemy::ChangBarricade() {

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		auto wallPos = GetStage()->GetSharedGameObject<Wall>(L"Wall")->GetComponent<Transform>()->GetPosition();
		auto dis = pos.z - wallPos.z;
		//池の中には作らない
		if (m_Pond == false) {
			//壁からある範囲に入るとバリケードを作らない
			if (dis > 5.0f) {
				InformationGetCell();
			}
		}
	}

}