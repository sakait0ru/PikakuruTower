/*!
@file CopyrightStage.cpp
@brief ���쌠��\������X�e�[�W
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// ���쌠��\������X�e�[�W
	//--------------------------------------------------------------------------------------
	void CopyrightStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();

	}

	//�X�v���C�g�̍쐬
	void CopyrightStage::CreateSprite() {
		AddGameObject<Sprite>(L"Copyright.png",
			Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f));
	}

	void CopyrightStage::OnCreate() {
		// �r���[�̍쐬
		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateSprite();

		// �t�F�[�h�C���̉摜�̍쐬
		AddGameObject<FadeSquareSprite>(FadeType::FadeIn);

	}
	void CopyrightStage::OnUpdate() {
		// ���b��Ƀt�F�[�h���J�n���邩
		const float m_FadeTime = 5.0f;

		auto elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;
		if (m_TotalTime > m_FadeTime) {
			AddGameObject<FadeSquareSprite>(FadeType::FadeOut, L"ToTitleStage");
			m_TotalTime = 0.0f;
		}
	}

}