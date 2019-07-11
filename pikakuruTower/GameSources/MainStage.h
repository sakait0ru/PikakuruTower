/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class PauseSprite;
	class WallUnit;
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class MainStage : public Stage {


		// Xmlファイルのパス
		wstring m_stageXmlPath;

		//Spriteかそうでないかを分離する配列
		vector< shared_ptr<GameObject> > m_SpriteVec;
		vector< shared_ptr<GameObject> > m_Object3DVec;
		//3Dの透明と非透明を分離する配列
		vector< shared_ptr<GameObject> > m_Object3DNormalVec;
		vector< shared_ptr<GameObject> > m_Object3DAlphaVec;

		//スプライト入れてる配列
		vector<weak_ptr<PauseSprite>> m_SpVec;
		//エフェクトのインターフェイス
		shared_ptr<EfkInterface> m_EfkInterface;

		//ビューの作成
		void CreateViewLight();
		// 床作成
		void CreateFloor();
		//セルマップの作成
		void CreateStageCellMap();
		// 手前の大きな壁作成
		void CreateWall();
		// UIの作成
		void CreateUI();
		// 障害物の作成
		void CreateGimmick();
		// プレイヤー（スポットライト）の作成
		void CreatePlayer();
		// Wave画像の生成
		void CreateWave();
		//敵の作成
		void CreateEnemy(float time);
		//エフェクトを作成
		void CreateEffect();

		float m_StartTime = 0;
		int PauseSelect = 0;

		shared_ptr<MyCamera> m_Camera;

		shared_ptr<SoundItem> m_BGM;

		bool m_Pause = false;
		bool m_PauseFade = false;

		Vec3 m_HpUIPos;
		bool m_cntlrock = false;

		bool FadeSwitch = true;      //フェードのスイッチ

		// Waveのエネミーを格納する場所
		vector< vector<EnemyParameter> > waveVec;

		// Waveの時間　これに応じて敵を出す
		float m_WaveTime = 0.0f;
		// Waveの敵をすべて出し終えているか
		bool m_WaveCreated = false;

		//エフェクト
		shared_ptr<EfkEffect> m_EfkEffect[7];
		//エフェクト実行オブジェクト
		shared_ptr<EfkPlay> m_EfkPlay[7];

		// ゲームオーバー用のTimer
		float m_GameOverTime = 0.0f;
		
		// ゲームクリア用のTimer
		float m_GameClearTime = 0.0f;

	public:
		//構築と破棄
		MainStage() :Stage(), m_SpVec(3) {}
		virtual ~MainStage() {}
		
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDraw()override;
		virtual void UpdateStage()override;
		virtual void DrawStage()override;
		void ChangePause(int num);

		//固定のボックスのコストをセルマップに反映
		void SetCellMapCost();

		//エフェクトのインターフェイスの取得
		shared_ptr<EfkInterface> GetEfkInterface() const {
			return m_EfkInterface;
		}

		float GetStartTime() const { return m_StartTime; }
		// Cameraを取得
		shared_ptr<MyCamera> GetCamera() { return m_Camera; }

		Vec3 GetHpUIPos() { return m_HpUIPos; }
		void SetHpUIPos(Vec3 v3) { m_HpUIPos = v3; }

		shared_ptr<EfkEffect> GetEfkDate(int i) { return m_EfkEffect[i]; }
	};

	
}
//end basecross

