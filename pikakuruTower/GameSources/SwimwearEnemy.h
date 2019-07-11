/*!
@file SwimwearEnemy.h
@brief �G
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// �����]���r
	//--------------------------------------------------------------------------------------
	class SwimwearEnemy :public Enemy {
	public:
		SwimwearEnemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const shared_ptr<StageCellMap>& CellMap
		);
		SwimwearEnemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const shared_ptr<StageCellMap>& CellMap,
			const int& captainNumber
		);

		~SwimwearEnemy() {}
		virtual void OnCreate() override;

		//�r�̒��ł̃X�s�[�h
		void PondInSpeed()override;
	};

}