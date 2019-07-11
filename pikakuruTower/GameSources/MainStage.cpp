/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {



	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void MainStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		//PtrCamera->SetEye(Vec3(2.0f, 2.0f, -7.0f));
		//PtrCamera->SetAt(Vec3(-90.0f, -15.0f, 0.0f));
		m_Camera = PtrCamera;
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	//�Z���}�b�v�̍쐬
	void MainStage::CreateStageCellMap() {
		float  PieceSize = 1.0f;
		auto Ptr = AddGameObject<StageCellMap>(Vec3(-15.0f, 0.0f, -10.0f), PieceSize, 30, 30);
		//�Z���}�b�v�̋���\������ꍇ�͈ȉ��̐ݒ�
		//Ptr->SetDrawActive(true);
		//����ɃZ���̃C���f�b�N�X�ƃR�X�g��\������ꍇ�͈ȉ��̐ݒ�
		//Ptr->SetCellStringActive(true);
		SetSharedGameObject(L"StageCellMap", Ptr);
		//�Z���}�b�v�ւ̃{�b�N�X�̃R�X�g�ݒ�
		SetCellMapCost();
	}

	void MainStage::CreateFloor() {
		GameObjecttXMLBuilder builder;

		builder.Register<FixedBox>(L"Floor");
		builder.Build(GetThis<Stage>(), m_stageXmlPath, L"GameStage/Floor");
		

		builder.Register<Tree>(L"Tree");
		builder.Build(GetThis<Stage>(), m_stageXmlPath, L"GameStage/Tree");


	}


	void MainStage::CreateUI()
	{
		// �X�e�[�W���Â�����}�X�N�̍쐬
		AddGameObject<NightMaskSprite>(L"NightMask.png", Vec2(2560, 1600), Vec2(0, 0));

		// �w�i�̐Ԃ̓z
		auto sprite = AddGameObject<Sprite>(L"red.png",
			Vec2(275.0f, 30.0f),
			Vec2(-437.0f, -355.0f));
		sprite->SetDrawLayer(11);
		// HP�o�[
		 AddGameObject<HpGage>(L"green.png",
			Vec2(275.0f, 30.0f),
			Vec2(-575.0f, -355.0f));
		// HP�Q�[�W�̘g
		sprite = AddGameObject<HpGageFrame>(L"UI0__0509.png",
			Vec2(1380.0f/4.0f, 976.0f/4.0f),
			Vec2(-450.0f, -300.0f));
			//Vec2(-470.0f, -310.0f));
		sprite->SetDrawLayer(11);

		// ���C�g�̃I���I�t��Ԃ�\������X�v���C�g
		AddGameObject<RightSuitch>(L"Light_on.png",
			Vec2(110.0f, 160.0f),
			Vec2(350.0f, -325.0f));
		// A�{�^���̕\��
		auto buttonSprite1 = AddGameObject<Sprite>(L"Abutton.png",
			Vec2(50.0f, 50.0f),
			Vec2(350.0f, -370.0f));
		buttonSprite1->SetDrawLayer(11);
		// LB�{�^���̕\��
		buttonSprite1 = AddGameObject<Sprite>(L"LBbutton.png",
			Vec2(50.0f, 50.0f),
			Vec2(375.0f, -275.0f));
		buttonSprite1->SetDrawLayer(11);


		// �M���ʂ̃X�v���C�g
		AddGameObject<ItemIcon>(L"Flash_Case.png",
			Vec2(100.0f, 100.0f),
			Vec2(550.0f, -330.0f));
		AddGameObject<ItemIcon>(L"Flash.png",
			Vec2(75.0f, 75.0f),
			Vec2(550.0f, -330.0f));
		
		auto GM = GameManager::getInstance();
		auto number = GM->GetFlashItem();
		auto numSprite = AddGameObject<NumberSprite>(L"Numder.png",
			Vec2(51.7f, 60.0f),
			Vec2(585.0f, -370.0f),
			number);
		numSprite->SetDrawLayer(11);
		SetSharedGameObject(L"NumberSprite", numSprite);
		// B�{�^���̕\��
		auto buttonSprite = AddGameObject<Sprite>(L"Bbutton.png",
			Vec2(50.0f,50.0f),
			Vec2(505.0f, -370.0f));
		buttonSprite->SetDrawLayer(11);

		// �E��̍���Wave����\������X�v���C�g
		auto waveSprite = AddGameObject<NowWaveSprite>(L"SummerWave1.png",
			Vec2(400, 100),
			Vec2(450.0f,350.0f));
		waveSprite->SetDrawLayer(11);
		SetSharedGameObject(L"WaveUI", waveSprite);

		// �|�[�Y��ʂ̉摜����
		AddGameObject<PauseSprite>(L"PauseWindow.png",
			Vec2(600, 600),
			Vec2(0, 0));
		auto pause = AddGameObject<PauseSprite>(L"PauseBack.png",
			Vec2(300, 75),
			Vec2(0, 90));
		pause->Akarusa(true);
		m_SpVec[0] = pause;
		pause = AddGameObject<PauseSprite>(L"PauseSelect.png",
			Vec2(250, 63),
			Vec2(0, -25));
		m_SpVec[1] = pause;
		pause->Akarusa(false);

		pause->GetComponent<PCTSpriteDraw>()->SetDiffuse(Col4(1, 1, 1, 0.5f));
		pause = AddGameObject<PauseSprite>(L"PauseTitle.png",
			Vec2(250, 63),
			Vec2(0, -140));
		m_SpVec[2] = pause;
		pause->Akarusa(false);

		pause->GetComponent<PCTSpriteDraw>()->SetDiffuse(Col4(1, 1, 1, 0.5f));
	}

	void MainStage::CreateWall() {

		// �ǂ̓����蔻��
		auto wall = AddGameObject<Wall>(
			Vec3(30.0f,2.0f, 1.0f),
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

		// �E�̑_����ꏊ
		auto wallTaget = AddGameObject<WallTaget>(
			Vec3(2.0f, 0.9f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(-3.0f, 0.4f, -7.55f));
		SetSharedGameObject(L"WallLeft", wallTaget);

		// ���̑_����ꏊ
		wallTaget = AddGameObject<WallTaget>(
			Vec3(2.0f, 0.9f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(3.0f, 0.4f, -7.55f));
		SetSharedGameObject(L"WallRight", wallTaget);

		// �ǂ̃��b�V����`��
		for (int i = 0; i < 20; i++) {
			AddGameObject<WallUnit>(
				Vec3(2.0f, 2.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-15.0f + (i * 2), 0.5f, -7.5f));
		}


		
	}

	void MainStage::CreateGimmick() {
		CreateSharedObjectGroup(L"Barricades");
		
		// �o���P�[�h
		GameObjecttXMLBuilder builder;
		builder.Register<Barricade>(L"Barricade");
		builder.Build(GetThis<Stage>(), m_stageXmlPath, L"GameStage/Barricade");

		// ���n
		builder.Register<SlowFloor>(L"SlowFloor");
		builder.Build(GetThis<Stage>(), m_stageXmlPath, L"GameStage/SlowFloor");
	}

	//�Œ�̃{�b�N�X�̃R�X�g���Z���}�b�v�ɔ��f
	void MainStage::SetCellMapCost() {
		//�Z���}�b�v����FixedBox�̏����Z�b�g
		auto PtrCellmap = GetSharedGameObject<StageCellMap>(L"StageCellMap");
		auto BoxGroup = GetSharedObjectGroup(L"Barricades");
		//�Z���}�b�v����Z���̔z����擾
		auto &CellVec = PtrCellmap->GetCellVec();
		//�{�b�N�X�O���[�v����{�b�N�X�̔z����擾
		auto &BoxVec = BoxGroup->GetGroupVector();
		vector<AABB>ObjectsAABBVec;
		for (auto&v : BoxVec) {
			auto FixedBoxPtr = dynamic_pointer_cast<Barricade>(v.lock());
			if (FixedBoxPtr) {
				auto ColPtr = FixedBoxPtr->GetComponent<CollisionSphere>();
				//�{�b�N�X�̏Փ˔��肩���b�s���O����AABB���擾���ĕۑ�
				ObjectsAABBVec.push_back(ColPtr->GetSphere().GetWrappedAABB());
			}
		}
		//�Z���z�񂩂�Z���X�L����
		for (auto&v : CellVec) {
			for (auto&v2 : v) {
				for (auto&vObj : ObjectsAABBVec) {
					if (HitTest::AABB_AABB_NOT_EQUAL(v2.m_PieceRange, vObj)) {
						// �{�b�N�X��ABB��NOT_EQUAL�ŏՓ˔���
						v2.m_Cost = -1;
						break;
					}
				}
			}
		}
	}
	//�v���C���[�̍쐬
	void MainStage::CreatePlayer() {
		//�v���[���[�̍쐬
		auto ptrPlayer = AddGameObject<Player>();
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
		CreateSharedObjectGroup(L"FireSphereGroup");

		// �v���C���[�i�X�|�b�g���C�g�j�̍쐬
		auto spotlight1 = AddGameObject<Spotlight>(Vec3(1.5f, 1.5f, 1.5f), Vec3(XM_PIDIV2, 0.0f, 0.0f), Vec3(0.0f, 0.01f, 0.0f));
		SetSharedGameObject(L"Spotlight", spotlight1);

		// �X�|�b�g���C�g�̌����̍쐬
		AddGameObject<SpotLightRay>(Vec3(2, 2, 2), Vec3(0, 0, 0), Vec3(0, 1.01f, 0));
	}
	
	// Wave�̉摜�̍쐬
	void MainStage::CreateWave() {
		auto WM = WaveManager::getInstance();
		auto GM = GameManager::getInstance();

		int waveNum = WM->GetWaveNum();
		int seasonNum = GM->GetStageNumber();

		wstring seasonArr[] = { L"Spring",L"Summer",L"Autumn",L"Winter" };
		// wave�̉摜�̖��O����
		wstring fileName = seasonArr[seasonNum - 1] + L"Wave" + to_wstring(waveNum) + L".png";
		// wave�\������X�v���C�g�\��
		AddGameObject<WaveSprite>(fileName, Vec2(0, 0));
		// wave�X�V
		GetSharedGameObject<NowWaveSprite>(L"WaveUI")->SetWaveNumber(fileName);

		waveVec = WM->GetStageDate();
	}

	void MainStage::CreateEnemy(float time) {

		auto WM = WaveManager::getInstance();

		auto ptrCellmap = GetSharedGameObject<StageCellMap>(L"StageCellMap");
		
		bool waveCreated = true;

		bool enemyCreate = false;

		for (auto i = 0; i < waveVec[0].size(); i++) {
			EnemyParameter *ep = NULL;
			ep = &waveVec[0][i];
			// �܂�����Ă��Ȃ�������
			if (!ep->created) {
				// wave���n�܂��Ĉ�莞�Ԃ����Ă�����
				if (ep->spawnTime <= time) {
					AddGameObject<NormalEnemy>(ep->scale, ep->rotation, ep->position, ptrCellmap, ep->captainNumber);
					GameManager::getInstance()->AddEnemyCount();
					ep->created = true;
					enemyCreate = true;
				}
				waveCreated = false;
			}
		}
		for (auto i = 0; i < waveVec[1].size(); i++) {
			EnemyParameter *ep = NULL;
			ep = &waveVec[1][i];
			if (!ep->created) {
				if (ep->spawnTime <= time) {
					AddGameObject<SwimwearEnemy>(ep->scale, ep->rotation, ep->position, ptrCellmap, ep->captainNumber);
					GameManager::getInstance()->AddEnemyCount();
					ep->created = true;
					enemyCreate = true;
				}
				waveCreated = false;
			}
		}
		for (auto i = 0; i < waveVec[2].size(); i++) {
			EnemyParameter *ep = NULL;
			ep = &waveVec[2][i];
			if (!ep->created) {
				if (ep->spawnTime <= time) {
					AddGameObject<ShieldEnemy>(ep->scale, ep->rotation, ep->position, ptrCellmap, ep->captainNumber);
					GameManager::getInstance()->AddEnemyCount();
					ep->created = true;
					enemyCreate = true;
				}
				waveCreated = false;
			}
		}
		for (auto i = 0; i < waveVec[3].size(); i++) {
			EnemyParameter *ep = NULL;
			ep = &waveVec[3][i];
			if (!ep->created) {
				if (ep->spawnTime <= time) {
					AddGameObject<HammerEnemy>(ep->scale, ep->rotation, ep->position, ptrCellmap);
					GameManager::getInstance()->AddEnemyCount();
					ep->created = true;
					enemyCreate = true;
				}
				waveCreated = false;
			}
		}
		for (auto i = 0; i < waveVec[4].size(); i++) {
			EnemyParameter *ep = NULL;
			ep = &waveVec[4][i];
			if (!ep->created) {
				if (ep->spawnTime <= time) {
					AddGameObject<WorkEnemy>(ep->scale, ep->rotation, ep->position, ptrCellmap, ep->captainNumber);
					GameManager::getInstance()->AddEnemyCount();
					ep->created = true;
					enemyCreate = true;
				}
				waveCreated = false;
			}
		}
		for (auto i = 0; i < waveVec[5].size(); i++) {
			EnemyParameter *ep = NULL;
			ep = &waveVec[5][i];
			if (!ep->created) {
				if (ep->spawnTime <= time) {
					AddGameObject<CaptainEnemy>(ep->scale, ep->rotation, ep->position, ptrCellmap, ep->captainNumber);
					GameManager::getInstance()->AddEnemyCount();
					ep->created = true;
					enemyCreate = true;
				}
				waveCreated = false;
			}
		}
		for (auto i = 0; i < waveVec[6].size(); i++) {
			EnemyParameter *ep = NULL;
			ep = &waveVec[6][i];
			if (!ep->created) {
				if (ep->spawnTime <= time) {
					AddGameObject<FastEnemy>(ep->scale, ep->rotation, ep->position, ptrCellmap, ep->captainNumber);
					GameManager::getInstance()->AddEnemyCount();
					ep->created = true;
					enemyCreate = true;
				}
				waveCreated = false;
			}
		}

		// ���ׂẴG�l�~�[���o���I����Ă�����
		if (waveCreated) {
			m_WaveCreated = waveCreated;
		}

		if (enemyCreate) {
			// ���̃^�[���ɃG�l�~�[����̂ł���������Ă�����
			App::GetApp()->GetXAudio2Manager()->Start(L"spawn.wav", 1, 0.4f);
		}
	}

	void MainStage::CreateEffect() {
		//���񂾂Ƃ��̃G�t�F�N�g
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\zonbikirafix.efk";
		auto ShEfkInterface = GetEfkInterface();
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

		//�X�|�[�����̃G�t�F�N�g
		App::GetApp()->GetDataDirectory(DataDir);
		TestEffectStr = DataDir + L"Effects\\zonbirisporn.efk";
		m_EfkEffect[4] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);

		//�C�₵�����̃G�t�F�N�g
		App::GetApp()->GetDataDirectory(DataDir);
		TestEffectStr = DataDir + L"Effects\\kizetukurukuru.efk";
		m_EfkEffect[5] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);
		
		//clear���̂̃G�t�F�N�g
		App::GetApp()->GetDataDirectory(DataDir);
		TestEffectStr = DataDir + L"Effects\\hanabi.efk";
		m_EfkEffect[6] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);

	}

	void MainStage::OnCreate() {
		try {			
			GameManager::getInstance()->ResetMainStage();
			WaveManager::getInstance()->ResetWaveNum();

			// ���C��BGM�̍Đ�
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"MainBGM.wav", XAUDIO2_LOOP_INFINITE, 0.2f);

			// �ǂݍ���Xml�t�@�C�����w��
			wstring dataDir;
			App::GetApp()->GetDataDirectory(dataDir);
			// �I������Ă���X�e�[�W�ԍ��ɂ���ēǂݍ���xml��ύX����
			switch (GameManager::getInstance()->GetStageNumber())
			{
			case 1:
				// Easy
				m_stageXmlPath = dataDir + L"Stage\\stage1.xml";
				break;
			case 2:
				// Nomal
				m_stageXmlPath = dataDir + L"Stage\\stage2.xml";
				break;
			case 3:
				// Hard
				m_stageXmlPath = dataDir + L"Stage\\stage3.xml";
				break;
			case 4:
				// Extra
				m_stageXmlPath = dataDir + L"Stage\\stage4.xml";
				break;
			default:
				break;
			}

			//�G�t�F�N�g�쐬
			m_EfkInterface = ObjectFactory::Create<EfkInterface>();

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			//UI�̍쐬
			CreateUI();

			// �M�~�b�N�̍쐬
			CreateGimmick();

			//�Z���}�b�v�̍쐬
			CreateStageCellMap();

			// ���̍쐬
			CreateFloor();

			// �ǂ̍쐬
			CreateWall();

			// �v���C���[�̍쐬
			CreatePlayer();

			// �G�̍쐬
			CreateWave();

			//�G�t�F�N�g�쐬
			CreateEffect();

			//���ׂč��I���Ă���t�F�[�h�C��
			//�t�F�[�h�C������I�u�W�F�N�g����
			AddGameObject<FadeStarSprite>(FadeType::FadeIn);
			
		}
		catch (...) {
			throw;
		}
	}

	void MainStage::ChangePause(int num) {
		for (int i = 0; i < 3; i++) {
			shared_ptr<PauseSprite> shptr = m_SpVec[i].lock();
			if (shptr) {
				if (i == num) {
					shptr->Akarusa(true);
				}
				else {
					shptr->Akarusa(false);
					shptr->GetComponent<PCTSpriteDraw>()->SetDiffuse(Col4(1, 1, 1, 0.5f));
				}
			}
		}
	}

	void MainStage::OnUpdate() {

		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];

		{ //���Z�b�g�{�^��
			if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_START && cntlVec.wPressedButtons & XINPUT_GAMEPAD_BACK && FadeSwitch == true) {
				FadeSwitch = false;
				//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTestStage");
				AddGameObject<FadeStarSprite>(FadeType::FadeOut, L"ToTitleStage");
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Stop(m_BGM);
			}
		}

		if (!GameManager::getInstance()->GetFinishActive()) {

			if (cntlVec.bConnected)
			{
				if (m_Pause) {
					//1��X�e�B�b�N�|������߂��܂Ń��b�N����
					if (!m_cntlrock)
					{
						//�X�e�B�b�N�����ɂ����Ƃ��ɓ���
						if (cntlVec.fThumbLY <= -0.8)
						{
							PauseSelect++;
							if (PauseSelect == 3) {
								PauseSelect = 0;
								//ChangePause(PauseSelect);
							}
							m_cntlrock = true;
							ChangePause(PauseSelect);
							App::GetApp()->GetXAudio2Manager()->Start(L"CursorMove.wav", 0, 0.5f);

						}
						//�X�e�B�b�N����ɂ����Ƃ��ɓ���
						else if (cntlVec.fThumbLY >= 0.8f)
						{
							PauseSelect--;
							if (PauseSelect == -1) {
								PauseSelect = 2;
								//ChangePause(PauseSelect);

							}
							m_cntlrock = true;
							ChangePause(PauseSelect);
							App::GetApp()->GetXAudio2Manager()->Start(L"CursorMove.wav", 0, 0.5f);
						}
					}
					else
					{
						//�X�e�B�b�N��߂�
						if (cntlVec.fThumbLY < 0.8f && cntlVec.fThumbLY > -0.8f)
						{
							m_cntlrock = false;
						}
					}
				}
			}


			switch (PauseSelect) {
				// �Q�[���ɖ߂�
			case 0:
				if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_A) {
					auto vec = GetGameObjectVec();
					if (m_Pause) {
						App::GetApp()->GetXAudio2Manager()->Start(L"Button.wav", 0, 0.5f);
						for (auto v : vec) {
							v->SetUpdateActive(true);
							if (v->FindTag(L"PauseMenu")) {
								// �|�[�Y���j���[������
								v->SetDrawActive(false);
							}
						}
						m_Pause = false;
					}
				}
				break;
				// �Z���N�g��
			case 1:
				if ((cntlVec.wPressedButtons & XINPUT_GAMEPAD_A) && !m_PauseFade)
				{
					if (m_Pause) {
						App::GetApp()->GetXAudio2Manager()->Start(L"Button.wav", 0, 0.5f);
						auto XAPtr = App::GetApp()->GetXAudio2Manager();
						XAPtr->Stop(m_BGM);
						AddGameObject<FadeStarSprite>(FadeType::FadeOut, L"ToSelectStage");
						m_PauseFade = true;
					}
				}
				break;
				// �^�C�g����
			case 2:

				if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_A)
				{
					if (m_Pause) {
						App::GetApp()->GetXAudio2Manager()->Start(L"Button.wav", 0, 0.5f);
						auto XAPtr = App::GetApp()->GetXAudio2Manager();
						XAPtr->Stop(m_BGM);
						AddGameObject<FadeStarSprite>(FadeType::FadeOut, L"ToTitleStage");
						m_PauseFade = true;
					}
				}
			}


			if ((cntlVec.wPressedButtons & XINPUT_GAMEPAD_START) && !m_PauseFade) {
				auto vec = GetGameObjectVec();
				if (m_Pause) {
					App::GetApp()->GetXAudio2Manager()->Start(L"Button.wav", 0, 0.5f);
					for (auto v : vec) {
						v->SetUpdateActive(true);
						if (v->FindTag(L"PauseMenu")) {
							// �|�[�Y���j���[������
							v->SetDrawActive(false);
						}
					}
					m_Pause = false;
				}
				else {
					for (auto v : vec) {
						// ��O�̓o�^
						if (!v->FindTag(L"Fade")) {
							v->SetUpdateActive(false);
						}
						if (v->FindTag(L"PauseMenu")) {
							// �|�[�Y���j���[���o��
							v->SetDrawActive(true);
						}
					}
					m_Pause = true;
				}

			}


			// �ŏ��̃J�����̈ړ����I�������
			//if (m_CameraObject->GetFinish) {
			//	GameManager::getInstance()->SetStartActive(true);
			//}




			auto WM = WaveManager::getInstance();
			// wave�̃G�l�~�[�����ׂďo�����Ă�����`�F�b�N
			if (m_WaveCreated) {
				// �G�̐���0�ɂȂ����玟��wave�ɂ����ށ@
				if (GameManager::getInstance()->GetEnemyCount() <= 0) {
					// ����wave���ŏIwave�Ȃ�
					if (WaveManager::getInstance()->GetMaxWave() == WaveManager::getInstance()->GetWaveNum() && !WaveManager::getInstance()->IsClear()) {
						// �N���A����
						WaveManager::getInstance()->SetClear(true);
						GameManager::getInstance()->SetFinishActive(true);


						m_EfkPlay[6]=ObjectFactory::Create<EfkPlay>(m_EfkEffect[6],Vec3(0,0,0));

						auto XAPtr = App::GetApp()->GetXAudio2Manager();
						XAPtr->Stop(m_BGM);

						// ���ł鑺�l���������@
						AddGameObject<MainStageHuman>(Vec3(3, 0.5f, -8));
						AddGameObject<MainStageHuman>(Vec3(-3, 0.5f, -8));
						AddGameObject<MainStageHuman>(Vec3(5, 0.5f, -8));
						AddGameObject<MainStageHuman>(Vec3(-5, 0.5f, -8));

						App::GetApp()->GetXAudio2Manager()->Start(L"Fanfare3.wav", 0, 0.5f);
					}
					// �ŏIWave�łȂ��Ȃ�
					else {
						// ����wave�Ɉړ�
						WaveManager::getInstance()->AddWaveNum();
						// wave�ɉ������G�𐶐�
						CreateWave();
						// Wave�̓G�����ɗp����ϐ�������
						m_WaveTime = 0.0f;
						m_WaveCreated = false;
					}
				}
			}
		}


		auto PtrMultiLight = CreateLight<MultiLight>();
		PtrMultiLight->SetDefaultLighting();
		auto lt = PtrMultiLight->GetLight(2);
		lt.SetPositionToDirectional(0, 5.0f, -5.0f);
		PtrMultiLight->SetLight(2, lt);

		// wall��Hp��0�ɂȂ����̂� �Q�[���I�[�o�[
		if (GameManager::getInstance()->GetWallHp() <= 0) {
			if (m_GameOverTime == 0) {
				// �ǂ������ꗎ���鉹�ǉ�
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Stop(m_BGM);
				m_BGM = XAPtr->Start(L"WallBreak.wav", XAUDIO2_NO_LOOP_REGION, 0.3f);
			}
			// �I��������Ƃ�`����
			GameManager::getInstance()->SetFinishActive(true);
			m_GameOverTime += App::GetApp()->GetElapsedTime();

			auto gameobjectVec = GetGameObjectVec();
			for (auto& object : gameobjectVec)
			{
				if (object->FindTag(L"WallUnit"))
				{
					dynamic_pointer_cast<WallUnit>(object)->WallUnitDown();
				}
			}


			if (m_GameOverTime > 2.5f) {
				//�@�Q�[���I�[�o�[����
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Stop(m_BGM);
				AddGameObject<FadeStarSprite>(FadeType::FadeOut, L"ToGameoverStage");
				m_GameOverTime = -10;
			}
		}

		static float time = 0;
		time += App::GetApp()->GetElapsedTime();
		if (time > 0.5f) {
			time = 0.0f;


			auto camera = GetView()->GetTargetCamera();
			auto cameraPos = camera->GetEye();
			cameraPos.y -= 1;
			cameraPos.z += 1;
			AddGameObject<EffectMove>(Vec3(0.5f, 0.5f, 0.5f), Vec3(0.0f, 0.0f, 0.0f), cameraPos);
		}

		if (!m_Pause) {
			// �G�t�F�N�g�̍X�V
			m_EfkInterface->OnUpdate();
			m_WaveTime += App::GetApp()->GetElapsedTime();
			// ����Wave�̃G�l�~�[����ɍ�葱����
			CreateEnemy(m_WaveTime);

		}

		if (WaveManager::getInstance()->IsClear()) {
			// �N���A�������̉��A����
			m_GameClearTime += App::GetApp()->GetElapsedTime();


			if (m_GameClearTime > 5.0f) {
				AddGameObject<FadeStarSprite>(FadeType::FadeOut, L"ToClearStage");

				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Stop(m_BGM);
				m_GameClearTime = -10;
			}

		}

	}
	//OnUpdatefin

	// �`��
	void MainStage::OnDraw() {
		auto& camera = GetView()->GetTargetCamera();
		m_EfkInterface->SetViewProj(camera->GetViewMatrix(), camera->GetProjMatrix());
		m_EfkInterface->OnDraw();
	}

	void MainStage::UpdateStage() {
		//�ǉ��E�폜�܂��I�u�W�F�N�g�̒ǉ��ƍ폜
		SetWaitToObjectVec();
		//Transform�R���|�[�l���g�̒l���o�b�N�A�b�v�ɃR�s�[
		for (auto ptr : GetGameObjectVec()) {
			if (ptr->IsUpdateActive()) {
				auto ptr2 = ptr->GetComponent<Transform>();
				ptr2->SetToBefore();
			}
		}
		//�����I�u�W�F�N�g�̃t�H�[�X�̏�����
		//if (IsPhysicsActive()) {
		//	pImpl->m_BasePhysics.InitForce();
		//}
		//�z�u�I�u�W�F�N�g�̍X�V����
		for (auto ptr : GetGameObjectVec()) {
			if (ptr->IsUpdateActive()) {
				ptr->OnUpdate();
			}
		}
		//���g�̍X�V����
		if (IsUpdateActive()) {
			OnUpdate();
		}
		//�����I�u�W�F�N�g�̍X�V
		//if (IsPhysicsActive()) {
		//	pImpl->m_BasePhysics.Update(false);
		//}
		//�z�u�I�u�W�F�N�g�̃R���|�[�l���g�X�V
		for (auto ptr : GetGameObjectVec()) {
			if (ptr->IsUpdateActive()) {
				ptr->ComponentUpdate();
			}
		}
		////�Փ˔���
		UpdateCollision();
		//�z�u�I�u�W�F�N�g�̍X�V�㏈��
		//for (auto ptr : GetGameObjectVec()) {
		//	if (ptr->IsUpdateActive()) {
		//		ptr->OnUpdate2();
		//	}
		//}
		////���g�̍X�V�㏈��
		//if (IsUpdateActive()) {
		//	OnUpdate2();
		//}

		//���g�̃r���[���A�b�v�f�[�g
		auto ViewPtr = GetView(false);
		if (ViewPtr && ViewPtr->IsUpdateActive()) {
			ViewPtr->OnUpdate();
		}
		//�q���X�e�[�W�̍X�V
		//for (auto PtrChileStage : GetChileStageVec()) {
		//	PtrChileStage->UpdateStage();
		//}
	}

	void MainStage::DrawStage() {
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
//end basecross
