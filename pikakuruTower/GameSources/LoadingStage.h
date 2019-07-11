 /*!
@file LoadingStage.h
@brief ロードシーン
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class LoadingZombie;
	class LoadingSelectSprite;
	class TriMoveSprite;
	//--------------------------------------------------------------------------------------
	///	ロードステージ
	//--------------------------------------------------------------------------------------
	class LoadingStage : public Stage {
		// Xmlファイルのパス
		wstring m_stageXmlPath;

		//ビューの作成
		void CreateViewLight();
		//ローディングスプライトの作成
		void CreateLoadingSprite();
		vector<shared_ptr<LoadingSelectSprite>> m_SpVec;


		int m_ReadNum = 0;

		bool m_CntlLock = true;

		bool FadeSwitch = true;      //フェードのスイッチ

		shared_ptr<Sprite> m_ReadmeSprite;
		shared_ptr<LoadingZombie> m_Enemy;

		shared_ptr<TriMoveSprite> m_RTriSprite;
		shared_ptr<TriMoveSprite> m_LTriSprite;
		
	public:
		LoadingStage() :Stage(), m_SpVec(10) {}
		virtual ~LoadingStage() {}
		//初期化
		void LoadingChangeSelect(int num);

		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;

		int GetReadNum() const { return m_ReadNum; }

	};

	//--------------------------------------------------------------------------------------
	///	読み込み中…スプライト
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
		//更新
		virtual void OnUpdate()override;

	};


	//--------------------------------------------------------------------------------------
	///	プレビューゾンビ
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
	///	LoadingSelectSprite画面用のスプライト
	//--------------------------------------------------------------------------------------
	class LoadingSelectSprite : public Sprite {
	public:
		//構築と破棄
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
	// エネミーのデータを受け取るクラス
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
		//構築と破棄
		EnemyDataLoad(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode);
		virtual ~EnemyDataLoad() {}

		virtual void OnCreate() override;
	};



	class TriMoveSprite : public Sprite {
	private:

		float m_QuaX = 0.0f;   //三角の変化量
		float m_MoveX = 1.0f;  //三角の動く速さ
		float m_MaxX = 20.0f;  //動く最大値


	public:
		TriMoveSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~TriMoveSprite() {}
		//更新
		virtual void OnUpdate()override;

		void RTriMove(bool Avtive);
		void LTriMove(bool Avtive);
	};
}