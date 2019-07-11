/*!
@file ShieldEnemy.cpp
@brief �G
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// �������]���r
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
		// ���]���r�̃��b�V���ɂ���
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"Shield_Walk.bbmf");
		m_Sex = EnemySex::Man;

		auto ptrShadow = AddComponent<Shadowmap>();

		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"Shield_Walk.bbmf");

		//������X�s�[�h
		m_EscapeSpeed = 0.4f;
		//HP
		m_MaxHp = 280;
		m_Hp = m_MaxHp;
		//���O
		m_Name = EnemyName::ShieldEnemy;
	}

	void ShieldEnemy::AwayMove() {
		//�悯�Ȃ�
		WalkMove();
	}
}