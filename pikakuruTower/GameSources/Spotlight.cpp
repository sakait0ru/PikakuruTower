/*!
@file Spotlight.cpp
@brief �X�|�b�g���C�g
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	Spotlight::Spotlight(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position) :
		MyGameObject(stagePtr),
		m_Scale(scale),
		m_Rotation(rotation),
		m_Position(position),
		m_On(true)
	{
	}

	Vec3 Spotlight::GetMoveVector() const 
	{
		Vec3 angle(0, 0, 0);
		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float fThumbLY = 0.0f;
		float fThumbLX = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			fThumbLY = cntlVec[0].fThumbLY;
			fThumbLX = cntlVec[0].fThumbLX;
			wButtons = cntlVec[0].wButtons;
		}
	
		if (fThumbLX != 0 || fThumbLY != 0) {
			float moveLength = 0;	//���������̃X�s�[�h
			//�R���g���[���̌����v�Z
			float moveX = fThumbLX;
			float moveZ = fThumbLY;
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//�R���g���[���̌�������p�x���v�Z
			//float cntlAngle = atan2(moveZ, moveX);
			//�g�[�^���̊p�x���Z�o
			//float totalAngle = cntlAngle;
			//�p�x����x�N�g�����쐬
		//	angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			//���K������
			angle.normalize();
			//�ړ��T�C�Y��ݒ�B
			angle *= moveSize;
			//Y���͕ω������Ȃ�
			angle.y = 0;
		}
		return angle;
	}

	void Spotlight::CalcDevPos()
	{
		auto ptrCamera = OnGetDrawCamera();
		Mat4x4 world, view, proj;
		world = GetComponent<Transform>()->GetWorldMatrix();
		view = ptrCamera->GetViewMatrix();
		proj = ptrCamera->GetProjMatrix();
		m_DevPos = Vec3(0);

		m_DevPos = XMVector3Project
		(m_DevPos, -1.0f, -1.0f, 2.0f, 2.0f, 0.0f, 1.0f, proj, view, world);
	}

	void Spotlight::MovePlayer() 
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		auto pos = GetComponent<Transform>()->GetPosition();
		if (angle.length() > 0.0f) 
		{
			pos += angle * elapsedTime * 6.0f;
		}
		CalcDevPos();
		
	
		//��]�̌v�Z
		if (angle.length() > 0.0f) 
		{
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, 1.0f);
		}
	}

	

	void Spotlight::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		auto ptrCol = AddComponent<CollisionSphere>();
		ptrCol->SetAfterCollision(AfterCollision::None);
		//ptrCol->SetDrawActive(true);

		// 3D�I�u�W�F�N�g�ł����Ă��
		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		//�`�悷��e�N�X�`����ݒ�
		ptrDraw->SetTextureResource(L"Spotlight.png");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		//�A�N�V�����R���|�[�l���g��ǉ�
		auto ptrAct = AddComponent<Action>();
		ptrAct->AddScaleTo(0.5f, Vec3(1.0f, 1.0f, 1.0f));



		SetAlphaActive(true);

		AddTag(L"Light");

		// �f�o�b�O�p�̕������ݒ�
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

	}

	void Spotlight::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Enemy")) {
			auto ptrEnemy = dynamic_pointer_cast<Enemy>(Other);
			if (ptrEnemy) {
				//ptrEnemy->FaintChange();
			}
		}
	}


#define MINIDOWN(X,Y) if(X > Y) X= Y -0.01;
#define MAXIDOWN(X,Y) if(X < Y) X= Y -0.01;
// �O�����Z�q

	void Spotlight::OnUpdate() {

		auto GM = GameManager::getInstance();
		if (!GM->GetFinishActive()) {
			//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
			//m_InputHandler.PushHandle(GetThis<Spotlight>());
			MovePlayer();

			auto ptrPosition = GetComponent<Transform>()->GetPosition();

			// �L�[�{�[�h�œ���
			auto ptrTrans = GetComponent<Transform>();
			auto pos = ptrTrans->GetPosition();


			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
			if (cntlVec.bConnected)
			{
				if (cntlVec.fThumbLX != 0 || cntlVec.fThumbLY != 0)
				{
					auto stage = GetStage();
					auto main = dynamic_pointer_cast<MainStage>(stage);
					if (main) {
						//MINIDOWN(pos.z, 15.5);

						if (pos.z > 15.5)
						{
							pos.z = 15.49f;
						}
						if (pos.z < -6.5)
						{
							pos.z = -6.49f;
						}
						if (pos.x > 12.5)
						{
							pos.x = 12.49f;
						}
						if (pos.x < -13.5)
						{
							pos.x = -13.49f;
						}
					}
					else {
						// �^�C�g���̎�
						if (pos.z > 15.5)
						{
							pos.z = 15.49f;
						}
						if (pos.z < -6.5)
						{
							pos.z = -6.49f;
						}
						if (pos.x > 10.5)
						{
							pos.x = 10.49f;
						}
						if (pos.x < -10.5)
						{
							pos.x = -10.49f;
						}
					}
					// �ړ�
					pos.x += cntlVec.fThumbLX * m_Speed;//0.05
					pos.z += cntlVec.fThumbLY * m_Speed;//0.05
				}


			}
			// �傫���̕ύX
			if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			{

				if (m_Big)
				{
					//m_Scale.x = 3.0f;//3.0f
					//m_Scale.y = 3.0f;//3.0f
					m_Big = false;
					m_LightPower = 3;//3
					if (!m_Big) {
						m_Speed = 0.12f;
					}
				}
				else
				{

					//m_Scale.x = 1.50f;
					//m_Scale.y = 1.50f;//1.50f;
					m_Big = true;
					if (!m_Active)
					{
						m_Speed = 0.12f;
					}
					else if (m_Big) {
						m_Speed = 0.05f;
					}
					m_LightPower = 8;//8
				}
			}
			// ���C�g�̃I���I�t�@�^�C�g�����Ƃ��ꂢ��Ȃ�
			auto stage = GetStage();
			auto main = dynamic_pointer_cast<MainStage>(stage);
			if (main) {
				if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER || cntlVec.wPressedButtons & XINPUT_GAMEPAD_A)
				{
					App::GetApp()->GetXAudio2Manager()->Start(L"lightOnOff.wav", 0, 0.2f);
					if (m_Active)
					{
						//SetDrawActive(false);

						m_Speed = 0.15f;
						//auto ptrDraw = AddComponent<PNTStaticDraw>();
						//ptrDraw->SetTextureResource(L"SpotlightOFF.png");

						m_Active = false;
						m_On = false;
					}
					else
					{
						SetDrawActive(true);

						m_Speed = 0.05f;
						auto ptrDraw = GetComponent<BcPNTStaticDraw>();
						ptrDraw->SetTextureResource(L"Spotlight.png");

						m_Active = true;
						m_On = true;
					}
				}
				// �R���g���[���[���ڑ�����Ă��Ȃ��Ƃ��̏���
				else
				{
					auto keyVec = App::GetApp()->GetInputDevice().GetKeyState();
					if (keyVec.m_bPushKeyTbl['W'])
					{
						pos.z += 0.1f;
					}
					if (keyVec.m_bPushKeyTbl['A'])
					{
						pos.x -= 0.1f;
					}
					if (keyVec.m_bPushKeyTbl['S'])
					{
						pos.z -= 0.1f;
					}
					if (keyVec.m_bPushKeyTbl['D'])
					{
						pos.x += 0.1f;
					}
				}
			}
			ptrTrans->SetPosition(pos);

			//�����ł��Ȃ������z
			// ���C�g���I�t�̎�
			if (!m_On)
			{
				// ���C�g������������
				if (m_Scale.x > 0.0f&& m_Scale.y > 0.0f)
				{
					m_Scale.x -= 0.2f;
					m_Scale.y -= 0.2f;
					m_Scale.z -= 0.2f;

				}
			}
			else {
				// �傫����Ԃɂ���
				if (!m_Big)
				{
					// �I�t�܂��͏�������Ԃ���傫����Ԃɂ��鏈��
					if (m_Scale.x < 3.0f&& m_Scale.y < 3.0f)
					{
						m_Scale.x += 0.2f;
						m_Scale.y += 0.2f;
						m_Scale.z += 0.2f;
					}

				}
				// ��������Ԃɂ���
				else {
					// �傫����Ԃ��珬������Ԃɂ��鏈��
					if (m_Scale.x > 1.50f&& m_Scale.y > 1.50f)
					{
						m_Scale.x -= 0.2f;
						m_Scale.y -= 0.2f;
						m_Scale.z -= 0.2f;
					}
					// �I�t�̏�Ԃ��珬������Ԃɂ��鏈��
					if (m_Scale.x < 1.50f&& m_Scale.y < 1.50f)
					{
						m_Scale.x += 0.2f;
						m_Scale.y += 0.2f;
						m_Scale.z += 0.2f;
					}

				}

			}

			ptrTrans->SetScale(m_Scale);

			auto ptrDraw = GetComponent<BcPNTStaticDraw>();

			float defScale = 1.0f - (m_Scale.x - 1.5f) * 0.3f / 1.6f;

			GameManager::getInstance()->SetSpotLightPosition(GetComponent<Transform>()->GetPosition());


			/*
			Vec3 scale = CalcScale();
			
			
			*/

			//�X�P�[���̓X�P�[����ύX����֐��@CalcScale
			//pos��pos��ύX����֐�			CalcPos
			//�X�s�[�h�̓X�s�[�h��ύX����֐�	CalcSeed
			//light��ύX����֐�				CalcLight

		}
	}
}
//end basecross