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

		float QuaX = 0.0f;   //三角の変化量
		float MoveX = 1.0f;  //三角の動く速さ
		float MaxX = 20.0f;  //動く最大値
	};

	class ClearStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateClearSprite();
		//入力ハンドラー
		InputHandler<ClearStage> m_InputHandler;
	public:
		//構築と破棄
		//ClearStage() :Stage() {}
		ClearStage() :Stage()
			, m_SpVec(9) {}
		virtual ~ClearStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		//Aボタン
		void OnPushA() {
			//何もない
		}
		//Bボタン
		void OnPushB();

		vector<shared_ptr<ClearAnimeSprite>> m_SpVec;

		shared_ptr<SoundItem> m_BGM;
		int m_StageNum = 0;

		bool m_CntrolLock;

		int PushTime = 0;

		float Accel = 0.99f;               //加速度
		float PushTimeEndS = 30.0f;        //次の選択までの間隔の初期値
		float PushTimeEnd = PushTimeEndS;  //次の選択までの間隔を初期値に設定	
		float PushTimeEndMax = 7.5f;       //最速値

		bool FadeSwitch = true;      //フェードのスイッチ

	};


	class ClearSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_TextureKey;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	TextureKey	テクスチャキー
		@param[in]	Trace	透明処理するかどうか
		@param[in]	StartScale	初期スケール
		@param[in]	StartPos	初期位置
		*/
		//--------------------------------------------------------------------------------------
		ClearSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//破棄
		virtual ~ClearSprite();
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate()override {}
	};
}
