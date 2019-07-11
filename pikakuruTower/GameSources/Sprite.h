/*!
@file Sprite.h
@brief �X�v���C�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	2D�̃X�v���C�g
	//--------------------------------------------------------------------------------------
	class Sprite : public MyGameObject {
	protected:
		wstring m_TextureKey;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
	public:
		Sprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~Sprite() {};
		virtual void OnCreate()override;
	};

	//--------------------------------------------------------------------------------------
	///	3D�̃X�v���C�g
	//--------------------------------------------------------------------------------------
	class Sprite3D : public MyGameObject {
	protected:
		wstring m_TextureKey;
		Vec3 m_StartScale;
		Vec3 m_StartRotation;
		Vec3 m_StartPos;

	public:
		Sprite3D(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec3& startScale,
			const Vec3& startRotaiton,
			const Vec3& startPos);
		~Sprite3D() {};
		virtual void OnCreate() override;
	};




}
