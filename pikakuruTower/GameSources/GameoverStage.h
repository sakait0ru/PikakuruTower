#pragma once
#include "stdafx.h"

namespace basecross {

	class GameoverAnimeSprite : public Sprite {

	private:
		Vec3 m_Rot = Vec3(0, 0, 0);

		float m_Speed = -0.07f;                    //��]����X�s�[�h
        float m_AccelPlus = 0.05f;                 //�����x
		float m_StartSpeed = m_Speed;              //���̃X�s�[�h
		float m_Accel = 1.00f;		               //��̉����x
		float m_AccelRot = m_Accel + m_AccelPlus;  //�����Ȃ����(0���甼���܂�)
		float m_DecelRot = m_Accel + -m_AccelPlus; //�x���Ȃ����(���������肫��܂�)

		float m_QuaX = 0.0f;   //�O�p�̕ω���
		float m_MoveX = 1.0f;  //�O�p�̓�������
		float m_MaxX = 20.0f;  //�����ő�l


	public:
		GameoverAnimeSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~GameoverAnimeSprite() {};

		void SetActive(bool Active);
		void Rotation(bool Active);
		void Transluc(bool Active);
	};

	class GameoverStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateGameoverSprite();
		//���̓n���h���[
		InputHandler<GameoverStage> m_InputHandler;


		int m_StageNum = 0;                //���I�����Ă�ԍ�

		bool m_CntrolLock;                 //�X�e�B�b�N����x�|�����烍�b�N

		int PushTime = 0;                  //�X�e�B�b�N��|�����������̎��Ԃ����

		float Accel = 0.99f;               //�����x
		float PushTimeEndS = 30.0f;        //���̑I���܂ł̊Ԋu�̏����l
		float PushTimeEnd = PushTimeEndS;  //���̑I���܂ł̊Ԋu�������l�ɐݒ�	
		float PushTimeEndMax = 7.5f;       //�ő��l

		bool FadeSwitch = true;            //�t�F�[�h���n�܂��Ă邩�ǂ���


	public:
		//�\�z�Ɣj��
		//GameoverStage() :Stage() {}
		
		GameoverStage() :Stage()
			, m_SpVec(8) {}

		virtual ~GameoverStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		//A�{�^��
		void OnPushA() {
			//�������Ȃ�
		}
		//B�{�^��
		void OnPushB();


		vector<shared_ptr<GameoverAnimeSprite>> m_SpVec;

		shared_ptr<SoundItem> m_BGM;
	};


	class GameoverSprite : public GameObject {
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
		GameoverSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//�j��
		virtual ~GameoverSprite();
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate()override {}
	};
}