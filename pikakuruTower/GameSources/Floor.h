/*!
@file Floor.h
@brief ��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	class FixedBox : public MyGameObject {
		Vec3 m_Scale;
		Quat m_Quat;
		Vec3 m_Position;

		wstring m_TextureName;
	public:
		//�\�z�Ɣj��
		FixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		FixedBox(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode);
		~FixedBox() {}
		//������
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//	�����܂�
	//--------------------------------------------------------------------------------------
	class FireTorch : public MyGameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_EfkEffect;
		//�G�t�F�N�g���s�I�u�W�F�N�g
		shared_ptr<EfkPlay> m_EfkPlay;
	public:
		//�\�z�Ɣj��
		FireTorch(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position
		);
		~FireTorch() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;


	};
}

//end basecross