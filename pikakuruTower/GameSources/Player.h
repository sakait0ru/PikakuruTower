/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Vibration
	{
	protected:
		float m_VibCount[4] = {};
		float m_VibInterval[4] = {};
		bool m_isVib[4] = {};
	public:
		DECLARE_SINGLETON_INSTANCE(Vibration)

		void SetVibration(float time, float left, float right, int CntNum = 0);

		void Update();
	};

	//--------------------------------------------------------------------------------------
	///	プレイヤー
	//--------------------------------------------------------------------------------------
	class Player : public MyGameObject {
	private:
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		float m_LightPower = 1.0f;

		//入力ハンドラー
		InputHandler<Player> m_InputHandler;

		bool m_Big = true;
		bool m_Active = true;

		//エフェクト
		shared_ptr<EfkEffect> m_EfkEffect;
		//エフェクト実行オブジェクト
		shared_ptr<EfkPlay> m_EfkPlay;

		// 閃光玉が使えるか
		bool m_IsFlashItem = true;
		// 閃光玉のインターバル時間
		float m_FlashItemTime = 0.0f;
		float m_FlashItemIntervalTime = 10.0f;

	public:
		Player(const shared_ptr<Stage>& stagePtr);
		Player(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position);
		~Player() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//Aボタン
		void OnPushA();
		//Xボタン
		void OnPushB();

		bool GetActive() const { return m_Active; }
		float GetLightPower() const { return m_LightPower; }
	};

	//--------------------------------------------------------------------------------------
	///	フラッシュ本体のスプライト
	//--------------------------------------------------------------------------------------
	class FlashSprite : public MyGameObject {
	private:
		float m_TotalTime;
		bool m_Stoped;
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		
		float m_ScaleSpanMat;
		float m_Spin;

		//エフェクト
		shared_ptr<EfkEffect> m_EfkEffect;
		//エフェクト実行オブジェクト
		shared_ptr<EfkPlay> m_EfkPlay;

	public:
		FlashSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec3& startScale,
			const Vec3& startRotaiton,
			const Vec3& startPos);
		~FlashSprite() {}

		void OnCreate() override;
		void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//	マスキングスプライト
	//--------------------------------------------------------------------------------------
	class FlashMaskSprite : public GameObject {
		wstring m_TextureKey;
		shared_ptr<MeshResource> m_SpriteMesh;
		float m_ScaleSpeed;
		float m_AlphaNum;
	public:
		//構築と破棄
		FlashMaskSprite(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey
		);
		virtual ~FlashMaskSprite();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//操作
		//描画
		virtual void OnDraw() override;
	};
}
//end basecross