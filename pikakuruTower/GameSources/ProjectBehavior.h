/*!
@file ProjectBehavior.h
@brief �v���W�F�N��`�̍s���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�R���g���[���̃{�^���̃n���h��
	//--------------------------------------------------------------------------------------
	template<typename T>
	struct InputHandler {
		void PushHandle(const shared_ptr<T>& Obj) {
			//�L�[�{�[�h�̎擾�i�D��j
			auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
			if (KeyState.m_bPressedKeyTbl[VK_SPACE]) {
				Obj->OnPushA();
				return;
			}
			if (KeyState.m_bPressedKeyTbl['B']) {
				Obj->OnPushB();
				return;
			}
			//�R���g���[���̎擾
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				//A�{�^��
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
					Obj->OnPushA();
				}
				//B�{�^��
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
					Obj->OnPushB();
				}
			}
		}
	};


	// �錾��������
	class Enemy;
	//�X�^�[�g�X�e�[�g
	class EnemyStartState:public ObjState<Enemy>
	{
		EnemyStartState() {}
	public:
		DECLARE_SINGLETON_INSTANCE(EnemyStartState)
		//�X�e�[�g�ɓ��������ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<Enemy>&Obj)override;
		//�X�e�[�g�ɓ����Ă���ԌĂ΂��֐�
		virtual void Execute(const shared_ptr<Enemy>&Obj)override;
		//�X�e�[�g���o��
		virtual void Exit(const shared_ptr<Enemy>&Obj)override;

	};

	// �G�l�~�[���ړ����Ă��鎞�̃X�e�[�g
	class EnemyMoveState :public ObjState<Enemy>
	{
		EnemyMoveState() {}
	public:
		DECLARE_SINGLETON_INSTANCE(EnemyMoveState)
		//�X�e�[�g�ɓ��������ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<Enemy>&Obj)override;
		//�X�e�[�g�ɓ����Ă���ԌĂ΂��֐�
		virtual void Execute(const shared_ptr<Enemy>&Obj)override;
		//�X�e�[�g���o��
		virtual void Exit(const shared_ptr<Enemy>&Obj)override;

	};
	//�G�l�~�[���l�ԏ�Ԃ̎��̃X�e�[�g
	class EnemyHumanState :public ObjState<Enemy>
	{
		EnemyHumanState(){}
	public:
		DECLARE_SINGLETON_INSTANCE(EnemyHumanState)
		//�X�e�[�g�ɓ��������ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<Enemy>&Obj)override;
		//�X�e�[�g�ɓ����Ă���ԌĂ΂��֐�
		virtual void Execute(const shared_ptr<Enemy>&Obj)override;
		//�X�e�[�g���o��
		virtual void Exit(const shared_ptr<Enemy>&Obj)override;

	};

	//���C�g�̃_���[�W���󂯂Ă��鎞�̃X�e�[�g
	class EnemyDamageState :public ObjState<Enemy>
	{
		EnemyDamageState() {}
	public:
		DECLARE_SINGLETON_INSTANCE(EnemyDamageState)
		//�X�e�[�g�ɓ��������ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<Enemy>&Obj)override;
		//�X�e�[�g�ɓ����Ă���ԌĂ΂��֐�
		virtual void Execute(const shared_ptr<Enemy>&Obj)override;
		//�X�e�[�g���o��
		virtual void Exit(const shared_ptr<Enemy>&Obj)override;

	};

	//�C���Ԃ̃X�e�[�g
	class EnemyStunState :public ObjState<Enemy>
	{
		EnemyStunState() {}
	public:
		DECLARE_SINGLETON_INSTANCE(EnemyStunState)
		//�X�e�[�g�ɓ��������ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<Enemy>&Obj)override;
		//�X�e�[�g�ɓ����Ă���ԌĂ΂��֐�
		virtual void Execute(const shared_ptr<Enemy>&Obj)override;
		//�X�e�[�g���o��
		virtual void Exit(const shared_ptr<Enemy>&Obj)override;

	};

	//�U���̃X�e�[�g
	class EnemyAttackState :public ObjState<Enemy>
	{
		EnemyAttackState() {}
	public:
		DECLARE_SINGLETON_INSTANCE(EnemyAttackState)
		//�X�e�[�g�ɓ��������ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<Enemy>&Obj)override;
		//�X�e�[�g�ɓ����Ă���ԌĂ΂��֐�
		virtual void Execute(const shared_ptr<Enemy>&Obj)override;
		//�X�e�[�g���o��
		virtual void Exit(const shared_ptr<Enemy>&Obj)override;

	};

}

//end basecross

