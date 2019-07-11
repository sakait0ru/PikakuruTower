/*!
@file GameManager.h
@brief ゲーム全体を管理するマネージャー
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	ゲーム全体を管理するマネージャー
	//--------------------------------------------------------------------------------------
	class GameManager {
	private:
		static GameManager* m_GM;

		// ステージ番号を記憶
		int m_StageNumber = 1;

		// ステージが始まったか
		bool m_Start = false;
		// ステージが終わっているか
		bool m_Finish = false;

		// 壁の耐久度
		int m_MaxWallHp = 100;
		// 各アイテムの最大所持数(1桁)
		int m_MaxFlashItem = 5;
		int m_MaxNetItem = 5;


		// 壁の今の耐久度
		int m_WallHp = m_MaxWallHp;
		// 閃光玉アイテムの数
		int m_FlashItem = 0;
		// ネットアイテムの数
		int m_NetItem = 0;
		// 今のステージにるEnemyの数
		int m_EnemyCount = 0;

		// spotlightの位置を記憶
		Vec3 m_SpotLightPosition;
	public:
		GameManager()
		{
		};
		~GameManager() {};
		static void CreateGM();
		static GameManager* getInstance();

		// 壁のHpを減らす
		void DamageWallHp(int attack = 1) { m_WallHp -= attack; }

		void HeelWallHp(int i) {
			m_WallHp += i;


			if (m_WallHp >= m_MaxWallHp) {
				m_WallHp = m_MaxWallHp;
			}
		}

		// 閃光玉アイテムを使う
		bool UseFlashItem() {
			// m_FlashItemが1個以上あれば
			if (m_FlashItem > 0) {
				m_FlashItem--;
				// 使えたのでtrue
				return true;
			}
			// 0以下で使えなかったのでfalse
			return false;
		}
		// ネットアイテムを使う
		bool UseNetItem() {
			// m_NetItemが1個以上あれば
			if (m_NetItem > 0) {
				m_NetItem--;
				// 使えたのでtrue
				return true;
			}
			// 0以下で使えなかったのでfalse
			return false;
		}

		// reset
		void ResetHp() { m_WallHp = m_MaxWallHp; }

		// 最初に持っているアイテムの数
		void ResetNetItem() { m_NetItem = 2; }
		void ResetFlashItem() { m_FlashItem = 2; }

		void ResetEnemyCount() { m_EnemyCount = 0; }

		// すべてリセットする
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
		//上限以上になっちゃう問題
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

	// waveに使うエネミーのパラメーター
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
	///	ゲーム全体を管理するマネージャー
	//--------------------------------------------------------------------------------------
	class WaveManager {
	private:
		static WaveManager* m_WM;

		// 今のWave
		int m_WaveNum = 1;
		// このステージの最大のWave数
		int m_MaxWave = 4;
		// クリアしているか
		bool m_Clear = false;

		vector< vector<EnemyParameter> > m_nullDate = {
			{
				// 普通のゾンビ
			},
			{
				// 水着ゾンビ　
			},
			{
				// シールドゾンビ　体力多め
			},
			{
				// ハンマーゾンビ　攻撃力高め
			},
			{
				// 工作ゾンビ　普通のゾンビと変わりなし
			},
			{
				//隊長ゾンビ　
			},
			{
				//速いゾンビ　
			},

		};

		vector< vector<EnemyParameter> > m_stageDate1 = {
			{
				// 普通のゾンビ

			},
			{
				// 水着ゾンビ　
			},
			{
				// シールドゾンビ　体力多め

			},
			{
				// ハンマーゾンビ　攻撃力高め
			},
			{
				// 工作ゾンビ　普通のゾンビと変わりなし
			},
			{
				//隊長ゾンビ　
			},
			{
				//速いゾンビ　
			},
		};
		vector< vector<EnemyParameter> > m_stageDate2 = {
			{
				// 普通のゾンビ
			},
			{
				// 水着ゾンビ
			},
			{
				// シールドゾンビ　体力多め
			},
			{
				// ハンマーゾンビ　攻撃力高め
			},
			{
				// 工作ゾンビ　普通のゾンビと変わりなし
			},
			{
				//隊長ゾンビ　
			},
			{
				//速いゾンビ　
			},

		};
		vector< vector<EnemyParameter> > m_stageDate3 = {
			{
				// 普通のゾンビ
			},
			{
				// 水着ゾンビ
			},
			{
				// シールドゾンビ　体力多め
			},
			{
				// ハンマーゾンビ　攻撃力高め
			},
			{
				// 工作ゾンビ　普通のゾンビと変わりなし
			},
			{
				//隊長ゾンビ　
			},
			{
				//速いゾンビ　
			},

		};
		vector< vector<EnemyParameter> > m_stageDate4 = {
			{
				// 普通のゾンビ
			},
			{
				// 水着ゾンビ
			},
			{
				// シールドゾンビ　体力多め
			},
			{
				// ハンマーゾンビ　攻撃力高め
			},
			{
				// 工作ゾンビ　普通のゾンビと変わりなし
			},
			{
				//隊長ゾンビ　
			},
			{
				//速いゾンビ　
			},

		};
		vector< vector<EnemyParameter> > m_stageDate5 = {
			{
				// 普通のゾンビ
			},
			{
				// 水着ゾンビ
			},
			{
				// シールドゾンビ　体力多め
			},
			{
				// ハンマーゾンビ　攻撃力高め
			},
			{
				// 工作ゾンビ　普通のゾンビと変わりなし
			},
			{
				//隊長ゾンビ　
			},
			{
				//速いゾンビ　
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
		// エネミーのデータを削除、まっさらにする
		void RemoveWaveEnemyData() {
			m_stageDate1 = m_nullDate;
			m_stageDate2 = m_nullDate;
			m_stageDate3 = m_nullDate;
			m_stageDate4 = m_nullDate;
		}


		// add
		//次のwaveにする
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
			//EnemyParameterに当てはめる
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