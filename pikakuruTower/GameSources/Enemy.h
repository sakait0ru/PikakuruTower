/*!
@file Enemy.h
@brief 敵
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Spotlight;
	class StopSprite;

	//	セル検索を使った行動クラスのフラグ
	enum class CellSearchFlg {
		Failed,
		Seek,
		Arrived
	};
	//エネミーの名前
	const enum class EnemyName {
		Enemy,
		SwimwearEnemy,
		FastEnemy,
		ShieldEnemy,
		HammerEnemy,
		WorkEnemy,
		CaptainEnemy
	};

	//エネミーが壁に戻ってきたときのエネミーのタイプ
	const enum class EnemyType {
		HpHeel,
		Net,
		Flash
	};

	//男女エネミーの性別
	const enum class EnemySex {
		Woman,
		Man,
	};

	class EffectPlayer : GameObject {
	private:
		// エフェクト
		vector<EfkEffect> m_Effect;
		// エフェクトを出すやつ
		vector<EfkPlay> m_Play;
	public:
		EffectPlayer(const shared_ptr<Stage>& stagePtr);
		~EffectPlayer();

		void EffectPlay(wstring effectName, Vec3 pos);
		//GetStage()->GetShardGameObject<EfkEffect>("EfkEffect")->EffectPlay(L"AttackEffect", Vec3(hoge));
	};

	//--------------------------------------------------------------------------------------
	// エネミー
	//--------------------------------------------------------------------------------------
	class Enemy : public MyGameObject {
	protected:
		Vec3 m_Scale;     //大きさ
		Vec3 m_Rotation;  //回転
		Vec3 m_Position;  //場所
		Vec3 m_Force;     //力
		Vec3 m_Velocity;  //速度
		weak_ptr<StageCellMap> m_CelMap;
		vector<CellIndex> m_CellPath;
		//現在の自分のセルインデックス
		int m_CellIndex;
		//めざす（次の）のセルインデックス
		int m_NextCellIndex;
		//ターゲットのセルインデックス
		int m_TargetCellIndex;

		float m_MaxHp = 200.0f;    //最大HP
		float m_Hp = 200.0f;       //現在のHP
		float m_EscapeSpeed = 1.0f;//光から避けるスピード
		float m_MoveSpeed = 10.0f;   //移動スピード（数が大きいほど遅くなる）
		float m_LightPawoo = 0.0f;
		float m_TotalTime = 0.0f;
		float m_ChangTime = 0.0f;
		float m_CellTime = 0.0f;
		int m_AttackPower = 3;     //エネミーの攻撃				
		int m_CaptainNumber = 0;	//隊長の番号

		bool m_FirstCelltime = true;
		bool m_Light = false;
		bool m_AnotherLight = true;
		//池に入っているか
		bool m_Pond = false;
		//壁に到達したか
		bool m_WallHit = false;

		//enemy名前
		EnemyName m_Name;
		// enemyタイプ
		EnemyType m_Type;
		//enemy性別
		EnemySex m_Sex;
		// プレイヤー
		shared_ptr<Spotlight> m_Spotlight;
		// 気絶スプライト
		shared_ptr<StopSprite> m_StopSprite;
		//ステートマシーン
		unique_ptr<LayeredStateMachine<Enemy>>m_StateMachine;

		Light m_MyLight;

		float m_EfkTime[6] = { 0.5f,0.5f,0.5f,0.5f,0.5f,0.5f };
	public:

		//エフェクト
		shared_ptr<EfkEffect> m_EfkEffect[6];
		//エフェクト実行オブジェクト
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

		//目的の場所をサーチする
		bool Search(const Vec3&TargetPos);
		//目的の場所をサーチしSeek行動をする
		CellSearchFlg SeekBehavior(const Vec3&TargetPos);
		//目的の場所にarrive行動をとる
		void ArriveBehavior(const Vec3& TargetPos);
		
		//歩く処理
		virtual void WalkMove();
		//左右の移動限度
		void MovingLimit();
		//回転
		void RotToHead();
		//池の中でのスピード
		virtual void PondInSpeed();
		//ライトに触れているかチェック
		void LightDamegeCheck();
		//ダメージを受けている
		void DamageReceive();
		//ライトから逃げる処理
		virtual void AwayMove();
		//ライトに触れていて離れているかチェック
		void NotDamegeCheck();
		//死んでいるかチェック
		virtual void DeathCheck();
		//壁を攻撃している時の処理
		void AttackAnimation();
		//壁に触れている時は回転を固定
		void RotWallFixed();
		//気絶できるかチェック
		void IsStunCheck();
		//気絶が終了した後の処理
		void StunFinish();
		//アクションするために回転を固定
		void ActionRotFixed();
		//人間になった時にアクションをする
		void HumanAction();
		//ゾンビから人間になるタイミング
		void ChangInstant();
		//テクスチャの変更
		virtual void ChangTex();
		//人間になった時の動き
		void HumanWalkMove();
		//人間の時かつ、ある一定ラインを越えたら消える
		void HumanLineOver();
		//空関数
		virtual void ChangBarricade() {};

		//最初のステート
		void StartBehavior();
		//行動
		void MoveBehavior();
		//人間
		void HumanBehavior();
		//ダメージ
		void DamageBehavior();
		//気絶
		void StunBehavior();
		//攻撃
		virtual void AttackBehavior();

		virtual void OnCollisionExit(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>& Other)override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		//アクセサ
		const unique_ptr<LayeredStateMachine<Enemy>>&GetStateMachine() {
			return m_StateMachine;
		}

		const Vec3& GetStartPosition()const {
			return m_Position;
		}

		int GetCaptainNumber() const { return m_CaptainNumber; }
		bool GetHumanState() { if (m_Hp <= 0) return true; return false; }
	};



	//エフェクトを出すobject
	class HpHeelEffect :public MyGameObject {
	protected:
		Vec3 m_Scale;     //大きさ
		Vec3 m_Rotation;  //回転
		Vec3 m_Position;  //場所
		
		float m_EfkTime = 0.5f;

	public:
		//エフェクト
		shared_ptr<EfkEffect> m_EfkEffect;
		//エフェクト実行オブジェクト
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

	//エフェクトの動き
	class EffectMove :public MyGameObject {
	protected:
		Vec3 m_Scale;     //大きさ
		Vec3 m_Rotation;  //回転
		Vec3 m_Position;  //場所
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