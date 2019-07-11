/*!
@file Spotlight.h
@brief スポットライト
*/

#pragma once
#include "stdafx.h"

namespace basecross 
{
	class Spotlight : public MyGameObject 
	{
	private:
		// コントローラから方向ベクトルを得る
		Vec3 GetMoveVector() const;
		// スポットライトのスクエア]
		//shared_ptr<MeshResource> m_SquareMeshResource;

		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		// ライトの強さエネミーに対する攻撃力
		float m_LightPower = 8;
		float m_Speed = 0.05;
		// 大きいとき
		bool m_Big = true;
		// オンかオフか
		bool m_Active = true;
		bool m_On = true;
		// 動かす関数
		void MovePlayer();
		//デバイスポジション
		Vec3 m_DevPos;

	public:
		Spotlight(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position);
		~Spotlight() {}

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;

		void CalcDevPos();

		bool GetActive() const { return m_Active; }
		bool GetBig() const { return m_Big; }
		float GetLightPower() const { return m_LightPower; }

		Vec3 GetDevPos() const { return m_DevPos; }

		bool GetOn() { return m_On; }
	};
}
//end basecross