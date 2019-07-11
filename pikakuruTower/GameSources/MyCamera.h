#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	MyCamera
	//--------------------------------------------------------------------------------------
	class MyCamera : public Camera {
		// �J�n���̉��o�Ɏg�p
		bool m_Start = true;
		// �h��
		bool m_Shake = false;
		float m_ShakeTime = 0.0f;
	public:
		MyCamera();
		~MyCamera() {}

		virtual void OnUpdate() override;

		void SetShake(bool b) { m_Shake = b; }
	};
}