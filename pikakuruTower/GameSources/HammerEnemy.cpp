/*!
@file HammerEnemy.cpp
@brief �G
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// �n���}�[�]���r
	//--------------------------------------------------------------------------------------
	HammerEnemy::HammerEnemy(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position,
		const shared_ptr<StageCellMap>& CellMap
	) :
		Enemy(stagePtr, scale, rotation, position, CellMap)
	{
	}

	void HammerEnemy::OnCreate() {
		Enemy::OnCreate();

		// �n���}�[�]���r�̃��b�V���ɂ���@���͉���Man
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"Hummer_Walk.bbmf");
		m_Sex = EnemySex::Man;

		auto ptrShadow = AddComponent<Shadowmap>();

		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"Hummer_Walk.bbmf");

		//������X�s�[�h
		m_EscapeSpeed = 0.4f;
		//HP
		m_MaxHp = 200;
		m_Hp = m_MaxHp;
		//���O
		m_Name = EnemyName::HammerEnemy;
		//pawa-
		m_AttackPower = 10;

		// �n���}�[�͂킩��₷���傫������
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(Vec3(0.6f, 0.6f, 0.6f));
	}

	Vec3 HammerEnemy::LightIgnore() {
		shared_ptr<GameObject> targetObject;
		auto ptrTrans = GetComponent<Transform>();
		auto Enemypos = ptrTrans->GetPosition();
		if (Enemypos.x > 0) {
			targetObject = GetStage()->GetSharedGameObject<WallTaget>(L"WallRight");
		}
		else {
			targetObject = GetStage()->GetSharedGameObject<WallTaget>(L"WallLeft");
		}
		auto spotPos = targetObject->GetComponent<Transform>()->GetPosition();

		auto pos = GetComponent<Transform>()->GetPosition();

		auto velo = spotPos - pos;
		velo.normalize();
		Vec3 vec = Vec3(velo.x * 0.01f, 0.0f, velo.z * 0.01f);
		return vec;
	}

	void HammerEnemy::WalkMove() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos += LightIgnore() * 3;
		ptrTrans->SetPosition(pos);
	}

	void HammerEnemy::AwayMove() {
		WalkMove();
	}

	void HammerEnemy::BarricadeBrekeAction() {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		if (ptrDraw->IsTargetAnimeEnd()) {
			if (ptrDraw->GetCurrentAnimation() == L"AttackBefore") {
				// �U�����̍Đ�
				App::GetApp()->GetXAudio2Manager()->Start(L"Zombie_Attack.wav", 0, 0.5f);

				// �G�t�F�N�g�̍Đ�
				auto ptrTrans = GetComponent<Transform>();
				auto pos = ptrTrans->GetPosition();
				pos.y += 1.5f;
				pos.z -= 1.0f;
				m_EfkPlay[1] = ObjectFactory::Create<EfkPlay>(m_EfkEffect[1], pos);

				ptrDraw->ChangeCurrentAnimation(L"AttackAfter");
			}
			if (ptrDraw->GetCurrentAnimation() == L"AttackAfter") {
				GetStateMachine()->Reset(EnemyMoveState::Instance());
				m_BarriHit = false;
			}
		}
	}
	void HammerEnemy::AttackBehavior() {
		if (m_BarriHit) {
			BarricadeBrekeAction();
		}
		else {
			auto ptrDraw = GetComponent<PNTBoneModelDraw>();
			// Attack�̃��[�V�������I�������
			if (ptrDraw->IsTargetAnimeEnd()) {
				// �I������A�j���[�V������AttackBefore�Ȃ�
				if (ptrDraw->GetCurrentAnimation() == L"AttackBefore") {
					{
						//�G�t�F�N�g�A�o�C�u���[�V�����Ȃ�
						AttackAnimation();
						// �U�����I������̂Ł@AttackAfter�A�j���[�V�������Đ�����
						ptrDraw->ChangeCurrentAnimation(L"AttackAfter");
					}
				}
				else {
					// AttackBefore����Ȃ������̂�AttackBefore���Đ�����
					ptrDraw->ChangeCurrentAnimation(L"AttackBefore");
				}
			}

			//���C�g����̃_���[�W
			DamageReceive();
			//HP��0�ȉ����`�F�b�N
			DeathCheck();
			//������Ǒ���
			RotWallFixed();
		}
	}

	void HammerEnemy::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		//�o���P�[�h�ɐG�ꂽ�Ƃ�
		if (Other->FindTag(L"Barricade")) {
			auto bari = dynamic_pointer_cast<Barricade>(Other);
			if (bari->GetIsAlive()) {
				bari->SetdIsAlive(false);
				m_BarriHit = true;
				GetStateMachine()->Reset(EnemyAttackState::Instance());
			}
		}

		// ���C�g�ɐG�ꂽ��
		if (Other->FindTag(L"Light")) {
			// ���C�g�t���O��true�ɂ���
			m_Light = true;

		}

		//�G���ǂɐG�ꂽ��
		if (m_Hp >= 0) {
			if (Other->FindTag(L"Wall")) {
				m_WallHit = true;
				GetStateMachine()->Reset(EnemyAttackState::Instance());
			}
		}

	}

}