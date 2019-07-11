#include "stdafx.h"
#include "Project.h"



namespace basecross {
	FadeStarSprite::FadeStarSprite(
		const shared_ptr<Stage>& stagePtr,
		const FadeType& fadeType,
		const wstring& stageString) :
		Sprite(stagePtr, L"StarFade.png", Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f)),   
		m_FadeType(fadeType),
		m_StageString(stageString)
	{
	}

	void FadeStarSprite::OnCreate() {
		Sprite::OnCreate();
		// レイヤーの設定
		SetDrawLayer(150);
		// タグの設定
		AddTag(L"Fade");
		// 不透明度
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 1.0));

		// 大きさの初期値
		auto ptrTrans = GetComponent<Transform>();
		switch (m_FadeType)
		{
		case FadeIn:
			ptrTrans->SetScale(Vec3(1280, 800, 1));
			break;
		case FadeOut:
			//float FadeOutX = 128000.0f;         //フェードアウト開始時のXの大きさ
			//float FadeOutY = 80000.0f;          //フェードアウト開始時のYの大きさ

			ptrTrans->SetScale(Vec3(128000, 80000, 1));
			break;
		default:
			break;
		}
	}

	void FadeStarSprite::OnUpdate() {	

		const float plusX = 1280.0f * 2.0f;      //Xの変わる速さ
		const float plusY = 800.0f * 2.0f;       //Yの変わる速さ

		auto ptrTrans = GetComponent<Transform>(); 
		// 大きさを取得
		auto scale = ptrTrans->GetScale();            

		switch (m_FadeType)
		{
		case FadeIn:
			scale.x += plusX;
			scale.y += plusY;

			ptrTrans->SetScale(scale);
			// 大きくなって画面が見えるようになったら
			if (scale.x >= 128000) {
				// このオブジェクトを削除
				GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
			}

			break;
		case FadeOut:
			scale.x -= plusX;
			scale.y -= plusY;

			// ローディング対策
			if (scale.x <= 1280) {
				scale.x = 1280;
			}
			if (scale.y <= 800) {
				scale.y = 800;
			}

			ptrTrans->SetScale(scale);
			// 小さくなったら
			if (scale.x <= 1280) {
				GetStage()->PostEvent(0.0f,GetThis<ObjectInterface>(),App::GetApp()->GetScene<Scene>(),m_StageString);
			}
			break;
		default:
			break;
		}
	}

	//--------------------------------------------------------------------------------------
	// メインでClearしたら喜ぶ人間
	//--------------------------------------------------------------------------------------
	MainStageHuman::MainStageHuman(const shared_ptr<Stage>& stagePtr, const Vec3 position)
		:MyGameObject(stagePtr),m_Position(position)
	{}

	void MainStageHuman::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(Vec3(0.5, 0.5, 0.5));
		ptrTrans->SetRotation(Vec3(0));
		ptrTrans->SetPosition(m_Position);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(2.5f, 2.5f, 2.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.75f, 0.0f)
		);

		auto ptrDraw = AddComponent<PNTBoneModelDraw>();

		ptrDraw->SetMeshResource(L"Man_Human.bbmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"Walk", 0, 60, true, 140.0f);
		ptrDraw->ChangeCurrentAnimation(L"Walk");

		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Man_Human.bbmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//ChangRot();
		auto ptrAction = AddComponent<Action>();
		ptrAction->AddMoveBy(0.5f, Vec3(0, 1, 0));
		ptrAction->AddMoveBy(0.5f, Vec3(0, -1, 0));
		//ループする
		ptrAction->SetLooped(true);
		//アクション開始
		ptrAction->Run();

	}

	void MainStageHuman::OnUpdate() {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elapsedTime);

	}
}