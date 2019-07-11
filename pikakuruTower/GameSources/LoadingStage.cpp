/*!
@file LoadingStage.cpp
@brief ロード画面
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	ロードステージ
	//--------------------------------------------------------------------------------------
	void LoadingStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 0.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	

	void LoadingStage::CreateLoadingSprite() {
		//背景
		AddGameObject<Sprite>(L"BG.png", Vec2(1280.0f, 800.0f), Vec2(0, 0));
		// 読み込み中・・・
		//AddGameObject<LoadingSprite>(L"Loading_1.png", Vec2(600.0f, 150.0f), Vec2(340.0f, -355.0f));
		AddGameObject<LoadingSprite>(L"Loading_1.png", Vec2(512.0f * 0.8f, 128.0f * 0.8f), Vec2(435, -336));
		
		// 説明画像
		m_ReadmeSprite = AddGameObject<Sprite>(L"ZombieReadme01.png", Vec2(800.0f, 800.0f), Vec2(250, 10));

		// 説明している画像の後ろも欲しい

		// カーソル		
		m_RTriSprite = AddGameObject<TriMoveSprite>(L"RightArrowfix.png", Vec2(50.0f, 50.0f), Vec2(-590.0f, 100));
		m_LTriSprite = AddGameObject<TriMoveSprite>(L"LeftArrowfix.png", Vec2(50.0f, 50.0f), Vec2(-190.0f, 100));

		// 「セレクトに戻る」のスプライト作成
		auto selectButton = AddGameObject<Sprite>(L"LoadingToSelectButton.png", Vec2(512.0f * 0.8f, 128.0f * 0.8f), Vec2(-435, -336));
		selectButton->SetDrawLayer(100);
	}

	//初期化
	void LoadingStage::OnCreate() {
		CreateViewLight();


		// エネミーデータをWaveManagerに渡してやる
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

		// waveにあるエネミーのデータを削除
		auto WM = WaveManager::getInstance();
		WM->RemoveWaveEnemyData();
		
		// エネミーのデータを代入する
		GameObjecttXMLBuilder builder;
		builder.Register<EnemyDataLoad>(L"Enemy");
		builder.Build(GetThis<Stage>(), m_stageXmlPath, L"GameStage/Enemy"); 


		// 左下のゾンビ
		m_Enemy = AddGameObject<LoadingZombie>();
		m_Enemy->SetDrawLayer(90);
		// スプライトの作成
		CreateLoadingSprite();
		//フェードインする
		AddGameObject<FadeStarSprite>(FadeType::FadeIn);

		// TipsSelectの点
		//auto select = AddGameObject<LoadingSelectSprite>(L"selectbar.png",Vec2(1024.0f * 0.1f, 1024.0f * 0.1f),Vec2(-120, -370)); //-120 ～　160 40   -370 0
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
		{ //リセットボタン
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
			if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_START && cntlVec.wPressedButtons & XINPUT_GAMEPAD_BACK && FadeSwitch == true) {
				FadeSwitch = false;
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			}
		}

		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cntlVec.bConnected) {
			if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_B) {
				// Selectに戻る
				AddGameObject<FadeStarSprite>(FadeType::FadeOut, L"ToSelectStage");
			}
		}

		//m_ReadNumを増やす
		if (cntlVec.bConnected) {
			if (m_CntlLock) {
				//スティックを右に倒す
				if (cntlVec.fThumbLX >= 0.8f) {
					//m_ReadNumが５より小さいときに入る 
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
				//スティックを左に倒す
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
				// それ以外の時
				m_CntlLock = true;
			}
		}

		switch (m_ReadNum)
		{
		case 0:
			m_ReadmeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"ZombieReadme01.png");//男ゾンビ
			m_SpVec[7]->Akarusa(false);
			m_SpVec[0]->Akarusa(true);
			m_SpVec[1]->Akarusa(false);
			break;
		case 1:
			m_ReadmeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"ZombieReadme02.png");//女ゾンビ
			m_SpVec[0]->Akarusa(false);
			m_SpVec[1]->Akarusa(true);
			m_SpVec[2]->Akarusa(false);
			break;
		case 2:
			m_ReadmeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"ZombieReadme03.png");//盾ゾンビ
			m_SpVec[1]->Akarusa(false);
			m_SpVec[2]->Akarusa(true);
			m_SpVec[3]->Akarusa(false);
			break;
		case 3:
			m_ReadmeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"ZombieReadme04.png");//水着ZombieReadme08.png
			m_SpVec[2]->Akarusa(false);
			m_SpVec[3]->Akarusa(true);
			m_SpVec[4]->Akarusa(false);
			break;
		case 4:
			m_ReadmeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"ZombieReadme05.png");//ZombieReadme07.png工作ゾンビ
			m_SpVec[3]->Akarusa(false);
			m_SpVec[4]->Akarusa(true);
			m_SpVec[5]->Akarusa(false);
			break;
		case 5:
			m_ReadmeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"ZombieReadme06.png");//隊長ゾンビ
			m_SpVec[4]->Akarusa(false);
			m_SpVec[5]->Akarusa(true);
			m_SpVec[6]->Akarusa(false);
			break;
		case 6:
			m_ReadmeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"ZombieReadme07.png");//浄化された人間
			m_SpVec[5]->Akarusa(false);
			m_SpVec[6]->Akarusa(true);
			m_SpVec[7]->Akarusa(false);
			break;
		case 7:
			m_ReadmeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"ZombieReadme8.png");//ハンマーゾンビ
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
	///	読み込み中…スプライト
	//--------------------------------------------------------------------------------------
	LoadingSprite::LoadingSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

	void LoadingSprite::OnUpdate() {
		// タワーがくるくる回転してて、読み込み完了したらライトを照らし始める

		SetDrawLayer(100);

		auto ptrDraw = GetComponent<PCTSpriteDraw>();

		auto elapsedTime = App::GetApp()->GetElapsedTime();

		// 3秒たったら読み込み完了
		if (m_ChangeTime > 3.0f) {
			ptrDraw->SetTextureResource(L"LoadingFinisf.png");
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
			//ptrTrans->SetScale(300.0f, 300.0f, 0.0f);

			//ptrTrans->SetScale(scale);

			// Aボタンを押したらゲームステージに移る
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
	///	プレビューゾンビ
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


		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(2.5f, 2.5f, 2.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.75f, 0.0f)
		);

		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		// メッシュの設定
		ptrDraw->SetMeshResource(L"Man_Zombie.bbmf");
		// アニメーションの設定
		ptrDraw->AddAnimation(L"Walk", 0, 120, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Walk");

		// 前面に表示
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
	///	LoadingSelectSprite画面用のスプライト
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
			//1回スティック倒したら戻すまでロックする
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
	// エネミーのデータを受け取るクラス
	//--------------------------------------------------------------------------------------
	EnemyDataLoad::EnemyDataLoad(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode) :
		MyGameObject(stagePtr) 
	{
		// 属性からwstringの文字列で取得できる
		auto scaleStr = XmlDocReader::GetAttribute(pNode, L"Scale");
		auto quatStr = XmlDocReader::GetAttribute(pNode, L"Quat");
		auto posStr = XmlDocReader::GetAttribute(pNode, L"Pos");

		// L"(0.0f,0.0f,0.0f)" になっているので"(",")"を取る
		scaleStr.pop_back();
		scaleStr.erase(scaleStr.begin());
		quatStr.pop_back();
		quatStr.erase(quatStr.begin());
		posStr.pop_back();
		posStr.erase(posStr.begin());

		//トークン（カラム）の配列
		vector<wstring> tokens;
		tokens.clear();

		// scaleStrをVec3型に変換
		Util::WStrToTokenVector(tokens, scaleStr, L',');
		//各トークン（カラム）をスケール、回転、位置に読み込む
		m_Scale = Vec3(
			(float)_wtof(tokens[0].c_str()),
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str())
		);
		tokens.clear();

		// Quatに変換
		Util::WStrToTokenVector(tokens, quatStr, L',');
		m_Quat = Quat(
			(float)_wtof(tokens[0].c_str()),
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str()),
			(float)_wtof(tokens[3].c_str())
		);
		tokens.clear();

		// scaleStrをVec3型に変換
		Util::WStrToTokenVector(tokens, posStr, L',');
		//各トークン（カラム）をスケール、回転、位置に読み込む
		m_Position = Vec3(
			(float)_wtof(tokens[0].c_str()),
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str())
		);
		tokens.clear();

		// WaveNum読み込み
		auto waveNumStr = XmlDocReader::GetAttribute(pNode, L"WaveNum");
		m_WaveNum = (int)_wtof(waveNumStr.c_str());

		// CaptainNum読み込み
		auto captainNumStr = XmlDocReader::GetAttribute(pNode, L"CaptainNum");
		m_CaptainNum = (int)_wtof(captainNumStr.c_str());

		// SpawnTime読み込み
		auto spawnTimeStr = XmlDocReader::GetAttribute(pNode, L"SpawnTime");
		m_SpawnTime = (float)_wtof(spawnTimeStr.c_str());

		// EnemyType読み込み
		auto enemyTypeStr = XmlDocReader::GetAttribute(pNode, L"EnemyType");
		m_EnemyType = (int)_wtof(enemyTypeStr.c_str());
	}

	void EnemyDataLoad::OnCreate() {
		// WaveManager
		auto WM = WaveManager::getInstance();
		
		WM->SetWaveDate(m_Scale, m_Quat, m_Position, m_WaveNum, m_CaptainNum, m_SpawnTime, m_EnemyType);

		// 後処理
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
			//三角を動かす
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
			//三角を動かす
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