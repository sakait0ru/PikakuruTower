/*!
@file ProjectBehavior.cpp
@brief プロジェクト定義の行動クラス実体
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {
	//スタートステート
	IMPLEMENT_SINGLETON_INSTANCE(EnemyStartState)
		void EnemyStartState::Enter(const shared_ptr<Enemy>&Obj) {
		Obj->GetComponent<Collision>()->SetUpdateActive(false);
		auto pos = Obj->GetComponent<Transform>()->GetPosition();
		pos.y = -2.0f;
		Obj->GetComponent<Transform>()->SetPosition(pos);	

		// モヤモヤエフェクト
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

	//エネミーが移動している時のステート
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

	//エネミーが人間状態の時のステート
	IMPLEMENT_SINGLETON_INSTANCE(EnemyHumanState)
		void EnemyHumanState::Enter(const shared_ptr<Enemy>&Obj) {
		GameManager::getInstance()->RemoveEnemyCount();
		Obj->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Walk");
		Obj->ChangBarricade();
		Obj->HumanAction();
		Obj->AddTag(L"Human");

		//// 緑のキラキラエフェクト
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

	//ライトのダメージを受けている時
	IMPLEMENT_SINGLETON_INSTANCE(EnemyDamageState)
		void EnemyDamageState::Enter(const shared_ptr<Enemy>&Obj) {
		Obj->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Walk");
		Obj->AddTag(L"Damege");
		//だめーじを受けている時の声
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

	//気絶状態のステート
	IMPLEMENT_SINGLETON_INSTANCE(EnemyStunState)
		void EnemyStunState::Enter(const shared_ptr<Enemy>&Obj) {
		Obj->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Stay");

		auto ptrTrans = Obj->GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		// エフェクトの位置を上げて長くする
		pos.y += 0.5f;
		Obj->m_EfkPlay[5] = ObjectFactory::Create<EfkPlay>(Obj->m_EfkEffect[5], pos);

		auto voiceKey = rand() % 10;
		switch (voiceKey)
		{
		case 0:
			//目がの声
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

	//攻撃のステート
	IMPLEMENT_SINGLETON_INSTANCE(EnemyAttackState)
		void EnemyAttackState::Enter(const shared_ptr<Enemy>&Obj) {
		Obj->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"AttackBefore");

		auto voiceKey = rand() % 10;
		switch (voiceKey)
		{
		case 0:
			//目がの声
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

