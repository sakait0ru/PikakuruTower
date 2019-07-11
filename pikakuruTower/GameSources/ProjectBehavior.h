/*!
@file ProjectBehavior.h
@brief プロジェク定義の行動クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	コントローラのボタンのハンドラ
	//--------------------------------------------------------------------------------------
	template<typename T>
	struct InputHandler {
		void PushHandle(const shared_ptr<T>& Obj) {
			//キーボードの取得（優先）
			auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
			if (KeyState.m_bPressedKeyTbl[VK_SPACE]) {
				Obj->OnPushA();
				return;
			}
			if (KeyState.m_bPressedKeyTbl['B']) {
				Obj->OnPushB();
				return;
			}
			//コントローラの取得
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				//Aボタン
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
					Obj->OnPushA();
				}
				//Bボタン
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
					Obj->OnPushB();
				}
			}
		}
	};


	// 宣言だけする
	class Enemy;
	//スタートステート
	class EnemyStartState:public ObjState<Enemy>
	{
		EnemyStartState() {}
	public:
		DECLARE_SINGLETON_INSTANCE(EnemyStartState)
		//ステートに入った時に呼ばれる関数
		virtual void Enter(const shared_ptr<Enemy>&Obj)override;
		//ステートに入っている間呼ばれる関数
		virtual void Execute(const shared_ptr<Enemy>&Obj)override;
		//ステートを出る
		virtual void Exit(const shared_ptr<Enemy>&Obj)override;

	};

	// エネミーが移動している時のステート
	class EnemyMoveState :public ObjState<Enemy>
	{
		EnemyMoveState() {}
	public:
		DECLARE_SINGLETON_INSTANCE(EnemyMoveState)
		//ステートに入った時に呼ばれる関数
		virtual void Enter(const shared_ptr<Enemy>&Obj)override;
		//ステートに入っている間呼ばれる関数
		virtual void Execute(const shared_ptr<Enemy>&Obj)override;
		//ステートを出る
		virtual void Exit(const shared_ptr<Enemy>&Obj)override;

	};
	//エネミーが人間状態の時のステート
	class EnemyHumanState :public ObjState<Enemy>
	{
		EnemyHumanState(){}
	public:
		DECLARE_SINGLETON_INSTANCE(EnemyHumanState)
		//ステートに入った時に呼ばれる関数
		virtual void Enter(const shared_ptr<Enemy>&Obj)override;
		//ステートに入っている間呼ばれる関数
		virtual void Execute(const shared_ptr<Enemy>&Obj)override;
		//ステートを出る
		virtual void Exit(const shared_ptr<Enemy>&Obj)override;

	};

	//ライトのダメージを受けている時のステート
	class EnemyDamageState :public ObjState<Enemy>
	{
		EnemyDamageState() {}
	public:
		DECLARE_SINGLETON_INSTANCE(EnemyDamageState)
		//ステートに入った時に呼ばれる関数
		virtual void Enter(const shared_ptr<Enemy>&Obj)override;
		//ステートに入っている間呼ばれる関数
		virtual void Execute(const shared_ptr<Enemy>&Obj)override;
		//ステートを出る
		virtual void Exit(const shared_ptr<Enemy>&Obj)override;

	};

	//気絶状態のステート
	class EnemyStunState :public ObjState<Enemy>
	{
		EnemyStunState() {}
	public:
		DECLARE_SINGLETON_INSTANCE(EnemyStunState)
		//ステートに入った時に呼ばれる関数
		virtual void Enter(const shared_ptr<Enemy>&Obj)override;
		//ステートに入っている間呼ばれる関数
		virtual void Execute(const shared_ptr<Enemy>&Obj)override;
		//ステートを出る
		virtual void Exit(const shared_ptr<Enemy>&Obj)override;

	};

	//攻撃のステート
	class EnemyAttackState :public ObjState<Enemy>
	{
		EnemyAttackState() {}
	public:
		DECLARE_SINGLETON_INSTANCE(EnemyAttackState)
		//ステートに入った時に呼ばれる関数
		virtual void Enter(const shared_ptr<Enemy>&Obj)override;
		//ステートに入っている間呼ばれる関数
		virtual void Execute(const shared_ptr<Enemy>&Obj)override;
		//ステートを出る
		virtual void Exit(const shared_ptr<Enemy>&Obj)override;

	};

}

//end basecross

