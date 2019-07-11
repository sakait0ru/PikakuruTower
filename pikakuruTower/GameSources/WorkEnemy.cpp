/*!
@file WorkEnemy.cpp
@brief �G
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// �H��]���r
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

		// �H��]���r�̃��b�V���ɂ���
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"Zombie_Work_Walk-Attack.bbmf");
		m_Sex = EnemySex::Man;

		auto ptrShadow = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"Zombie_Work_Walk-Attack.bbmf");

		//������X�s�[�h
		m_EscapeSpeed = 0.8f;
		//HP
		m_MaxHp = 120;
		m_Hp = m_MaxHp;
		//���O
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
						L"�G���[",
						L"�G���[",
						L"�G���["
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
		//�r�̒��ɂ͍��Ȃ�
		if (m_Pond == false) {
			//�ǂ��炠��͈͂ɓ���ƃo���P�[�h�����Ȃ�
			if (dis > 5.0f) {
				InformationGetCell();
			}
		}
	}

}