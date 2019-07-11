/*!
@file MyCamera.cpp
@brief カメラ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	MyCamera::MyCamera() :
		Camera()
	{}

	void MyCamera::OnUpdate() {

		// カメラの移動、スポットライトに合わせて移動
		Vec3 spotPos = GameManager::getInstance()->GeSpotLightPositon();
		if (spotPos.z >= 0.0f) {
			SetEye(Vec3(0.0f + (spotPos.x / 3.0f), 15.0f, -14.0f + spotPos.z));
			SetAt(Vec3(0.0f + (spotPos.x / 3.0f), 0.0f, 0.0f + spotPos.z));
		}
		else {
			SetEye(Vec3(0.0f + (spotPos.x / 3.0f), 15.0f, -14.0f));
			SetAt(Vec3(0.0f + (spotPos.x / 3.0f), 0.0f, 0.0f));
			spotPos.z *= 0.0f;
		}

		// 揺れるフラグがたっていたら
		if (m_Shake) {

			// 揺れる処理
			float r = (float)(rand() % 2);
			float r2 = (float)(rand() % 2);
			SetEye(Vec3(0.0f + (spotPos.x / 3.0f) + (r*0.15f), 15.0f, -14.0f + spotPos.z + (r2*0.15f)));
			SetAt(Vec3(0.0f + (spotPos.x / 3.0f) + (r*0.15f), 0.0f, 0.0f + spotPos.z + (r2*0.15f)));

			m_ShakeTime += App::GetApp()->GetElapsedTime();
			if (m_ShakeTime > 0.25f) {
				m_ShakeTime = 0;
				m_Shake = false;
			}
		}

		if (GameManager::getInstance()->GetFinishActive()) {
			SetEye(Vec3(0.0f, 15.0f, -14.0f));
			SetAt(Vec3(0.0f, 0.0f, 0.0f));

		}


		Camera::OnUpdate();

	}
}