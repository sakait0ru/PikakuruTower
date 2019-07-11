/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Vibration
	{
	protected:
		float m_VibCount[4] = {};
		float m_VibInterval[4] = {};
		bool m_isVib[4] = {};
	public:
		DECLARE_SINGLETON_INSTANCE(Vibration)

		void SetVibration(float time, float left, float right, int CntNum = 0);

		void Update();
	};

	//--------------------------------------------------------------------------------------
	///	�v���C���[
	//--------------------------------------------------------------------------------------
	class Player : public MyGameObject {
	private:
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		float m_LightPower = 1.0f;

		//���̓n���h���[
		InputHandler<Player> m_InputHandler;

		bool m_Big = true;
		bool m_Active = true;

		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_EfkEffect;
		//�G�t�F�N�g���s�I�u�W�F�N�g
		shared_ptr<EfkPlay> m_EfkPlay;

		// �M���ʂ��g���邩
		bool m_IsFlashItem = true;
		// �M���ʂ̃C���^�[�o������
		float m_FlashItemTime = 0.0f;
		float m_FlashItemIntervalTime = 10.0f;

	public:
		Player(const shared_ptr<Stage>& stagePtr);
		Player(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position);
		~Player() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//A�{�^��
		void OnPushA();
		//X�{�^��
		void OnPushB();

		bool GetActive() const { return m_Active; }
		float GetLightPower() const { return m_LightPower; }
	};

	//--------------------------------------------------------------------------------------
	///	�t���b�V���{�̂̃X�v���C�g
	//--------------------------------------------------------------------------------------
	class FlashSprite : public MyGameObject {
	private:
		float m_TotalTime;
		bool m_Stoped;
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		
		float m_ScaleSpanMat;
		float m_Spin;

		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_EfkEffect;
		//�G�t�F�N�g���s�I�u�W�F�N�g
		shared_ptr<EfkPlay> m_EfkPlay;

	public:
		FlashSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec3& startScale,
			const Vec3& startRotaiton,
			const Vec3& startPos);
		~FlashSprite() {}

		void OnCreate() override;
		void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//	�}�X�L���O�X�v���C�g
	//--------------------------------------------------------------------------------------
	class FlashMaskSprite : public GameObject {
		wstring m_TextureKey;
		shared_ptr<MeshResource> m_SpriteMesh;
		float m_ScaleSpeed;
		float m_AlphaNum;
	public:
		//�\�z�Ɣj��
		FlashMaskSprite(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey
		);
		virtual ~FlashMaskSprite();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//����
		//�`��
		virtual void OnDraw() override;
	};
}
//end basecross