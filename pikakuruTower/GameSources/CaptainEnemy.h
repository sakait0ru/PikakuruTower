/*!
@file CaptainEnemy.h
@brief �G
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// �����]���r
	//--------------------------------------------------------------------------------------
	class CaptainEnemy :public Enemy {
	protected:
		float m_CaptainTime = 0.0f;
	public:
		CaptainEnemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const shared_ptr<StageCellMap>& CellMap
		);
		CaptainEnemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const shared_ptr<StageCellMap>& CellMap,
			const int& captainNumber
		);

		~CaptainEnemy() {}
		virtual void OnCreate() override;

		//���G�͈͂������Ă���̂ő��߂ɂ悯��
		void SearchRange();
		//���C���̓���
		void WalkMove() override;
		//�l�ԂɂȂ������e�N�X�`���𔒔��l�ԂɌŒ�
		void ChangTex()override {
			auto ptrDraw = GetComponent<PNTBoneModelDraw>();
			ptrDraw->SetMeshResource(L"Man2_Human.bbmf");
		}	
	};

}