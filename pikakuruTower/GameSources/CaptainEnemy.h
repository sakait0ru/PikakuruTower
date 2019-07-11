/*!
@file CaptainEnemy.h
@brief 敵
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// 隊長ゾンビ
	//--------------------------------------------------------------------------------------
	class CaptainEnemy :public Enemy {
	protected:
		float m_CaptainTime = 0.0f;
	public:
		CaptainEnemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const shared_ptr<StageCellMap>& CellMap
		);
		CaptainEnemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const shared_ptr<StageCellMap>& CellMap,
			const int& captainNumber
		);

		~CaptainEnemy() {}
		virtual void OnCreate() override;

		//索敵範囲を持っているので早めによける
		void SearchRange();
		//メインの動き
		void WalkMove() override;
		//人間になった時テクスチャを白髪人間に固定
		void ChangTex()override {
			auto ptrDraw = GetComponent<PNTBoneModelDraw>();
			ptrDraw->SetMeshResource(L"Man2_Human.bbmf");
		}	
	};

}