/*!
@file FadeSquare.h
@brief Fadeの四角版
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// 四角のFade 
	//--------------------------------------------------------------------------------------
	class FadeSquareSprite : public Sprite {
	private:
		// フェードのタイプ
		FadeType m_Type;
		// 遷移するステージ
		wstring m_StageString;

	public:
		FadeSquareSprite(const shared_ptr<Stage>& stagePtr,
			const FadeType& fadeType,
			const wstring& stageString = L"ToTitleStage");
		~FadeSquareSprite() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}
