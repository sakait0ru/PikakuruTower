/*!
@file TitleEnemy.h
@brief �G
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// �^�C�g����ʂŎg���]���r
	//--------------------------------------------------------------------------------------
	class TitleEnemy :public MyGameObject {
		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_EfkEffect[4];
		//�G�t�F�N�g���s�I�u�W�F�N�g
		shared_ptr<EfkPlay> m_EfkPlay[4];
	protected:
		Vec3 m_Scale;     //�傫��
		Vec3 m_Rotation;  //��]
		Vec3 m_Position;  //�ꏊ

		int m_Nunber = 0;
		int Key = 0;
		float m_MaxHp = 200.0f;    //�ő�HP
		float m_Hp = 200.0f;       //���݂�HP
		float m_ChangTime = 0.0f;

		bool m_Light = false;
		bool m_AnotherLight = false;
		bool m_Damage = false;
		bool m_Hit = false;

		unique_ptr<LayeredStateMachine<TitleEnemy>>m_StateMachine;
		// �v���C���[
		shared_ptr<Spotlight> m_Spotlight;

		float m_EfkTime[4] = { 0.5f,0.5f,0.5f,0.5f };

	public:


		TitleEnemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position
		);
		~TitleEnemy() {}

		virtual void OnCreate() override;
		virtual void OnUpdate()override;

		//����
		void WalkMove();
		//�ړ�����
		Vec3 HumanMove();
		//�l�ԂɂȂ������̓���
		void HumanWalkMove();
		//��]
		void RotToHead();
		//�_���[�W�`�F�b�N
		void LightDamegeCheck();
		//���C�g����_���[�W���󂯂Ă���
		void DamageReceive();
		//�e�N�X�`���̕ύX
		void ChangTex();

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExit(shared_ptr<GameObject>& Other) override;

	};

}