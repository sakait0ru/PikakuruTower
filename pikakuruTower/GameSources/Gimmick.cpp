#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�o���P�[�h
	//--------------------------------------------------------------------------------------
	Barricade::Barricade(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position

	) :
		MyGameObject(stagePtr),
		m_Scale(scale),
		m_Quat(rotation),
		m_Position(position)
	{}
	Barricade::Barricade(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode) :
		MyGameObject(stagePtr),
		m_Scale(0),
		m_Quat(0),
		m_Position(0)
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
	}

	void Barricade::OnCreate() {
		// �Z���}�b�v�̑Ώۂ̃O���[�v�ɂ����
		GetStage()->GetSharedObjectGroup(L"Barricades")->IntoGroup(GetThis<Barricade>());

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetQuaternion(m_Quat);
		ptrTrans->SetPosition(m_Position);
		
		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.75f, 0.75f, 0.75f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -1.2f, 0.0f)
		);


		// �����蔻��͗�����
		auto ptrColl = AddComponent<CollisionSphere>();
		//ptrColl->SetDrawActive(true);
		ptrColl->SetFixed(true);

		SetAlphaActive(true);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"Barricade.bmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		auto ptrShadow = AddComponent<Shadowmap>();

		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"Barricade.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		AddTag(L"Barricade");

		//�G�t�F�N�g�̏�����
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\wallbreak2.efk";
		auto ShEfkInterface = GetTypeStage<MainStage>()->GetEfkInterface();
		m_EfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);

		//// �G�t�F�N�g�e�X�g
		//auto ptr = GetComponent<Transform>();
		////�G�t�F�N�g�̃v���C
		//m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, ptr->GetPosition());


	}

	void Barricade::OnUpdate() {
		// �o���P�[�h���j�󂳂ꂽ��
		if (!m_IsAlive) {
			m_DeathTotalTime += App::GetApp()->GetElapsedTime();

			// �������o��
			// �o���P�[�h���ɒ��߂�
			auto ptrTrans = GetComponent<Transform>();
			auto pos = ptrTrans->GetPosition();
			pos.y -= 0.05f;
			ptrTrans->SetPosition(pos);

			if (m_DeathTotalTime > m_DeathTime) {
				// ����Ă��ǁ@���ɍs������I�u�W�F�N�g������
				GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
				// �G�t�F�N�g���~�߂�
				//m_EfkPlay->StopEffect();
			}
		}

	}

	void Barricade::RemoveObject() {


	}



	//--------------------------------------------------------------------------------------
	//	�����܂�
	//--------------------------------------------------------------------------------------
	SlowFloor::SlowFloor(const shared_ptr<Stage>& stagePtr,
		const Vec3& position) :
		MyGameObject(stagePtr),
		m_Position(position)
	{}
	SlowFloor::SlowFloor(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode) :
		MyGameObject(stagePtr),
		m_Scale(0),
		m_Quat(0),
		m_Position(0)
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
	}


	void SlowFloor::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetQuaternion(m_Quat);
		ptrTrans->SetPosition(m_Position);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		SetAlphaActive(true);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		// �e�N�X�`��������
		ptrDraw->SetTextureResource(L"Blue.png");

		AddTag(L"SlowFloor");

	}

	void SlowFloor::OnUpdate() {

	}


	//--------------------------------------------------------------------------------------
	//	��
	//--------------------------------------------------------------------------------------
	Tree::Tree(const shared_ptr<Stage>& stagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		MyGameObject(stagePtr),
		m_Scale(Scale),
		m_Quat(Rotation),
		m_Position(Position),
		m_MeshName(L"Tree.bmf")
	{}
	Tree::Tree(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode) :
		MyGameObject(stagePtr),
		m_Scale(0),
		m_Quat(0),
		m_Position(0),
		m_MeshName(L"Tree.bmf")
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

		m_MeshName = XmlDocReader::GetAttribute(pNode, L"MeshName");
	}


	//������
	void Tree::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetQuaternion(m_Quat);
		ptrTransform->SetPosition(m_Position);

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.75f, 0.75f, 0.75f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.6f, 0.0f)
		);
		SetAlphaActive(true);

		// ���b�V���̕`��
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(m_MeshName);
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//�e�̕`��
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(m_MeshName);
		ptrShadow->SetMeshToTransformMatrix(spanMat);


	}
	//--------------------------------------------------------------------------------------
	//	�؂̃X�v���C�g�RD
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	TreeSprite::TreeSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec3& startScale,
		const Vec3& startRotaiton,
		const Vec3& startPos
	) :
		Sprite3D(stagePtr, textureKey, startScale, startRotaiton, startPos)
	{}
	
}