/*!
@file Wall.h
@brief ��
*/

#pragma once
#include "stdafx.h"

namespace basecross 
{
	//--------------------------------------------------------------------------------------
	//	�ǂ̓����蔻��
	//--------------------------------------------------------------------------------------
	class Wall : public MyGameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		Wall(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		~Wall() {}
		//������
		virtual void OnCreate() override;
	};	

	//--------------------------------------------------------------------------------------
	//	�ǂ̃��f����P��
	//--------------------------------------------------------------------------------------
	class WallUnit : public MyGameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		WallUnit(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		~WallUnit() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//�Q�[���I�[�o�[���������A�ǂ�������
		void WallUnitDown();
	};


	//--------------------------------------------------------------------------------------
	//	�ǂ̑_����Ƃ���
	//--------------------------------------------------------------------------------------
	class WallTaget : public MyGameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		WallTaget(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		~WallTaget() {}
		//������
		virtual void OnCreate() override;
	};


	//--------------------------------------------------------------------------------------
	//	�^���[
	//--------------------------------------------------------------------------------------
	class Tower : public MyGameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		Tower(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		~Tower() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//	�^���[�̉��̂Ƃ���
	//--------------------------------------------------------------------------------------
	class TowerUnder : public MyGameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		TowerUnder(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		~TowerUnder() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

}