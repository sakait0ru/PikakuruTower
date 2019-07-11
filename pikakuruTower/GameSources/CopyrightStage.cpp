/*!
@file CopyrightStage.cpp
@brief 著作権を表示するステージ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// 著作権を表示するステージ
	//--------------------------------------------------------------------------------------
	void CopyrightStage::CreateViewLight() {
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
	void CopyrightStage::CreateSprite() {
		AddGameObject<Sprite>(L"Copyright.png",
			Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f));
	}

	void CopyrightStage::OnCreate() {
		// ビューの作成
		CreateViewLight();
		//スプライトの作成
		CreateSprite();

		// フェードインの画像の作成
		AddGameObject<FadeSquareSprite>(FadeType::FadeIn);

	}
	void CopyrightStage::OnUpdate() {
		// 何秒後にフェードを開始するか
		const float m_FadeTime = 5.0f;

		auto elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;
		if (m_TotalTime > m_FadeTime) {
			AddGameObject<FadeSquareSprite>(FadeType::FadeOut, L"ToTitleStage");
			m_TotalTime = 0.0f;
		}
	}

}