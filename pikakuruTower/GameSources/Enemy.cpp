/*!
@file Enemy.cpp
@brief �G
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	// �G�l�~�[
	//--------------------------------------------------------------------------------------
	Enemy::Enemy(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position,
		const shared_ptr<StageCellMap>& CellMap
	) :
		MyGameObject(stagePtr),
		m_Scale(scale),
		m_Rotation(rotation),
		m_Position(position),
		m_CelMap(CellMap),
		m_CaptainNumber(0)
	{
	}

	Enemy::Enemy(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position,
		const shared_ptr<StageCellMap>& CellMap,
		const int& captainNumber
	) :
		MyGameObject(stagePtr),
		m_Scale(scale),
		m_Rotation(rotation),
		m_Position(position),
		m_CelMap(CellMap),
		m_CaptainNumber(captainNumber)
	{
	}

	void Enemy::OnCreate() {
		AddTag(L"Enemy");
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		auto ptrColl = AddComponent<CollisionSphere>();
		//ptrColl->SetExcludeCollisionGroup(L"Barricades");
		//ptrColl->SetDrawActive(true);
		auto MapPtr = m_CelMap.lock();
		if (MapPtr) {
			AddComponent<PathSearch>(MapPtr);
		}

		SetAlphaActive(true);

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(2.5f, 2.5f, 2.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.75f, 0.0f)
		);

		auto ptrDraw = AddComponent<PNTBoneModelDraw>();

		auto MeshKey = rand() % 2;
		switch (MeshKey)
		{
		case 0:
			ptrDraw->SetMeshResource(L"Man_Zombie.bbmf");
			m_Sex = EnemySex::Man;
			break;

		case 1:
			ptrDraw->SetMeshResource(L"Woman_Zombie.bbmf");
			m_Sex = EnemySex::Woman;
			break;
		default:
			throw BaseException(
				L"�G���[",
				L"SetMeshResource",
				L"OnCreate"
			);
			break;
		}
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		// �A�j���[�V�����̒ǉ�
		ptrDraw->AddAnimation(L"Stay", 0, 1, true, 1);
		ptrDraw->AddAnimation(L"Walk", 0, 60, true, 140.0f);
		ptrDraw->AddAnimation(L"Attack", 61, 60, false, 50.0f);
		ptrDraw->AddAnimation(L"AttackBefore", 61, 30, false, 50.0f);
		ptrDraw->AddAnimation(L"AttackAfter", 91, 30, false, 50.0f);
		ptrDraw->ChangeCurrentAnimation(L"Stay");



		auto ptrShadow = AddComponent<Shadowmap>();


		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"Man_Zombie.bbmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		m_Spotlight = GetStage()->GetSharedGameObject<Spotlight>(L"Spotlight");

		//�^�C�v
		m_Type = EnemyType::HpHeel;
		//���O
		m_Name = EnemyName::Enemy;

		// �G�t�F�N�g�̎���
		for (int i = 0; i < 6; i++) {
			m_EfkEffect[i] = GetTypeStage<MainStage>()->GetEfkDate(i);
		}

		//�X�e�[�g�}�V�[���̍\�z
		m_StateMachine.reset(new LayeredStateMachine<Enemy>(GetThis<Enemy>()));
		//�ŏ��̃X�e�[�g��EnemyMoveState�ɐݒ�
		GetStateMachine()->Reset(EnemyStartState::Instance());

		// �f�o�b�O�p�̕������ݒ�
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 100.0f, 640.0f, 480.0f));

	}

	void Enemy::OnUpdate() {
		m_StateMachine->Update();
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elapsedTime);

		//debugstring
		wstringstream ss;
		auto strDraw = GetComponent<StringSprite>();
		//strDraw->SetText(ss.str());

	}

	void Enemy::OnUpdate2() {

	}


	/*-�Z���}�b�v�֘A-----------------------------------------------*/
	bool Enemy::Search(const Vec3&TargetPos) {
		auto MapPtr = m_CelMap.lock();
		if (MapPtr) {
			auto PathPtr = GetComponent<PathSearch>();
			m_CellPath.clear();
			//�p�X������������
			if (PathPtr->SearchCell(TargetPos, m_CellPath)) {
				//��������������
				m_CellIndex = 0;
				m_TargetCellIndex = (int)(m_CellPath.size() - 1);
				if (m_CellIndex == m_TargetCellIndex) {
					//���łɓ����Z���ɂ���
					m_NextCellIndex = m_CellIndex;
				}
				else {
					//����Ă���
					m_NextCellIndex = m_CellIndex + 1;

				}
				return true;
			}
			else {
				//���s����
				m_CellIndex = -1;
				m_NextCellIndex = -1;
				m_TargetCellIndex = -1;
			}
		}
		return false;
	}

	CellSearchFlg Enemy::SeekBehavior(const Vec3& TargetPos) {
		auto MyPos = GetComponent<Transform>()->GetPosition();
		auto MapPtr = m_CelMap.lock();
		if (!MapPtr) {
			return CellSearchFlg::Failed;
		}
		m_CellTime += App::GetApp()->GetElapsedTime();
		if (m_CellTime >= 1.0f) {
			if (Search(TargetPos)) {
				auto PtrSeek = GetBehavior<SeekSteering>();
				auto PtrArrive = GetBehavior<ArriveSteering>();
				if (m_NextCellIndex == 0) {
					m_Force = PtrArrive->Execute(m_Force, m_Velocity, TargetPos);
					//��������
					return CellSearchFlg::Arrived;
				}
				else {
					AABB ret;
					MapPtr->FindAABB(m_CellPath[m_NextCellIndex], ret);
					auto Pos = ret.GetCenter();
					Pos.y = TargetPos.y;
					m_Force = PtrSeek->Execute(m_Force, m_Velocity, Pos);
					return CellSearchFlg::Seek;
				}
			}
			else {
				auto PtrSeek = GetBehavior<SeekSteering>();
				CellIndex WallCell;
				if (MapPtr->FindCell(TargetPos, WallCell)) {
					AABB ret;
					MapPtr->FindAABB(WallCell, ret);
					auto Pos = ret.GetCenter();
					Pos.y = TargetPos.y;
					m_Force = PtrSeek->Execute(m_Force, m_Velocity, Pos);
					return CellSearchFlg::Seek;
				}
			}
			m_CellTime = 0.0f;
			m_FirstCelltime = false;
		}



		return CellSearchFlg::Failed;
	}

	void Enemy::ArriveBehavior(const Vec3&TargetPos) {
		auto PtrArrive = GetBehavior<ArriveSteering>();
		m_Force = PtrArrive->Execute(m_Force, m_Velocity, TargetPos);
	}
	/*--------------------------------------------------------------*/

	void Enemy::WalkMove() {
		m_Force.setAll(0.0f);
		// ������Object
		shared_ptr<GameObject> targetObject;
		// CaptainNumber��0����Ȃ��Ƃ��A�ݒ肵�Ȃ��Ǝ�����0�ɂȂ�
		if (m_CaptainNumber != 0) {
			// ���̃I�u�W�F�N�g���z�u����Ă���X�e�[�W�̂��ׂẴI�u�W�F�N�g���擾����
			auto stageGameObjectVev = GetStage()->GetGameObjectVec();
			for (auto gameObject : stageGameObjectVev) {
				// ���o����gameObject��CaptainEnemy�ɕϊ�
				auto ce = dynamic_pointer_cast<CaptainEnemy>(gameObject);
				// ���s������false���Ԃ��Ă���A
				if (ce) { // ����
					// �ϊ��ɐ��������]���r�������Ă��邩
					if (!ce->GetHumanState()) { // �����Ă�
						// �����Ă���CaptainEnemy��Number���擾
						auto ceNumber = ce->GetCaptainNumber();
						// �����̔ԍ��ƈ�v���Ă��邩�m�F
						if (ceNumber == m_CaptainNumber) {
							// target��object��CaptainEnemy������
							targetObject = gameObject;
							// ���������̂�for���[�v�𔲂��o��
							break;
						}
					}
				}
			}
		}
		// ��̏��������s���āA���ɂ�������Ȃ�������
		if (targetObject == nullptr) {
			auto ptrTrans = GetComponent<Transform>();
			auto pos = ptrTrans->GetPosition();
			if (pos.x > 0) {
				targetObject = GetStage()->GetSharedGameObject<WallTaget>(L"WallRight");
			}
			else {
				targetObject = GetStage()->GetSharedGameObject<WallTaget>(L"WallLeft");
			}
		}

		//auto wallPtr = GetStage()->GetSharedGameObject<Wall>(L"Wall");
		auto wallPos = targetObject->GetComponent<Transform>()->GetPosition();
		wallPos.y = GetStartPosition().y;
		if (SeekBehavior(wallPos) == CellSearchFlg::Failed) {
			if (SeekBehavior(GetStartPosition()) == CellSearchFlg::Arrived) {
				ArriveBehavior(GetStartPosition());
			}
		}
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_Velocity += m_Force;
		auto pos = GetComponent<Transform>()->GetPosition();
		auto newPos = pos + (m_Velocity * ElapsedTime / m_MoveSpeed);
		GetComponent<Transform>()->SetPosition(newPos);
	}

	//�G�l�~�[�̌��x�ړ�
	void Enemy::MovingLimit() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		auto time = App::GetApp()->GetElapsedTime();

		if (pos.x > 12.5)
		{
			pos.x = 12.5f;
		}
		if (pos.x < -13.5)
		{
			pos.x = -13.5f;
		}
		ptrTrans->SetPosition(pos);
	}

	void Enemy::RotToHead() {
		auto ptrColl = GetComponent<CollisionSphere>();
		auto ptrTrans = GetComponent<Transform>();
		Vec3 Velocity = ptrColl->GetVelocity();
		if (Velocity.length() > 0.0f) {
			Vec3 rot = Velocity;
			rot.normalize();
			float ToAngle = atan2(rot.x, rot.z);
			Quat Qt;
			Qt.rotationRollPitchYawFromVector(Vec3(0, ToAngle + XM_PI, 0));
			Qt.normalize();
			//���݂̉�]���擾
			Quat NowQt = ptrTrans->GetQuaternion();
			//���݂ƖڕW���ԁi10����1�j
			NowQt = XMQuaternionSlerp(NowQt, Qt, 0.1f);
			ptrTrans->SetQuaternion(NowQt);
		}
	}

	void Enemy::PondInSpeed() {
		if (m_Pond) {
			auto elapsedTime = App::GetApp()->GetElapsedTime();
			auto ptrTrans = GetComponent<Transform>();
			auto pos = ptrTrans->GetPosition();
			pos.z += 0.8f*elapsedTime;
			ptrTrans->SetPosition(pos);
		}
	}

	void Enemy::LightDamegeCheck() {
		//���C�g�ɂ������Ă��Ă����C�g���I���Ȃ�
		if (m_Light && m_Spotlight->GetActive()) {
			//�_���[�W�X�e�[�g��
			GetStateMachine()->Reset(EnemyDamageState::Instance());
		}
	}

	void Enemy::DamageReceive() {
		if (m_Light&&m_Spotlight->GetActive()) {
			auto lightPower = m_Spotlight->GetLightPower();
			m_Hp -= lightPower * 0.3f;

			m_EfkTime[2] += App::GetApp()->GetElapsedTime();
			if (m_EfkTime[2] >= 0.5f) {
				m_EfkTime[2] = 0.0f;
				// �T�E���h�̍Đ�
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(L"Zombie_Damage.wav", 0, 0.1f);
				// �_���[�W���󂯂Ă��鎞�̃G�t�F�N�g�Đ�
				auto ptrTrans = GetComponent<Transform>();
				m_EfkPlay[2] = ObjectFactory::Create<EfkPlay>(m_EfkEffect[2], ptrTrans->GetPosition());
			}
		}
	}

	void Enemy::AwayMove() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		auto posX = pos.x;
		auto rot = ptrTrans->GetRotation();
		auto lightPtr = GetStage()->GetSharedGameObject<Spotlight>(L"Spotlight");
		auto lightPos = lightPtr->GetComponent<Transform>()->GetPosition();
		auto lightPosX = lightPos.x;
		auto totalPos = posX - lightPosX;
		//�r�ɓ����Ă�����
		if (m_Pond == true) {
			if (totalPos < 0) {
				pos.x += m_EscapeSpeed * -0.005f;
			}
			else if (totalPos > 0) {
				pos.x += m_EscapeSpeed * 0.005f;
			}
		}
		//�r�ɓ����Ă��Ȃ�
		else {
			if (totalPos < 0) {
				pos.x += m_EscapeSpeed * -0.02f;
			}
			else if (totalPos > 0) {
				pos.x += m_EscapeSpeed * 0.02f;
			}
		}
		ptrTrans->SetRotation(rot);
		ptrTrans->SetPosition(pos);
	}

	void Enemy::NotDamegeCheck() {
		if (m_Light == false || !m_Spotlight->GetActive()) {
			GetStateMachine()->Reset(EnemyMoveState::Instance());
		}
	}

	void Enemy::DeathCheck() {
		//Hp��0�ȉ��ɂȂ��Ă�����
		if (m_Hp <= 0) {
			//�l�ԃX�e�[�g��
			GetStateMachine()->Reset(EnemyHumanState::Instance());
		}
	}

	void Enemy::AttackAnimation() {
		// �T�E���h�̍Đ�
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(L"Zombie_Attack.wav", 0, 0.5f);
		// �G�t�F�N�g�̍Đ�
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos.y += 1.5f;
		pos.z -= 1.0f;
		m_EfkPlay[1] = ObjectFactory::Create<EfkPlay>(m_EfkEffect[1], pos);
		// �ǂ�Hp�����炷
		GameManager::getInstance()->DamageWallHp(m_AttackPower);
		// �J������DamegeFlg��True�ɂ���
		GetTypeStage<MainStage>()->GetCamera()->SetShake(true);
		// �_���[�W���󂯂����̐Ԃ��}�X�N�̍쐬
		GetStage()->AddGameObject<DamegeSprite>(L"DamegeSprite.png", Vec2(1280, 800), Vec2(0, 0));
		// �R���g���[���[��h�炷
		Vibration::Instance()->SetVibration(0.2f, 0.5f, 0.5f);
	}

	void Enemy::RotWallFixed() {
		//������Ǒ���
		auto ptrTrans = GetComponent<Transform>();
		auto rot = ptrTrans->GetRotation();
		rot.y = 0;
		ptrTrans->SetRotation(rot);

	}

	void Enemy::IsStunCheck() {
		if (m_Hp >= 0) {
			m_TotalTime = 0.0f;
			GetStateMachine()->Reset(EnemyStunState::Instance());
		}
	}

	void Enemy::StunFinish() {
		m_TotalTime += App::GetApp()->GetElapsedTime();
		//�C��
		if (m_TotalTime >= 7.0f) {
			m_TotalTime = 0.0f;
			//�ǂɃq�b�g���Ă�����
			if (m_WallHit == true) {
				GetStateMachine()->Reset(EnemyAttackState::Instance());
			}
			//�������Ƃ𑱂���
			GetStateMachine()->Reset(EnemyMoveState::Instance());
		}
	}

	void Enemy::ActionRotFixed() {
		auto ptrTrans = GetComponent<Transform>();
		auto rot = ptrTrans->GetRotation();
		rot = Vec3(0.0f, 0.0f, 0.0f);
		ptrTrans->SetRotation(rot);
	}

	//�l�ԂɂȂ����u�Ԃ̓���
	void Enemy::HumanAction() {
		// �l�ԂɂȂ������̃G�t�F�N�g
		auto ptrTrans = GetComponent<Transform>();
		m_EfkPlay[0] = ObjectFactory::Create<EfkPlay>(m_EfkEffect[0], ptrTrans->GetPosition());
		//�T�E���h�̍Đ�
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(L"Zombie_Zouka.wav", 0, 0.5f);


		auto ptrAction = AddComponent<Action>();
		ptrAction->AddMoveBy(1.0f, Vec3(0, 0, 0));
		ptrAction->AddRotateTo(0.5f, Vec3(0, 0, XM_PIDIV2));
		ptrAction->AddRotateBy(0.5f, Vec3(0, 0, -XM_PIDIV2));
		ptrAction->AddMoveBy(0.5f, Vec3(0, 2.0f, 0), Lerp::Linear, Lerp::EaseOut, Lerp::Linear);
		ptrAction->AddRotateBy(0.5f, Vec3(0, XM_PI, 0));
		ptrAction->AddRotateBy(0.5f, Vec3(0, XM_PI, 0));
		ptrAction->AddMoveBy(0.5f, Vec3(0, -2.0f, 0), Lerp::Linear, Lerp::Easein, Lerp::Linear);
		//���[�v����
		ptrAction->SetLooped(false);
		//�A�N�V�����J�n
		ptrAction->Run();
	}

	void Enemy::ChangInstant() {
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		m_ChangTime += elapsedTime;
		if (m_ChangTime >= 1.3f) {
			m_ChangTime = 0.0f;
			//�A�N�V�����̓o�^
			ChangTex();
		}
	}

	void Enemy::ChangTex() {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		if (m_Sex == EnemySex::Man) {
			ptrDraw->SetMeshResource(L"Man_Human.bbmf");
		}
		else if (m_Sex == EnemySex::Woman) {
			ptrDraw->SetMeshResource(L"Woman_Human.bbmf");
		}

		auto ptrShadow = GetComponent<Shadowmap>();
		if (m_Name == EnemyName::ShieldEnemy) {
			ptrShadow->SetMeshResource(L"Man_Human.bbmf");
		}
		if (m_Name == EnemyName::HammerEnemy) {
			ptrShadow->SetMeshResource(L"Man_Human.bbmf");
		}
		if (m_Name == EnemyName::WorkEnemy) {
			ptrShadow->SetMeshResource(L"Man_Human.bbmf");
		}

	}

	//�l�ԂɂȂ������̓���
	void Enemy::HumanWalkMove() {
		//�����蔻����Ȃ���
		auto ptrColl = GetComponent<CollisionSphere>();
		ptrColl->AddExcludeCollisionTag(L"Enemy");
		ptrColl->AddExcludeCollisionTag(L"Barricade");

		m_Force.setAll(0.0f);
		shared_ptr<GameObject> targetObject;
		if (targetObject == nullptr) {
			auto ptrTrans = GetComponent<Transform>();
			auto pos = ptrTrans->GetPosition();
			if (pos.x > 0) {
				targetObject = GetStage()->GetSharedGameObject<WallTaget>(L"WallRight");
			}
			else {
				targetObject = GetStage()->GetSharedGameObject<WallTaget>(L"WallLeft");
			}
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
		Pos += m_Velocity * ElapsedTime;
		GetComponent<Transform>()->SetPosition(Pos);
	}

	void Enemy::HumanLineOver() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		if (m_Hp < 0) {
			if (pos.z < -6.0f) {
				switch (m_Type)
				{
				case basecross::EnemyType::HpHeel:
					GameManager::getInstance()->HeelWallHp(2);
					break;
				case basecross::EnemyType::Net:
					break;
				case basecross::EnemyType::Flash:
					break;
				default:
					break;
				}
				m_EfkPlay[3]->StopEffect();
				//�񕜂̐�
				auto voiceKey = rand() % 10;
				switch (voiceKey)
				{
				case 0:
					App::GetApp()->GetXAudio2Manager()->Start(L"HeelVoice.wav", 0, 0.5f);
					break;
				default:
					break;
				}

				GetStage()->AddGameObject<HpHeelEffect>(Vec3(0.5f, 0.5f, 0.5f), Vec3(0.0f, 0.0f, 0.0f), GetComponent<Transform>()->GetPosition());
				GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
			}
		}
	}
	/*-�X�e�[�g�}�V�[���֘A-------------------------------------*/
	//�ŏ��̓���
	void Enemy::StartBehavior() {
		//�G�l�~�[�̐�������Ă���̓���
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos.y += 0.01f;
		if (pos.y > 0.5f) {
			pos.y = 0.5f;
			GetStateMachine()->Reset(EnemyMoveState::Instance());
		}
		ptrTrans->SetPosition(pos);
	}
	//�]���r�̓���
	void Enemy::MoveBehavior() {
		//���C�g�ɓ������Ă��邩�`�F�b�N
		LightDamegeCheck();
		//���C���̓���
		WalkMove();
		//��]����
		RotToHead();
		//���E�̈ړ����x
		MovingLimit();
		//HP��0�ȉ����`�F�b�N
		DeathCheck();
	}

	//�l�ԂɂȂ�����
	void Enemy::HumanBehavior() {
		//�l�ԂɂȂ������̓���
		HumanWalkMove();
		//��]����
		RotToHead();
	}
	//���C�g�̃_���[�W���󂯂Ă��鎞
	void Enemy::DamageBehavior() {
		//���C�g���瓦���鏈��
		AwayMove();
		//���C�g����̃_���[�W
		DamageReceive();
		//HP��0�ȉ����`�F�b�N
		DeathCheck();
		//���C�g�ɐG��Ă��ė���Ă��邩�`�F�b�N
		NotDamegeCheck();
	}
	//�C��
	void Enemy::StunBehavior() {
		//�C�⎞�Ԃ��߂�����̏���
		StunFinish();
		//���C�g����̃_���[�W
		DamageReceive();
		//HP��0�ȉ����`�F�b�N
		DeathCheck();
	}

	//�ǂɑ΂���U��
	void Enemy::AttackBehavior() {
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
	}

	/*----------------------------------------------------------*/

	void Enemy::OnCollisionExit(shared_ptr<GameObject>& Other) {
		// ���C�g���痣�ꂽ��
		if (Other->FindTag(L"Light")) {
			//���C�g�t���O��false�ɂ���
			m_Light = false;
		}
		// �r���痣�ꂽ��
		if (Other->FindTag(L"SlowFloor")) {
			//�r�t���O��false�ɂ���
			m_Pond = false;
		}
	}
	void Enemy::OnCollisionExcute(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"SlowFloor")) {
			m_Pond = true;
		}
	}
	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& Other) {

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

	//--------------------------------------------------------------------------------------
	//�G�t�F�N�g���o��object
	//--------------------------------------------------------------------------------------

	HpHeelEffect::HpHeelEffect(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position
	) :
		MyGameObject(stagePtr),
		m_Scale(scale),
		m_Rotation(rotation),
		m_Position(position)
	{
	}

	void HpHeelEffect::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		//�l�ԂɂȂ�Ƃ��̃G�t�F�N�g
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\zonbiheal.efk";
		auto ShEfkInterface = GetTypeStage<MainStage>()->GetEfkInterface();
		m_EfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);


		auto pos = GetComponent<Transform>()->GetPosition();
		m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, pos);

	}
	void HpHeelEffect::OnUpdate() {


		auto ptrTrans = GetComponent<Transform>();
		auto after = ptrTrans->GetPosition();
		auto pos = ptrTrans->GetPosition();

		auto hpUIPos = GetTypeStage<MainStage>()->GetHpUIPos();
		auto d = hpUIPos - after;
		// ��������
		auto To = pow((hpUIPos.x - pos.x)*(hpUIPos.x - pos.x) + (hpUIPos.z - pos.z)*(hpUIPos.z - pos.z), 0.5);
		if (To < 0.5) {
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}
		d.normalize();
		pos += d * 0.2f;
		ptrTrans->SetPosition(pos);

		auto befor = ptrTrans->GetPosition();
		auto dis = befor - after;
		m_EfkPlay->AddLocation(Vec3(dis.x, 0, dis.z));
	}


	EffectMove::EffectMove(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position
	) :
		MyGameObject(stagePtr),
		m_Scale(scale),
		m_Rotation(rotation),
		m_Position(position)
	{
	}
	void EffectMove::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		//auto ptrDraw = AddComponent<PNTStaticDraw>();
		//ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

	}
	void EffectMove::OnUpdate() {

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		auto at = GetStage()->GetView()->GetTargetCamera()->GetAt();
		at.x += -7.0f;
		at.z += -7.0f;
		//auto vec = at - pos;
		//vec.normalize();

		//pos += vec;

		ptrTrans->SetPosition(at);

		if (pos.y < 1.0f) {
			GetTypeStage<MainStage>()->SetHpUIPos(pos);
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}
	}

}
//end basecross