#pragma once
#include "stdafx.h"

namespace basecross {

	class ClearAnimeSprite : public Sprite {
	private:
		Vec3 m_Rot = Vec3(0, 0, 0);

		float m_Speed = -0.07f;
		float m_AccelPlus = 0.05f;
		float m_StartSpeed = m_Speed;
		float m_Accel = 1.00f;
		float m_AccelRot = m_Accel + m_AccelPlus;
		float m_DecelRot = m_Accel + -m_AccelPlus;

	public:
		ClearAnimeSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~ClearAnimeSprite() {};

		void SetActive(bool Active);
		void Rotation(bool Active);
		void Transluc(bool Active);

		float QuaX = 0.0f;   //�O�p�̕ω���
		float MoveX = 1.0f;  //�O�p�̓�������
		float MaxX = 20.0f;  //�����ő�l
	};

	class ClearStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateClearSprite();
		//���̓n���h���[
		InputHandler<ClearStage> m_InputHandler;
	public:
		//�\�z�Ɣj��
		//ClearStage() :Stage() {}
		ClearStage() :Stage()
			, m_SpVec(9) {}
		virtual ~ClearStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		//A�{�^��
		void OnPushA() {
			//�����Ȃ�
		}
		//B�{�^��
		void OnPushB();

		vector<shared_ptr<ClearAnimeSprite>> m_SpVec;

		shared_ptr<SoundItem> m_BGM;
		int m_StageNum = 0;

		bool m_CntrolLock;

		int PushTime = 0;

		float Accel = 0.99f;               //�����x
		float PushTimeEndS = 30.0f;        //���̑I���܂ł̊Ԋu�̏����l
		float PushTimeEnd = PushTimeEndS;  //���̑I���܂ł̊Ԋu�������l�ɐݒ�	
		float PushTimeEndMax = 7.5f;       //�ő��l

		bool FadeSwitch = true;      //�t�F�[�h�̃X�C�b�`

	};


	class ClearSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_TextureKey;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	TextureKey	�e�N�X�`���L�[
		@param[in]	Trace	�����������邩�ǂ���
		@param[in]	StartScale	�����X�P�[��
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		ClearSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//�j��
		virtual ~ClearSprite();
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate()override {}
	};
}
