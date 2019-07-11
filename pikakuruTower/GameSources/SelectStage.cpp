/*!

@file GameStage.cpp

@brief ゲームステージ実体

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
	//	明るい所を表示するスプライト
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
	// 更新
	void SelectSpotSprite::OnUpdate() {
		// このオブジェクトのTransformを取得
		auto ptrTrans = GetComponent<Transform>();
		// このオブジェクトの位置を取得
		auto pos = ptrTrans->GetPosition();

		// 配置してあるステージから、今選択しているステージ番号を取得
		auto stageNum = GetTypeStage<SelectStage>()->GetStageNum();
		// 配置してあるステージから、ステージスプライトの配列を取得
		auto spVec = GetTypeStage<SelectStage>()->GetSpVec();
		// ステージ番号から今選択しているステージスプライトを特定
		auto stageSprite = spVec[++stageNum];
		// 特定したスプライトの位置を取得
		auto nowSpritePos = stageSprite->GetComponent<Transform>()->GetPosition();

		// ステージスプライトの位置から自分の位置を引いて距離を求める
		auto dis = nowSpritePos - pos;
		// 移動量を計算
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

		// 位置に移動量を足す
		pos.x += moveX;
		pos.y += moveY;

		// 位置をセット
		ptrTrans->SetPosition(pos);
	}

	//--------------------------------------------------------------------------------------
	//	セレクトステージクラス
	//--------------------------------------------------------------------------------------
	void SelectStage::CreateViewLight() {

		auto PtrView = CreateView<SingleView>();

		//ビューのカメラの設定

		auto PtrCamera = ObjectFactory::Create<Camera>();

		PtrView->SetCamera(PtrCamera);

		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));

		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));

		//マルチライトの作成

		auto PtrMultiLight = CreateLight<MultiLight>();

		//デフォルトのライティングを指定

		PtrMultiLight->SetDefaultLighting();

	}

	//UIの作成
	void SelectStage::CreateUI() {
		// 「ステージ選択」のスプライト作成
		AddGameObject<Sprite>(L"SelectToStageButton.png", Vec2(512.0f * 0.8f, 128.0f * 0.8f), Vec2(435, -336));
		// 「タイトルに戻る」のスプライト作成
		AddGameObject<Sprite>(L"SelectToTitleButton.png", Vec2(512.0f * 0.8f, 128.0f * 0.8f), Vec2(-435, -336));
	}

	//初期化

	void SelectStage::OnCreate() {

		CreateViewLight();
		// メインBGMの再生
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"TitleBGM.wav", XAUDIO2_LOOP_INFINITE, 0.5f);

		//フェードインする		
		AddGameObject<FadeStarSprite>(FadeType::FadeIn);

		// 背景を生成
		m_SpVec[0] = AddGameObject<AnimeSprite>(L"SelectBG.png", Vec2(2560.0f, 800.0f), Vec2(640.0f, 0.0f));
		// 難易度のスプライトを生成
		m_SpVec[1] = AddGameObject<AnimeSprite>(L"Easy.png", Vec2(773.0f * 0.4, 773.0f * 0.4), Vec2(-300.0f, 50.0f));
		m_SpVec[2] = AddGameObject<AnimeSprite>(L"Normal.png", Vec2(1012.0f * 0.4, 1012.0f * 0.4), Vec2(0.0f, -200.0f));
		m_SpVec[3] = AddGameObject<AnimeSprite>(L"Hard.png", Vec2(863.0f * 0.4, 863.0f * 0.4), Vec2(375.0f, 25.0f));
		m_SpVec[4] = AddGameObject<AnimeSprite>(L"Extra.png", Vec2(863.0f * 0.4, 863.0f * 0.4), Vec2(1280.0f, 0.0f));

		m_SpotSprite = AddGameObject<SelectSpotSprite>(L"NightMaskSelect.png", Vec2(3840.0f * 1.6, 1920.0f * 1.6), Vec2(-300.0f, 0.0f));

		// ステージセレクトの画像生成
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

		// UIの作成
		CreateUI();
	}

	//更新

	void SelectStage::OnUpdate() {

		{ //リセットボタン
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
			if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_START && cntlVec.wPressedButtons & XINPUT_GAMEPAD_BACK && m_FadeSwitch == true) {
				m_FadeSwitch = false;
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			}
		}

		bool SelectSpotFlag = m_SpotSprite->GetSelectSpotFlag();

		// 選んでいるステージがExtraなら画面を右に移動する
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
			//前がエクストラなら
			if (m_Extra) {
				float elapsedTime = App::GetApp()->GetElapsedTime();
				m_TotalTime += elapsedTime;

				// 選んでるのがExtra以外の時
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

			//1回スティック倒したら戻すまでロックする
			if (SelectSpotFlag == true && m_FadeSwitch == true) {
				if (!m_CntrolLock) {


					//スティックを右に倒す
					if (cntlVec.fThumbLX >= 0.8f) {
						// 3だったらこれ以上右に動かない
						if (m_StageNum != 3) {
							m_StageNum++;
							m_CntrolLock = true;
							m_TotalTime = 0.0f;
							m_Extra = false;

							//m_Extra = false
							App::GetApp()->GetXAudio2Manager()->Start(L"CursorMove.wav", 0, 0.5f);
						}
					}
					//スティックを左に倒す
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
					//スティックを戻す
					if (cntlVec.fThumbLX < 0.8f && cntlVec.fThumbLX > -0.8f) {
						m_CntrolLock = false;
					}
				}
			}

			//左右の三角の表示
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

			// 上限設定
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

		//三角を動かす
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


		//三角を動かす
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