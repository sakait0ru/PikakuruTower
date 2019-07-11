#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	MyCamera
	//--------------------------------------------------------------------------------------
	class MyCamera : public Camera {
		// 開始時の演出に使用
		bool m_Start = true;
		// 揺れ
		bool m_Shake = false;
		float m_ShakeTime = 0.0f;
	public:
		MyCamera();
		~MyCamera() {}

		virtual void OnUpdate() override;

		void SetShake(bool b) { m_Shake = b; }
	};
}