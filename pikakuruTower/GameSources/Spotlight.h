/*!
@file Spotlight.h
@brief �X�|�b�g���C�g
*/

#pragma once
#include "stdafx.h"

namespace basecross 
{
	class Spotlight : public MyGameObject 
	{
	private:
		// �R���g���[����������x�N�g���𓾂�
		Vec3 GetMoveVector() const;
		// �X�|�b�g���C�g�̃X�N�G�A]
		//shared_ptr<MeshResource> m_SquareMeshResource;

		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		// ���C�g�̋����G�l�~�[�ɑ΂���U����
		float m_LightPower = 8;
		float m_Speed = 0.05;
		// �傫���Ƃ�
		bool m_Big = true;
		// �I�����I�t��
		bool m_Active = true;
		bool m_On = true;
		// �������֐�
		void MovePlayer();
		//�f�o�C�X�|�W�V����
		Vec3 m_DevPos;

	public:
		Spotlight(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position);
		~Spotlight() {}

		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;

		void CalcDevPos();

		bool GetActive() const { return m_Active; }
		bool GetBig() const { return m_Big; }
		float GetLightPower() const { return m_LightPower; }

		Vec3 GetDevPos() const { return m_DevPos; }

		bool GetOn() { return m_On; }
	};
}
//end basecross