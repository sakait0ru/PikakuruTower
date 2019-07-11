#pragma once
#include "stdafx.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	//	ライトの形
	//--------------------------------------------------------------------------------------
	class SpotLightRay : public MyGameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		shared_ptr<MeshResource> m_MeshResource;
	public:
		//構築と破棄
		SpotLightRay(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		~SpotLightRay() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}