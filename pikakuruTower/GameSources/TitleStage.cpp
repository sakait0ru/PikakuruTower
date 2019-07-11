#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// タイトルの画像とゲームスタートの画像
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
	// タイトルに使うPlayer
	//--------------------------------------------------------------------------------------
	TitlePlayer::TitlePlayer(const shared_ptr<Stage>& stagePtr) :
		MyGameObject(stagePtr)
	{
	}
	TitlePlayer::TitlePlayer(const shared_ptr<Stage>& stagePtr, const Vec3 & scale, const Vec3 & rotation, const Vec3 & position) :
		MyGameObject(stagePtr)
	{
	}
	//あみ発射装置　= Player
	void TitlePlayer::OnCreate()
	{
		//初期位置などの設定
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(0.55f, 0.75f, 0.55f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(0, 0.525f, -6.1f);
	}


	//--------------------------------------------------------------------------------------
	// タイトルステージ
	//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		//PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		//PtrCamera->SetEye(Vec3(0.0f, 15.0f, -25.0f));
		PtrCamera->SetEye(Vec3(0.0f, 15, -14.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();

	}


	void TitleStage::CreateFloor() {
		AddGameObject<FixedBox>(
			//大きさ(Scale)
			Vec3(55.0f, 1.0f, 55.0f),
			// 回転(Rotation)
			Vec3(0.0f, 0.0f, 0.0f),
			// 位置(Position)
			Vec3(0.0f, -0.5f, 10.0f));
	};

	void TitleStage::CreateTitlePlayer() {
		//プレーヤーの作成
		auto ptrPlayer = AddGameObject<TitlePlayer>();
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
		CreateSharedObjectGroup(L"FireSphereGroup");

		// プレイヤー（スポットライト）の作成
		auto spotlight1 = AddGameObject<Spotlight>(Vec3(1.5f, 1.5f, 1.5f), Vec3(XM_PIDIV2, 0.0f, 0.0f), Vec3(0.0f, 0.01f, 0.0f));
		SetSharedGameObject(L"Spotlight", spotlight1);
	}

	void TitleStage::CreateWall() {

		auto wall = AddGameObject<Wall>(
			Vec3(30.0f, 2.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, -7.5f));
		SetSharedGameObject(L"Wall", wall);

		//タワーの下の部分
		auto towerBody = AddGameObject<TowerUnder>(
			Vec3(3.0f, 3.0f, 3.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.5f, -8.5f));

		// タワーの回転する部分
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

		// 壁制作
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
		//padから入力がなかったら計測
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cntlVec.wReleasedButtons == false && cntlVec.fThumbLX == 0 && cntlVec.fThumbLY == 0) {
			auto elapsedTime = App::GetApp()->GetElapsedTime();
			m_MovieTime += elapsedTime;
		}
	}
	//初期化
	void TitleStage::OnCreate() {
		WaveManager::getInstance()->ResetWaveNum();
		GameManager::getInstance()->ResetMainStage();

		CreateViewLight();

		// メインBGMの再生
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"TitleBGM.wav", XAUDIO2_LOOP_INFINITE, 0.5f);

		//エフェクト作成
		m_EfkInterface = ObjectFactory::Create<EfkInterface>();

		// 「ゲームをおわる」のスプライト作成
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

		// スポットライトの光線の作成
		AddGameObject<SpotLightRay>(Vec3(2, 2, 2), Vec3(0, 0, 0), Vec3(0, 1.01f, 0));



		//フェードの画像の作成
		AddGameObject<FadeStarSprite>(FadeType::FadeIn);

		// 木の生成
		// 読み込むXmlファイルを指定
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		auto stageXmlPath = dataDir + L"Stage\\title.xml";

		GameObjecttXMLBuilder builder;
		builder.Register<Tree>(L"Tree");
		builder.Build(GetThis<Stage>(), stageXmlPath, L"GameStage/Tree");

	}

	//更新
	void TitleStage::OnUpdate() {

		CreateTimer();

		m_EfkInterface->OnUpdate();

		static float a = 0;
		a += App::GetApp()->GetElapsedTime();
		// Gameが始まってから 0.0fたったら、タイトルが降ってくる
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

			// ここにゲームが始まったときの演出を書く
			// カメラ画面の奥を移す
			// ノーマルゾンビがでてくる
			// ゾンビが迫ってくる
			// カメラ手前にもどる
			// たいまつが点火する
			// タワーが回転する
			// タワーが光り始める
			// タワーからスポットライトがでる
			// ゾンビが浄化される
			// 人間になって壁に来る
			
			// ↑のが全部終わったら、タイトルが出てくる
		}




		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cntlVec.bConnected) {

			// 開始時の演出がすべておわっていて　かつ　Aを押したらフェードアウト開始
			if (FadeCount == 0 && cntlVec.wPressedButtons & XINPUT_GAMEPAD_A && FadeSwitch == true) {
				if (!m_Start) {
					FadeSwitch = false;
					auto XAPtr = App::GetApp()->GetXAudio2Manager();
					XAPtr->Stop(m_BGM);

					App::GetApp()->GetXAudio2Manager()->Start(L"Button.wav", 0, 0.5f);

					//点滅のスピードを速くする
					FalseTimeEnd *= FlashingSpeed;
					TrueTimeEnd *= FlashingSpeed;
					DecSwitch += 1.0f;

					if (DecSwitch >= 1.0f) {
						DecTime += 1.0f;                  //ボタンを押してからの時間計測開始               
						if (DecTime >= FlashingTime) {
							m_SpVec[4]->SetActive(false);
							TrueTimePlus = 0.0f;          //点滅しなくなる
							if (DecTime >= FlashingEnd) {
							}
						}
					}

					AddGameObject<FadeStarSprite>(FadeType::FadeOut, L"ToSelectStage");
				}
			}

			// Bを押したらゲームが終わる
			if (FadeCount == 0 && cntlVec.wPressedButtons & XINPUT_GAMEPAD_B && FadeSwitch == true) {
				// ゲームを終わる
				//PostQuitMessage(0);
				//return;
			}

			// 開始の演出が終わっていなかったら終わらせる　待機状態になる
			if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_A && m_Start == true || m_Time >= 28.0f) {
				m_SpVec[1]->PikaDrop(false);
				m_SpVec[2]->KuruDrop(false);
				m_SpVec[3]->StarDrop(false);

				m_Start = false;
			}


			// ゲームスタートの文字表示
			if (m_Start == false) {
				//trueの時
				if (Switch <= 0.0f) {
					FalseTime = 0.0f; //falseの時の時間のリセット
					TrueTime += 1.0f; //時間計測開始
					//一定時間経過して透明にさせる
					if (TrueTime >= TrueTimeEnd) {
						Switch += 1.0f;
						m_SpVec[4]->SetActive(false);
					}
				}
				//falseの時
				else {
					TrueTime = 0.0f; //trueの時の時間のリセット
					FalseTime += TrueTimePlus; //時間計測開始
					//一定時間経過して表示させる
					if (FalseTime >= FalseTimeEnd) {
						Switch += -1.0f;
						m_SpVec[4]->SetActive(true);
					}
				}
			}
		}

		// 30秒経過したらムービー再生する
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
		//レイヤーの取得と設定
		set<int> DrawLayers;
		//Spriteかそうでないかを分離
		for (auto ptr : GetGameObjectVec()) {
			if (ptr->IsDrawActive()) {
				//描画レイヤーに登録
				DrawLayers.insert(ptr->GetDrawLayer());
				//Spriteかその派生クラスなら分離
				if (ptr->GetComponent<SpriteBaseDraw>(false) || ptr->IsSpriteDraw()) {
					m_SpriteVec.push_back(ptr);
				}
				else {
					m_Object3DVec.push_back(ptr);
				}
			}
		}
		//3Dの透明と非透明を分離
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
		//カメラの位置
		bsm::Vec3 CameraEye = PtrCamera->GetEye();
		//透明の3Dオブジェクトをカメラからの距離でソート
		//以下は、オブジェクトを引数に取りboolを返すラムダ式
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

				//3Dノーマルオブジェクトの描画準備
		for (auto ptr : m_Object3DNormalVec) {
			ptr->OnPreDraw();
		}
		//3D透明オブジェクトの描画準備
		//for (auto ptr : m_Object3DAlphaVec) {
		//	ptr->OnPreDraw();
		//}
		//パーティクルの描画準備（透明）
		GetParticleManager(false)->OnPreDraw();
		//パーティクルの描画準備（加算）
		GetParticleManager(true)->OnPreDraw();
		//スプライトオブジェクトの描画準備
		for (auto ptr : m_SpriteVec) {
			ptr->OnPreDraw();
		}

		//--------------------------------------------------------
		//スプライトをZ座標距離でソート
		//以下は、オブジェクトを引数に取りboolを返すラムダ式
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
			//3Dノーマルオブジェクトの描画
			for (auto ptr : m_Object3DNormalVec) {
				if (ptr->GetDrawLayer() == Tgt) {
					ptr->OnDraw();
				}
			}
			//3D透明オブジェクトの描画
			for (auto ptr : m_Object3DAlphaVec) {
				if (ptr->GetDrawLayer() == Tgt) {
					ptr->OnDraw();
				}
			}
			//パーティクルの描画
			//パーティクルマネージャは描画レイヤーごとに初期化されるので
			//毎レイヤー描画する
			//透明処理
			GetParticleManager(false)->OnDraw();
			//加算処理
			GetParticleManager(true)->OnDraw();
		}
		for (auto it = DrawLayers.begin(); it != DrawLayers.end(); it++) {
			int Tgt = *it;

			//スプライトオブジェクトの描画
			for (auto ptr : m_SpriteVec) {
				if (ptr->GetDrawLayer() == Tgt) {
					ptr->OnDraw();
					if (Tgt == 2) {
						//ステージのDraw();
						OnDraw();
					}
				}
			}
		}
		//ワーク用配列のクリア
		//ワーク配列は毎ターンごとに初期化されるが、
		//最大値は減らないので2回目のターン以降は高速に動作する
		m_Object3DVec.clear();
		m_SpriteVec.clear();
		m_Object3DNormalVec.clear();
		m_Object3DAlphaVec.clear();
	}



}





