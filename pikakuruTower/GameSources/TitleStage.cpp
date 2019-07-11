#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// �^�C�g���̉摜�ƃQ�[���X�^�[�g�̉摜
	//--------------------------------------------------------------------------------------
	TitleAnimeSprite::TitleAnimeSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr,
			textureKey,
			startScale,
			startPos)
	{
	}

	void TitleAnimeSprite::OnUpdate() {

	}

	void TitleAnimeSprite::SetActive(bool Active) {

		auto ptrTrans = GetComponent<Transform>();
		auto scale = ptrTrans->GetScale();

		if (Active) {
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 1.0));

		}
		else {
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 0.0));

		}
	}

	void TitleAnimeSprite::Rotation(bool Active) {
		if (Active) {

			m_Rot += Vec3(0, 0, -0.07);

			auto ptrTrans = GetComponent<Transform>();
			ptrTrans->SetRotation(m_Rot);

		}
		else {

			auto ptrTrans = GetComponent<Transform>();
			ptrTrans->SetRotation(m_Rot);
		}
	}

	void TitleAnimeSprite::PikaDrop(bool Active) {
		if (Active) {
			auto ptrTrans = GetComponent<Transform>();
			ptrTrans->SetPosition(m_PikaPos);

			m_PikaPos.y += -10.0f;

			if (m_PikaPos.y <= 225.0f) {
				m_PikaPos.y = 225.0f;

			}

		}
		else {
			auto ptrTrans = GetComponent<Transform>();
			ptrTrans->SetPosition(m_PikaPos);

			m_PikaPos = Vec3(-315.0f, 225.0f, 0.0f);
		}
	}

	void TitleAnimeSprite::StarDrop(bool Active) {
		if (Active) {
			auto ptrTrans = GetComponent<Transform>();
			ptrTrans->SetPosition(m_StarPos);

			m_StarPos.x += -6.5f * 0.8;
			m_StarPos.y += -13.0f * 0.8;

			if (m_StarPos.x <= -470.0f) {
				m_StarPos.x = -470.0f;
			}
			if (m_StarPos.y <= 210.0f) {
				m_StarPos.y = 210.0f;
			}

		}
		else {
			auto ptrTrans = GetComponent<Transform>();
			ptrTrans->SetPosition(m_StarPos);

			m_StarPos = Vec3(-470.0f, 210.0f, 0.0f);
		}
	}

	void TitleAnimeSprite::KuruDrop(bool Active) {
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, m_Transpar));


		if (Active) {

			m_KuruTime += 0.1f;
			//if (m_KuruTime >= 13.0f) {
			if (m_KuruTime >= 18.0f) {
				m_Transpar += 0.01;

				m_Rot += Vec3(0, 0, m_RotSpeed);

				if (m_Rot.z > XM_2PI) {
					m_RotSpeed = 0.0f;
					m_Rot = Vec3(0, 0, 0);
					m_Transpar = 1.0f;
				}
			}

			auto ptrTrans = GetComponent<Transform>();
			ptrTrans->SetRotation(m_Rot);

		}
		else {
			m_RotSpeed = 0.0f;
			m_Rot = Vec3(0, 0, 0);
			m_Transpar = 1.0f;


			m_Rot = Vec3(0, 0, 0);
			auto ptrTrans = GetComponent<Transform>();
			ptrTrans->SetRotation(m_Rot);
		}
	}

	//--------------------------------------------------------------------------------------
	// �^�C�g���Ɏg��Player
	//--------------------------------------------------------------------------------------
	TitlePlayer::TitlePlayer(const shared_ptr<Stage>& stagePtr) :
		MyGameObject(stagePtr)
	{
	}
	TitlePlayer::TitlePlayer(const shared_ptr<Stage>& stagePtr, const Vec3 & scale, const Vec3 & rotation, const Vec3 & position) :
		MyGameObject(stagePtr)
	{
	}
	//���ݔ��ˑ��u�@= Player
	void TitlePlayer::OnCreate()
	{
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(0.55f, 0.75f, 0.55f);	//���a25�Z���`�̋���
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(0, 0.525f, -6.1f);
	}


	//--------------------------------------------------------------------------------------
	// �^�C�g���X�e�[�W
	//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		//PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		//PtrCamera->SetEye(Vec3(0.0f, 15.0f, -25.0f));
		PtrCamera->SetEye(Vec3(0.0f, 15, -14.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();

	}


	void TitleStage::CreateFloor() {
		AddGameObject<FixedBox>(
			//�傫��(Scale)
			Vec3(55.0f, 1.0f, 55.0f),
			// ��](Rotation)
			Vec3(0.0f, 0.0f, 0.0f),
			// �ʒu(Position)
			Vec3(0.0f, -0.5f, 10.0f));
	};

	void TitleStage::CreateTitlePlayer() {
		//�v���[���[�̍쐬
		auto ptrPlayer = AddGameObject<TitlePlayer>();
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
		CreateSharedObjectGroup(L"FireSphereGroup");

		// �v���C���[�i�X�|�b�g���C�g�j�̍쐬
		auto spotlight1 = AddGameObject<Spotlight>(Vec3(1.5f, 1.5f, 1.5f), Vec3(XM_PIDIV2, 0.0f, 0.0f), Vec3(0.0f, 0.01f, 0.0f));
		SetSharedGameObject(L"Spotlight", spotlight1);
	}

	void TitleStage::CreateWall() {

		auto wall = AddGameObject<Wall>(
			Vec3(30.0f, 2.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, -7.5f));
		SetSharedGameObject(L"Wall", wall);

		//�^���[�̉��̕���
		auto towerBody = AddGameObject<TowerUnder>(
			Vec3(3.0f, 3.0f, 3.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.5f, -8.5f));

		// �^���[�̉�]���镔��
		AddGameObject<Tower>(
			Vec3(1.8f, 1.8f, 1.8f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 2.5f, -8.5f));


		auto wallTaget = AddGameObject<WallTaget>(
			Vec3(2.0f, 0.9f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(-3.0f, 0.4f, -7.55f));
		SetSharedGameObject(L"WallLeft", wallTaget);


		wallTaget = AddGameObject<WallTaget>(
			Vec3(2.0f, 0.9f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(3.0f, 0.4f, -7.55f));
		SetSharedGameObject(L"WallRight", wallTaget);

		// �ǐ���
		for (int i = 0; i < 20; i++) {
			AddGameObject<WallUnit>(
				Vec3(2.0f, 2.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-10.0f + (i * 2), 0.5f, -7.5f));
		}

	}

	void TitleStage::CreateFireTorch() {
		AddGameObject<FireTorch>(Vec3(1.0f, 1.0f, 1.0f), Vec3(0, 0, 0), Vec3(-5.0f, 0.5f, -8.0f));
		AddGameObject<FireTorch>(Vec3(1.0f, 1.0f, 1.0f), Vec3(0, 0, 0), Vec3(5.0f, 0.5f, -8.0f));
	}

	void TitleStage::CreateTimer() {
		//pad������͂��Ȃ�������v��
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cntlVec.wReleasedButtons == false && cntlVec.fThumbLX == 0 && cntlVec.fThumbLY == 0) {
			auto elapsedTime = App::GetApp()->GetElapsedTime();
			m_MovieTime += elapsedTime;
		}
	}
	//������
	void TitleStage::OnCreate() {
		WaveManager::getInstance()->ResetWaveNum();
		GameManager::getInstance()->ResetMainStage();

		CreateViewLight();

		// ���C��BGM�̍Đ�
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"TitleBGM.wav", XAUDIO2_LOOP_INFINITE, 0.5f);

		//�G�t�F�N�g�쐬
		m_EfkInterface = ObjectFactory::Create<EfkInterface>();

		// �u�Q�[���������v�̃X�v���C�g�쐬
		//auto a = AddGameObject<Sprite>(L"TitleToEndButton.png", Vec2(512.0f * 0.8f, 128.0f * 0.8f), Vec2(-435, -336));
		//a->SetDrawLayer(100);

		m_SpVec[1] = AddGameObject<TitleAnimeSprite>(L"TitlePika.png", Vec2(2197.0f * 0.4f, 779.0f * 0.4f), Vec2(-315.0f, 225.0f));
		m_SpVec[2] = AddGameObject<TitleAnimeSprite>(L"TitleKuru.png", Vec2(1877.0f * 0.4f, 779.0f * 0.4f), Vec2(275.0f, 225.0f));
		m_SpVec[3] = AddGameObject<TitleAnimeSprite>(L"TitleStar.png", Vec2(256.0f * 0.4f, 256.0f * 0.4f), Vec2(-470.0f, 210.0f));
		m_SpVec[4] = AddGameObject<TitleAnimeSprite>(L"GameStart_A.png", Vec2(2387.0f * 0.25f, 487.0f * 0.25f), Vec2(0.0f, -225.0f));

		m_SpVec[1]->SetDrawActive(true);
		m_SpVec[2]->SetDrawActive(true);
		m_SpVec[3]->SetDrawActive(true);
		m_SpVec[4]->SetDrawActive(true);

		m_SpVec[1]->SetDrawLayer(5);
		m_SpVec[2]->SetDrawLayer(5);
		m_SpVec[3]->SetDrawLayer(5);
		m_SpVec[4]->SetDrawLayer(5);

		m_SpVec[4]->SetActive(false);

		CreateFloor();
		CreateTitlePlayer();
		CreateWall();
		CreateFireTorch();

		AddGameObject<TitleEnemy>(Vec3(0.5f, 0.5f, 0.5f), Vec3(0.0f, -1.6f, 0.0f), Vec3(-15.0f, 0.5f, 0.0f));

		AddGameObject<NightMaskSprite>(L"NightMask.png", Vec2(2560, 1600), Vec2(0, 0));

		// �X�|�b�g���C�g�̌����̍쐬
		AddGameObject<SpotLightRay>(Vec3(2, 2, 2), Vec3(0, 0, 0), Vec3(0, 1.01f, 0));



		//�t�F�[�h�̉摜�̍쐬
		AddGameObject<FadeStarSprite>(FadeType::FadeIn);

		// �؂̐���
		// �ǂݍ���Xml�t�@�C�����w��
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		auto stageXmlPath = dataDir + L"Stage\\title.xml";

		GameObjecttXMLBuilder builder;
		builder.Register<Tree>(L"Tree");
		builder.Build(GetThis<Stage>(), stageXmlPath, L"GameStage/Tree");

	}

	//�X�V
	void TitleStage::OnUpdate() {

		CreateTimer();

		m_EfkInterface->OnUpdate();

		static float a = 0;
		a += App::GetApp()->GetElapsedTime();
		// Game���n�܂��Ă��� 0.0f��������A�^�C�g�����~���Ă���
		if (a >= 0.0f) {
			for (int i = 1; i < 4; i++) {
				m_SpVec[i]->SetDrawActive(true);
			}

			m_SpVec[1]->PikaDrop(true);
			m_SpVec[2]->KuruDrop(true);
			m_SpVec[3]->StarDrop(true);
			m_SpVec[3]->Rotation(true);

			m_Time += 0.1f;
			if (m_Time >= 30.0f) {
				m_Time = 30.0f;
			}
		}
		else {
			for (int i = 1; i < 4; i++) {
				m_SpVec[i]->SetDrawActive(false);
			}

			// �����ɃQ�[�����n�܂����Ƃ��̉��o������
			// �J������ʂ̉����ڂ�
			// �m�[�}���]���r���łĂ���
			// �]���r�������Ă���
			// �J������O�ɂ��ǂ�
			// �����܂��_�΂���
			// �^���[����]����
			// �^���[������n�߂�
			// �^���[����X�|�b�g���C�g���ł�
			// �]���r���򉻂����
			// �l�ԂɂȂ��ĕǂɗ���
			
			// ���̂��S���I�������A�^�C�g�����o�Ă���
		}




		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cntlVec.bConnected) {

			// �J�n���̉��o�����ׂĂ�����Ă��ā@���@A����������t�F�[�h�A�E�g�J�n
			if (FadeCount == 0 && cntlVec.wPressedButtons & XINPUT_GAMEPAD_A && FadeSwitch == true) {
				if (!m_Start) {
					FadeSwitch = false;
					auto XAPtr = App::GetApp()->GetXAudio2Manager();
					XAPtr->Stop(m_BGM);

					App::GetApp()->GetXAudio2Manager()->Start(L"Button.wav", 0, 0.5f);

					//�_�ł̃X�s�[�h�𑬂�����
					FalseTimeEnd *= FlashingSpeed;
					TrueTimeEnd *= FlashingSpeed;
					DecSwitch += 1.0f;

					if (DecSwitch >= 1.0f) {
						DecTime += 1.0f;                  //�{�^���������Ă���̎��Ԍv���J�n               
						if (DecTime >= FlashingTime) {
							m_SpVec[4]->SetActive(false);
							TrueTimePlus = 0.0f;          //�_�ł��Ȃ��Ȃ�
							if (DecTime >= FlashingEnd) {
							}
						}
					}

					AddGameObject<FadeStarSprite>(FadeType::FadeOut, L"ToSelectStage");
				}
			}

			// B����������Q�[�����I���
			if (FadeCount == 0 && cntlVec.wPressedButtons & XINPUT_GAMEPAD_B && FadeSwitch == true) {
				// �Q�[�����I���
				//PostQuitMessage(0);
				//return;
			}

			// �J�n�̉��o���I����Ă��Ȃ�������I��点��@�ҋ@��ԂɂȂ�
			if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_A && m_Start == true || m_Time >= 28.0f) {
				m_SpVec[1]->PikaDrop(false);
				m_SpVec[2]->KuruDrop(false);
				m_SpVec[3]->StarDrop(false);

				m_Start = false;
			}


			// �Q�[���X�^�[�g�̕����\��
			if (m_Start == false) {
				//true�̎�
				if (Switch <= 0.0f) {
					FalseTime = 0.0f; //false�̎��̎��Ԃ̃��Z�b�g
					TrueTime += 1.0f; //���Ԍv���J�n
					//��莞�Ԍo�߂��ē����ɂ�����
					if (TrueTime >= TrueTimeEnd) {
						Switch += 1.0f;
						m_SpVec[4]->SetActive(false);
					}
				}
				//false�̎�
				else {
					TrueTime = 0.0f; //true�̎��̎��Ԃ̃��Z�b�g
					FalseTime += TrueTimePlus; //���Ԍv���J�n
					//��莞�Ԍo�߂��ĕ\��������
					if (FalseTime >= FalseTimeEnd) {
						Switch += -1.0f;
						m_SpVec[4]->SetActive(true);
					}
				}
			}
		}

		// 30�b�o�߂����烀�[�r�[�Đ�����
		if (m_MovieTime >= 30.0f) {
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Stop(m_BGM);

			m_MovieTime = 0.0f;

			AddGameObject<FadeSquareSprite>(FadeType::FadeOut, L"MovieStage");
		}
	}

	void TitleStage::OnDraw() {
		auto& camera = GetView()->GetTargetCamera();
		m_EfkInterface->SetViewProj(camera->GetViewMatrix(), camera->GetProjMatrix());
		m_EfkInterface->OnDraw();
	}

	void TitleStage::DrawStage() {
		//���C���[�̎擾�Ɛݒ�
		set<int> DrawLayers;
		//Sprite�������łȂ����𕪗�
		for (auto ptr : GetGameObjectVec()) {
			if (ptr->IsDrawActive()) {
				//�`�惌�C���[�ɓo�^
				DrawLayers.insert(ptr->GetDrawLayer());
				//Sprite�����̔h���N���X�Ȃ番��
				if (ptr->GetComponent<SpriteBaseDraw>(false) || ptr->IsSpriteDraw()) {
					m_SpriteVec.push_back(ptr);
				}
				else {
					m_Object3DVec.push_back(ptr);
				}
			}
		}
		//3D�̓����Ɣ񓧖��𕪗�
		for (auto ptr : m_Object3DVec) {
			if (ptr->IsDrawActive()) {
				if (ptr->IsAlphaActive()) {
					m_Object3DAlphaVec.push_back(ptr);
				}
				else {
					m_Object3DNormalVec.push_back(ptr);
				}
			}
		}

		auto PtrCamera = GetView()->GetTargetCamera();
		//�J�����̈ʒu
		bsm::Vec3 CameraEye = PtrCamera->GetEye();
		//������3D�I�u�W�F�N�g���J��������̋����Ń\�[�g
		//�ȉ��́A�I�u�W�F�N�g�������Ɏ��bool��Ԃ������_��
		//--------------------------------------------------------
		auto func = [&](shared_ptr<GameObject>& Left, shared_ptr<GameObject>& Right)->bool {
			auto PtrLeftTrans = Left->GetComponent<Transform>();
			auto PtrRightTrans = Right->GetComponent<Transform>();

			auto LeftPos = PtrLeftTrans->GetWorldMatrix().transInMatrix();
			auto RightPos = PtrRightTrans->GetWorldMatrix().transInMatrix();

			auto LeftLen = bsm::length(LeftPos - CameraEye);
			auto RightLen = bsm::length(RightPos - CameraEye);

			return (LeftLen > RightLen);
		};

		//		std::sort(m_Object3DAlphaVec.begin(), m_Object3DAlphaVec.end(), func);

				//3D�m�[�}���I�u�W�F�N�g�̕`�揀��
		for (auto ptr : m_Object3DNormalVec) {
			ptr->OnPreDraw();
		}
		//3D�����I�u�W�F�N�g�̕`�揀��
		//for (auto ptr : m_Object3DAlphaVec) {
		//	ptr->OnPreDraw();
		//}
		//�p�[�e�B�N���̕`�揀���i�����j
		GetParticleManager(false)->OnPreDraw();
		//�p�[�e�B�N���̕`�揀���i���Z�j
		GetParticleManager(true)->OnPreDraw();
		//�X�v���C�g�I�u�W�F�N�g�̕`�揀��
		for (auto ptr : m_SpriteVec) {
			ptr->OnPreDraw();
		}

		//--------------------------------------------------------
		//�X�v���C�g��Z���W�����Ń\�[�g
		//�ȉ��́A�I�u�W�F�N�g�������Ɏ��bool��Ԃ������_��
		//--------------------------------------------------------
		auto funcSprite = [&](shared_ptr<GameObject>& Left, shared_ptr<GameObject>& Right)->bool {
			auto PtrLeftTrans = Left->GetComponent<Transform>();
			auto PtrRightTrans = Right->GetComponent<Transform>();

			auto LeftPos = PtrLeftTrans->GetWorldMatrix().transInMatrix();
			auto RightPos = PtrRightTrans->GetWorldMatrix().transInMatrix();

			float LeftZ = LeftPos.z;
			float RightZ = RightPos.z;
			return (LeftZ > RightZ);
		};
		std::sort(m_SpriteVec.begin(), m_SpriteVec.end(), funcSprite);

		for (auto it = DrawLayers.begin(); it != DrawLayers.end(); it++) {
			int Tgt = *it;
			//3D�m�[�}���I�u�W�F�N�g�̕`��
			for (auto ptr : m_Object3DNormalVec) {
				if (ptr->GetDrawLayer() == Tgt) {
					ptr->OnDraw();
				}
			}
			//3D�����I�u�W�F�N�g�̕`��
			for (auto ptr : m_Object3DAlphaVec) {
				if (ptr->GetDrawLayer() == Tgt) {
					ptr->OnDraw();
				}
			}
			//�p�[�e�B�N���̕`��
			//�p�[�e�B�N���}�l�[�W���͕`�惌�C���[���Ƃɏ����������̂�
			//�����C���[�`�悷��
			//��������
			GetParticleManager(false)->OnDraw();
			//���Z����
			GetParticleManager(true)->OnDraw();
		}
		for (auto it = DrawLayers.begin(); it != DrawLayers.end(); it++) {
			int Tgt = *it;

			//�X�v���C�g�I�u�W�F�N�g�̕`��
			for (auto ptr : m_SpriteVec) {
				if (ptr->GetDrawLayer() == Tgt) {
					ptr->OnDraw();
					if (Tgt == 2) {
						//�X�e�[�W��Draw();
						OnDraw();
					}
				}
			}
		}
		//���[�N�p�z��̃N���A
		//���[�N�z��͖��^�[�����Ƃɏ���������邪�A
		//�ő�l�͌���Ȃ��̂�2��ڂ̃^�[���ȍ~�͍����ɓ��삷��
		m_Object3DVec.clear();
		m_SpriteVec.clear();
		m_Object3DNormalVec.clear();
		m_Object3DAlphaVec.clear();
	}



}





