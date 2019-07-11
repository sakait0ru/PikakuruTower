/*!
@file TitleEnemy.cpp
@brief �G
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// �^�C�g����ʂŎg���]���r
	//--------------------------------------------------------------------------------------
	TitleEnemy::TitleEnemy(const shared_ptr<Stage>& stagePtr,
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
	void TitleEnemy::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(2.5f, 2.5f, 2.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.75f, 0.0f)
		);
		auto ptrColl = AddComponent<CollisionSphere>();
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		auto ptrShadow = AddComponent<Shadowmap>();
		//�ŏ���Mesh��ݒ�
		ptrDraw->SetMeshResource(L"Man_Zombie.bbmf");
		ptrShadow->SetMeshResource(L"Man_Zombie.bbmf");

		// �A�j���[�V�����̒ǉ�
		ptrDraw->AddAnimation(L"Stay", 0, 1, true, 1);
		ptrDraw->AddAnimation(L"Walk", 0, 60, true, 100.0f);
		ptrDraw->ChangeCurrentAnimation(L"Walk");

		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		SetAlphaActive(true);

		m_Spotlight = GetStage()->GetSharedGameObject<Spotlight>(L"Spotlight");

		//�A�N�V�����̓o�^
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

		//���񂾂Ƃ��̃G�t�F�N�g
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\zonbikirafix.efk";
		auto ShEfkInterface = GetTypeStage<TitleStage>()->GetEfkInterface();
		m_EfkEffect[0] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);

		//�l�ԂɂȂ�Ƃ��̃G�t�F�N�g
		App::GetApp()->GetDataDirectory(DataDir);
		TestEffectStr = DataDir + L"Effects\\zonbiattack.efk";
		m_EfkEffect[1] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);

		//�_���[�W���󂯂Ă��鎞�̃G�t�F�N�g
		App::GetApp()->GetDataDirectory(DataDir);
		TestEffectStr = DataDir + L"Effects\\zonbinowdamage.efk";
		m_EfkEffect[2] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);

		//����ŉ񕜂��鎞�̃G�t�F�N�g
		App::GetApp()->GetDataDirectory(DataDir);
		TestEffectStr = DataDir + L"Effects\\zonbiheal.efk";
		m_EfkEffect[3] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);


	}
	void TitleEnemy::OnUpdate() {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		auto ptrShadow = AddComponent<Shadowmap>();
		auto ptrTrans = GetComponent<Transform>();
		//���񂾂Ƃ��̏���
		if (m_Hp < 0) {
			m_Hp = 0;
			//�G�t�F�N�g�̃v���C
			m_EfkPlay[0] = ObjectFactory::Create<EfkPlay>(m_EfkEffect[0], ptrTrans->GetPosition());
			m_EfkPlay[3] = ObjectFactory::Create<EfkPlay>(m_EfkEffect[3], ptrTrans->GetPosition());
			//�T�E���h�̍Đ�
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"Zombie_Zouka.wav", 0, 0.5f);
			//�A�N�V�����J�n
			GetComponent<Action>()->Run();
		}
		//���񂾂��Ƃ̏���
		if (m_Hp == 0) {
			auto ptrTrans = GetComponent<Transform>();
			auto after = ptrTrans->GetPosition();
			//�l�Ԃ̃e�N�X�`���ɕύX
			ChangTex();
			//�l�Ԃ̎��̓���
			HumanWalkMove();
			//��]
			RotToHead();
			auto befor = ptrTrans->GetPosition();
			auto dis = befor - after;
			auto action = GetComponent<Action>();
			if (action->GetArrived()) {
				m_EfkPlay[3]->AddLocation(Vec3(dis.x, 0, dis.z));
			}
		}
		else if (m_Damage) {
			//�_���[�W�`�F�b�N
			LightDamegeCheck();
			//���C�g�̃_���[�W���󂯂Ă���
			DamageReceive();
		}
		else {
			//����
			WalkMove();
			//��]
			RotToHead();
			//�_���[�W�`�F�b�N
			LightDamegeCheck();
		}

		//������E�ֈړ��̎��̏���
		auto pos = ptrTrans->GetPosition();
		if (Key == 0) {
			if (pos.x > 15.0 || m_Hit == true)
			{
				m_Hit = false;
				pos.x = -15.0f;
				pos.z = 0.0f;
				m_Nunber += 1;
				Key = rand() % 2;
				m_Hp = m_MaxHp;
				auto ptrShadow = AddComponent<Shadowmap>();
				switch (m_Nunber)
				{
				case 0:
					ptrDraw->SetMeshResource(L"Man_Zombie.bbmf");
					//�e�̌`�i���b�V���j��ݒ�
					ptrShadow->SetMeshResource(L"Man_Zombie.bbmf");
					break;

				case 1:
					ptrDraw->SetMeshResource(L"Woman_Zombie.bbmf");
					ptrShadow->SetMeshResource(L"Woman_Zombie.bbmf");
					break;
				case 2:
					ptrDraw->SetMeshResource(L"Polis_Zombie.bbmf");
					ptrShadow->SetMeshResource(L"Polis_Zombie.bbmf");
					break;
				case 3:
					ptrDraw->SetMeshResource(L"Zombie_Work_Walk-Attack.bbmf");
					ptrShadow->SetMeshResource(L"Zombie_Work_Walk-Attack.bbmf");
					break;
				case 4:
					ptrDraw->SetMeshResource(L"Hummer_Walk.bbmf");
					ptrShadow->SetMeshResource(L"Hummer_Walk.bbmf");
					break;
				case 5:
					ptrDraw->SetMeshResource(L"Shield_Walk.bbmf");
					ptrShadow->SetMeshResource(L"Shield_Walk.bbmf");
					break;
				case 6:
					ptrDraw->SetMeshResource(L"Runner_Zombie.bbmf");
					ptrShadow->SetMeshResource(L"Runner_Zombie.bbmf");
					break;

				case 7:
					ptrDraw->SetMeshResource(L"Swimwear_Zombie.bbmf");
					ptrShadow->SetMeshResource(L"Swimwear_Zombie.bbmf");
					break;

				default:
					m_Nunber = 0;
					ptrDraw->SetMeshResource(L"Man_Zombie.bbmf");
					//�e�̌`�i���b�V���j��ݒ�
					ptrShadow->SetMeshResource(L"Man_Zombie.bbmf");
					break;
				}

			}

		}

		//�E���獶�ֈړ��̎��̏���
		if (Key == 1) {
			if (pos.x < -15.0 || m_Hit == true)
			{
				m_Hit = false;
				pos.x = 15.0f;
				pos.z = 0.0f;
				m_Nunber += 1;
				Key = rand() % 2;
				m_Hp = m_MaxHp;
				auto ptrShadow = AddComponent<Shadowmap>();
				switch (m_Nunber)
				{
				case 0:
					ptrDraw->SetMeshResource(L"Man_Zombie.bbmf");
					//�e�̌`�i���b�V���j��ݒ�
					ptrShadow->SetMeshResource(L"Man_Zombie.bbmf");
					break;

				case 1:
					ptrDraw->SetMeshResource(L"Woman_Zombie.bbmf");
					ptrShadow->SetMeshResource(L"Woman_Zombie.bbmf");
					break;
				case 2:
					ptrDraw->SetMeshResource(L"Polis_Zombie.bbmf");
					ptrShadow->SetMeshResource(L"Polis_Zombie.bbmf");
					break;
				case 3:
					ptrDraw->SetMeshResource(L"Zombie_Work_Walk-Attack.bbmf");
					ptrShadow->SetMeshResource(L"Zombie_Work_Walk-Attack.bbmf");
					break;
				case 4:
					ptrDraw->SetMeshResource(L"Hummer_Walk.bbmf");
					ptrShadow->SetMeshResource(L"Hummer_Walk.bbmf");
					break;
				case 5:
					ptrDraw->SetMeshResource(L"Shield_Walk.bbmf");
					ptrShadow->SetMeshResource(L"Shield_Walk.bbmf");
					break;
				case 6:
					ptrDraw->SetMeshResource(L"Runner_Zombie.bbmf");
					ptrShadow->SetMeshResource(L"Runner_Zombie.bbmf");
					break;

				case 7:
					ptrDraw->SetMeshResource(L"Swimwear_Zombie.bbmf");
					ptrShadow->SetMeshResource(L"Swimwear_Zombie.bbmf");
					break;

				default:
					m_Nunber = 0;
					ptrDraw->SetMeshResource(L"Man_Zombie.bbmf");
					//�e�̌`�i���b�V���j��ݒ�
					ptrShadow->SetMeshResource(L"Man_Zombie.bbmf");
					break;
				}

			}

		}
		ptrTrans->SetPosition(pos);

		float elapsedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elapsedTime);
	}

	void TitleEnemy::WalkMove() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		if (Key == 0) {
			pos.x += 1.0f*elapsedTime;
		}
		if (Key == 1) {
			pos.x -= 1.0f*elapsedTime;
		}
		ptrTrans->SetPosition(pos);
	}

	Vec3 TitleEnemy::HumanMove() {
		auto spotPos = GetStage()->GetSharedGameObject<Wall>(L"Wall")->GetComponent<Transform>()->GetPosition();

		auto pos = GetComponent<Transform>()->GetPosition();

		auto velo = spotPos - pos;
		velo.normalize();
		Vec3 vec = Vec3(velo.x * 0.01f, 0.0f, velo.z * 0.01f);
		return vec;
	}

	void TitleEnemy::HumanWalkMove() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos += HumanMove() * 15;
		ptrTrans->SetPosition(pos);
	}

	void TitleEnemy::RotToHead() {
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

	void TitleEnemy::LightDamegeCheck() {
		//���C�g�ɂ������Ă��Ă����C�g���I���Ȃ�
		if (m_Light && m_Spotlight->GetActive()) {
			m_Damage = true;

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
		else {
			m_Damage = false;
		}
	}
	void TitleEnemy::DamageReceive() {
		//���C�g�ɓ������Ă��Ȃ�
		if (m_Light == false) {
			WalkMove();
		}

		//�悯�Ȃ�
		if (m_Nunber == 4) {
			WalkMove();
		}
		//�悯�Ȃ�
		else if (m_Nunber == 5) {
			WalkMove();
		}
		//�悯��
		else {
			WalkMove();
			auto ptrTrans = GetComponent<Transform>();
			auto pos = ptrTrans->GetPosition();
			auto posZ = pos.z;
			auto lightPtr = GetStage()->GetSharedGameObject<Spotlight>(L"Spotlight");
			auto lightPos = lightPtr->GetComponent<Transform>()->GetPosition();
			auto lightPosZ = lightPos.z;
			auto totalPos = posZ - lightPosZ;
			if (totalPos < 0) {
				pos.z += 0.5f * -0.02f;
			}
			if (totalPos > 0) {
				pos.z += 0.5f * 0.02f;
			}
			ptrTrans->SetPosition(pos);
		}
		//�_���[�W
		auto lightPower = m_Spotlight->GetLightPower();
		m_Hp -= lightPower * 0.3f;

	}


	void TitleEnemy::ChangTex() {
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		auto ptrShadow = AddComponent<Shadowmap>();
		if (m_Nunber == 1) {
			ptrDraw->SetMeshResource(L"Woman_Human.bbmf");
			ptrShadow->SetMeshResource(L"Woman_Human.bbmf");
		}
		else if (m_Nunber == 2) {
			ptrDraw->SetMeshResource(L"Man2_Human.bbmf");
			ptrShadow->SetMeshResource(L"Man2_Human.bbmf");
		}
		else {
			ptrDraw->SetMeshResource(L"Man_Human.bbmf");
			ptrShadow->SetMeshResource(L"Man_Human.bbmf");
		}
	}


	void TitleEnemy::OnCollisionExit(shared_ptr<GameObject>& Other) {
		// ���C�g���痣�ꂽ��
		if (Other->FindTag(L"Light")) {
			// ���C�g�t���O��false�ɂ���
			m_Light = false;
		}
	}
	void TitleEnemy::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		// ���C�g�ɐG�ꂽ��
		if (Other->FindTag(L"Light")) {
			// ���C�g�t���O��true�ɂ���
			m_Light = true;
		}
		if (Other->FindTag(L"Wall")) {
			m_Hit = true;
			m_EfkPlay[3]->StopEffect();
		}
	}

}