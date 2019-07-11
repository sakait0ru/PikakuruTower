/*!
@file LoadingStage.cpp
@brief ���[�h���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	���[�h�X�e�[�W
	//--------------------------------------------------------------------------------------
	void LoadingStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 0.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	

	void LoadingStage::CreateLoadingSprite() {
		//�w�i
		AddGameObject<Sprite>(L"BG.png", Vec2(1280.0f, 800.0f), Vec2(0, 0));
		// �ǂݍ��ݒ��E�E�E
		//AddGameObject<LoadingSprite>(L"Loading_1.png", Vec2(600.0f, 150.0f), Vec2(340.0f, -355.0f));
		AddGameObject<LoadingSprite>(L"Loading_1.png", Vec2(512.0f * 0.8f, 128.0f * 0.8f), Vec2(435, -336));
		
		// �����摜
		m_ReadmeSprite = AddGameObject<Sprite>(L"ZombieReadme01.png", Vec2(800.0f, 800.0f), Vec2(250, 10));

		// �������Ă���摜�̌����~����

		// �J�[�\��		
		m_RTriSprite = AddGameObject<TriMoveSprite>(L"RightArrowfix.png", Vec2(50.0f, 50.0f), Vec2(-590.0f, 100));
		m_LTriSprite = AddGameObject<TriMoveSprite>(L"LeftArrowfix.png", Vec2(50.0f, 50.0f), Vec2(-190.0f, 100));

		// �u�Z���N�g�ɖ߂�v�̃X�v���C�g�쐬
		auto selectButton = AddGameObject<Sprite>(L"LoadingToSelectButton.png", Vec2(512.0f * 0.8f, 128.0f * 0.8f), Vec2(-435, -336));
		selectButton->SetDrawLayer(100);
	}

	//������
	void LoadingStage::OnCreate() {
		CreateViewLight();


		// �G�l�~�[�f�[�^��WaveManager�ɓn���Ă��
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

		// wave�ɂ���G�l�~�[�̃f�[�^���폜
		auto WM = WaveManager::getInstance();
		WM->RemoveWaveEnemyData();
		
		// �G�l�~�[�̃f�[�^��������
		GameObjecttXMLBuilder builder;
		builder.Register<EnemyDataLoad>(L"Enemy");
		builder.Build(GetThis<Stage>(), m_stageXmlPath, L"GameStage/Enemy"); 


		// �����̃]���r
		m_Enemy = AddGameObject<LoadingZombie>();
		m_Enemy->SetDrawLayer(90);
		// �X�v���C�g�̍쐬
		CreateLoadingSprite();
		//�t�F�[�h�C������
		AddGameObject<FadeStarSprite>(FadeType::FadeIn);

		// TipsSelect�̓_
		//auto select = AddGameObject<LoadingSelectSprite>(L"selectbar.png",Vec2(1024.0f * 0.1f, 1024.0f * 0.1f),Vec2(-120, -370)); //-120 �`�@160 40   -370 0
		auto select = AddGameObject<LoadingSelectSprite>(L"selectbar.png", Vec2(1024.0f * 0.1f, 1024.0f * 0.1f), Vec2(-530, 100));
		m_SpVec[0] = select;
		select->Akarusa(false);
	
		select = AddGameObject<LoadingSelectSprite>(L"selectbar.png", Vec2(1024.0f * 0.1f, 1024.0f * 0.1f), Vec2(-490, 100));
		m_SpVec[1] = select;	
		select->Akarusa(false);
		
		select = AddGameObject<LoadingSelectSprite>(L"selectbar.png", Vec2(1024.0f * 0.1f, 1024.0f * 0.1f), Vec2(-450, 100));
		m_SpVec[2] = select;
		select->Akarusa(false);

		select = AddGameObject<LoadingSelectSprite>(L"selectbar.png", Vec2(1024.0f * 0.1f, 1024.0f * 0.1f), Vec2(-410, 100));
		m_SpVec[3] = select;
		select->Akarusa(false);

		select = AddGameObject<LoadingSelectSprite>(L"selectbar.png", Vec2(1024.0f * 0.1f, 1024.0f * 0.1f), Vec2(-370, 100));
		m_SpVec[4] = select;
		select->Akarusa(false);

		select = AddGameObject<LoadingSelectSprite>(L"selectbar.png", Vec2(1024.0f * 0.1f, 1024.0f * 0.1f), Vec2(-330, 100));
		m_SpVec[5] = select;
		select->Akarusa(false);

		select = AddGameObject<LoadingSelectSprite>(L"selectbar.png", Vec2(1024.0f * 0.1f, 1024.0f * 0.1f), Vec2(-290, 100));
		m_SpVec[6] = select;
		select->Akarusa(false);

		select = AddGameObject<LoadingSelectSprite>(L"selectbar.png", Vec2(1024.0f * 0.1f, 1024.0f * 0.1f), Vec2(-250, 100));
		m_SpVec[7] = select;
		select->Akarusa(false);


	}



	void LoadingStage::OnUpdate() {
		{ //���Z�b�g�{�^��
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
			if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_START && cntlVec.wPressedButtons & XINPUT_GAMEPAD_BACK && FadeSwitch == true) {
				FadeSwitch = false;
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			}
		}

		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cntlVec.bConnected) {
			if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_B) {
				// Select�ɖ߂�
				AddGameObject<FadeStarSprite>(FadeType::FadeOut, L"ToSelectStage");
			}
		}

		//m_ReadNum�𑝂₷
		if (cntlVec.bConnected) {
			if (m_CntlLock) {
				//�X�e�B�b�N���E�ɓ|��
				if (cntlVec.fThumbLX >= 0.8f) {
					//m_ReadNum���T��菬�����Ƃ��ɓ��� 
					if (m_ReadNum == 7)
					{
						m_ReadNum = -1;
						m_CntlLock = false;
						m_Enemy->SetRot(Vec3(0, 0, 0));
					}
					m_ReadNum += 1;
					m_CntlLock = false;
					App::GetApp()->GetXAudio2Manager()->Start(L"CursorMove.wav", 0, 0.5f);
				}
				//�X�e�B�b�N�����ɓ|��
				else if (cntlVec.fThumbLX <= -0.8f) {
					if (m_ReadNum == 0) {

						m_ReadNum = 8;
						m_CntlLock = false;

						m_Enemy->SetRot(Vec3(0, 0, 0));
					}
					m_ReadNum -= 1;
					m_CntlLock = false;
					App::GetApp()->GetXAudio2Manager()->Start(L"CursorMove.wav", 0, 0.5f);
				}
			}
			else if (cntlVec.fThumbLX < 0.8f && cntlVec.fThumbLX > -0.8f) {
				// ����ȊO�̎�
				m_CntlLock = true;
			}
		}

		switch (m_ReadNum)
		{
		case 0:
			m_ReadmeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"ZombieReadme01.png");//�j�]���r
			m_SpVec[7]->Akarusa(false);
			m_SpVec[0]->Akarusa(true);
			m_SpVec[1]->Akarusa(false);
			break;
		case 1:
			m_ReadmeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"ZombieReadme02.png");//���]���r
			m_SpVec[0]->Akarusa(false);
			m_SpVec[1]->Akarusa(true);
			m_SpVec[2]->Akarusa(false);
			break;
		case 2:
			m_ReadmeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"ZombieReadme03.png");//���]���r
			m_SpVec[1]->Akarusa(false);
			m_SpVec[2]->Akarusa(true);
			m_SpVec[3]->Akarusa(false);
			break;
		case 3:
			m_ReadmeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"ZombieReadme04.png");//����ZombieReadme08.png
			m_SpVec[2]->Akarusa(false);
			m_SpVec[3]->Akarusa(true);
			m_SpVec[4]->Akarusa(false);
			break;
		case 4:
			m_ReadmeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"ZombieReadme05.png");//ZombieReadme07.png�H��]���r
			m_SpVec[3]->Akarusa(false);
			m_SpVec[4]->Akarusa(true);
			m_SpVec[5]->Akarusa(false);
			break;
		case 5:
			m_ReadmeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"ZombieReadme06.png");//�����]���r
			m_SpVec[4]->Akarusa(false);
			m_SpVec[5]->Akarusa(true);
			m_SpVec[6]->Akarusa(false);
			break;
		case 6:
			m_ReadmeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"ZombieReadme07.png");//�򉻂��ꂽ�l��
			m_SpVec[5]->Akarusa(false);
			m_SpVec[6]->Akarusa(true);
			m_SpVec[7]->Akarusa(false);
			break;
		case 7:
			m_ReadmeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"ZombieReadme8.png");//�n���}�[�]���r
			m_SpVec[6]->Akarusa(false);
			m_SpVec[7]->Akarusa(true);
			m_SpVec[0]->Akarusa(false);		
			break;
		default:		
			break;
		}

		m_LTriSprite->LTriMove(true);
		m_RTriSprite->RTriMove(true);
	}

	//--------------------------------------------------------------------------------------
	///	�ǂݍ��ݒ��c�X�v���C�g
	//--------------------------------------------------------------------------------------
	LoadingSprite::LoadingSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

	void LoadingSprite::OnUpdate() {
		// �^���[�����邭���]���ĂāA�ǂݍ��݊��������烉�C�g���Ƃ炵�n�߂�

		SetDrawLayer(100);

		auto ptrDraw = GetComponent<PCTSpriteDraw>();

		auto elapsedTime = App::GetApp()->GetElapsedTime();

		// 3�b��������ǂݍ��݊���
		if (m_ChangeTime > 3.0f) {
			ptrDraw->SetTextureResource(L"LoadingFinisf.png");
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
			//ptrTrans->SetScale(300.0f, 300.0f, 0.0f);

			//ptrTrans->SetScale(scale);

			// A�{�^������������Q�[���X�e�[�W�Ɉڂ�
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
					GetStage()->AddGameObject<FadeStarSprite>(FadeType::FadeOut, L"ToMainStage");
				}
			}


		}
		else {
			m_TotalTime += elapsedTime;
			m_ChangeTime += elapsedTime;

			if (m_ChangeTime > 3.0f) {
				App::GetApp()->GetXAudio2Manager()->Start(L"tugi_Wave.wav", 0, 0.2f);
			}

			if (m_TotalTime < 0.5f) {
				ptrDraw->SetTextureResource(L"Loading_1.png");
			}
			else if (m_TotalTime < 1.0f) {
				ptrDraw->SetTextureResource(L"Loading_2.png");
			}
			else if (m_TotalTime < 1.5f) {
				ptrDraw->SetTextureResource(L"Loading_3.png");
			}
			else {
				m_TotalTime = 0.0f;
			}


			//if (m_TotalTime < 1.0f) {
			//	ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, m_TotalTime));
			//}
			//else {
			//	auto dis = m_TotalTime - 1.0f;
			//	ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f - dis));
			//}
			//if (m_TotalTime > 2.0f) {
			//	m_TotalTime = 0.0f;
			//}

		

		}
	}

	//--------------------------------------------------------------------------------------
	///	�v���r���[�]���r
	//--------------------------------------------------------------------------------------
	LoadingZombie::LoadingZombie(const shared_ptr<Stage>& stagePtr) :
		MyGameObject(stagePtr)
	{
	}

	void LoadingZombie::OnCreate() {

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(Vec3(1,1,1));
		ptrTrans->SetRotation(m_Rot);
		ptrTrans->SetPosition(Vec3(-1.25f,-0.9f,0));


		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(2.5f, 2.5f, 2.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.75f, 0.0f)
		);

		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		// ���b�V���̐ݒ�
		ptrDraw->SetMeshResource(L"Man_Zombie.bbmf");
		// �A�j���[�V�����̐ݒ�
		ptrDraw->AddAnimation(L"Walk", 0, 120, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Walk");

		// �O�ʂɕ\��
		SetDrawLayer(100);
	}

	void LoadingZombie::OnUpdate() {

		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		int readNum = GetTypeStage<LoadingStage>()->GetReadNum();
		switch (readNum)
		{
		case 0:
			ptrDraw->SetMeshResource(L"Man_Zombie.bbmf");
			break;
		case 1:
			ptrDraw->SetMeshResource(L"Woman_Zombie.bbmf");
			break;
		case 2:
			ptrDraw->SetMeshResource(L"Shield_Walk.bbmf");
			break;
		case 3:
			ptrDraw->SetMeshResource(L"Swimwear_Zombie.bbmf");
			break;
		case 4:
			ptrDraw->SetMeshResource(L"Zombie_Work_Walk-Attack.bbmf");//
			break;
		case 5:
			ptrDraw->SetMeshResource(L"Polis_Zombie.bbmf");//
			break;
		case 6:
			ptrDraw->SetMeshResource(L"Hummer_Walk.bbmf");//
			break;
		case 7:
			ptrDraw->SetMeshResource(L"Man_Human.bbmf");//
		default:
			break;
		}

		float elapsedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elapsedTime);

		m_Rot += Vec3(0, 0.01f, 0);
		if (m_Rot.y >= XM_2PI) {
			m_Rot = Vec3(0, 0, 0);
		}
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetRotation(m_Rot);

	}

	//--------------------------------------------------------------------------------------
	///	LoadingSelectSprite��ʗp�̃X�v���C�g
	//--------------------------------------------------------------------------------------
	LoadingSelectSprite::LoadingSelectSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}


	void LoadingSelectSprite::OnCreate() {
		Sprite::OnCreate();
		/*SetDrawLayer(100);
		AddTag(L"PauseMenu");
		SetDrawActive(false);
*/
	}


	
	void LoadingSelectSprite::OnUpdate()
	{
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];


		if (cntlVec.bConnected)
		{
			//1��X�e�B�b�N�|������߂��܂Ń��b�N����
			if (!m_cntlrock)
			{
				
			}
		}

	}

	void LoadingSelectSprite::Akarusa(bool flg)
	{
		//GetComponent<PCTSpriteDraw>()->SetDiffuse(Col4(1, 1, 1, 1.0f));
		if (flg) 
		{
			auto texture = GetComponent<PCTSpriteDraw>();
			texture->SetTextureResource(L"nowselectbar.png");
			auto ptrTrans = GetComponent<Transform>();
			ptrTrans->SetScale(Vec3(1024.0f * 0.04f, 1024.0f * 0.04f,1.0f));
			
		}
		else  {
			GetComponent<PCTSpriteDraw>()->SetTextureResource(L"selectbar.png");
			auto ptrTrans = GetComponent<Transform>();
			ptrTrans->SetScale(Vec3(1024.0f * 0.04f, 1024.0f * 0.04f, 1.0f));


		}
	}


	//--------------------------------------------------------------------------------------
	// �G�l�~�[�̃f�[�^���󂯎��N���X
	//--------------------------------------------------------------------------------------
	EnemyDataLoad::EnemyDataLoad(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode) :
		MyGameObject(stagePtr) 
	{
		// ��������wstring�̕�����Ŏ擾�ł���
		auto scaleStr = XmlDocReader::GetAttribute(pNode, L"Scale");
		auto quatStr = XmlDocReader::GetAttribute(pNode, L"Quat");
		auto posStr = XmlDocReader::GetAttribute(pNode, L"Pos");

		// L"(0.0f,0.0f,0.0f)" �ɂȂ��Ă���̂�"(",")"�����
		scaleStr.pop_back();
		scaleStr.erase(scaleStr.begin());
		quatStr.pop_back();
		quatStr.erase(quatStr.begin());
		posStr.pop_back();
		posStr.erase(posStr.begin());

		//�g�[�N���i�J�����j�̔z��
		vector<wstring> tokens;
		tokens.clear();

		// scaleStr��Vec3�^�ɕϊ�
		Util::WStrToTokenVector(tokens, scaleStr, L',');
		//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
		m_Scale = Vec3(
			(float)_wtof(tokens[0].c_str()),
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str())
		);
		tokens.clear();

		// Quat�ɕϊ�
		Util::WStrToTokenVector(tokens, quatStr, L',');
		m_Quat = Quat(
			(float)_wtof(tokens[0].c_str()),
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str()),
			(float)_wtof(tokens[3].c_str())
		);
		tokens.clear();

		// scaleStr��Vec3�^�ɕϊ�
		Util::WStrToTokenVector(tokens, posStr, L',');
		//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
		m_Position = Vec3(
			(float)_wtof(tokens[0].c_str()),
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str())
		);
		tokens.clear();

		// WaveNum�ǂݍ���
		auto waveNumStr = XmlDocReader::GetAttribute(pNode, L"WaveNum");
		m_WaveNum = (int)_wtof(waveNumStr.c_str());

		// CaptainNum�ǂݍ���
		auto captainNumStr = XmlDocReader::GetAttribute(pNode, L"CaptainNum");
		m_CaptainNum = (int)_wtof(captainNumStr.c_str());

		// SpawnTime�ǂݍ���
		auto spawnTimeStr = XmlDocReader::GetAttribute(pNode, L"SpawnTime");
		m_SpawnTime = (float)_wtof(spawnTimeStr.c_str());

		// EnemyType�ǂݍ���
		auto enemyTypeStr = XmlDocReader::GetAttribute(pNode, L"EnemyType");
		m_EnemyType = (int)_wtof(enemyTypeStr.c_str());
	}

	void EnemyDataLoad::OnCreate() {
		// WaveManager
		auto WM = WaveManager::getInstance();
		
		WM->SetWaveDate(m_Scale, m_Quat, m_Position, m_WaveNum, m_CaptainNum, m_SpawnTime, m_EnemyType);

		// �㏈��
		GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
	}


	TriMoveSprite::TriMoveSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

	void TriMoveSprite::RTriMove(bool Active) {
		auto ptrTrans = GetComponent<Transform>();
		auto position = ptrTrans->GetPosition();

		if (Active) {
			//�O�p�𓮂���
			position.x += -m_MoveX;
			m_QuaX += m_MoveX;

			if (m_QuaX >= m_MaxX) {
				m_MoveX *= -1;
			}
			if (m_QuaX < 0) {
				m_MoveX *= -1;
			}

		}
		else {
		}
		ptrTrans->SetPosition(position);
	}

	void TriMoveSprite::LTriMove(bool Active) {
		auto ptrTrans = GetComponent<Transform>();
		auto position = ptrTrans->GetPosition();

		if (Active) {
			//�O�p�𓮂���
			position.x += m_MoveX;
			m_QuaX += m_MoveX;

			if (m_QuaX >= m_MaxX) {
				m_MoveX *= -1;
			}
			if (m_QuaX < 0) {
				m_MoveX *= -1;
			}

		}
		else {
			
		}
		ptrTrans->SetPosition(position);
	}

	void TriMoveSprite::OnUpdate() {
		//TriMove(true);
	}

}