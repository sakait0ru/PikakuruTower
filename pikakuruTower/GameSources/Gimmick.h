#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	バリケード
	//--------------------------------------------------------------------------------------
	class Barricade : public MyGameObject {
	private:
		Vec3 m_Scale;
		Quat m_Quat;
		Vec3 m_Position;

		//死んでからたった時間
		float m_DeathTotalTime = 0.0f;
		// 消える時間
		float m_DeathTime = 2.0f;

		// 生き残っているか
		bool m_IsAlive = true;

		//エフェクト
		shared_ptr<EfkEffect> m_EfkEffect;
		//エフェクト実行オブジェクト
		shared_ptr<EfkPlay> m_EfkPlay;
	public:
		Barricade(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position
		);
		Barricade(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode);

		~Barricade() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		// バリケードが壊れる時の動き
		void RemoveObject();
		
		//　生きているか設定
		void SetdIsAlive(bool b) { 
			auto ptrColl = AddComponent<CollisionSphere>();
			//ptrColl->RemoveExcludeCollisionTag(L"Enemy");
			ptrColl->SetSleepActive(true);
			m_IsAlive = false;
		}

		bool GetIsAlive() { return m_IsAlive; }
	};

	//--------------------------------------------------------------------------------------
	//	水たまり
	//--------------------------------------------------------------------------------------
	class SlowFloor : public MyGameObject {
	private:
		Vec3 m_Scale;
		Quat m_Quat;
		Vec3 m_Position;

	public:
		SlowFloor(const shared_ptr<Stage>& stagePtr, const Vec3& position);
		SlowFloor(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode);

		~SlowFloor() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};

	//--------------------------------------------------------------------------------------
	//	木
	//--------------------------------------------------------------------------------------
	class Tree : public MyGameObject {
		Vec3 m_Scale;
		Quat m_Quat;
		Vec3 m_Position;
		wstring m_MeshName;
	public:
		//構築と破棄
		Tree(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		Tree(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode);
		~Tree() {}
		//初期化
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//	木のスプライト３D
	//--------------------------------------------------------------------------------------
	class TreeSprite : public Sprite3D {
	public:
		//構築と破棄
		TreeSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec3& startScale,
			const Vec3& startRotaiton,
			const Vec3& startPos
		);
		~TreeSprite() {}

	};

}