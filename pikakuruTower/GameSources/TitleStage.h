#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// �^�C�g���̉摜�ƃQ�[���X�^�[�g�̉摜
	//--------------------------------------------------------------------------------------
	class TitleAnimeSprite : public Sprite {
		Vec3 m_Rot = Vec3(0, 0, 0);
		Vec3 m_PikaPos = Vec3(-315.0f, 1025.0f, 0.0f);
		Vec3 m_StarPos = Vec3(-470.0f + 700.0f , 210.0f + 1385.6f , 0.0f);
		//Vec3 m_KuruPos = Vec3(-315.0f, 1025.0f, 0.0f);

		float m_KuruTime = 0.0f;
		float m_Transpar = 0.0f;
		float m_RotSpeed = 0.07f;
		

	public:
		TitleAnimeSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~TitleAnimeSprite() {};

		virtual void OnUpdate()override;

		void SetActive(bool Active);
		void Rotation(bool Active);

		void PikaDrop(bool Active);
		void KuruDrop(bool Active);
		void StarDrop(bool Active);

	};
	//--------------------------------------------------------------------------------------
	// �^�C�g���ɂ���Player
	//--------------------------------------------------------------------------------------
	class TitlePlayer : public MyGameObject {
	private:
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		float m_LightPower = 1.0f;

		//���̓n���h���[
		InputHandler<TitlePlayer> m_InputHandler;

		bool m_Big = true;
		bool m_Active = true;

		////�G�t�F�N�g
		//shared_ptr<EfkEffect> m_EfkEffect;
		////�G�t�F�N�g���s�I�u�W�F�N�g
		//shared_ptr<EfkPlay> m_EfkPlay;
	public:
		TitlePlayer(const shared_ptr<Stage>& stagePtr);
		TitlePlayer(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position);
		~TitlePlayer() {}

		virtual void OnCreate() override;
		//virtual void OnUpdate() override;
		//A�{�^��
		//void OnPushA();
		//X�{�^��
		//void OnPushB();

		bool GetActive() const { return m_Active; }
		float GetLightPower() const { return m_LightPower; }
	};

	//--------------------------------------------------------------------------------------
	// �^�C�g���X�e�[�W
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {

		//Sprite�������łȂ����𕪗�����z��
		vector< shared_ptr<GameObject> > m_SpriteVec;
		vector< shared_ptr<GameObject> > m_Object3DVec;
		//3D�̓����Ɣ񓧖��𕪗�����z��
		vector< shared_ptr<GameObject> > m_Object3DNormalVec;
		vector< shared_ptr<GameObject> > m_Object3DAlphaVec;

		//�G�t�F�N�g�̃C���^�[�t�F�C�X
		shared_ptr<EfkInterface> m_EfkInterface;


		//�r���[�̍쐬
		void CreateViewLight();
		// ���̍쐬
		void CreateFloor();
		// �X�|�b�g���C�g���쐬
		void CreateTitlePlayer();
		// ��O�̕ǂ��쐬
		void CreateWall();
		// �����܂��쐬
		void CreateFireTorch();
		//�^�C�}�[���쐬
		void CreateTimer();

		float TrueTime;               //true�̎��̎��Ԍv��
		float FalseTime;              //false�̎��̎��Ԍv��
		float TrueTimeEnd = 45.0f;    //�\�����Ă鎞��
		float FalseTimeEnd = 15.0f;   //�����ɂ��Ă鎞��
		float Switch = 1.0f;          //true��false�̐؂�ւ��p
		float TrueTimePlus = 1.0f;

		float DecTime;                //�{�^�������Ă���̎��Ԍv��
		float DecSwitch = 0.0f;       //����L�[�̃X�C�b�`

		float FlashingSpeed = 0.2f;
		float FlashingTime = 80.0f;
		float FlashingEnd = 120.0f;

		bool FadeSwitch = true;      //�t�F�[�h�̃X�C�b�`
		float FadeCount = 0.0f;  //�t�F�[�h�J�n����̎��Ԍv��

		bool m_Start = true;         //�^�C�g�����S�������Ă��邩�ǂ���
		float m_Time = 0.0f;         //���Ԍv��

		// movie���Đ�����܂ł̎���
		float m_MovieTime = 0.0f;

		vector<shared_ptr<TitleAnimeSprite>> m_SpVec;

		shared_ptr<SoundItem> m_BGM;
	public:
		//�\�z�Ɣj��
		TitleStage() :Stage()
			, m_SpVec(6) {}


		virtual ~TitleStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		//�`��
		virtual void OnDraw() override;
		
		// �X�e�[�W��Draw���鏇��
		virtual void DrawStage()override;

		//�G�t�F�N�g�̃C���^�[�t�F�C�X�̎擾
		shared_ptr<EfkInterface> GetEfkInterface() const {
			return m_EfkInterface;
		}

	};
}
