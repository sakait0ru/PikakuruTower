/*!
@file Enemy.cpp
@brief 敵
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	// エネミー
	//--------------------------------------------------------------------------------------
	Enemy::Enemy(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position,
		const shared_ptr<StageCellMap>& CellMap
	) :
		MyGameObject(stagePtr),
		m_Scale(scale),
		m_Rotation(rotation),
		m_Position(position),
		m_CelMap(CellMap),
		m_CaptainNumber(0)
	{
	}

	Enemy::Enemy(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position,
		const shared_ptr<StageCellMap>& CellMap,
		const int& captainNumber
	) :
		MyGameObject(stagePtr),
		m_Scale(scale),
		m_Rotation(rotation),
		m_Position(position),
		m_CelMap(CellMap),
		m_CaptainNumber(captainNumber)
	{
	}

	void Enemy::OnCreate() {
		AddTag(L"Enemy");
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		auto ptrColl = AddComponent<CollisionSphere>();
		//ptrColl->SetExcludeCollisionGroup(L"Barricades");
		//ptrColl->SetDrawActive(true);
		auto MapPtr = m_CelMap.lock();
		if (MapPtr) {
			AddComponent<PathSearch>(MapPtr);
		}

		SetAlphaActive(true);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(2.5f, 2.5f, 2.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.75f, 0.0f)
		);

		auto ptrDraw = AddComponent<PNTBoneModelDraw>();

		auto MeshKey = rand() % 2;
		switch (MeshKey)
		{
		case 0:
			ptrDraw->SetMeshResource(L"Man_Zombie.bbmf");
			m_Sex = EnemySex::Man;
			break;

		case 1:
			ptrDraw->SetMeshResource(L"Woman_Zombie.bbmf");
			m_Sex = EnemySex::Woman;
			break;
		default:
			throw BaseException(
				L"エラー",
				L"SetMeshResource",
				L"OnCreate"
			);
			break;
		}
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		// アニメーションの追加
		ptrDraw->AddAnimation(L"Stay", 0, 1, true, 1);
		ptrDraw->AddAnimation(L"Walk", 0, 60, true, 140.0f);
		ptrDraw->AddAnimation(L"Attack", 61, 60, false, 50.0f);
		ptrDraw->AddAnimation(L"AttackBefore", 61, 30, false, 50.0f);
		ptrDraw->AddAnimation(L"AttackAfter", 91, 30, false, 50.0f);
		ptrDraw->ChangeCurrentAnimation(L"Stay");



		auto ptrShadow = AddComponent<Shadowmap>();


		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Man_Zombie.bbmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		m_Spotlight = GetStage()->GetSharedGameObject<Spotlight>(L"Spotlight");

		//タイプ
		m_Type = EnemyType::HpHeel;
		//名前
		m_Name = EnemyName::Enemy;

		// エフェクトの実装
		for (int i = 0; i < 6; i++) {
			m_EfkEffect[i] = GetTypeStage<MainStage>()->GetEfkDate(i);
		}

		//ステートマシーンの構築
		m_StateMachine.reset(new LayeredStateMachine<Enemy>(GetThis<Enemy>()));
		//最初のステートをEnemyMoveStateに設定
		GetStateMachine()->Reset(EnemyStartState::Instance());

		// デバッグ用の文字列を設定
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 100.0f, 640.0f, 480.0f));

	}

	void Enemy::OnUpdate() {
		m_StateMachine->Update();
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elapsedTime);

		//debugstring
		wstringstream ss;
		auto strDraw = GetComponent<StringSprite>();
		//strDraw->SetText(ss.str());

	}

	void Enemy::OnUpdate2() {

	}


	/*-セルマップ関連-----------------------------------------------*/
	bool Enemy::Search(const Vec3&TargetPos) {
		auto MapPtr = m_CelMap.lock();
		if (MapPtr) {
			auto PathPtr = GetComponent<PathSearch>();
			m_CellPath.clear();
			//パス検索をかける
			if (PathPtr->SearchCell(TargetPos, m_CellPath)) {
				//検索が成功した
				m_CellIndex = 0;
				m_TargetCellIndex = (int)(m_CellPath.size() - 1);
				if (m_CellIndex == m_TargetCellIndex) {
					//すでに同じセルにいる
					m_NextCellIndex = m_CellIndex;
				}
				else {
					//離れている
					m_NextCellIndex = m_CellIndex + 1;

				}
				return true;
			}
			else {
				//失敗した
				m_CellIndex = -1;
				m_NextCellIndex = -1;
				m_TargetCellIndex = -1;
			}
		}
		return false;
	}

	CellSearchFlg Enemy::SeekBehavior(const Vec3& TargetPos) {
		auto MyPos = GetComponent<Transform>()->GetPosition();
		auto MapPtr = m_CelMap.lock();
		if (!MapPtr) {
			return CellSearchFlg::Failed;
		}
		m_CellTime += App::GetApp()->GetElapsedTime();
		if (m_CellTime >= 1.0f) {
			if (Search(TargetPos)) {
				auto PtrSeek = GetBehavior<SeekSteering>();
				auto PtrArrive = GetBehavior<ArriveSteering>();
				if (m_NextCellIndex == 0) {
					m_Force = PtrArrive->Execute(m_Force, m_Velocity, TargetPos);
					//到着した
					return CellSearchFlg::Arrived;
				}
				else {
					AABB ret;
					MapPtr->FindAABB(m_CellPath[m_NextCellIndex], ret);
					auto Pos = ret.GetCenter();
					Pos.y = TargetPos.y;
					m_Force = PtrSeek->Execute(m_Force, m_Velocity, Pos);
					return CellSearchFlg::Seek;
				}
			}
			else {
				auto PtrSeek = GetBehavior<SeekSteering>();
				CellIndex WallCell;
				if (MapPtr->FindCell(TargetPos, WallCell)) {
					AABB ret;
					MapPtr->FindAABB(WallCell, ret);
					auto Pos = ret.GetCenter();
					Pos.y = TargetPos.y;
					m_Force = PtrSeek->Execute(m_Force, m_Velocity, Pos);
					return CellSearchFlg::Seek;
				}
			}
			m_CellTime = 0.0f;
			m_FirstCelltime = false;
		}



		return CellSearchFlg::Failed;
	}

	void Enemy::ArriveBehavior(const Vec3&TargetPos) {
		auto PtrArrive = GetBehavior<ArriveSteering>();
		m_Force = PtrArrive->Execute(m_Force, m_Velocity, TargetPos);
	}
	/*--------------------------------------------------------------*/

	void Enemy::WalkMove() {
		m_Force.setAll(0.0f);
		// 向かうObject
		shared_ptr<GameObject> targetObject;
		// CaptainNumberが0じゃないとき、設定しないと自動で0になる
		if (m_CaptainNumber != 0) {
			// このオブジェクトが配置されているステージのすべてのオブジェクトを取得する
			auto stageGameObjectVev = GetStage()->GetGameObjectVec();
			for (auto gameObject : stageGameObjectVev) {
				// 取り出したgameObjectをCaptainEnemyに変換
				auto ce = dynamic_pointer_cast<CaptainEnemy>(gameObject);
				// 失敗したらfalseが返ってくる、
				if (ce) { // 成功
					// 変換に成功したゾンビが生きているか
					if (!ce->GetHumanState()) { // 生きてた
						// 生きているCaptainEnemyのNumberを取得
						auto ceNumber = ce->GetCaptainNumber();
						// 自分の番号と一致しているか確認
						if (ceNumber == m_CaptainNumber) {
							// targetのobjectにCaptainEnemyを入れる
							targetObject = gameObject;
							// 見つかったのでforループを抜け出す
							break;
						}
					}
				}
			}
		}
		// 上の処理を実行して、何にも見つからなかったら
		if (targetObject == nullptr) {
			auto ptrTrans = GetComponent<Transform>();
			auto pos = ptrTrans->GetPosition();
			if (pos.x > 0) {
				targetObject = GetStage()->GetSharedGameObject<WallTaget>(L"WallRight");
			}
			else {
				targetObject = GetStage()->GetSharedGameObject<WallTaget>(L"WallLeft");
			}
		}

		//auto wallPtr = GetStage()->GetSharedGameObject<Wall>(L"Wall");
		auto wallPos = targetObject->GetComponent<Transform>()->GetPosition();
		wallPos.y = GetStartPosition().y;
		if (SeekBehavior(wallPos) == CellSearchFlg::Failed) {
			if (SeekBehavior(GetStartPosition()) == CellSearchFlg::Arrived) {
				ArriveBehavior(GetStartPosition());
			}
		}
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_Velocity += m_Force;
		auto pos = GetComponent<Transform>()->GetPosition();
		auto newPos = pos + (m_Velocity * ElapsedTime / m_MoveSpeed);
		GetComponent<Transform>()->SetPosition(newPos);
	}

	//エネミーの限度移動
	void Enemy::MovingLimit() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		auto time = App::GetApp()->GetElapsedTime();

		if (pos.x > 12.5)
		{
			pos.x = 12.5f;
		}
		if (pos.x < -13.5)
		{
			pos.x = -13.5f;
		}
		ptrTrans->SetPosition(pos);
	}

	void Enemy::RotToHead() {
		auto ptrColl = GetComponent<CollisionSphere>();
		auto ptrTrans = GetComponent<Transform>();
		Vec3 Velocity = ptrColl->GetVelocity();
		if (Velocity.length() > 0.0f) {
			Vec3 rot = Velocity;
			rot.normalize();
			float ToAngle = atan2(rot.x, rot.z);
			Quat Qt;
			Qt.rotationRollPitchYawFromVector(Vec3(0, ToAngle + XM_PI, 0));
			Qt.normalize();
			//現在の回転を取得
			Quat NowQt = ptrTrans->GetQuaternion();
			//現在と目標を補間（10分の1）
			NowQt = XMQuaternionSlerp(NowQt, Qt, 0.1f);
			ptrTrans->SetQuaternion(NowQt);
		}
	}

	void Enemy::PondInSpeed() {
		if (m_Pond) {
			auto elapsedTime = App::GetApp()->GetElapsedTime();
			auto ptrTrans = GetComponent<Transform>();
			auto pos = ptrTrans->GetPosition();
			pos.z += 0.8f*elapsedTime;
			ptrTrans->SetPosition(pos);
		}
	}

	void Enemy::LightDamegeCheck() {
		//ライトにあたっていてかつライトがオンなら
		if (m_Light && m_Spotlight->GetActive()) {
			//ダメージステートへ
			GetStateMachine()->Reset(EnemyDamageState::Instance());
		}
	}

	void Enemy::DamageReceive() {
		if (m_Light&&m_Spotlight->GetActive()) {
			auto lightPower = m_Spotlight->GetLightPower();
			m_Hp -= lightPower * 0.3f;

			m_EfkTime[2] += App::GetApp()->GetElapsedTime();
			if (m_EfkTime[2] >= 0.5f) {
				m_EfkTime[2] = 0.0f;
				// サウンドの再生
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(L"Zombie_Damage.wav", 0, 0.1f);
				// ダメージを受けている時のエフェクト再生
				auto ptrTrans = GetComponent<Transform>();
				m_EfkPlay[2] = ObjectFactory::Create<EfkPlay>(m_EfkEffect[2], ptrTrans->GetPosition());
			}
		}
	}

	void Enemy::AwayMove() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		auto posX = pos.x;
		auto rot = ptrTrans->GetRotation();
		auto lightPtr = GetStage()->GetSharedGameObject<Spotlight>(L"Spotlight");
		auto lightPos = lightPtr->GetComponent<Transform>()->GetPosition();
		auto lightPosX = lightPos.x;
		auto totalPos = posX - lightPosX;
		//池に入っていたら
		if (m_Pond == true) {
			if (totalPos < 0) {
				pos.x += m_EscapeSpeed * -0.005f;
			}
			else if (totalPos > 0) {
				pos.x += m_EscapeSpeed * 0.005f;
			}
		}
		//池に入っていない
		else {
			if (totalPos < 0) {
				pos.x += m_EscapeSpeed * -0.02f;
			}
			else if (totalPos > 0) {
				pos.x += m_EscapeSpeed * 0.02f;
			}
		}
		ptrTrans->SetRotation(rot);
		ptrTrans->SetPosition(pos);
	}

	void Enemy::NotDamegeCheck() {
		if (m_Light == false || !m_Spotlight->GetActive()) {
			GetStateMachine()->Reset(EnemyMoveState::Instance());
		}
	}

	void Enemy::DeathCheck() {
		//Hpが0以下になっていたら
		if (m_Hp <= 0) {
			//人間ステートへ
			GetStateMachine()->Reset(EnemyHumanState::Instance());
		}
	}

	void Enemy::AttackAnimation() {
		// サウンドの再生
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(L"Zombie_Attack.wav", 0, 0.5f);
		// エフェクトの再生
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos.y += 1.5f;
		pos.z -= 1.0f;
		m_EfkPlay[1] = ObjectFactory::Create<EfkPlay>(m_EfkEffect[1], pos);
		// 壁のHpを減らす
		GameManager::getInstance()->DamageWallHp(m_AttackPower);
		// カメラのDamegeFlgをTrueにする
		GetTypeStage<MainStage>()->GetCamera()->SetShake(true);
		// ダメージを受けた時の赤いマスクの作成
		GetStage()->AddGameObject<DamegeSprite>(L"DamegeSprite.png", Vec2(1280, 800), Vec2(0, 0));
		// コントローラーを揺らす
		Vibration::Instance()->SetVibration(0.2f, 0.5f, 0.5f);
	}

	void Enemy::RotWallFixed() {
		//向きを壁側に
		auto ptrTrans = GetComponent<Transform>();
		auto rot = ptrTrans->GetRotation();
		rot.y = 0;
		ptrTrans->SetRotation(rot);

	}

	void Enemy::IsStunCheck() {
		if (m_Hp >= 0) {
			m_TotalTime = 0.0f;
			GetStateMachine()->Reset(EnemyStunState::Instance());
		}
	}

	void Enemy::StunFinish() {
		m_TotalTime += App::GetApp()->GetElapsedTime();
		//気絶
		if (m_TotalTime >= 7.0f) {
			m_TotalTime = 0.0f;
			//壁にヒットしていたら
			if (m_WallHit == true) {
				GetStateMachine()->Reset(EnemyAttackState::Instance());
			}
			//歩くことを続ける
			GetStateMachine()->Reset(EnemyMoveState::Instance());
		}
	}

	void Enemy::ActionRotFixed() {
		auto ptrTrans = GetComponent<Transform>();
		auto rot = ptrTrans->GetRotation();
		rot = Vec3(0.0f, 0.0f, 0.0f);
		ptrTrans->SetRotation(rot);
	}

	//人間になった瞬間の動き
	void Enemy::HumanAction() {
		// 人間になった時のエフェクト
		auto ptrTrans = GetComponent<Transform>();
		m_EfkPlay[0] = ObjectFactory::Create<EfkPlay>(m_EfkEffect[0], ptrTrans->GetPosition());
		//サウンドの再生
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(L"Zombie_Zouka.wav", 0, 0.5f);


		auto ptrAction = AddComponent<Action>();
		ptrAction->AddMoveBy(1.0f, Vec3(0, 0, 0));
		ptrAction->AddRotateTo(0.5f, Vec3(0, 0, XM_PIDIV2));
		ptrAction->AddRotateBy(0.5f, Vec3(0, 0, -XM_PIDIV2));
		ptrAction->AddMoveBy(0.5f, Vec3(0, 2.0f, 0), Lerp::Linear, Lerp::EaseOut, Lerp::Linear);
		ptrAction->AddRotateBy(0.5f, Vec3(0, XM_PI, 0));
		ptrAction->AddRotateBy(0.5f, Vec3(0, XM_PI, 0));
		ptrAction->AddMoveBy(0.5f, Vec3(0, -2.0f, 0), Lerp::Linear, Lerp::Easein, Lerp::Linear);
		//ループする
		ptrAction->SetLooped(false);
		//アクション開始
		ptrAction->Run();
	}

	void Enemy::ChangInstant() {
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		m_ChangTime += elapsedTime;
		if (m_ChangTime >= 1.3f) {
			m_ChangTime = 0.0f;
			//アクションの登録
			ChangTex();
		}
	}

	void Enemy::ChangTex() {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		if (m_Sex == EnemySex::Man) {
			ptrDraw->SetMeshResource(L"Man_Human.bbmf");
		}
		else if (m_Sex == EnemySex::Woman) {
			ptrDraw->SetMeshResource(L"Woman_Human.bbmf");
		}

		auto ptrShadow = GetComponent<Shadowmap>();
		if (m_Name == EnemyName::ShieldEnemy) {
			ptrShadow->SetMeshResource(L"Man_Human.bbmf");
		}
		if (m_Name == EnemyName::HammerEnemy) {
			ptrShadow->SetMeshResource(L"Man_Human.bbmf");
		}
		if (m_Name == EnemyName::WorkEnemy) {
			ptrShadow->SetMeshResource(L"Man_Human.bbmf");
		}

	}

	//人間になった時の動き
	void Enemy::HumanWalkMove() {
		//当たり判定をなくす
		auto ptrColl = GetComponent<CollisionSphere>();
		ptrColl->AddExcludeCollisionTag(L"Enemy");
		ptrColl->AddExcludeCollisionTag(L"Barricade");

		m_Force.setAll(0.0f);
		shared_ptr<GameObject> targetObject;
		if (targetObject == nullptr) {
			auto ptrTrans = GetComponent<Transform>();
			auto pos = ptrTrans->GetPosition();
			if (pos.x > 0) {
				targetObject = GetStage()->GetSharedGameObject<WallTaget>(L"WallRight");
			}
			else {
				targetObject = GetStage()->GetSharedGameObject<WallTaget>(L"WallLeft");
			}
		}
		auto wallPos = targetObject->GetComponent<Transform>()->GetPosition();
		wallPos.y = GetStartPosition().y;
		if (SeekBehavior(wallPos) == CellSearchFlg::Failed) {
			if (SeekBehavior(GetStartPosition()) == CellSearchFlg::Arrived) {
				ArriveBehavior(GetStartPosition());
			}
		}

		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_Velocity += m_Force;
		auto Pos = GetComponent<Transform>()->GetPosition();
		Pos += m_Velocity * ElapsedTime;
		GetComponent<Transform>()->SetPosition(Pos);
	}

	void Enemy::HumanLineOver() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		if (m_Hp < 0) {
			if (pos.z < -6.0f) {
				switch (m_Type)
				{
				case basecross::EnemyType::HpHeel:
					GameManager::getInstance()->HeelWallHp(2);
					break;
				case basecross::EnemyType::Net:
					break;
				case basecross::EnemyType::Flash:
					break;
				default:
					break;
				}
				m_EfkPlay[3]->StopEffect();
				//回復の声
				auto voiceKey = rand() % 10;
				switch (voiceKey)
				{
				case 0:
					App::GetApp()->GetXAudio2Manager()->Start(L"HeelVoice.wav", 0, 0.5f);
					break;
				default:
					break;
				}

				GetStage()->AddGameObject<HpHeelEffect>(Vec3(0.5f, 0.5f, 0.5f), Vec3(0.0f, 0.0f, 0.0f), GetComponent<Transform>()->GetPosition());
				GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
			}
		}
	}
	/*-ステートマシーン関連-------------------------------------*/
	//最初の動き
	void Enemy::StartBehavior() {
		//エネミーの生成されてからの動き
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos.y += 0.01f;
		if (pos.y > 0.5f) {
			pos.y = 0.5f;
			GetStateMachine()->Reset(EnemyMoveState::Instance());
		}
		ptrTrans->SetPosition(pos);
	}
	//ゾンビの動き
	void Enemy::MoveBehavior() {
		//ライトに当たっているかチェック
		LightDamegeCheck();
		//メインの動き
		WalkMove();
		//回転処理
		RotToHead();
		//左右の移動限度
		MovingLimit();
		//HPが0以下かチェック
		DeathCheck();
	}

	//人間になった時
	void Enemy::HumanBehavior() {
		//人間になった時の動き
		HumanWalkMove();
		//回転処理
		RotToHead();
	}
	//ライトのダメージを受けている時
	void Enemy::DamageBehavior() {
		//ライトから逃げる処理
		AwayMove();
		//ライトからのダメージ
		DamageReceive();
		//HPが0以下かチェック
		DeathCheck();
		//ライトに触れていて離れているかチェック
		NotDamegeCheck();
	}
	//気絶
	void Enemy::StunBehavior() {
		//気絶時間を過ぎた後の処理
		StunFinish();
		//ライトからのダメージ
		DamageReceive();
		//HPが0以下かチェック
		DeathCheck();
	}

	//壁に対する攻撃
	void Enemy::AttackBehavior() {
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
	}

	/*----------------------------------------------------------*/

	void Enemy::OnCollisionExit(shared_ptr<GameObject>& Other) {
		// ライトから離れた時
		if (Other->FindTag(L"Light")) {
			//ライトフラグをfalseにする
			m_Light = false;
		}
		// 池から離れた時
		if (Other->FindTag(L"SlowFloor")) {
			//池フラグをfalseにする
			m_Pond = false;
		}
	}
	void Enemy::OnCollisionExcute(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"SlowFloor")) {
			m_Pond = true;
		}
	}
	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& Other) {

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

	//--------------------------------------------------------------------------------------
	//エフェクトを出すobject
	//--------------------------------------------------------------------------------------

	HpHeelEffect::HpHeelEffect(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position
	) :
		MyGameObject(stagePtr),
		m_Scale(scale),
		m_Rotation(rotation),
		m_Position(position)
	{
	}

	void HpHeelEffect::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		//人間になるときのエフェクト
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\zonbiheal.efk";
		auto ShEfkInterface = GetTypeStage<MainStage>()->GetEfkInterface();
		m_EfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);


		auto pos = GetComponent<Transform>()->GetPosition();
		m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, pos);

	}
	void HpHeelEffect::OnUpdate() {


		auto ptrTrans = GetComponent<Transform>();
		auto after = ptrTrans->GetPosition();
		auto pos = ptrTrans->GetPosition();

		auto hpUIPos = GetTypeStage<MainStage>()->GetHpUIPos();
		auto d = hpUIPos - after;
		// 消す処理
		auto To = pow((hpUIPos.x - pos.x)*(hpUIPos.x - pos.x) + (hpUIPos.z - pos.z)*(hpUIPos.z - pos.z), 0.5);
		if (To < 0.5) {
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}
		d.normalize();
		pos += d * 0.2f;
		ptrTrans->SetPosition(pos);

		auto befor = ptrTrans->GetPosition();
		auto dis = befor - after;
		m_EfkPlay->AddLocation(Vec3(dis.x, 0, dis.z));
	}


	EffectMove::EffectMove(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position
	) :
		MyGameObject(stagePtr),
		m_Scale(scale),
		m_Rotation(rotation),
		m_Position(position)
	{
	}
	void EffectMove::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		//auto ptrDraw = AddComponent<PNTStaticDraw>();
		//ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

	}
	void EffectMove::OnUpdate() {

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		auto at = GetStage()->GetView()->GetTargetCamera()->GetAt();
		at.x += -7.0f;
		at.z += -7.0f;
		//auto vec = at - pos;
		//vec.normalize();

		//pos += vec;

		ptrTrans->SetPosition(at);

		if (pos.y < 1.0f) {
			GetTypeStage<MainStage>()->SetHpUIPos(pos);
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}
	}

}
//end basecross