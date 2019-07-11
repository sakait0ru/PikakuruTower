/*!
@file FadeSquare.h
@brief Fade�̎l�p��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// �l�p��Fade 
	//--------------------------------------------------------------------------------------
	class FadeSquareSprite : public Sprite {
	private:
		// �t�F�[�h�̃^�C�v
		FadeType m_Type;
		// �J�ڂ���X�e�[�W
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
