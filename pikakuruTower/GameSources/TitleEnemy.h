/*!
@file TitleEnemy.h
@brief 敵
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// タイトル画面で使うゾンビ
	//--------------------------------------------------------------------------------------
	class TitleEnemy :public MyGameObject {
		//エフェクト
		shared_ptr<EfkEffect> m_EfkEffect[4];
		//エフェクト実行オブジェクト
		shared_ptr<EfkPlay> m_EfkPlay[4];
	protected:
		Vec3 m_Scale;     //大きさ
		Vec3 m_Rotation;  //回転
		Vec3 m_Position;  //場所

		int m_Nunber = 0;
		int Key = 0;
		float m_MaxHp = 200.0f;    //最大HP
		float m_Hp = 200.0f;       //現在のHP
		float m_ChangTime = 0.0f;

		bool m_Light = false;
		bool m_AnotherLight = false;
		bool m_Damage = false;
		bool m_Hit = false;

		unique_ptr<LayeredStateMachine<TitleEnemy>>m_StateMachine;
		// プレイヤー
		shared_ptr<Spotlight> m_Spotlight;

		float m_EfkTime[4] = { 0.5f,0.5f,0.5f,0.5f };

	public:


		TitleEnemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position
		);
		~TitleEnemy() {}

		virtual void OnCreate() override;
		virtual void OnUpdate()override;

		//歩く
		void WalkMove();
		//移動処理
		Vec3 HumanMove();
		//人間になった時の動き
		void HumanWalkMove();
		//回転
		void RotToHead();
		//ダメージチェック
		void LightDamegeCheck();
		//ライトからダメージを受けている
		void DamageReceive();
		//テクスチャの変更
		void ChangTex();

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExit(shared_ptr<GameObject>& Other) override;

	};

}