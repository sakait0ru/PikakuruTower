/*!
@file GameManager.h
@brief �Q�[���S�̂��Ǘ�����}�l�[�W���[
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	�Q�[���S�̂��Ǘ�����}�l�[�W���[
	//--------------------------------------------------------------------------------------
	class GameManager {
	private:
		static GameManager* m_GM;

		// �X�e�[�W�ԍ����L��
		int m_StageNumber = 1;

		// �X�e�[�W���n�܂�����
		bool m_Start = false;
		// �X�e�[�W���I����Ă��邩
		bool m_Finish = false;

		// �ǂ̑ϋv�x
		int m_MaxWallHp = 100;
		// �e�A�C�e���̍ő及����(1��)
		int m_MaxFlashItem = 5;
		int m_MaxNetItem = 5;


		// �ǂ̍��̑ϋv�x
		int m_WallHp = m_MaxWallHp;
		// �M���ʃA�C�e���̐�
		int m_FlashItem = 0;
		// �l�b�g�A�C�e���̐�
		int m_NetItem = 0;
		// ���̃X�e�[�W�ɂ�Enemy�̐�
		int m_EnemyCount = 0;

		// spotlight�̈ʒu���L��
		Vec3 m_SpotLightPosition;
	public:
		GameManager()
		{
		};
		~GameManager() {};
		static void CreateGM();
		static GameManager* getInstance();

		// �ǂ�Hp�����炷
		void DamageWallHp(int attack = 1) { m_WallHp -= attack; }

		void HeelWallHp(int i) {
			m_WallHp += i;


			if (m_WallHp >= m_MaxWallHp) {
				m_WallHp = m_MaxWallHp;
			}
		}

		// �M���ʃA�C�e�����g��
		bool UseFlashItem() {
			// m_FlashItem��1�ȏ゠���
			if (m_FlashItem > 0) {
				m_FlashItem--;
				// �g�����̂�true
				return true;
			}
			// 0�ȉ��Ŏg���Ȃ������̂�false
			return false;
		}
		// �l�b�g�A�C�e�����g��
		bool UseNetItem() {
			// m_NetItem��1�ȏ゠���
			if (m_NetItem > 0) {
				m_NetItem--;
				// �g�����̂�true
				return true;
			}
			// 0�ȉ��Ŏg���Ȃ������̂�false
			return false;
		}

		// reset
		void ResetHp() { m_WallHp = m_MaxWallHp; }

		// �ŏ��Ɏ����Ă���A�C�e���̐�
		void ResetNetItem() { m_NetItem = 2; }
		void ResetFlashItem() { m_FlashItem = 2; }

		void ResetEnemyCount() { m_EnemyCount = 0; }

		// ���ׂă��Z�b�g����
		void ResetMainStage() {
			m_Start = false;
			m_Finish = false;
			ResetHp();
			ResetFlashItem();
			ResetNetItem();
			ResetEnemyCount();
		}

		// Remove
		void RemoveEnemyCount() { m_EnemyCount--; }

		// add
		//����ȏ�ɂȂ����Ⴄ���
		void AddFlashItem() { if (m_FlashItem < m_MaxFlashItem) m_FlashItem++; }
		void AddNetItem() { if (m_NetItem < m_MaxNetItem) m_NetItem++; }

		void AddEnemyCount() { m_EnemyCount++; }

		// get
		int GetStageNumber() const { return m_StageNumber; }
		bool GetStartActive() const { return m_Start; }
		bool GetFinishActive() const { return m_Finish; }

		int GetWallHp() const { return m_WallHp; }
		int GetMaxWallHp() const { return m_MaxWallHp; }

		int GetFlashItem() const { return m_FlashItem; }
		int GetNetItem() const { return m_NetItem; }

		int GetEnemyCount() const { return m_EnemyCount; }

		Vec3 GeSpotLightPositon() const { return m_SpotLightPosition; }

		// set
		void GetStageNumber(const int i) { m_StageNumber = i; }
		void SetStartActive(const bool b) { m_Start = b; }
		void SetFinishActive(const bool b) { m_Finish = b; }

		void SetSpotLightPosition(Vec3 spotLightPosition) { m_SpotLightPosition = spotLightPosition; }
	};

	// wave�Ɏg���G�l�~�[�̃p�����[�^�[
	struct EnemyParameter
	{
		Vec3 scale;
		Vec3 rotation;
		Vec3 position;
		int  captainNumber = 0;
		float spawnTime = 0.0f;
		bool created = false;
	};

	//--------------------------------------------------------------------------------------
	///	�Q�[���S�̂��Ǘ�����}�l�[�W���[
	//--------------------------------------------------------------------------------------
	class WaveManager {
	private:
		static WaveManager* m_WM;

		// ����Wave
		int m_WaveNum = 1;
		// ���̃X�e�[�W�̍ő��Wave��
		int m_MaxWave = 4;
		// �N���A���Ă��邩
		bool m_Clear = false;

		vector< vector<EnemyParameter> > m_nullDate = {
			{
				// ���ʂ̃]���r
			},
			{
				// �����]���r�@
			},
			{
				// �V�[���h�]���r�@�̗͑���
			},
			{
				// �n���}�[�]���r�@�U���͍���
			},
			{
				// �H��]���r�@���ʂ̃]���r�ƕς��Ȃ�
			},
			{
				//�����]���r�@
			},
			{
				//�����]���r�@
			},

		};

		vector< vector<EnemyParameter> > m_stageDate1 = {
			{
				// ���ʂ̃]���r

			},
			{
				// �����]���r�@
			},
			{
				// �V�[���h�]���r�@�̗͑���

			},
			{
				// �n���}�[�]���r�@�U���͍���
			},
			{
				// �H��]���r�@���ʂ̃]���r�ƕς��Ȃ�
			},
			{
				//�����]���r�@
			},
			{
				//�����]���r�@
			},
		};
		vector< vector<EnemyParameter> > m_stageDate2 = {
			{
				// ���ʂ̃]���r
			},
			{
				// �����]���r
			},
			{
				// �V�[���h�]���r�@�̗͑���
			},
			{
				// �n���}�[�]���r�@�U���͍���
			},
			{
				// �H��]���r�@���ʂ̃]���r�ƕς��Ȃ�
			},
			{
				//�����]���r�@
			},
			{
				//�����]���r�@
			},

		};
		vector< vector<EnemyParameter> > m_stageDate3 = {
			{
				// ���ʂ̃]���r
			},
			{
				// �����]���r
			},
			{
				// �V�[���h�]���r�@�̗͑���
			},
			{
				// �n���}�[�]���r�@�U���͍���
			},
			{
				// �H��]���r�@���ʂ̃]���r�ƕς��Ȃ�
			},
			{
				//�����]���r�@
			},
			{
				//�����]���r�@
			},

		};
		vector< vector<EnemyParameter> > m_stageDate4 = {
			{
				// ���ʂ̃]���r
			},
			{
				// �����]���r
			},
			{
				// �V�[���h�]���r�@�̗͑���
			},
			{
				// �n���}�[�]���r�@�U���͍���
			},
			{
				// �H��]���r�@���ʂ̃]���r�ƕς��Ȃ�
			},
			{
				//�����]���r�@
			},
			{
				//�����]���r�@
			},

		};
		vector< vector<EnemyParameter> > m_stageDate5 = {
			{
				// ���ʂ̃]���r
			},
			{
				// �����]���r
			},
			{
				// �V�[���h�]���r�@�̗͑���
			},
			{
				// �n���}�[�]���r�@�U���͍���
			},
			{
				// �H��]���r�@���ʂ̃]���r�ƕς��Ȃ�
			},
			{
				//�����]���r�@
			},
			{
				//�����]���r�@
			},
		};

	public:
		WaveManager()
		{
		};
		~WaveManager() {};
		static void CreateWM();
		static WaveManager* getInstance();

		// reset
		void ResetWaveNum() { 
			m_WaveNum = 1; 
			m_Clear = false;
		}

		// remove
		// �G�l�~�[�̃f�[�^���폜�A�܂�����ɂ���
		void RemoveWaveEnemyData() {
			m_stageDate1 = m_nullDate;
			m_stageDate2 = m_nullDate;
			m_stageDate3 = m_nullDate;
			m_stageDate4 = m_nullDate;
		}


		// add
		//����wave�ɂ���
		void AddWaveNum() { m_WaveNum++; }

		// get
		int GetWaveNum() const { return m_WaveNum; }
		int GetMaxWave() const { return m_MaxWave; }
		vector< vector<EnemyParameter> > GetStageDate() const {
			switch (m_WaveNum)
			{
			case 1:
				return m_stageDate1;
				break;
			case 2:
				return m_stageDate2;
				break;
			case 3:
				return m_stageDate3;
				break;
			case 4:
				return m_stageDate4;
				break;
			case 5:
				return m_stageDate5;
				break;
			default:
				return m_stageDate1;
				break;
			}
		}
		bool IsClear() const { return m_Clear; }

		// set
		void SetMaxWave(int i) { m_MaxWave = i; }
		void SetClear(bool b) { m_Clear = b; }

		void SetWaveDate(Vec3 scale,Quat quat,Vec3 pos,int waveNum,int captainNum,float spawnTime,int enemyType) {
			//EnemyParameter�ɓ��Ă͂߂�
			EnemyParameter ep = { scale , Vec3(0, 0, 0) ,pos ,captainNum ,spawnTime };
			switch (waveNum)
			{
			case 0:
				m_stageDate1[enemyType].push_back(ep);
				break;
			case 1:
				m_stageDate2[enemyType].push_back(ep);
				break;
			case 2:
				m_stageDate3[enemyType].push_back(ep);
				break;
			case 3:
				m_stageDate4[enemyType].push_back(ep);
				break;
			default:
				break;
			}

		}
	};

}