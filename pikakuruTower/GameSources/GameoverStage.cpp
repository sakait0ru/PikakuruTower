#include "stdafx.h"
#include "Project.h"

namespace basecross {

	GameoverAnimeSprite::GameoverAnimeSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr,
			textureKey,
			startScale,
			startPos)
	{
	}

	void GameoverAnimeSprite::SetActive(bool Active) {

		auto ptrTrans = GetComponent<Transform>();
		auto scale = ptrTrans->GetScale();
		auto position = ptrTrans->GetPosition();

		if (Active) {
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 1.0));

			//三角を動かす
			position.x += m_MoveX;
			m_QuaX += m_MoveX;

			if (m_QuaX >= m_MaxX) {
				m_MoveX *= -1;
			}
			if (m_QuaX < 0) {
				m_MoveX *= -1;
			}

			ptrTrans->SetPosition(position);

		}
		else {
			//表示を消す
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 0.0));
		}
	}

	//回転させる
	void GameoverAnimeSprite::Rotation(bool Active) {

		if (Active) {		
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 1.0));

			m_Rot += Vec3(0, 0, m_Speed);

			//0から半分まで
			if (m_Rot.z <= 0 && m_Rot.z > -XM_PI) {
				m_Speed *= m_AccelRot;
			}
			//半分から回りきるまで
			else if (m_Rot.z <= -XM_PI && m_Rot.z > -XM_2PI) {
				m_Speed *= m_DecelRot;
			}
			//回りきってから
			else if (m_Rot.z <= -XM_2PI) {
				m_Rot = Vec3(0, 0, 0);
				m_Speed = m_StartSpeed;
			}

			auto ptrTrans = GetComponent<Transform>();
			ptrTrans->SetRotation(m_Rot);

		}
		else {
			//表示を薄くする
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 0.4));

			//角度を0にする
			m_Rot = Vec3(0, 0, 0);
			//回転を止める
			m_Speed = m_StartSpeed;

			auto ptrTrans = GetComponent<Transform>();
			ptrTrans->SetRotation(m_Rot);
		}
	}

	void GameoverAnimeSprite::Transluc(bool Active) {
		if (Active) {
			//表示する
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 1.0));

		}
		else {
			//薄く表示する
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 0.4));

		}
	}

	void GameoverStage::CreateViewLight() {
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

	//スプライトの作成
	void GameoverStage::CreateGameoverSprite() {
		AddGameObject<GameoverSprite>(L"OverBG.png", false,
			Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f));
	}

	//初期化
	void GameoverStage::OnCreate() {
		// メインBGMの再生
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"Gameover.wav", XAUDIO2_LOOP_INFINITE, 0.5f);

		CreateViewLight();
		//スプライトの作成
		CreateGameoverSprite();
		m_SpVec[0] = AddGameObject<GameoverAnimeSprite>(L"GameOver.png", Vec2(1000.0f, 500.0f), Vec2(0.0f, 100.0f));

		m_SpVec[1] = AddGameObject<GameoverAnimeSprite>(L"AgainArrow.png", Vec2(150.0f, 150.0f), Vec2(-225.0f, -200.0f));
		m_SpVec[2] = AddGameObject<GameoverAnimeSprite>(L"AgainText.png", Vec2(150.0f, 150.0f), Vec2(-225.0f, -200.0f));

		m_SpVec[3] = AddGameObject<GameoverAnimeSprite>(L"SelectArrow.png", Vec2(150.0f, 150.0f), Vec2(225.0f, -200.0f));
		m_SpVec[4] = AddGameObject<GameoverAnimeSprite>(L"SelectMap.png", Vec2(150.0f, 150.0f), Vec2(225.0f, -200.0f));
		m_SpVec[5] = AddGameObject<GameoverAnimeSprite>(L"SelectText.png", Vec2(150.0f, 150.0f), Vec2(225.0f, -200.0f));

		m_SpVec[6] = AddGameObject<GameoverAnimeSprite>(L"Trigone.png", Vec2(50.0f, 50.0f), Vec2(-365.0f, -200.0f));
		m_SpVec[7] = AddGameObject<GameoverAnimeSprite>(L"Trigone.png", Vec2(50.0f, 50.0f), Vec2(85.0f, -200.0f));

		m_SpVec[0]->SetDrawActive(true);
		m_SpVec[1]->SetDrawActive(true);
		m_SpVec[2]->SetDrawActive(true);
		m_SpVec[3]->SetDrawActive(true);
		m_SpVec[4]->SetDrawActive(true);
		m_SpVec[5]->SetDrawActive(true);
		m_SpVec[6]->SetDrawActive(true);
		m_SpVec[7]->SetDrawActive(true);

		//フェードインする
		AddGameObject<FadeStarSprite>(FadeType::FadeIn);


	}

	//更新
	void GameoverStage::OnUpdate() {
		{ //リセットボタン
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
			if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_START && cntlVec.wPressedButtons & XINPUT_GAMEPAD_BACK && FadeSwitch == true) {
				FadeSwitch = false;
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			}
		}

		//コントローラチェックして入力があればコマンド呼び出し
		//m_InputHandler.PushHandle(GetThis<GameoverStage>());

		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];

		if (cntlVec.bConnected) {
			if (FadeSwitch == true) {

				//1回スティック倒したら戻すまでロックする
				if (!m_CntrolLock) {

					//スティックを右に倒す
					if (cntlVec.fThumbLX >= 0.8f) {
						m_StageNum++;
						m_CntrolLock = true;
						App::GetApp()->GetXAudio2Manager()->Start(L"CursorMove.wav", 0, 0.5f);
					}
					//スティックを左に倒す
					else if (cntlVec.fThumbLX <= -0.8f) {
						m_StageNum--;
						m_CntrolLock = true;
						App::GetApp()->GetXAudio2Manager()->Start(L"CursorMove.wav", 0, 0.5f);
					}
				}
				else {
					//スティックを戻す
					if (cntlVec.fThumbLX < 0.8f && cntlVec.fThumbLX > -0.8f) {
						m_CntrolLock = false;
						PushTime = 0;
						PushTimeEnd = PushTimeEndS;
					}
				}

				//スティックを倒し続けた場合の処理
				if (cntlVec.fThumbLX >= 0.8f) {
					//次の選択をする間隔が短くなっていく
					PushTime += 1;
					PushTimeEnd *= Accel;
				}
				else if (cntlVec.fThumbLX <= -0.8f) {
					PushTime += 1;
					PushTimeEnd *= Accel;
				}

				//PushTimeEndまでいったらスティックのロックを解除
				if (PushTime >= PushTimeEnd) {
					m_CntrolLock = false;
					PushTime = 0;
				}
				//ある程度速くなったら最速値にする
				if (PushTimeEnd <= 17) {
					PushTimeEnd = PushTimeEndMax;
				}
			}

			if (m_StageNum == 0) {
				m_SpVec[1]->Rotation(true);
				m_SpVec[2]->Transluc(true);

				m_SpVec[3]->Rotation(false);
				m_SpVec[4]->Transluc(false);
				m_SpVec[5]->Transluc(false);

				m_SpVec[6]->SetActive(true);
				m_SpVec[7]->SetActive(false);
			}
			else if (m_StageNum == 1) {
				m_SpVec[1]->Rotation(false);
				m_SpVec[2]->Transluc(false);

				m_SpVec[3]->Rotation(true);
				m_SpVec[4]->Transluc(true);
				m_SpVec[5]->Transluc(true);

				m_SpVec[6]->SetActive(false);
				m_SpVec[7]->SetActive(true);

			}

			if (m_StageNum == 2) {
				m_StageNum = 0;
			}
			else if (m_StageNum == -1) {
				m_StageNum = 1;
			}

			if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_A && FadeSwitch == true) {
				FadeSwitch = false;
				if (m_StageNum == 0) {
					App::GetApp()->GetXAudio2Manager()->Start(L"Button.wav", 0, 0.5f);
					auto XAPtr = App::GetApp()->GetXAudio2Manager();
					XAPtr->Stop(m_BGM);
					AddGameObject<FadeStarSprite>(FadeType::FadeOut, L"ToMainStage");
				}
				else if (m_StageNum == 1) {
					App::GetApp()->GetXAudio2Manager()->Start(L"Button.wav", 0, 0.5f);
					auto XAPtr = App::GetApp()->GetXAudio2Manager();
					XAPtr->Stop(m_BGM);
					AddGameObject<FadeStarSprite>(FadeType::FadeOut, L"ToSelectStage");
				}
			}
		}

	}

	//Bボタン
	void GameoverStage::OnPushB() {
	}

	GameoverSprite::GameoverSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos)
	{}

	GameoverSprite::~GameoverSprite() {}
	void GameoverSprite::OnCreate() {
		float HelfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_TextureKey);
	}

}