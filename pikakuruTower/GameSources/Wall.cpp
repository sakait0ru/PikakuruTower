/*!
@file Wall.cpp
@brief ��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�ǂ̓����蔻��
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

	//������
	void Wall::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetDrawActive(true);
		ptrColl->SetMakedSize(1.5f);
		ptrColl->SetFixed(true);
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		AddTag(L"Wall");


	}

	//--------------------------------------------------------------------------------------
	//	�ǂ̃��f����P��
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

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.75f, 0.75f, 0.75f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PIDIV2, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		SetAlphaActive(true);

		// ���b�V���̕`��
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"Wall.bmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//�e�̕`��
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"Wall.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		AddTag(L"WallUnit");
	}

	void WallUnit::OnUpdate() {
	}

	//�Q�[���I�[�o�[���������A�ǂ�������
	void WallUnit::WallUnitDown() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos.y -= 0.01f;
		ptrTrans->SetPosition(pos);
	}

	//--------------------------------------------------------------------------------------
	//	�ǂ̑_����Ƃ���
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

	//������
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
	//	�^���[
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

	//������
	void Tower::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
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

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
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
	//	�^���[�̉��̂Ƃ���
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

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
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

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"Tower_Under.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		AddTag(L"Wall");

	}

	void TowerUnder::OnUpdate() {

	}


}
//end basecross
