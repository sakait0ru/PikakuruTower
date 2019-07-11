/*!
@file CopyrightStage.h
@brief ���쌠��\������X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// ���쌠��\������X�e�[�W
	//--------------------------------------------------------------------------------------
	class CopyrightStage : public Stage {
	private:
		float m_TotalTime = 0.0f;

		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateSprite();
	public:
		CopyrightStage() :Stage() {}
		~CopyrightStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;

	};

}