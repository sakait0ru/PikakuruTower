/*!
@file CopyrightStage.h
@brief 著作権を表示するステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// 著作権を表示するステージ
	//--------------------------------------------------------------------------------------
	class CopyrightStage : public Stage {
	private:
		float m_TotalTime = 0.0f;

		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateSprite();
	public:
		CopyrightStage() :Stage() {}
		~CopyrightStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;

	};

}