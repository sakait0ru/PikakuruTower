/*!
@file Wall.cpp
@brief 壁
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	壁の当たり判定
	//--------------------------------------------------------------------------------------
	Wall::Wall(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		MyGameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}

	//初期化
	void Wall::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetDrawActive(true);
		ptrColl->SetMakedSize(1.5f);
		ptrColl->SetFixed(true);
		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		AddTag(L"Wall");


	}

	//--------------------------------------------------------------------------------------
	//	壁のモデル一単位
	//--------------------------------------------------------------------------------------
	WallUnit::WallUnit(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		MyGameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}
	void WallUnit::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.75f, 0.75f, 0.75f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PIDIV2, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		SetAlphaActive(true);

		// メッシュの描画
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"Wall.bmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//影の描画
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"Wall.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		AddTag(L"WallUnit");
	}

	void WallUnit::OnUpdate() {
	}

	//ゲームオーバーだった時、壁が下がる
	void WallUnit::WallUnitDown() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos.y -= 0.01f;
		ptrTrans->SetPosition(pos);
	}

	//--------------------------------------------------------------------------------------
	//	壁の狙えるところ
	//--------------------------------------------------------------------------------------
	WallTaget::WallTaget(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		MyGameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}

	//初期化
	void WallTaget::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(true);
		SetAlphaActive(true);
		SetDrawActive(false);
	}


	//--------------------------------------------------------------------------------------
	//	タワー
	//--------------------------------------------------------------------------------------
	Tower::Tower(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		MyGameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}

	//初期化
	void Tower::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.75f, 0.75f, 0.75f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"Tower_Top.bmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetOwnShadowActive(true);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Tower_Top.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		AddTag(L"Wall");
	}

	void Tower::OnUpdate() {

		auto light = GetStage()->GetSharedGameObject<Spotlight>(L"Spotlight");
		auto lightTrans = light->GetComponent<Transform>();
		auto lightPos = lightTrans->GetPosition();

		auto ptrTrans = GetComponent<Transform>();
		auto ptrPos = ptrTrans->GetPosition();

		auto vec = lightPos - ptrPos;

		float angle = atan2(vec.z, vec.x);

		ptrTrans->SetRotation(Vec3(0.0f, -angle, 0.0f));

	}

	//--------------------------------------------------------------------------------------
	//	タワーの下のところ
	//--------------------------------------------------------------------------------------
	TowerUnder::TowerUnder(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		MyGameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}

	void TowerUnder::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.75f, 0.75f, 0.75f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"Tower_Under.bmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetOwnShadowActive(true);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Tower_Under.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		AddTag(L"Wall");

	}

	void TowerUnder::OnUpdate() {

	}


}
//end basecross
