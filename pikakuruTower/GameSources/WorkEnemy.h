/*!
@file WorkEnemy.h
@brief 敵
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// 工作ゾンビ
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

		//セルマップの情報をとってきてマス目にバリケードを配置
		void InformationGetCell();
		//InformationGetCell使用するための条件について
		void ChangBarricade()override;
	};

}