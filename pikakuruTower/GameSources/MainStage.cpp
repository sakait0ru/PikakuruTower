/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {



	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void MainStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		//PtrCamera->SetEye(Vec3(2.0f, 2.0f, -7.0f));
		//PtrCamera->SetAt(Vec3(-90.0f, -15.0f, 0.0f));
		m_Camera = PtrCamera;
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	//セルマップの作成
	void MainStage::CreateStageCellMap() {
		float  PieceSize = 1.0f;
		auto Ptr = AddGameObject<StageCellMap>(Vec3(-15.0f, 0.0f, -10.0f), PieceSize, 30, 30);
		//セルマップの区画を表示する場合は以下の設定
		//Ptr->SetDrawActive(true);
		//さらにセルのインデックスとコストを表示する場合は以下の設定
		//Ptr->SetCellStringActive(true);
		SetSharedGameObject(L"StageCellMap", Ptr);
		//セルマップへのボックスのコスト設定
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
		// ステージを暗くするマスクの作成
		AddGameObject<NightMaskSprite>(L"NightMask.png", Vec2(2560, 1600), Vec2(0, 0));

		// 背景の赤の奴
		auto sprite = AddGameObject<Sprite>(L"red.png",
			Vec2(275.0f, 30.0f),
			Vec2(-437.0f, -355.0f));
		sprite->SetDrawLayer(11);
		// HPバー
		 AddGameObject<HpGage>(L"green.png",
			Vec2(275.0f, 30.0f),
			Vec2(-575.0f, -355.0f));
		// HPゲージの枠
		sprite = AddGameObject<HpGageFrame>(L"UI0__0509.png",
			Vec2(1380.0f/4.0f, 976.0f/4.0f),
			Vec2(-450.0f, -300.0f));
			//Vec2(-470.0f, -310.0f));
		sprite->SetDrawLayer(11);

		// ライトのオンオフ状態を表示するスプライト
		AddGameObject<RightSuitch>(L"Light_on.png",
			Vec2(110.0f, 160.0f),
			Vec2(350.0f, -325.0f));
		// Aボタンの表示
		auto buttonSprite1 = AddGameObject<Sprite>(L"Abutton.png",
			Vec2(50.0f, 50.0f),
			Vec2(350.0f, -370.0f));
		buttonSprite1->SetDrawLayer(11);
		// LBボタンの表示
		buttonSprite1 = AddGameObject<Sprite>(L"LBbutton.png",
			Vec2(50.0f, 50.0f),
			Vec2(375.0f, -275.0f));
		buttonSprite1->SetDrawLayer(11);


		// 閃光玉のスプライト
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
		// Bボタンの表示
		auto buttonSprite = AddGameObject<Sprite>(L"Bbutton.png",
			Vec2(50.0f,50.0f),
			Vec2(505.0f, -370.0f));
		buttonSprite->SetDrawLayer(11);

		// 右上の今のWave数を表示するスプライト
		auto waveSprite = AddGameObject<NowWaveSprite>(L"SummerWave1.png",
			Vec2(400, 100),
			Vec2(450.0f,350.0f));
		waveSprite->SetDrawLayer(11);
		SetSharedGameObject(L"WaveUI", waveSprite);

		// ポーズ画面の画像生成
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

		// 壁の当たり判定
		auto wall = AddGameObject<Wall>(
			Vec3(30.0f,2.0f, 1.0f),
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

		// 右の狙われる場所
		auto wallTaget = AddGameObject<WallTaget>(
			Vec3(2.0f, 0.9f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(-3.0f, 0.4f, -7.55f));
		SetSharedGameObject(L"WallLeft", wallTaget);

		// 左の狙われる場所
		wallTaget = AddGameObject<WallTaget>(
			Vec3(2.0f, 0.9f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(3.0f, 0.4f, -7.55f));
		SetSharedGameObject(L"WallRight", wallTaget);

		// 壁のメッシュを描画
		for (int i = 0; i < 20; i++) {
			AddGameObject<WallUnit>(
				Vec3(2.0f, 2.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-15.0f + (i * 2), 0.5f, -7.5f));
		}


		
	}

	void MainStage::CreateGimmick() {
		CreateSharedObjectGroup(L"Barricades");
		
		// バリケード
		GameObjecttXMLBuilder builder;
		builder.Register<Barricade>(L"Barricade");
		builder.Build(GetThis<Stage>(), m_stageXmlPath, L"GameStage/Barricade");

		// 沼地
		builder.Register<SlowFloor>(L"SlowFloor");
		builder.Build(GetThis<Stage>(), m_stageXmlPath, L"GameStage/SlowFloor");
	}

	//固定のボックスのコストをセルマップに反映
	void MainStage::SetCellMapCost() {
		//セルマップ内にFixedBoxの情報をセット
		auto PtrCellmap = GetSharedGameObject<StageCellMap>(L"StageCellMap");
		auto BoxGroup = GetSharedObjectGroup(L"Barricades");
		//セルマップからセルの配列を取得
		auto &CellVec = PtrCellmap->GetCellVec();
		//ボックスグループからボックスの配列を取得
		auto &BoxVec = BoxGroup->GetGroupVector();
		vector<AABB>ObjectsAABBVec;
		for (auto&v : BoxVec) {
			auto FixedBoxPtr = dynamic_pointer_cast<Barricade>(v.lock());
			if (FixedBoxPtr) {
				auto ColPtr = FixedBoxPtr->GetComponent<CollisionSphere>();
				//ボックスの衝突判定かラッピングするAABBを取得して保存
				ObjectsAABBVec.push_back(ColPtr->GetSphere().GetWrappedAABB());
			}
		}
		//セル配列からセルスキャン
		for (auto&v : CellVec) {
			for (auto&v2 : v) {
				for (auto&vObj : ObjectsAABBVec) {
					if (HitTest::AABB_AABB_NOT_EQUAL(v2.m_PieceRange, vObj)) {
						// ボックスのABBとNOT_EQUALで衝突判定
						v2.m_Cost = -1;
						break;
					}
				}
			}
		}
	}
	//プレイヤーの作成
	void MainStage::CreatePlayer() {
		//プレーヤーの作成
		auto ptrPlayer = AddGameObject<Player>();
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
		CreateSharedObjectGroup(L"FireSphereGroup");

		// プレイヤー（スポットライト）の作成
		auto spotlight1 = AddGameObject<Spotlight>(Vec3(1.5f, 1.5f, 1.5f), Vec3(XM_PIDIV2, 0.0f, 0.0f), Vec3(0.0f, 0.01f, 0.0f));
		SetSharedGameObject(L"Spotlight", spotlight1);

		// スポットライトの光線の作成
		AddGameObject<SpotLightRay>(Vec3(2, 2, 2), Vec3(0, 0, 0), Vec3(0, 1.01f, 0));
	}
	
	// Waveの画像の作成
	void MainStage::CreateWave() {
		auto WM = WaveManager::getInstance();
		auto GM = GameManager::getInstance();

		int waveNum = WM->GetWaveNum();
		int seasonNum = GM->GetStageNumber();

		wstring seasonArr[] = { L"Spring",L"Summer",L"Autumn",L"Winter" };
		// waveの画像の名前結合
		wstring fileName = seasonArr[seasonNum - 1] + L"Wave" + to_wstring(waveNum) + L".png";
		// wave表示するスプライト表示
		AddGameObject<WaveSprite>(fileName, Vec2(0, 0));
		// wave更新
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
			// まだ作られていなかったら
			if (!ep->created) {
				// waveが始まって一定時間たっていたら
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

		// すべてのエネミーを出し終わっていたら
		if (waveCreated) {
			m_WaveCreated = waveCreated;
		}

		if (enemyCreate) {
			// このターンにエネミーが一体でも生成されていたら
			App::GetApp()->GetXAudio2Manager()->Start(L"spawn.wav", 1, 0.4f);
		}
	}

	void MainStage::CreateEffect() {
		//死んだときのエフェクト
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\zonbikirafix.efk";
		auto ShEfkInterface = GetEfkInterface();
		m_EfkEffect[0] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);

		//人間になるときのエフェクト
		App::GetApp()->GetDataDirectory(DataDir);
		TestEffectStr = DataDir + L"Effects\\zonbiattack.efk";
		m_EfkEffect[1] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);

		//ダメージを受けている時のエフェクト
		App::GetApp()->GetDataDirectory(DataDir);
		TestEffectStr = DataDir + L"Effects\\zonbinowdamage.efk";
		m_EfkEffect[2] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);

		//死んで回復する時のエフェクト
		App::GetApp()->GetDataDirectory(DataDir);
		TestEffectStr = DataDir + L"Effects\\zonbiheal.efk";
		m_EfkEffect[3] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);

		//スポーン時のエフェクト
		App::GetApp()->GetDataDirectory(DataDir);
		TestEffectStr = DataDir + L"Effects\\zonbirisporn.efk";
		m_EfkEffect[4] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);

		//気絶した時のエフェクト
		App::GetApp()->GetDataDirectory(DataDir);
		TestEffectStr = DataDir + L"Effects\\kizetukurukuru.efk";
		m_EfkEffect[5] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);
		
		//clear時ののエフェクト
		App::GetApp()->GetDataDirectory(DataDir);
		TestEffectStr = DataDir + L"Effects\\hanabi.efk";
		m_EfkEffect[6] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);

	}

	void MainStage::OnCreate() {
		try {			
			GameManager::getInstance()->ResetMainStage();
			WaveManager::getInstance()->ResetWaveNum();

			// メインBGMの再生
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"MainBGM.wav", XAUDIO2_LOOP_INFINITE, 0.2f);

			// 読み込むXmlファイルを指定
			wstring dataDir;
			App::GetApp()->GetDataDirectory(dataDir);
			// 選択されているステージ番号によって読み込むxmlを変更する
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

			//エフェクト作成
			m_EfkInterface = ObjectFactory::Create<EfkInterface>();

			//ビューとライトの作成
			CreateViewLight();

			//UIの作成
			CreateUI();

			// ギミックの作成
			CreateGimmick();

			//セルマップの作成
			CreateStageCellMap();

			// 床の作成
			CreateFloor();

			// 壁の作成
			CreateWall();

			// プレイヤーの作成
			CreatePlayer();

			// 敵の作成
			CreateWave();

			//エフェクト作成
			CreateEffect();

			//すべて作り終えてからフェードイン
			//フェードインするオブジェクト生成
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

		{ //リセットボタン
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
					//1回スティック倒したら戻すまでロックする
					if (!m_cntlrock)
					{
						//スティックを下にしたときに入る
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
						//スティックを上にしたときに入る
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
						//スティックを戻す
						if (cntlVec.fThumbLY < 0.8f && cntlVec.fThumbLY > -0.8f)
						{
							m_cntlrock = false;
						}
					}
				}
			}


			switch (PauseSelect) {
				// ゲームに戻る
			case 0:
				if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_A) {
					auto vec = GetGameObjectVec();
					if (m_Pause) {
						App::GetApp()->GetXAudio2Manager()->Start(L"Button.wav", 0, 0.5f);
						for (auto v : vec) {
							v->SetUpdateActive(true);
							if (v->FindTag(L"PauseMenu")) {
								// ポーズメニューを消す
								v->SetDrawActive(false);
							}
						}
						m_Pause = false;
					}
				}
				break;
				// セレクトへ
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
				// タイトルへ
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
							// ポーズメニューを消す
							v->SetDrawActive(false);
						}
					}
					m_Pause = false;
				}
				else {
					for (auto v : vec) {
						// 例外の登録
						if (!v->FindTag(L"Fade")) {
							v->SetUpdateActive(false);
						}
						if (v->FindTag(L"PauseMenu")) {
							// ポーズメニューを出す
							v->SetDrawActive(true);
						}
					}
					m_Pause = true;
				}

			}


			// 最初のカメラの移動が終わったら
			//if (m_CameraObject->GetFinish) {
			//	GameManager::getInstance()->SetStartActive(true);
			//}




			auto WM = WaveManager::getInstance();
			// waveのエネミーがすべて出現していたらチェック
			if (m_WaveCreated) {
				// 敵の数が0になったら次のwaveにすすむ　
				if (GameManager::getInstance()->GetEnemyCount() <= 0) {
					// 今のwaveが最終waveなら
					if (WaveManager::getInstance()->GetMaxWave() == WaveManager::getInstance()->GetWaveNum() && !WaveManager::getInstance()->IsClear()) {
						// クリアする
						WaveManager::getInstance()->SetClear(true);
						GameManager::getInstance()->SetFinishActive(true);


						m_EfkPlay[6]=ObjectFactory::Create<EfkPlay>(m_EfkEffect[6],Vec3(0,0,0));

						auto XAPtr = App::GetApp()->GetXAudio2Manager();
						XAPtr->Stop(m_BGM);

						// 喜んでる村人せいせい　
						AddGameObject<MainStageHuman>(Vec3(3, 0.5f, -8));
						AddGameObject<MainStageHuman>(Vec3(-3, 0.5f, -8));
						AddGameObject<MainStageHuman>(Vec3(5, 0.5f, -8));
						AddGameObject<MainStageHuman>(Vec3(-5, 0.5f, -8));

						App::GetApp()->GetXAudio2Manager()->Start(L"Fanfare3.wav", 0, 0.5f);
					}
					// 最終Waveでないなら
					else {
						// 次のwaveに移動
						WaveManager::getInstance()->AddWaveNum();
						// waveに応じた敵を生成
						CreateWave();
						// Waveの敵生成に用いる変数初期化
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

		// wallのHpが0になったので ゲームオーバー
		if (GameManager::getInstance()->GetWallHp() <= 0) {
			if (m_GameOverTime == 0) {
				// 壁がくずれ落ちる音追加
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Stop(m_BGM);
				m_BGM = XAPtr->Start(L"WallBreak.wav", XAUDIO2_NO_LOOP_REGION, 0.3f);
			}
			// 終わったことを伝える
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
				//　ゲームオーバー処理
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
			// エフェクトの更新
			m_EfkInterface->OnUpdate();
			m_WaveTime += App::GetApp()->GetElapsedTime();
			// 今のWaveのエネミーを常に作り続ける
			CreateEnemy(m_WaveTime);

		}

		if (WaveManager::getInstance()->IsClear()) {
			// クリアした時の音、処理
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

	// 描画
	void MainStage::OnDraw() {
		auto& camera = GetView()->GetTargetCamera();
		m_EfkInterface->SetViewProj(camera->GetViewMatrix(), camera->GetProjMatrix());
		m_EfkInterface->OnDraw();
	}

	void MainStage::UpdateStage() {
		//追加・削除まちオブジェクトの追加と削除
		SetWaitToObjectVec();
		//Transformコンポーネントの値をバックアップにコピー
		for (auto ptr : GetGameObjectVec()) {
			if (ptr->IsUpdateActive()) {
				auto ptr2 = ptr->GetComponent<Transform>();
				ptr2->SetToBefore();
			}
		}
		//物理オブジェクトのフォースの初期化
		//if (IsPhysicsActive()) {
		//	pImpl->m_BasePhysics.InitForce();
		//}
		//配置オブジェクトの更新処理
		for (auto ptr : GetGameObjectVec()) {
			if (ptr->IsUpdateActive()) {
				ptr->OnUpdate();
			}
		}
		//自身の更新処理
		if (IsUpdateActive()) {
			OnUpdate();
		}
		//物理オブジェクトの更新
		//if (IsPhysicsActive()) {
		//	pImpl->m_BasePhysics.Update(false);
		//}
		//配置オブジェクトのコンポーネント更新
		for (auto ptr : GetGameObjectVec()) {
			if (ptr->IsUpdateActive()) {
				ptr->ComponentUpdate();
			}
		}
		////衝突判定
		UpdateCollision();
		//配置オブジェクトの更新後処理
		//for (auto ptr : GetGameObjectVec()) {
		//	if (ptr->IsUpdateActive()) {
		//		ptr->OnUpdate2();
		//	}
		//}
		////自身の更新後処理
		//if (IsUpdateActive()) {
		//	OnUpdate2();
		//}

		//自身のビューをアップデート
		auto ViewPtr = GetView(false);
		if (ViewPtr && ViewPtr->IsUpdateActive()) {
			ViewPtr->OnUpdate();
		}
		//子供ステージの更新
		//for (auto PtrChileStage : GetChileStageVec()) {
		//	PtrChileStage->UpdateStage();
		//}
	}

	void MainStage::DrawStage() {
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
//end basecross
