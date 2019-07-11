/*!
@file CaptainEnemy.cpp
@brief �G
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// �����]���r
	//--------------------------------------------------------------------------------------
	CaptainEnemy::CaptainEnemy(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position,
		const shared_ptr<StageCellMap>& CellMap
	) :
		Enemy(stagePtr, scale, rotation, position, CellMap)
	{
	}

	CaptainEnemy::CaptainEnemy(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position,
		const shared_ptr<StageCellMap>& CellMap,
		const int& captainNumber
	) :
		Enemy(stagePtr, scale, rotation, position, CellMap, captainNumber)

	{}

	void CaptainEnemy::OnCreate() {
		Enemy::OnCreate();
		AddTag(L"CaptainEnemy");

		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"Polis_Zombie.bbmf");

		//������X�s�[�h
		m_EscapeSpeed = 1.5f;
		//HP
		m_MaxHp = 300;
		m_Hp = m_MaxHp;
		//���O
		m_Name = EnemyName::CaptainEnemy;

		// �L���v�e���͂킩��₷���傫������
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(Vec3(0.7f, 0.7f, 0.7f));
	}

	void CaptainEnemy::SearchRange() {
		auto lightActive = GetStage()->GetSharedGameObject<Spotlight>(L"Spotlight")->GetActive();
		if (lightActive == true) {
			auto ptrTrans = GetComponent<Transform>();
			auto pos = ptrTrans->GetPosition();
			auto lightPtr = GetStage()->GetSharedGameObject<Spotlight>(L"Spotlight");
			auto lightPos = lightPtr->GetComponent<Transform>()->GetPosition();
			auto totalPos = pos - lightPos;
			if (totalPos.length() <= 2.0f) {
				AwayMove();
			}
		}
	}

	//���C���̓���
	void CaptainEnemy::WalkMove() {
		m_Force.setAll(0.0f);
		shared_ptr<GameObject> targetObject;
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();

		if (pos.x > 0) {
			targetObject = GetStage()->GetSharedGameObject<WallTaget>(L"WallRight");
		}
		else {
			targetObject = GetStage()->GetSharedGameObject<WallTaget>(L"WallLeft");
		}
		auto wallPos = targetObject->GetComponent<Transform>()->GetPosition();
		wallPos.y = GetStartPosition().y;
		if (SeekBehavior(wallPos) == CellSearchFlg::Failed) {
			if (SeekBehavior(GetStartPosition()) == CellSearchFlg::Arrived) {
				ArriveBehavior(GetStartPosition());
			}
		}
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_Velocity += m_Force;
		auto Pos = GetComponent<Transform>()->GetPosition();
		Pos += m_Velocity * ElapsedTime *0.125;
		GetComponent<Transform>()->SetPosition(Pos);

		//���G�͈͂������Ă���̂ő��߂ɂ悯��
		SearchRange();
	}
}