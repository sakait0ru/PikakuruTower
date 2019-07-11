#pragma once
#include "stdafx.h"

namespace basecross {

	class GameoverAnimeSprite : public Sprite {

	private:
		Vec3 m_Rot = Vec3(0, 0, 0);

		float m_Speed = -0.07f;                    //回転するスピード
        float m_AccelPlus = 0.05f;                 //加速度
		float m_StartSpeed = m_Speed;              //元のスピード
		float m_Accel = 1.00f;		               //基準の加速度
		float m_AccelRot = m_Accel + m_AccelPlus;  //速くなる加速(0から半分まで)
		float m_DecelRot = m_Accel + -m_AccelPlus; //遅くなる加速(半分から回りきるまで)

		float m_QuaX = 0.0f;   //三角の変化量
		float m_MoveX = 1.0f;  //三角の動く速さ
		float m_MaxX = 20.0f;  //動く最大値


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
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateGameoverSprite();
		//入力ハンドラー
		InputHandler<GameoverStage> m_InputHandler;


		int m_StageNum = 0;                //今選択してる番号

		bool m_CntrolLock;                 //スティックを一度倒したらロック

		int PushTime = 0;                  //スティックを倒し続けた時の時間を取る

		float Accel = 0.99f;               //加速度
		float PushTimeEndS = 30.0f;        //次の選択までの間隔の初期値
		float PushTimeEnd = PushTimeEndS;  //次の選択までの間隔を初期値に設定	
		float PushTimeEndMax = 7.5f;       //最速値

		bool FadeSwitch = true;            //フェードが始まってるかどうか


	public:
		//構築と破棄
		//GameoverStage() :Stage() {}
		
		GameoverStage() :Stage()
			, m_SpVec(8) {}

		virtual ~GameoverStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		//Aボタン
		void OnPushA() {
			//何もしない
		}
		//Bボタン
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
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	TextureKey	テクスチャキー
		@param[in]	Trace	透明処理するかどうか
		@param[in]	StartScale	初期スケール
		@param[in]	StartPos	初期位置
		*/
		//--------------------------------------------------------------------------------------
		GameoverSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//破棄
		virtual ~GameoverSprite();
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate()override {}
	};
}