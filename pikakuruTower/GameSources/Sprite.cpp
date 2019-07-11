/*!
@file Sprite.cpp
@brief �X�v���C�g
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	2D�̃X�v���C�g
	//--------------------------------------------------------------------------------------
	Sprite::Sprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		MyGameObject(stagePtr),
		m_TextureKey(textureKey),
		m_StartScale(startScale),
		m_StartPos(startPos)
	{}

	void Sprite::OnCreate() {
		float helfSize = 0.5f;
		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f, -0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, -0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f,  1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f,  1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//0  1
		//2  3
		//
		SetAlphaActive(true);

		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);

		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_TextureKey);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);

	}


	//--------------------------------------------------------------------------------------
	///	3D�̃X�v���C�g
	//--------------------------------------------------------------------------------------
	Sprite3D::Sprite3D(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec3& startScale,
		const Vec3& startRotaiton,
		const Vec3& startPos) :
		MyGameObject(stagePtr),
		m_TextureKey(textureKey),
		m_StartScale(startScale),
		m_StartRotation(startRotaiton),
		m_StartPos(startPos)
	{}

	void Sprite3D::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale);
		ptrTrans->SetRotation(m_StartRotation);
		ptrTrans->SetPosition(m_StartPos);

		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		//�`�悷��e�N�X�`����ݒ�
		ptrDraw->SetTextureResource(m_TextureKey);
		SetAlphaActive(true);

	}

}