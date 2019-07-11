#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	バリケード
	//--------------------------------------------------------------------------------------
	Barricade::Barricade(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position

	) :
		MyGameObject(stagePtr),
		m_Scale(scale),
		m_Quat(rotation),
		m_Position(position)
	{}
	Barricade::Barricade(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode) :
		MyGameObject(stagePtr),
		m_Scale(0),
		m_Quat(0),
		m_Position(0)
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
	}

	void Barricade::OnCreate() {
		// セルマップの対象のグループにいれる
		GetStage()->GetSharedObjectGroup(L"Barricades")->IntoGroup(GetThis<Barricade>());

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetQuaternion(m_Quat);
		ptrTrans->SetPosition(m_Position);
		
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.75f, 0.75f, 0.75f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -1.2f, 0.0f)
		);


		// 当たり判定は立方体
		auto ptrColl = AddComponent<CollisionSphere>();
		//ptrColl->SetDrawActive(true);
		ptrColl->SetFixed(true);

		SetAlphaActive(true);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"Barricade.bmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		auto ptrShadow = AddComponent<Shadowmap>();

		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Barricade.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		AddTag(L"Barricade");

		//エフェクトの初期化
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\wallbreak2.efk";
		auto ShEfkInterface = GetTypeStage<MainStage>()->GetEfkInterface();
		m_EfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);

		//// エフェクトテスト
		//auto ptr = GetComponent<Transform>();
		////エフェクトのプレイ
		//m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, ptr->GetPosition());


	}

	void Barricade::OnUpdate() {
		// バリケードが破壊されたら
		if (!m_IsAlive) {
			m_DeathTotalTime += App::GetApp()->GetElapsedTime();

			// 砂煙を出す
			// バリケード下に沈める
			auto ptrTrans = GetComponent<Transform>();
			auto pos = ptrTrans->GetPosition();
			pos.y -= 0.05f;
			ptrTrans->SetPosition(pos);

			if (m_DeathTotalTime > m_DeathTime) {
				// あるていど　下に行ったらオブジェクトを消す
				GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
				// エフェクトを止める
				//m_EfkPlay->StopEffect();
			}
		}

	}

	void Barricade::RemoveObject() {


	}



	//--------------------------------------------------------------------------------------
	//	水たまり
	//--------------------------------------------------------------------------------------
	SlowFloor::SlowFloor(const shared_ptr<Stage>& stagePtr,
		const Vec3& position) :
		MyGameObject(stagePtr),
		m_Position(position)
	{}
	SlowFloor::SlowFloor(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode) :
		MyGameObject(stagePtr),
		m_Scale(0),
		m_Quat(0),
		m_Position(0)
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
	}


	void SlowFloor::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetQuaternion(m_Quat);
		ptrTrans->SetPosition(m_Position);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		SetAlphaActive(true);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		// テクスチャださい
		ptrDraw->SetTextureResource(L"Blue.png");

		AddTag(L"SlowFloor");

	}

	void SlowFloor::OnUpdate() {

	}


	//--------------------------------------------------------------------------------------
	//	木
	//--------------------------------------------------------------------------------------
	Tree::Tree(const shared_ptr<Stage>& stagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		MyGameObject(stagePtr),
		m_Scale(Scale),
		m_Quat(Rotation),
		m_Position(Position),
		m_MeshName(L"Tree.bmf")
	{}
	Tree::Tree(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode) :
		MyGameObject(stagePtr),
		m_Scale(0),
		m_Quat(0),
		m_Position(0),
		m_MeshName(L"Tree.bmf")
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

		m_MeshName = XmlDocReader::GetAttribute(pNode, L"MeshName");
	}


	//初期化
	void Tree::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetQuaternion(m_Quat);
		ptrTransform->SetPosition(m_Position);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.75f, 0.75f, 0.75f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.6f, 0.0f)
		);
		SetAlphaActive(true);

		// メッシュの描画
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(m_MeshName);
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//影の描画
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(m_MeshName);
		ptrShadow->SetMeshToTransformMatrix(spanMat);


	}
	//--------------------------------------------------------------------------------------
	//	木のスプライト３D
	//--------------------------------------------------------------------------------------
	//構築と破棄
	TreeSprite::TreeSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec3& startScale,
		const Vec3& startRotaiton,
		const Vec3& startPos
	) :
		Sprite3D(stagePtr, textureKey, startScale, startRotaiton, startPos)
	{}
	
}