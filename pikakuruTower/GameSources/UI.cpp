/*!
@file UI.cpp
@brief UI
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

//--------------------------------------------------------------------------------------
///	ライトのスイッチ
//--------------------------------------------------------------------------------------

	RightSuitch::RightSuitch(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

	void RightSuitch::OnCreate() {
		float helfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-0, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-0, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, -helfSize, 0), Col4(1.0f, 01.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(Vec3(m_StartPos.x, m_StartPos.y, 0.0f));
		// ピボットを右端にする
		ptrTrans->SetPivot(0.0f, 0.0f, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(L"Light_on.png");


		AddTag(L"UI");

		

		SetDrawLayer(11);
		SetAlphaActive(true);

		//スプライトの厚さ		
		ptrDraw->SetDiffuse(Col4(1, 1, 1, 11.1f));
	}


	void RightSuitch::OnUpdate() {

		// ドローコンポーネントを取得
		auto ptrDraw = GetComponent<PCTSpriteDraw>();

		// Spotlight.cppのを持ってきた
		auto on = GetStage()->GetSharedGameObject<Spotlight>(L"Spotlight")->GetOn();
		if (on) {
			// ライトがついていたらON.jpgに張り替える
			ptrDraw->SetTextureResource(L"Light_on.png");
		}
		else {
			// その他はOFF.jpgに張り替える
			ptrDraw->SetTextureResource(L"Light_off.png");
		}

		
	}

	//--------------------------------------------------------------------------------------
	///	HPゲージのスプライト
	//--------------------------------------------------------------------------------------
	HpGage::HpGage(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale, 
			const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale,startPos)
	{}

	void HpGage::OnCreate() {
		float helfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-0, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-0, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, -helfSize, 0), Col4(1.0f, 01.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(Vec3(m_StartPos.x,m_StartPos.y,0.0f));
		// ピボットを右端にする
		ptrTrans->SetPivot(0.0f, 0.0f, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_TextureKey);

		AddTag(L"UI");
		
		SetDrawLayer(11);
	}
	void HpGage::OnUpdate() {
					
		{ // ダメージを受けた時
			auto ptrTrans = GetComponent<Transform>();
			auto scale = ptrTrans->GetScale();

			auto GM = GameManager::getInstance();
			int hp = GM->GetWallHp();
			int maxHp = GM->GetMaxWallHp();
			float rate = float(maxHp) / (float)hp;

			scale.x = m_StartScale.x / rate;
			ptrTrans->SetScale(scale);
		}
	}

	//--------------------------------------------------------------------------------------
	///	Hpゲージの枠のスプライト
	//--------------------------------------------------------------------------------------
	HpGageFrame::HpGageFrame(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

	void HpGageFrame::OnCreate() {
		Sprite::OnCreate();
		SetDrawLayer(11);

	}

	void HpGageFrame::OnUpdate() {

		auto GM = GameManager::getInstance();
		auto maxHp = GM->GetMaxWallHp();
		auto hp = GM->GetWallHp();

		float dis = (float)hp / (float)maxHp;

		auto ptrDraw = GetComponent<PCTSpriteDraw>();

		if (dis < 0.25f) {
			ptrDraw->SetTextureResource(L"UI75__0509.png");
		}
		else if (dis < 0.6f) {
			ptrDraw->SetTextureResource(L"UI50__0509.png");
		}
		else if(dis < 0.8f){
			ptrDraw->SetTextureResource(L"UI25__0509.png");		
		}
		else {
			ptrDraw->SetTextureResource(L"UI0__0509.png");
		}



	}

	//--------------------------------------------------------------------------------------
	///	アイテムアイコンのスプライト
	//--------------------------------------------------------------------------------------
	ItemIcon::ItemIcon(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

	void ItemIcon::OnCreate() {
		Sprite::OnCreate();
		SetDrawLayer(10);
	}

	void ItemIcon::OnUpdate() {

	}

	//--------------------------------------------------------------------------------------
	///	数字を表示するスプライト
	//--------------------------------------------------------------------------------------
	NumberSprite::NumberSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos,
		const int& number) :
		Sprite(stagePtr, textureKey, startScale, startPos),
		m_Number(number)
	{}

	void NumberSprite::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);

		//頂点配列
		vector<VertexPositionNormalTexture> vertices;
		//インデックスを作成するための配列
		vector<uint16_t> indices;
		//Squareの作成(ヘルパー関数を利用)
		MeshUtill::CreateSquare(1.0f, vertices, indices);

		//UV値の変更
		float from = ((float)m_Number) / 10.0f;
		float to = from + (1.0f / 10.0f);
		//左上頂点
		vertices[0].textureCoordinate = Vec2(from, 0);
		//右上頂点
		vertices[1].textureCoordinate = Vec2(to, 0);
		//左下頂点
		vertices[2].textureCoordinate = Vec2(from, 1.0f);
		//右下頂点	
		vertices[3].textureCoordinate = Vec2(to, 1.0f);

		//頂点の型を変えた新しい頂点を作成
		vector<VertexPositionColorTexture> new_vertices;
		for (auto& v : vertices) {
			VertexPositionColorTexture nv;
			nv.position = v.position;
			nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
			nv.textureCoordinate = v.textureCoordinate;
			new_vertices.push_back(nv);
		}
		SetAlphaActive(true);

		auto ptrDraw = AddComponent<PCTSpriteDraw>(new_vertices, indices);
		ptrDraw->SetTextureResource(m_TextureKey);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);

		SetDrawLayer(10);



	}

	void NumberSprite::OnUpdate() {

	}

	// Nunberの表示を変更する
	void NumberSprite::ChangeNumber(int i) {
		m_Number = i;

		//頂点配列
		vector<VertexPositionNormalTexture> vertices;
		//インデックスを作成するための配列
		vector<uint16_t> indices;
		//Squareの作成(ヘルパー関数を利用)
		MeshUtill::CreateSquare(1.0f, vertices, indices);

		//UV値の変更
		float from = ((float)m_Number) / 10.0f;
		float to = from + (1.0f / 10.0f);
		//左上頂点
		vertices[0].textureCoordinate = Vec2(from, 0);
		//右上頂点
		vertices[1].textureCoordinate = Vec2(to, 0);
		//左下頂点
		vertices[2].textureCoordinate = Vec2(from, 1.0f);
		//右下頂点	
		vertices[3].textureCoordinate = Vec2(to, 1.0f);

		//頂点の型を変えた新しい頂点を作成
		vector<VertexPositionColorTexture> new_vertices;
		for (auto& v : vertices)
		{
			VertexPositionColorTexture nv;
			nv.position = v.position;
			nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
			nv.textureCoordinate = v.textureCoordinate;
			new_vertices.push_back(nv);
		}

		SetAlphaActive(true);


		auto m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);

		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetMeshResource(m_SquareMeshResource);

	}

	//--------------------------------------------------------------------------------------
	///	現在のWaveを表示して消えるスプライト
	//--------------------------------------------------------------------------------------
	WaveSprite::WaveSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, Vec2(1254, 256), startPos),
		m_TotalTime(0.0f),
		m_RemoveTime(3.0f)
	{}
	
	void WaveSprite::OnCreate() {
		Sprite::OnCreate();
		SetDrawLayer(10);
		//サウンドの再生
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(L"tugi_Wave.wav", 0, 0.3f);
	}
	void WaveSprite::OnUpdate() {
		// 拡大からの縮小で消える
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		auto scale = ptrTrans->GetScale();

		auto ptrDraw = GetComponent<PCTSpriteDraw>();

		float removeTimeHalf = m_RemoveTime / 2.0f;

		float dis;
		if (m_TotalTime < removeTimeHalf) {
			dis = m_TotalTime / removeTimeHalf;
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, dis));
		}
		else {
			dis = (m_TotalTime - removeTimeHalf) / removeTimeHalf;
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f- dis));
		}


		if (m_TotalTime > m_RemoveTime) {
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}
	}
	//--------------------------------------------------------------------------------------
	///	現在のWaveを表示するスプライト
	//--------------------------------------------------------------------------------------
	NowWaveSprite::NowWaveSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

	void NowWaveSprite::SetWaveNumber(wstring fileName) {
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		fileName = L"Small" + fileName;
		ptrDraw->SetTextureResource(fileName);
	}

	//--------------------------------------------------------------------------------------
	///	夜にするスプライト
	//--------------------------------------------------------------------------------------
	//構築と破棄
	NightMaskSprite::NightMaskSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos):
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}


	void NightMaskSprite::OnCreate() {
		Sprite::OnCreate();
		SetDrawLayer(2);

		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetDiffuse(Col4(1, 1, 1, 0.6f));
	}


	void NightMaskSprite::OnUpdate() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();

		auto spotLight = GetStage()->GetSharedGameObject<Spotlight>(L"Spotlight");
		spotLight->CalcDevPos();
		Vec3 spotDevPos = spotLight->GetDevPos();


		pos.x = spotDevPos.x * 640;
		pos.y = -spotDevPos.y * 400;
		ptrTrans->SetPosition(pos);

		auto spotActive = spotLight->GetActive();
		auto spotScale = spotLight->GetBig();
		auto ptrDraw = GetComponent<PCTSpriteDraw>();

		// ついている時
		if (spotActive) {
			// 大きい時
			if (spotScale) {
				ptrDraw->SetTextureResource(L"NightMaskSmall.png");
				
			}
			// 小さい時
			else{
				ptrDraw->SetTextureResource(L"NightMask.png");
			}
		}
		// ついていない時
		else {
			ptrDraw->SetTextureResource(L"Black.png");
		}


		//auto mainStageStartTime = GetTypeStage<MainStage>()->GetStartTime();
		//if (mainStageStartTime < 3.0f) {
		//	m_StartAlpha = ((mainStageStartTime / 10.0f) * 2.0f);

		//	auto ptrDraw = GetComponent<PCTSpriteDraw>();
		//	ptrDraw->SetDiffuse(Col4(1, 1, 1, m_StartAlpha));
		//}


		// ステージクリアしたら明るくなる
		if (WaveManager::getInstance()->IsClear()) {

			m_Alpha -= 0.01f;

			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1, 1, 1, m_Alpha));
		}

	}
	
	//--------------------------------------------------------------------------------------
	///	ダメージを受けた時の赤いスプライト
	//--------------------------------------------------------------------------------------
	//構築と破棄
	DamegeSprite::DamegeSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}


	void DamegeSprite::OnCreate() {
		Sprite::OnCreate();
		SetDrawLayer(3);

		// 薄くする
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetDiffuse(Col4(1, 1, 1, 0.6f));
	}

	void DamegeSprite::OnUpdate() {
		// 拡大からの縮小で消える
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		auto scale = ptrTrans->GetScale();

		auto ptrDraw = GetComponent<PCTSpriteDraw>();

		float removeTimeHalf = m_RemoveTime / 2.0f;

		float dis;
		if (m_TotalTime < removeTimeHalf) {
			dis = m_TotalTime / removeTimeHalf;
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, dis));
		}
		else {
			dis = (m_TotalTime - removeTimeHalf) / removeTimeHalf;
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f - dis));
		}


		if (m_TotalTime > m_RemoveTime) {
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}

	}

	//--------------------------------------------------------------------------------------
	///	Pause画面用のスプライト
	//--------------------------------------------------------------------------------------
	PauseSprite::PauseSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}


	void PauseSprite::OnCreate() {
		Sprite::OnCreate();
		SetDrawLayer(100);
		AddTag(L"PauseMenu");
		SetDrawActive(false);
		
	}

	void PauseSprite::OnUpdate()
	{


	}
	void PauseSprite::Akarusa(bool flg)
	{
		GetComponent<PCTSpriteDraw>()->SetDiffuse(Col4(1, 1, 1, 1.0f));
	}
}

//end basecross
