/*!
@file Floor.cpp
@brief 床
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//構築と破棄
	FixedBox::FixedBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		MyGameObject(StagePtr),
		m_Scale(Scale),
		m_Quat(Rotation),
		m_Position(Position),
		m_TextureName(L"FloorSpring.png")
	{}

	FixedBox::FixedBox(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode) :
		MyGameObject(stagePtr),
		m_Scale(0),
		m_Quat(0),
		m_Position(0),
		m_TextureName(L"FloorSpring.png")
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

		m_TextureName = XmlDocReader::GetAttribute(pNode, L"TextureName");
	}

	//初期化
	void FixedBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetQuaternion(m_Quat);
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//タグをつける
		AddTag(L"FixedBox");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(m_TextureName);

		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		//ptrDraw->SetDiffuse(Col4(0.4f, 0.4f, 0.4f, 1.0f));
	}

	//--------------------------------------------------------------------------------------
	//	たいまつ
	//--------------------------------------------------------------------------------------
	FireTorch::FireTorch(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position
	) :
		MyGameObject(stagePtr),
		m_Scale(scale),
		m_Rotation(rotation),
		m_Position(position)
	{}
	// 構築
	void FireTorch::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.75f, 0.75f, 0.75f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -1.2f, 0.0f)
		);

		SetAlphaActive(true);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"Barricade.bmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		auto ptrShadow = AddComponent<Shadowmap>();

		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Barricade.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);


		//エフェクトの初期化
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\fire.efk";
		auto ShEfkInterface = GetTypeStage<TitleStage>()->GetEfkInterface();
		m_EfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);



		// エフェクトの再生
		// エフェクトテスト
		auto ptr = GetComponent<Transform>();
		//エフェクトのプレイ
		m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, ptr->GetPosition());
	}

	void FireTorch::OnUpdate() {
		//static bool a = true;
		//if (a) {
		//	auto ptrTrans = GetComponent<Transform>();
		//	auto pos = ptrTrans->GetPosition();
		//	m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, pos);
		//	a = false;
		//}

		//// エフェクトテスト
		//auto Ptr = GetComponent<Transform>();
		////エフェクトのプレイ
		//m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, Ptr->GetPosition());

	}

	
}

//end basecross
