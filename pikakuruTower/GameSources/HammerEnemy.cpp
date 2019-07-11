/*!
@file HammerEnemy.cpp
@brief 敵
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// ハンマーゾンビ
	//--------------------------------------------------------------------------------------
	HammerEnemy::HammerEnemy(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position,
		const shared_ptr<StageCellMap>& CellMap
	) :
		Enemy(stagePtr, scale, rotation, position, CellMap)
	{
	}

	void HammerEnemy::OnCreate() {
		Enemy::OnCreate();

		// ハンマーゾンビのメッシュにする　今は仮でMan
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"Hummer_Walk.bbmf");
		m_Sex = EnemySex::Man;

		auto ptrShadow = AddComponent<Shadowmap>();

		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Hummer_Walk.bbmf");

		//避けるスピード
		m_EscapeSpeed = 0.4f;
		//HP
		m_MaxHp = 200;
		m_Hp = m_MaxHp;
		//名前
		m_Name = EnemyName::HammerEnemy;
		//pawa-
		m_AttackPower = 10;

		// ハンマーはわかりやすく大きくする
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(Vec3(0.6f, 0.6f, 0.6f));
	}

	Vec3 HammerEnemy::LightIgnore() {
		shared_ptr<GameObject> targetObject;
		auto ptrTrans = GetComponent<Transform>();
		auto Enemypos = ptrTrans->GetPosition();
		if (Enemypos.x > 0) {
			targetObject = GetStage()->GetSharedGameObject<WallTaget>(L"WallRight");
		}
		else {
			targetObject = GetStage()->GetSharedGameObject<WallTaget>(L"WallLeft");
		}
		auto spotPos = targetObject->GetComponent<Transform>()->GetPosition();

		auto pos = GetComponent<Transform>()->GetPosition();

		auto velo = spotPos - pos;
		velo.normalize();
		Vec3 vec = Vec3(velo.x * 0.01f, 0.0f, velo.z * 0.01f);
		return vec;
	}

	void HammerEnemy::WalkMove() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos += LightIgnore() * 3;
		ptrTrans->SetPosition(pos);
	}

	void HammerEnemy::AwayMove() {
		WalkMove();
	}

	void HammerEnemy::BarricadeBrekeAction() {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		if (ptrDraw->IsTargetAnimeEnd()) {
			if (ptrDraw->GetCurrentAnimation() == L"AttackBefore") {
				// 攻撃音の再生
				App::GetApp()->GetXAudio2Manager()->Start(L"Zombie_Attack.wav", 0, 0.5f);

				// エフェクトの再生
				auto ptrTrans = GetComponent<Transform>();
				auto pos = ptrTrans->GetPosition();
				pos.y += 1.5f;
				pos.z -= 1.0f;
				m_EfkPlay[1] = ObjectFactory::Create<EfkPlay>(m_EfkEffect[1], pos);

				ptrDraw->ChangeCurrentAnimation(L"AttackAfter");
			}
			if (ptrDraw->GetCurrentAnimation() == L"AttackAfter") {
				GetStateMachine()->Reset(EnemyMoveState::Instance());
				m_BarriHit = false;
			}
		}
	}
	void HammerEnemy::AttackBehavior() {
		if (m_BarriHit) {
			BarricadeBrekeAction();
		}
		else {
			auto ptrDraw = GetComponent<PNTBoneModelDraw>();
			// Attackのモーションが終わったら
			if (ptrDraw->IsTargetAnimeEnd()) {
				// 終わったアニメーションがAttackBeforeなら
				if (ptrDraw->GetCurrentAnimation() == L"AttackBefore") {
					{
						//エフェクト、バイブレーションなど
						AttackAnimation();
						// 攻撃が終わったので　AttackAfterアニメーションを再生する
						ptrDraw->ChangeCurrentAnimation(L"AttackAfter");
					}
				}
				else {
					// AttackBeforeじゃなかったのでAttackBeforeを再生する
					ptrDraw->ChangeCurrentAnimation(L"AttackBefore");
				}
			}

			//ライトからのダメージ
			DamageReceive();
			//HPが0以下かチェック
			DeathCheck();
			//向きを壁側に
			RotWallFixed();
		}
	}

	void HammerEnemy::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		//バリケードに触れたとき
		if (Other->FindTag(L"Barricade")) {
			auto bari = dynamic_pointer_cast<Barricade>(Other);
			if (bari->GetIsAlive()) {
				bari->SetdIsAlive(false);
				m_BarriHit = true;
				GetStateMachine()->Reset(EnemyAttackState::Instance());
			}
		}

		// ライトに触れた時
		if (Other->FindTag(L"Light")) {
			// ライトフラグをtrueにする
			m_Light = true;

		}

		//敵かつ壁に触れた時
		if (m_Hp >= 0) {
			if (Other->FindTag(L"Wall")) {
				m_WallHit = true;
				GetStateMachine()->Reset(EnemyAttackState::Instance());
			}
		}

	}

}