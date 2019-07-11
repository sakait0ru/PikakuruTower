/*!
@file HammerEnemy.h
@brief �G
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// �n���}�[�]���r
	//--------------------------------------------------------------------------------------
	class HammerEnemy :public Enemy {
	private:
		//�ǂɓ��B������
		bool m_BarriHit = false;
	public:
		HammerEnemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const shared_ptr<StageCellMap>& CellMap
		);
		~HammerEnemy() {}
		virtual void OnCreate() override;

		//���ɓ������Ă��悯�Ȃ�����
		Vec3 LightIgnore();
		//���C���̓���
		void WalkMove()override;
		//���C�g���瓦���鏈��
		void AwayMove()override;
		//�o���P�[�h���󂷃A�N�V����
		void BarricadeBrekeAction();
		//�ǂɑ΂���U��
		virtual void AttackBehavior()override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

	};

}