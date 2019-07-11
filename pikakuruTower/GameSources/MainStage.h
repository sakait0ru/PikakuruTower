/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class PauseSprite;
	class WallUnit;
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class MainStage : public Stage {


		// Xml�t�@�C���̃p�X
		wstring m_stageXmlPath;

		//Sprite�������łȂ����𕪗�����z��
		vector< shared_ptr<GameObject> > m_SpriteVec;
		vector< shared_ptr<GameObject> > m_Object3DVec;
		//3D�̓����Ɣ񓧖��𕪗�����z��
		vector< shared_ptr<GameObject> > m_Object3DNormalVec;
		vector< shared_ptr<GameObject> > m_Object3DAlphaVec;

		//�X�v���C�g����Ă�z��
		vector<weak_ptr<PauseSprite>> m_SpVec;
		//�G�t�F�N�g�̃C���^�[�t�F�C�X
		shared_ptr<EfkInterface> m_EfkInterface;

		//�r���[�̍쐬
		void CreateViewLight();
		// ���쐬
		void CreateFloor();
		//�Z���}�b�v�̍쐬
		void CreateStageCellMap();
		// ��O�̑傫�ȕǍ쐬
		void CreateWall();
		// UI�̍쐬
		void CreateUI();
		// ��Q���̍쐬
		void CreateGimmick();
		// �v���C���[�i�X�|�b�g���C�g�j�̍쐬
		void CreatePlayer();
		// Wave�摜�̐���
		void CreateWave();
		//�G�̍쐬
		void CreateEnemy(float time);
		//�G�t�F�N�g���쐬
		void CreateEffect();

		float m_StartTime = 0;
		int PauseSelect = 0;

		shared_ptr<MyCamera> m_Camera;

		shared_ptr<SoundItem> m_BGM;

		bool m_Pause = false;
		bool m_PauseFade = false;

		Vec3 m_HpUIPos;
		bool m_cntlrock = false;

		bool FadeSwitch = true;      //�t�F�[�h�̃X�C�b�`

		// Wave�̃G�l�~�[���i�[����ꏊ
		vector< vector<EnemyParameter> > waveVec;

		// Wave�̎��ԁ@����ɉ����ēG���o��
		float m_WaveTime = 0.0f;
		// Wave�̓G�����ׂďo���I���Ă��邩
		bool m_WaveCreated = false;

		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_EfkEffect[7];
		//�G�t�F�N�g���s�I�u�W�F�N�g
		shared_ptr<EfkPlay> m_EfkPlay[7];

		// �Q�[���I�[�o�[�p��Timer
		float m_GameOverTime = 0.0f;
		
		// �Q�[���N���A�p��Timer
		float m_GameClearTime = 0.0f;

	public:
		//�\�z�Ɣj��
		MainStage() :Stage(), m_SpVec(3) {}
		virtual ~MainStage() {}
		
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDraw()override;
		virtual void UpdateStage()override;
		virtual void DrawStage()override;
		void ChangePause(int num);

		//�Œ�̃{�b�N�X�̃R�X�g���Z���}�b�v�ɔ��f
		void SetCellMapCost();

		//�G�t�F�N�g�̃C���^�[�t�F�C�X�̎擾
		shared_ptr<EfkInterface> GetEfkInterface() const {
			return m_EfkInterface;
		}

		float GetStartTime() const { return m_StartTime; }
		// Camera���擾
		shared_ptr<MyCamera> GetCamera() { return m_Camera; }

		Vec3 GetHpUIPos() { return m_HpUIPos; }
		void SetHpUIPos(Vec3 v3) { m_HpUIPos = v3; }

		shared_ptr<EfkEffect> GetEfkDate(int i) { return m_EfkEffect[i]; }
	};

	
}
//end basecross

