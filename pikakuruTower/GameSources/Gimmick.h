#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�o���P�[�h
	//--------------------------------------------------------------------------------------
	class Barricade : public MyGameObject {
	private:
		Vec3 m_Scale;
		Quat m_Quat;
		Vec3 m_Position;

		//����ł��炽��������
		float m_DeathTotalTime = 0.0f;
		// �����鎞��
		float m_DeathTime = 2.0f;

		// �����c���Ă��邩
		bool m_IsAlive = true;

		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_EfkEffect;
		//�G�t�F�N�g���s�I�u�W�F�N�g
		shared_ptr<EfkPlay> m_EfkPlay;
	public:
		Barricade(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position
		);
		Barricade(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode);

		~Barricade() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		// �o���P�[�h�����鎞�̓���
		void RemoveObject();
		
		//�@�����Ă��邩�ݒ�
		void SetdIsAlive(bool b) { 
			auto ptrColl = AddComponent<CollisionSphere>();
			//ptrColl->RemoveExcludeCollisionTag(L"Enemy");
			ptrColl->SetSleepActive(true);
			m_IsAlive = false;
		}

		bool GetIsAlive() { return m_IsAlive; }
	};

	//--------------------------------------------------------------------------------------
	//	�����܂�
	//--------------------------------------------------------------------------------------
	class SlowFloor : public MyGameObject {
	private:
		Vec3 m_Scale;
		Quat m_Quat;
		Vec3 m_Position;

	public:
		SlowFloor(const shared_ptr<Stage>& stagePtr, const Vec3& position);
		SlowFloor(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode);

		~SlowFloor() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};

	//--------------------------------------------------------------------------------------
	//	��
	//--------------------------------------------------------------------------------------
	class Tree : public MyGameObject {
		Vec3 m_Scale;
		Quat m_Quat;
		Vec3 m_Position;
		wstring m_MeshName;
	public:
		//�\�z�Ɣj��
		Tree(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		Tree(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode);
		~Tree() {}
		//������
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//	�؂̃X�v���C�g�RD
	//--------------------------------------------------------------------------------------
	class TreeSprite : public Sprite3D {
	public:
		//�\�z�Ɣj��
		TreeSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec3& startScale,
			const Vec3& startRotaiton,
			const Vec3& startPos
		);
		~TreeSprite() {}

	};

}