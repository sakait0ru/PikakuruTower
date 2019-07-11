/*!
@file Wall.h
@brief 壁
*/

#pragma once
#include "stdafx.h"

namespace basecross 
{
	//--------------------------------------------------------------------------------------
	//	壁の当たり判定
	//--------------------------------------------------------------------------------------
	class Wall : public MyGameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//構築と破棄
		Wall(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		~Wall() {}
		//初期化
		virtual void OnCreate() override;
	};	

	//--------------------------------------------------------------------------------------
	//	壁のモデル一単位
	//--------------------------------------------------------------------------------------
	class WallUnit : public MyGameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//構築と破棄
		WallUnit(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		~WallUnit() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//ゲームオーバーだった時、壁が下がる
		void WallUnitDown();
	};


	//--------------------------------------------------------------------------------------
	//	壁の狙えるところ
	//--------------------------------------------------------------------------------------
	class WallTaget : public MyGameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//構築と破棄
		WallTaget(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		~WallTaget() {}
		//初期化
		virtual void OnCreate() override;
	};


	//--------------------------------------------------------------------------------------
	//	タワー
	//--------------------------------------------------------------------------------------
	class Tower : public MyGameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//構築と破棄
		Tower(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		~Tower() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//	タワーの下のところ
	//--------------------------------------------------------------------------------------
	class TowerUnder : public MyGameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//構築と破棄
		TowerUnder(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		~TowerUnder() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

}