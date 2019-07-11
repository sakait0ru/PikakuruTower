/*!
@file Floor.h
@brief 床
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	class FixedBox : public MyGameObject {
		Vec3 m_Scale;
		Quat m_Quat;
		Vec3 m_Position;

		wstring m_TextureName;
	public:
		//構築と破棄
		FixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		FixedBox(const shared_ptr<Stage>& stagePtr, IXMLDOMNodePtr pNode);
		~FixedBox() {}
		//初期化
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//	たいまつ
	//--------------------------------------------------------------------------------------
	class FireTorch : public MyGameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		//エフェクト
		shared_ptr<EfkEffect> m_EfkEffect;
		//エフェクト実行オブジェクト
		shared_ptr<EfkPlay> m_EfkPlay;
	public:
		//構築と破棄
		FireTorch(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position
		);
		~FireTorch() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;


	};
}

//end basecross