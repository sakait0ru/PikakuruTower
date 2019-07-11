/*!

@file GameStage.h

@brief ゲームステージ

*/



#pragma once

#include "stdafx.h"

namespace basecross {
	class SelectTriMoveSprite;


	class AnimeSprite : public Sprite {
		float m_LightMove = 25.0f;        
		float m_LightMoveEnd = 300.0f;
		float m_LightQuaMove = 0.0f;

	public:
		AnimeSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~AnimeSprite() {};

		virtual void OnUpdate()override;

		Vec3 GetStartPos() const { return Vec3(m_StartPos.x, m_StartPos.y,0); }
	};


	// 明るい所を表示するスプライト
	class SelectSpotSprite : public Sprite {
	public:
		SelectSpotSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		~SelectSpotSprite() {}

		bool SelectSpotFlag;

		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		bool GetSelectSpotFlag() { return SelectSpotFlag; }

	};
	//--------------------------------------------------------------------------------------

	//	セレクトステージクラス

	//--------------------------------------------------------------------------------------

	class SelectStage : public Stage {

		//ビューの作成
		void CreateViewLight();

		//UIの作成
		void CreateUI();

		vector<shared_ptr<AnimeSprite>> m_SpVec;
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SelectSpotSprite> m_SpotSprite;

		shared_ptr<SelectTriMoveSprite> m_RTriSprite;
		shared_ptr<SelectTriMoveSprite> m_LTriSprite;

		int m_StageNum = 0;            //今選択してるステージ番号

		bool m_CntrolLock;             //スティックを一度倒したらロック

		bool m_FadeSwitch = true;      //フェードのスイッチ

		bool m_Extra = false;
		float m_TotalTime = 0.0f;
		float m_MoveTime = 1.5f;	   // 移動にかかる時間

	public:
		//構築と破棄
		SelectStage() :Stage(), m_CntrolLock(false)
			, m_SpVec(9)
		{
		}
		virtual ~SelectStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;

		int GetStageNum() { return m_StageNum; } 
		vector<shared_ptr<AnimeSprite>> GetSpVec() const { return m_SpVec; }
	};



	class SelectTriMoveSprite : public Sprite {
	private:

		float m_QuaX = 0.0f;   //三角の変化量
		float m_MoveX = 1.0f;  //三角の動く速さ
		float m_MaxX = 20.0f;  //動く最大値


	public:
		SelectTriMoveSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~SelectTriMoveSprite() {}
		//更新
		virtual void OnUpdate()override;

		void RTriMove(bool Avtive);
		void LTriMove(bool Avtive);
	};

}

//end basecross