#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// タイトルの画像とゲームスタートの画像
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
	// タイトルにつかうPlayer
	//--------------------------------------------------------------------------------------
	class TitlePlayer : public MyGameObject {
	private:
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		float m_LightPower = 1.0f;

		//入力ハンドラー
		InputHandler<TitlePlayer> m_InputHandler;

		bool m_Big = true;
		bool m_Active = true;

		////エフェクト
		//shared_ptr<EfkEffect> m_EfkEffect;
		////エフェクト実行オブジェクト
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
		//Aボタン
		//void OnPushA();
		//Xボタン
		//void OnPushB();

		bool GetActive() const { return m_Active; }
		float GetLightPower() const { return m_LightPower; }
	};

	//--------------------------------------------------------------------------------------
	// タイトルステージ
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {

		//Spriteかそうでないかを分離する配列
		vector< shared_ptr<GameObject> > m_SpriteVec;
		vector< shared_ptr<GameObject> > m_Object3DVec;
		//3Dの透明と非透明を分離する配列
		vector< shared_ptr<GameObject> > m_Object3DNormalVec;
		vector< shared_ptr<GameObject> > m_Object3DAlphaVec;

		//エフェクトのインターフェイス
		shared_ptr<EfkInterface> m_EfkInterface;


		//ビューの作成
		void CreateViewLight();
		// 床の作成
		void CreateFloor();
		// スポットライトを作成
		void CreateTitlePlayer();
		// 手前の壁を作成
		void CreateWall();
		// たいまつを作成
		void CreateFireTorch();
		//タイマーを作成
		void CreateTimer();

		float TrueTime;               //trueの時の時間計測
		float FalseTime;              //falseの時の時間計測
		float TrueTimeEnd = 45.0f;    //表示してる時間
		float FalseTimeEnd = 15.0f;   //透明にしてる時間
		float Switch = 1.0f;          //trueとfalseの切り替え用
		float TrueTimePlus = 1.0f;

		float DecTime;                //ボタン押してからの時間計測
		float DecSwitch = 0.0f;       //決定キーのスイッチ

		float FlashingSpeed = 0.2f;
		float FlashingTime = 80.0f;
		float FlashingEnd = 120.0f;

		bool FadeSwitch = true;      //フェードのスイッチ
		float FadeCount = 0.0f;  //フェード開始からの時間計測

		bool m_Start = true;         //タイトルロゴが動いているかどうか
		float m_Time = 0.0f;         //時間計測

		// movieを再生するまでの時間
		float m_MovieTime = 0.0f;

		vector<shared_ptr<TitleAnimeSprite>> m_SpVec;

		shared_ptr<SoundItem> m_BGM;
	public:
		//構築と破棄
		TitleStage() :Stage()
			, m_SpVec(6) {}


		virtual ~TitleStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		//描画
		virtual void OnDraw() override;
		
		// ステージのDrawする順番
		virtual void DrawStage()override;

		//エフェクトのインターフェイスの取得
		shared_ptr<EfkInterface> GetEfkInterface() const {
			return m_EfkInterface;
		}

	};
}
