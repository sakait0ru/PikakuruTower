/*!
@file MyGameObject.h
@brief ���̃Q�[���p�̃Q�[���I�u�W�F�N�g�N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MyGameObject : public GameObject {
	public:
		MyGameObject(const shared_ptr<Stage>& stagePtr);
		~MyGameObject() {}
	};
}
//end basecross