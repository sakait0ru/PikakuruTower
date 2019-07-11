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
		// ���C���[�̐ݒ�
		SetDrawLayer(150);
		// �^�O�̐ݒ�
		AddTag(L"Fade");
		// �s�����x
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 1.0));

		// �傫���̏����l
		auto ptrTrans = GetComponent<Transform>();
		switch (m_FadeType)
		{
		case FadeIn:
			ptrTrans->SetScale(Vec3(1280, 800, 1));
			break;
		case FadeOut:
			//float FadeOutX = 128000.0f;         //�t�F�[�h�A�E�g�J�n����X�̑傫��
			//float FadeOutY = 80000.0f;          //�t�F�[�h�A�E�g�J�n����Y�̑傫��

			ptrTrans->SetScale(Vec3(128000, 80000, 1));
			break;
		default:
			break;
		}
	}

	void FadeStarSprite::OnUpdate() {	

		const float plusX = 1280.0f * 2.0f;      //X�̕ς�鑬��
		const float plusY = 800.0f * 2.0f;       //Y�̕ς�鑬��

		auto ptrTrans = GetComponent<Transform>(); 
		// �傫�����擾
		auto scale = ptrTrans->GetScale();            

		switch (m_FadeType)
		{
		case FadeIn:
			scale.x += plusX;
			scale.y += plusY;

			ptrTrans->SetScale(scale);
			// �傫���Ȃ��ĉ�ʂ�������悤�ɂȂ�����
			if (scale.x >= 128000) {
				// ���̃I�u�W�F�N�g���폜
				GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
			}

			break;
		case FadeOut:
			scale.x -= plusX;
			scale.y -= plusY;

			// ���[�f�B���O�΍�
			if (scale.x <= 1280) {
				scale.x = 1280;
			}
			if (scale.y <= 800) {
				scale.y = 800;
			}

			ptrTrans->SetScale(scale);
			// �������Ȃ�����
			if (scale.x <= 1280) {
				GetStage()->PostEvent(0.0f,GetThis<ObjectInterface>(),App::GetApp()->GetScene<Scene>(),m_StageString);
			}
			break;
		default:
			break;
		}
	}

	//--------------------------------------------------------------------------------------
	// ���C����Clear�������Ԑl��
	//--------------------------------------------------------------------------------------
	MainStageHuman::MainStageHuman(const shared_ptr<Stage>& stagePtr, const Vec3 position)
		:MyGameObject(stagePtr),m_Position(position)
	{}

	void MainStageHuman::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(Vec3(0.5, 0.5, 0.5));
		ptrTrans->SetRotation(Vec3(0));
		ptrTrans->SetPosition(m_Position);

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
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
		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"Man_Human.bbmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//ChangRot();
		auto ptrAction = AddComponent<Action>();
		ptrAction->AddMoveBy(0.5f, Vec3(0, 1, 0));
		ptrAction->AddMoveBy(0.5f, Vec3(0, -1, 0));
		//���[�v����
		ptrAction->SetLooped(true);
		//�A�N�V�����J�n
		ptrAction->Run();

	}

	void MainStageHuman::OnUpdate() {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elapsedTime);

	}
}