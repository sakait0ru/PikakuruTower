/*!

@file GameStage.cpp

@brief �Q�[���X�e�[�W����

*/



#include "stdafx.h"
#include "Project.h"


namespace basecross {
	AnimeSprite::AnimeSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr,
			textureKey,
			startScale,
			startPos)

	{
	}
	void AnimeSprite::OnUpdate() {

	}


	//--------------------------------------------------------------------------------------
	//	���邢����\������X�v���C�g
	//--------------------------------------------------------------------------------------
	SelectSpotSprite::SelectSpotSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{
	}
	void SelectSpotSprite::OnCreate() {
		Sprite::OnCreate();
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 0.6f));
	}
	// �X�V
	void SelectSpotSprite::OnUpdate() {
		// ���̃I�u�W�F�N�g��Transform���擾
		auto ptrTrans = GetComponent<Transform>();
		// ���̃I�u�W�F�N�g�̈ʒu���擾
		auto pos = ptrTrans->GetPosition();

		// �z�u���Ă���X�e�[�W����A���I�����Ă���X�e�[�W�ԍ����擾
		auto stageNum = GetTypeStage<SelectStage>()->GetStageNum();
		// �z�u���Ă���X�e�[�W����A�X�e�[�W�X�v���C�g�̔z����擾
		auto spVec = GetTypeStage<SelectStage>()->GetSpVec();
		// �X�e�[�W�ԍ����獡�I�����Ă���X�e�[�W�X�v���C�g�����
		auto stageSprite = spVec[++stageNum];
		// ���肵���X�v���C�g�̈ʒu���擾
		auto nowSpritePos = stageSprite->GetComponent<Transform>()->GetPosition();

		// �X�e�[�W�X�v���C�g�̈ʒu���玩���̈ʒu�������ċ��������߂�
		auto dis = nowSpritePos - pos;
		// �ړ��ʂ��v�Z
		float moveX = dis.x / 10.0f;
		float moveY = dis.y / 10.0f;

		float Pickdis = 7.0f;

		if (moveY < Pickdis && moveY >= 0.0f) {
			SelectSpotFlag = true;
		}
		else if (moveY > -Pickdis && moveY <= 0.0f) {
			SelectSpotFlag = true;
		}
		else {
			SelectSpotFlag = false;
		}

		// �ʒu�Ɉړ��ʂ𑫂�
		pos.x += moveX;
		pos.y += moveY;

		// �ʒu���Z�b�g
		ptrTrans->SetPosition(pos);
	}

	//--------------------------------------------------------------------------------------
	//	�Z���N�g�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	void SelectStage::CreateViewLight() {

		auto PtrView = CreateView<SingleView>();

		//�r���[�̃J�����̐ݒ�

		auto PtrCamera = ObjectFactory::Create<Camera>();

		PtrView->SetCamera(PtrCamera);

		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));

		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));

		//�}���`���C�g�̍쐬

		auto PtrMultiLight = CreateLight<MultiLight>();

		//�f�t�H���g�̃��C�e�B���O���w��

		PtrMultiLight->SetDefaultLighting();

	}

	//UI�̍쐬
	void SelectStage::CreateUI() {
		// �u�X�e�[�W�I���v�̃X�v���C�g�쐬
		AddGameObject<Sprite>(L"SelectToStageButton.png", Vec2(512.0f * 0.8f, 128.0f * 0.8f), Vec2(435, -336));
		// �u�^�C�g���ɖ߂�v�̃X�v���C�g�쐬
		AddGameObject<Sprite>(L"SelectToTitleButton.png", Vec2(512.0f * 0.8f, 128.0f * 0.8f), Vec2(-435, -336));
	}

	//������

	void SelectStage::OnCreate() {

		CreateViewLight();
		// ���C��BGM�̍Đ�
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"TitleBGM.wav", XAUDIO2_LOOP_INFINITE, 0.5f);

		//�t�F�[�h�C������		
		AddGameObject<FadeStarSprite>(FadeType::FadeIn);

		// �w�i�𐶐�
		m_SpVec[0] = AddGameObject<AnimeSprite>(L"SelectBG.png", Vec2(2560.0f, 800.0f), Vec2(640.0f, 0.0f));
		// ��Փx�̃X�v���C�g�𐶐�
		m_SpVec[1] = AddGameObject<AnimeSprite>(L"Easy.png", Vec2(773.0f * 0.4, 773.0f * 0.4), Vec2(-300.0f, 50.0f));
		m_SpVec[2] = AddGameObject<AnimeSprite>(L"Normal.png", Vec2(1012.0f * 0.4, 1012.0f * 0.4), Vec2(0.0f, -200.0f));
		m_SpVec[3] = AddGameObject<AnimeSprite>(L"Hard.png", Vec2(863.0f * 0.4, 863.0f * 0.4), Vec2(375.0f, 25.0f));
		m_SpVec[4] = AddGameObject<AnimeSprite>(L"Extra.png", Vec2(863.0f * 0.4, 863.0f * 0.4), Vec2(1280.0f, 0.0f));

		m_SpotSprite = AddGameObject<SelectSpotSprite>(L"NightMaskSelect.png", Vec2(3840.0f * 1.6, 1920.0f * 1.6), Vec2(-300.0f, 0.0f));

		// �X�e�[�W�Z���N�g�̉摜����
		auto buttonSprite = AddGameObject<Sprite>(L"StageSelect.png",
			Vec2(2211.0f / 3.0f, 629.0f / 3.0f),
			Vec2(0.0f, 275.0f));
		buttonSprite->SetDrawLayer(11);


		m_SpVec[0]->SetDrawActive(true);
		m_SpVec[1]->SetDrawActive(true);
		m_SpVec[2]->SetDrawActive(true);
		m_SpVec[3]->SetDrawActive(true);
		m_SpVec[4]->SetDrawActive(true);

		m_RTriSprite = AddGameObject<SelectTriMoveSprite>(L"RightArrowfix.png", Vec2(50.0f, 50.0f), Vec2(-480.0f, 0));
		m_LTriSprite = AddGameObject<SelectTriMoveSprite>(L"LeftArrowfix.png", Vec2(50.0f, 50.0f), Vec2(570.0f, 0));

		// UI�̍쐬
		CreateUI();
	}

	//�X�V

	void SelectStage::OnUpdate() {

		{ //���Z�b�g�{�^��
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
			if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_START && cntlVec.wPressedButtons & XINPUT_GAMEPAD_BACK && m_FadeSwitch == true) {
				m_FadeSwitch = false;
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			}
		}

		bool SelectSpotFlag = m_SpotSprite->GetSelectSpotFlag();

		// �I��ł���X�e�[�W��Extra�Ȃ��ʂ��E�Ɉړ�����
		if (m_StageNum == 3) {

			float elapsedTime = App::GetApp()->GetElapsedTime();
			m_TotalTime += elapsedTime;


			for (int i = 0; i < 5; i++) {
				auto ptrTrans = m_SpVec[i]->GetComponent<Transform>();
				Easing<Vec3> easing;

				Vec3 startPos = m_SpVec[i]->GetStartPos();
				Vec3 endPos = startPos;
				endPos.x -= 1280;
				auto tgtPos = easing.EaseOut(EasingType::Sinusoidal, startPos, endPos, m_TotalTime, m_MoveTime);
				ptrTrans->SetPosition(tgtPos);
			}
			if (m_TotalTime >= m_MoveTime) {
				m_TotalTime = m_MoveTime;
				SelectSpotFlag = true;
			}
			else {
				SelectSpotFlag = false;
			}

		}
		else {
			//�O���G�N�X�g���Ȃ�
			if (m_Extra) {
				float elapsedTime = App::GetApp()->GetElapsedTime();
				m_TotalTime += elapsedTime;

				// �I��ł�̂�Extra�ȊO�̎�
				for (int i = 0; i < 5; i++) {
					auto ptrTrans = m_SpVec[i]->GetComponent<Transform>();
					Easing<Vec3> easing;

					Vec3 startPos = m_SpVec[i]->GetStartPos();
					Vec3 endPos = startPos;
					endPos.x -= 1280;
					auto tgtPos = easing.EaseOut(EasingType::Sinusoidal, endPos, startPos, m_TotalTime, m_MoveTime);
					ptrTrans->SetPosition(tgtPos);
				}
				if (m_TotalTime >= m_MoveTime) {
					m_TotalTime = m_MoveTime;
					SelectSpotFlag = true;
				}
				else {
					SelectSpotFlag = false;
				}
			}
		}


		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cntlVec.bConnected) {

			//1��X�e�B�b�N�|������߂��܂Ń��b�N����
			if (SelectSpotFlag == true && m_FadeSwitch == true) {
				if (!m_CntrolLock) {


					//�X�e�B�b�N���E�ɓ|��
					if (cntlVec.fThumbLX >= 0.8f) {
						// 3�������炱��ȏ�E�ɓ����Ȃ�
						if (m_StageNum != 3) {
							m_StageNum++;
							m_CntrolLock = true;
							m_TotalTime = 0.0f;
							m_Extra = false;

							//m_Extra = false
							App::GetApp()->GetXAudio2Manager()->Start(L"CursorMove.wav", 0, 0.5f);
						}
					}
					//�X�e�B�b�N�����ɓ|��
					else if (cntlVec.fThumbLX <= -0.8f) {
						if (m_StageNum == 3) {
							m_Extra = true;
						}
						else {
							m_Extra = false;
						}
						m_StageNum--;
						m_CntrolLock = true;
						m_TotalTime = 0.0f;
						App::GetApp()->GetXAudio2Manager()->Start(L"CursorMove.wav", 0, 0.5f);
					}

				}
				else {
					//�X�e�B�b�N��߂�
					if (cntlVec.fThumbLX < 0.8f && cntlVec.fThumbLX > -0.8f) {
						m_CntrolLock = false;
					}
				}
			}

			//���E�̎O�p�̕\��
			if (m_StageNum == 0) {
				m_RTriSprite->RTriMove(false);
				m_LTriSprite->LTriMove(true);
			}
			else if (m_StageNum == 1) {
				m_RTriSprite->RTriMove(true);
				m_LTriSprite->LTriMove(true);
			}
			else if (m_StageNum == 2) {
				m_RTriSprite->RTriMove(true);
				m_LTriSprite->LTriMove(true);
			}
			else if (m_StageNum == 3) {
				m_RTriSprite->RTriMove(true);
				m_LTriSprite->LTriMove(false);
			}

			// ����ݒ�
			if (m_StageNum == 4) {
				m_StageNum = 3;
			}
			else if (m_StageNum == -1) {
				m_StageNum = 0;
			}


			if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_A && SelectSpotFlag == true && m_FadeSwitch == true) {
				m_FadeSwitch = false;
				GameManager::getInstance()->GetStageNumber(m_StageNum + 1);

				App::GetApp()->GetXAudio2Manager()->Start(L"Button.wav", 0, 0.5f);
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Stop(m_BGM);
				AddGameObject<FadeStarSprite>(FadeType::FadeOut, L"ToLoadingStage");
			}

			if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_B && m_FadeSwitch == true) {
				m_FadeSwitch = false;
				GameManager::getInstance()->GetStageNumber(m_StageNum + 1);

				App::GetApp()->GetXAudio2Manager()->Start(L"Button.wav", 0, 0.5f);
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Stop(m_BGM);
				AddGameObject<FadeStarSprite>(FadeType::FadeOut, L"ToLoadingStage");
				AddGameObject<FadeStarSprite>(FadeType::FadeOut, L"ToTitleStage");

			}
		}

	}

	SelectTriMoveSprite::SelectTriMoveSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

	void SelectTriMoveSprite::RTriMove(bool Active) {
		auto ptrTrans = GetComponent<Transform>();
		auto position = ptrTrans->GetPosition();

		//�O�p�𓮂���
		position.x += -m_MoveX;
		m_QuaX += m_MoveX;

		if (m_QuaX >= m_MaxX) {
			m_MoveX *= -1;
		}
		if (m_QuaX < 0) {
			m_MoveX *= -1;
		}


		if (Active) {
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 1.0));
		}
		else {
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 0.0));
		}
		ptrTrans->SetPosition(position);
	}



	void SelectTriMoveSprite::LTriMove(bool Active) {
		auto ptrTrans = GetComponent<Transform>();
		auto position = ptrTrans->GetPosition();


		//�O�p�𓮂���
		position.x += m_MoveX;
		m_QuaX += m_MoveX;

		if (m_QuaX >= m_MaxX) {
			m_MoveX *= -1;
		}
		if (m_QuaX < 0) {
			m_MoveX *= -1;
		}


		if (Active) {
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 1.0));

		}
		else {
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 0.0));
		}
		ptrTrans->SetPosition(position);
	}

	void SelectTriMoveSprite::OnUpdate() {

	}

}

//end basecross