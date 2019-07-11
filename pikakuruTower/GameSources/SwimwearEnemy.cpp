/*!
@file SwimwearEnemy.cpp
@brief �G
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// �����]���r
	//--------------------------------------------------------------------------------------
	SwimwearEnemy::SwimwearEnemy(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position,
		const shared_ptr<StageCellMap>& CellMap
	) :
		Enemy(stagePtr, scale, rotation, position, CellMap)
	{
	}

	SwimwearEnemy::SwimwearEnemy(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position,
		const shared_ptr<StageCellMap>& CellMap,
		const int& captainNumber
	) :
		Enemy(stagePtr, scale, rotation, position, CellMap, captainNumber)
	{
	}
	void SwimwearEnemy::OnCreate() {
		Enemy::OnCreate();
		//�e�N�X�`��
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"Swimwear_Zombie.bbmf");

		//������X�s�[�h
		m_EscapeSpeed = 2.0f;
		//HP
		m_MaxHp = 120;
		m_Hp = m_MaxHp;
		//���O
		m_Name = EnemyName::SwimwearEnemy;

	}

	void SwimwearEnemy::PondInSpeed() {
		if (m_Pond) {
			auto elapsedTime = App::GetApp()->GetElapsedTime();
			auto ptrTrans = GetComponent<Transform>();
			auto pos = ptrTrans->GetPosition();
			pos.z += -2.0f*elapsedTime;
			ptrTrans->SetPosition(pos);
		}
	}
}