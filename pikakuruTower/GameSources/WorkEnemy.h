/*!
@file WorkEnemy.h
@brief �G
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// �H��]���r
	//--------------------------------------------------------------------------------------
	class WorkEnemy :public Enemy {
	public:
		WorkEnemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const shared_ptr<StageCellMap>& CellMap
		);
		WorkEnemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const shared_ptr<StageCellMap>& CellMap,
			const int& captainNumber
		);

		~WorkEnemy() {}
		virtual void OnCreate() override;

		//�Z���}�b�v�̏����Ƃ��Ă��ă}�X�ڂɃo���P�[�h��z�u
		void InformationGetCell();
		//InformationGetCell�g�p���邽�߂̏����ɂ���
		void ChangBarricade()override;
	};

}