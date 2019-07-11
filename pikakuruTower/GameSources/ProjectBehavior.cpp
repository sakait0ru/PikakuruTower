/*!
@file ProjectBehavior.cpp
@brief �v���W�F�N�g��`�̍s���N���X����
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {
	//�X�^�[�g�X�e�[�g
	IMPLEMENT_SINGLETON_INSTANCE(EnemyStartState)
		void EnemyStartState::Enter(const shared_ptr<Enemy>&Obj) {
		Obj->GetComponent<Collision>()->SetUpdateActive(false);
		auto pos = Obj->GetComponent<Transform>()->GetPosition();
		pos.y = -2.0f;
		Obj->GetComponent<Transform>()->SetPosition(pos);	

		// ���������G�t�F�N�g
		pos.y = 0;
		Obj->m_EfkPlay[4] = ObjectFactory::Create<EfkPlay>(Obj->m_EfkEffect[4], pos);

		Obj->AddTag(L"Start");
	}
	void EnemyStartState::Execute(const shared_ptr<Enemy>&Obj) {
		Obj->StartBehavior();

	}
	void EnemyStartState::Exit(const shared_ptr<Enemy>&Obj) {
		Obj->GetComponent<Collision>()->SetUpdateActive(true);
		Obj->RemoveTag(L"Start");
	}

	//�G�l�~�[���ړ����Ă��鎞�̃X�e�[�g
	IMPLEMENT_SINGLETON_INSTANCE(EnemyMoveState)
		void EnemyMoveState::Enter(const shared_ptr<Enemy>&Obj) {
		Obj->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Walk");

	}
	void EnemyMoveState::Execute(const shared_ptr<Enemy>&Obj) {
		Obj->MoveBehavior();
		Obj->PondInSpeed();
	}
	void EnemyMoveState::Exit(const shared_ptr<Enemy>&Obj) {
	}

	//�G�l�~�[���l�ԏ�Ԃ̎��̃X�e�[�g
	IMPLEMENT_SINGLETON_INSTANCE(EnemyHumanState)
		void EnemyHumanState::Enter(const shared_ptr<Enemy>&Obj) {
		GameManager::getInstance()->RemoveEnemyCount();
		Obj->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Walk");
		Obj->ChangBarricade();
		Obj->HumanAction();
		Obj->AddTag(L"Human");

		//// �΂̃L���L���G�t�F�N�g
		auto ptrTrans = Obj->GetComponent<Transform>();
		Obj->m_EfkPlay[3] = ObjectFactory::Create<EfkPlay>(Obj->m_EfkEffect[3], ptrTrans->GetPosition());

		Obj->GetComponent<Collision>()->AddExcludeCollisionTag(L"Wall");
		Obj->GetComponent<Collision>()->AddExcludeCollisionTag(L"Enemy");
		Obj->GetComponent<Collision>()->AddExcludeCollisionTag(L"Barricade");

		auto voiceKey = rand() % 10;
		switch (voiceKey)
		{
		case 0:
			App::GetApp()->GetXAudio2Manager()->Start(L"Thankyou.wav", 0, 0.5f);
			break;
		default:
			break;
		}

	}
	void EnemyHumanState::Execute(const shared_ptr<Enemy>&Obj) {
		auto ptrTrans = Obj->GetComponent<Transform>();
		auto after = ptrTrans->GetPosition();
		Obj->GetComponent<Collision>()->AddExcludeCollisionTag(L"Wall");
		Obj->HumanBehavior();
		Obj->ChangInstant();
		auto befor = ptrTrans->GetPosition();
		auto dis = befor - after;
		auto action = Obj->GetComponent<Action>();
		if (action->GetArrived()) {
			Obj->m_EfkPlay[3]->AddLocation(Vec3(dis.x, 0, dis.z));
			Obj->HumanLineOver();
		}

	}
	void EnemyHumanState::Exit(const shared_ptr<Enemy>&Obj) {
		Obj->RemoveTag(L"Human");
	}

	//���C�g�̃_���[�W���󂯂Ă��鎞
	IMPLEMENT_SINGLETON_INSTANCE(EnemyDamageState)
		void EnemyDamageState::Enter(const shared_ptr<Enemy>&Obj) {
		Obj->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Walk");
		Obj->AddTag(L"Damege");
		//���߁[�����󂯂Ă��鎞�̐�
		auto voiceKey = rand() % 10;
		switch (voiceKey)
		{
		case 0:
			App::GetApp()->GetXAudio2Manager()->Start(L"dmageVoice.wav", 0, 0.5f);
			break;
		default:
			break;
		}
	}
	void EnemyDamageState::Execute(const shared_ptr<Enemy>&Obj) {
		Obj->DamageBehavior();
	}
	void EnemyDamageState::Exit(const shared_ptr<Enemy>&Obj) {
		Obj->RemoveTag(L"Damege");
	}

	//�C���Ԃ̃X�e�[�g
	IMPLEMENT_SINGLETON_INSTANCE(EnemyStunState)
		void EnemyStunState::Enter(const shared_ptr<Enemy>&Obj) {
		Obj->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Stay");

		auto ptrTrans = Obj->GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		// �G�t�F�N�g�̈ʒu���グ�Ē�������
		pos.y += 0.5f;
		Obj->m_EfkPlay[5] = ObjectFactory::Create<EfkPlay>(Obj->m_EfkEffect[5], pos);

		auto voiceKey = rand() % 10;
		switch (voiceKey)
		{
		case 0:
			//�ڂ��̐�
			App::GetApp()->GetXAudio2Manager()->Start(L"flashVoice.wav", 0, 0.3f);
			break;
		default:
			break;
		}

	}
	void EnemyStunState::Execute(const shared_ptr<Enemy>&Obj) {
		Obj->StunBehavior();
	}
	void EnemyStunState::Exit(const shared_ptr<Enemy>&Obj) {
		Obj->m_EfkPlay[5]->StopEffect();
	}

	//�U���̃X�e�[�g
	IMPLEMENT_SINGLETON_INSTANCE(EnemyAttackState)
		void EnemyAttackState::Enter(const shared_ptr<Enemy>&Obj) {
		Obj->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"AttackBefore");

		auto voiceKey = rand() % 10;
		switch (voiceKey)
		{
		case 0:
			//�ڂ��̐�
			App::GetApp()->GetXAudio2Manager()->Start(L"AttackVoice.wav", 0, 0.3f);
			break;
		default:
			break;
		}
		Obj->RotWallFixed();
	}
	void EnemyAttackState::Execute(const shared_ptr<Enemy>&Obj) {
		Obj->AttackBehavior();		
	}
	void EnemyAttackState::Exit(const shared_ptr<Enemy>&Obj) {
	}

}

//end basecross

