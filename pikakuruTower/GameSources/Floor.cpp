/*!
@file Floor.cpp
@brief ��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	FixedBox::FixedBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		MyGameObject(StagePtr),
		m_Scale(Scale),
		m_Quat(Rotation),
		m_Position(Position),
		m_TextureName(L"FloorSpring.png")
	{}

	FixedBox::FixedBox(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode) :
		MyGameObject(stagePtr),
		m_Scale(0),
		m_Quat(0),
		m_Position(0),
		m_TextureName(L"FloorSpring.png")
	{
		// ��������wstring�̕�����Ŏ擾�ł���
		auto scaleStr = XmlDocReader::GetAttribute(pNode, L"Scale");
		auto quatStr = XmlDocReader::GetAttribute(pNode, L"Quat");
		auto posStr = XmlDocReader::GetAttribute(pNode, L"Pos");

		// L"(0.0f,0.0f,0.0f)" �ɂȂ��Ă���̂�"(",")"�����
		scaleStr.pop_back();
		scaleStr.erase(scaleStr.begin());
		quatStr.pop_back();
		quatStr.erase(quatStr.begin());
		posStr.pop_back();
		posStr.erase(posStr.begin());

		//�g�[�N���i�J�����j�̔z��
		vector<wstring> tokens;
		tokens.clear();

		// scaleStr��Vec3�^�ɕϊ�
		Util::WStrToTokenVector(tokens, scaleStr, L',');
		//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
		m_Scale = Vec3(
			(float)_wtof(tokens[0].c_str()),
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str())
		);
		tokens.clear();

		// Quat�ɕϊ�
		Util::WStrToTokenVector(tokens, quatStr, L',');
		m_Quat = Quat(
			(float)_wtof(tokens[0].c_str()),
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str()),
			(float)_wtof(tokens[3].c_str())
		);
		tokens.clear();

		// scaleStr��Vec3�^�ɕϊ�
		Util::WStrToTokenVector(tokens, posStr, L',');
		//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
		m_Position = Vec3(
			(float)_wtof(tokens[0].c_str()),
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str())
		);
		tokens.clear();

		m_TextureName = XmlDocReader::GetAttribute(pNode, L"TextureName");
	}

	//������
	void FixedBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetQuaternion(m_Quat);
		ptrTransform->SetPosition(m_Position);
		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//�^�O������
		AddTag(L"FixedBox");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(m_TextureName);

		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		//ptrDraw->SetDiffuse(Col4(0.4f, 0.4f, 0.4f, 1.0f));
	}

	//--------------------------------------------------------------------------------------
	//	�����܂�
	//--------------------------------------------------------------------------------------
	FireTorch::FireTorch(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position
	) :
		MyGameObject(stagePtr),
		m_Scale(scale),
		m_Rotation(rotation),
		m_Position(position)
	{}
	// �\�z
	void FireTorch::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.75f, 0.75f, 0.75f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -1.2f, 0.0f)
		);

		SetAlphaActive(true);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"Barricade.bmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		auto ptrShadow = AddComponent<Shadowmap>();

		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"Barricade.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);


		//�G�t�F�N�g�̏�����
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\fire.efk";
		auto ShEfkInterface = GetTypeStage<TitleStage>()->GetEfkInterface();
		m_EfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);



		// �G�t�F�N�g�̍Đ�
		// �G�t�F�N�g�e�X�g
		auto ptr = GetComponent<Transform>();
		//�G�t�F�N�g�̃v���C
		m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, ptr->GetPosition());
	}

	void FireTorch::OnUpdate() {
		//static bool a = true;
		//if (a) {
		//	auto ptrTrans = GetComponent<Transform>();
		//	auto pos = ptrTrans->GetPosition();
		//	m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, pos);
		//	a = false;
		//}

		//// �G�t�F�N�g�e�X�g
		//auto Ptr = GetComponent<Transform>();
		////�G�t�F�N�g�̃v���C
		//m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, Ptr->GetPosition());

	}

	
}

//end basecross
