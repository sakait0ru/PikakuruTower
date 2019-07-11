/*!
@file Enemy.h
@brief �G
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Spotlight;
	class StopSprite;

	//	�Z���������g�����s���N���X�̃t���O
	enum class CellSearchFlg {
		Failed,
		Seek,
		Arrived
	};
	//�G�l�~�[�̖��O
	const enum class EnemyName {
		Enemy,
		SwimwearEnemy,
		FastEnemy,
		ShieldEnemy,
		HammerEnemy,
		WorkEnemy,
		CaptainEnemy
	};

	//�G�l�~�[���ǂɖ߂��Ă����Ƃ��̃G�l�~�[�̃^�C�v
	const enum class EnemyType {
		HpHeel,
		Net,
		Flash
	};

	//�j���G�l�~�[�̐���
	const enum class EnemySex {
		Woman,
		Man,
	};

	class EffectPlayer : GameObject {
	private:
		// �G�t�F�N�g
		vector<EfkEffect> m_Effect;
		// �G�t�F�N�g���o�����
		vector<EfkPlay> m_Play;
	public:
		EffectPlayer(const shared_ptr<Stage>& stagePtr);
		~EffectPlayer();

		void EffectPlay(wstring effectName, Vec3 pos);
		//GetStage()->GetShardGameObject<EfkEffect>("EfkEffect")->EffectPlay(L"AttackEffect", Vec3(hoge));
	};

	//--------------------------------------------------------------------------------------
	// �G�l�~�[
	//--------------------------------------------------------------------------------------
	class Enemy : public MyGameObject {
	protected:
		Vec3 m_Scale;     //�傫��
		Vec3 m_Rotation;  //��]
		Vec3 m_Position;  //�ꏊ
		Vec3 m_Force;     //��
		Vec3 m_Velocity;  //���x
		weak_ptr<StageCellMap> m_CelMap;
		vector<CellIndex> m_CellPath;
		//���݂̎����̃Z���C���f�b�N�X
		int m_CellIndex;
		//�߂����i���́j�̃Z���C���f�b�N�X
		int m_NextCellIndex;
		//�^�[�Q�b�g�̃Z���C���f�b�N�X
		int m_TargetCellIndex;

		float m_MaxHp = 200.0f;    //�ő�HP
		float m_Hp = 200.0f;       //���݂�HP
		float m_EscapeSpeed = 1.0f;//�����������X�s�[�h
		float m_MoveSpeed = 10.0f;   //�ړ��X�s�[�h�i�����傫���قǒx���Ȃ�j
		float m_LightPawoo = 0.0f;
		float m_TotalTime = 0.0f;
		float m_ChangTime = 0.0f;
		float m_CellTime = 0.0f;
		int m_AttackPower = 3;     //�G�l�~�[�̍U��				
		int m_CaptainNumber = 0;	//�����̔ԍ�

		bool m_FirstCelltime = true;
		bool m_Light = false;
		bool m_AnotherLight = true;
		//�r�ɓ����Ă��邩
		bool m_Pond = false;
		//�ǂɓ��B������
		bool m_WallHit = false;

		//enemy���O
		EnemyName m_Name;
		// enemy�^�C�v
		EnemyType m_Type;
		//enemy����
		EnemySex m_Sex;
		// �v���C���[
		shared_ptr<Spotlight> m_Spotlight;
		// �C��X�v���C�g
		shared_ptr<StopSprite> m_StopSprite;
		//�X�e�[�g�}�V�[��
		unique_ptr<LayeredStateMachine<Enemy>>m_StateMachine;

		Light m_MyLight;

		float m_EfkTime[6] = { 0.5f,0.5f,0.5f,0.5f,0.5f,0.5f };
	public:

		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_EfkEffect[6];
		//�G�t�F�N�g���s�I�u�W�F�N�g
		shared_ptr<EfkPlay> m_EfkPlay[6];
		Enemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const shared_ptr<StageCellMap>& CellMap
		);
		Enemy(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const shared_ptr<StageCellMap>& CellMap,
			const int& captainNumber
		);
		~Enemy() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;

		//�ړI�̏ꏊ���T�[�`����
		bool Search(const Vec3&TargetPos);
		//�ړI�̏ꏊ���T�[�`��Seek�s��������
		CellSearchFlg SeekBehavior(const Vec3&TargetPos);
		//�ړI�̏ꏊ��arrive�s�����Ƃ�
		void ArriveBehavior(const Vec3& TargetPos);
		
		//��������
		virtual void WalkMove();
		//���E�̈ړ����x
		void MovingLimit();
		//��]
		void RotToHead();
		//�r�̒��ł̃X�s�[�h
		virtual void PondInSpeed();
		//���C�g�ɐG��Ă��邩�`�F�b�N
		void LightDamegeCheck();
		//�_���[�W���󂯂Ă���
		void DamageReceive();
		//���C�g���瓦���鏈��
		virtual void AwayMove();
		//���C�g�ɐG��Ă��ė���Ă��邩�`�F�b�N
		void NotDamegeCheck();
		//����ł��邩�`�F�b�N
		virtual void DeathCheck();
		//�ǂ��U�����Ă��鎞�̏���
		void AttackAnimation();
		//�ǂɐG��Ă��鎞�͉�]���Œ�
		void RotWallFixed();
		//�C��ł��邩�`�F�b�N
		void IsStunCheck();
		//�C�₪�I��������̏���
		void StunFinish();
		//�A�N�V�������邽�߂ɉ�]���Œ�
		void ActionRotFixed();
		//�l�ԂɂȂ������ɃA�N�V����������
		void HumanAction();
		//�]���r����l�ԂɂȂ�^�C�~���O
		void ChangInstant();
		//�e�N�X�`���̕ύX
		virtual void ChangTex();
		//�l�ԂɂȂ������̓���
		void HumanWalkMove();
		//�l�Ԃ̎����A�����胉�C�����z�����������
		void HumanLineOver();
		//��֐�
		virtual void ChangBarricade() {};

		//�ŏ��̃X�e�[�g
		void StartBehavior();
		//�s��
		void MoveBehavior();
		//�l��
		void HumanBehavior();
		//�_���[�W
		void DamageBehavior();
		//�C��
		void StunBehavior();
		//�U��
		virtual void AttackBehavior();

		virtual void OnCollisionExit(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>& Other)override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		//�A�N�Z�T
		const unique_ptr<LayeredStateMachine<Enemy>>&GetStateMachine() {
			return m_StateMachine;
		}

		const Vec3& GetStartPosition()const {
			return m_Position;
		}

		int GetCaptainNumber() const { return m_CaptainNumber; }
		bool GetHumanState() { if (m_Hp <= 0) return true; return false; }
	};



	//�G�t�F�N�g���o��object
	class HpHeelEffect :public MyGameObject {
	protected:
		Vec3 m_Scale;     //�傫��
		Vec3 m_Rotation;  //��]
		Vec3 m_Position;  //�ꏊ
		
		float m_EfkTime = 0.5f;

	public:
		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_EfkEffect;
		//�G�t�F�N�g���s�I�u�W�F�N�g
		shared_ptr<EfkPlay> m_EfkPlay;

		HpHeelEffect(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position
		);
		~HpHeelEffect() {}

		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};

	//�G�t�F�N�g�̓���
	class EffectMove :public MyGameObject {
	protected:
		Vec3 m_Scale;     //�傫��
		Vec3 m_Rotation;  //��]
		Vec3 m_Position;  //�ꏊ
	public:

		EffectMove(const shared_ptr<Stage>& stagePtr,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position
		);
		~EffectMove() {}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;

	};
}
//end basecross