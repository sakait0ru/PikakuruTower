 /*!
@file LoadingStage.h
@brief ���[�h�V�[��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class LoadingZombie;
	class LoadingSelectSprite;
	class TriMoveSprite;
	//--------------------------------------------------------------------------------------
	///	���[�h�X�e�[�W
	//--------------------------------------------------------------------------------------
	class LoadingStage : public Stage {
		// Xml�t�@�C���̃p�X
		wstring m_stageXmlPath;

		//�r���[�̍쐬
		void CreateViewLight();
		//���[�f�B���O�X�v���C�g�̍쐬
		void CreateLoadingSprite();
		vector<shared_ptr<LoadingSelectSprite>> m_SpVec;


		int m_ReadNum = 0;

		bool m_CntlLock = true;

		bool FadeSwitch = true;      //�t�F�[�h�̃X�C�b�`

		shared_ptr<Sprite> m_ReadmeSprite;
		shared_ptr<LoadingZombie> m_Enemy;

		shared_ptr<TriMoveSprite> m_RTriSprite;
		shared_ptr<TriMoveSprite> m_LTriSprite;
		
	public:
		LoadingStage() :Stage(), m_SpVec(10) {}
		virtual ~LoadingStage() {}
		//������
		void LoadingChangeSelect(int num);

		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;

		int GetReadNum() const { return m_ReadNum; }

	};

	//--------------------------------------------------------------------------------------
	///	�ǂݍ��ݒ��c�X�v���C�g
	//--------------------------------------------------------------------------------------
	class LoadingSprite : public Sprite {
	private:
		float m_TotalTime = 0.0f;
		float m_ChangeTime = 0.0f;

	public:
		LoadingSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~LoadingSprite() {}
		//�X�V
		virtual void OnUpdate()override;

	};


	//--------------------------------------------------------------------------------------
	///	�v���r���[�]���r
	//--------------------------------------------------------------------------------------
	class LoadingZombie : public MyGameObject {
	private:
		Vec3 m_Rot = Vec3(0, 0, 0);
	public:
		LoadingZombie(const shared_ptr<Stage>& stagePtr);
		~LoadingZombie() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void SetRot(const Vec3 rot) { m_Rot = rot; }
	};

	//--------------------------------------------------------------------------------------
	///	LoadingSelectSprite��ʗp�̃X�v���C�g
	//--------------------------------------------------------------------------------------
	class LoadingSelectSprite : public Sprite {
	public:
		//�\�z�Ɣj��
		LoadingSelectSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		bool m_cntlrock;

		virtual ~LoadingSelectSprite() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void Akarusa(bool flg);
	};

	//--------------------------------------------------------------------------------------
	// �G�l�~�[�̃f�[�^���󂯎��N���X
	//--------------------------------------------------------------------------------------
	class EnemyDataLoad : public MyGameObject {
	private:
		Vec3 m_Scale;
		Quat m_Quat;
		Vec3 m_Position;

		int m_WaveNum;

		int m_CaptainNum;

		float m_SpawnTime;

		int m_EnemyType;
	public:
		//�\�z�Ɣj��
		EnemyDataLoad(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode);
		virtual ~EnemyDataLoad() {}

		virtual void OnCreate() override;
	};



	class TriMoveSprite : public Sprite {
	private:

		float m_QuaX = 0.0f;   //�O�p�̕ω���
		float m_MoveX = 1.0f;  //�O�p�̓�������
		float m_MaxX = 20.0f;  //�����ő�l


	public:
		TriMoveSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~TriMoveSprite() {}
		//�X�V
		virtual void OnUpdate()override;

		void RTriMove(bool Avtive);
		void LTriMove(bool Avtive);
	};
}