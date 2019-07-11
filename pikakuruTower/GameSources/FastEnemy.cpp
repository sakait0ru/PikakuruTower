/*!
@file FastEnemy.cpp
@brief �G
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// �����]���r
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
		//�e�N�X�`��
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"Runner_Zombie.bbmf");

		//������X�s�[�h
		m_EscapeSpeed = 2.0f;
		//�����X�s�[�h
		m_MoveSpeed = 4.0f;
		//HP
		m_MaxHp = 120;
		m_Hp = m_MaxHp;
		//���O
		m_Name = EnemyName::FastEnemy;

		ptrDraw->AddAnimation(L"Walk", 0, 60, true, 250.0f);
	}
}