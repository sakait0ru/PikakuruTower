/*!
@file Spotlight.cpp
@brief スポットライト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	Spotlight::Spotlight(const shared_ptr<Stage>& stagePtr,
		const Vec3& scale,
		const Vec3& rotation,
		const Vec3& position) :
		MyGameObject(stagePtr),
		m_Scale(scale),
		m_Rotation(rotation),
		m_Position(position),
		m_On(true)
	{
	}

	Vec3 Spotlight::GetMoveVector() const 
	{
		Vec3 angle(0, 0, 0);
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float fThumbLY = 0.0f;
		float fThumbLX = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			fThumbLY = cntlVec[0].fThumbLY;
			fThumbLX = cntlVec[0].fThumbLX;
			wButtons = cntlVec[0].wButtons;
		}
	
		if (fThumbLX != 0 || fThumbLY != 0) {
			float moveLength = 0;	//動いた時のスピード
			//コントローラの向き計算
			float moveX = fThumbLX;
			float moveZ = fThumbLY;
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//コントローラの向きから角度を計算
			//float cntlAngle = atan2(moveZ, moveX);
			//トータルの角度を算出
			//float totalAngle = cntlAngle;
			//角度からベクトルを作成
		//	angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			//正規化する
			angle.normalize();
			//移動サイズを設定。
			angle *= moveSize;
			//Y軸は変化させない
			angle.y = 0;
		}
		return angle;
	}

	void Spotlight::CalcDevPos()
	{
		auto ptrCamera = OnGetDrawCamera();
		Mat4x4 world, view, proj;
		world = GetComponent<Transform>()->GetWorldMatrix();
		view = ptrCamera->GetViewMatrix();
		proj = ptrCamera->GetProjMatrix();
		m_DevPos = Vec3(0);

		m_DevPos = XMVector3Project
		(m_DevPos, -1.0f, -1.0f, 2.0f, 2.0f, 0.0f, 1.0f, proj, view, world);
	}

	void Spotlight::MovePlayer() 
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		auto pos = GetComponent<Transform>()->GetPosition();
		if (angle.length() > 0.0f) 
		{
			pos += angle * elapsedTime * 6.0f;
		}
		CalcDevPos();
		
	
		//回転の計算
		if (angle.length() > 0.0f) 
		{
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, 1.0f);
		}
	}

	

	void Spotlight::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		auto ptrCol = AddComponent<CollisionSphere>();
		ptrCol->SetAfterCollision(AfterCollision::None);
		//ptrCol->SetDrawActive(true);

		// 3Dオブジェクトでおいてる版
		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		//描画するテクスチャを設定
		ptrDraw->SetTextureResource(L"Spotlight.png");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		//アクションコンポーネントを追加
		auto ptrAct = AddComponent<Action>();
		ptrAct->AddScaleTo(0.5f, Vec3(1.0f, 1.0f, 1.0f));



		SetAlphaActive(true);

		AddTag(L"Light");

		// デバッグ用の文字列を設定
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

	}

	void Spotlight::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Enemy")) {
			auto ptrEnemy = dynamic_pointer_cast<Enemy>(Other);
			if (ptrEnemy) {
				//ptrEnemy->FaintChange();
			}
		}
	}


#define MINIDOWN(X,Y) if(X > Y) X= Y -0.01;
#define MAXIDOWN(X,Y) if(X < Y) X= Y -0.01;
// 三項演算子

	void Spotlight::OnUpdate() {

		auto GM = GameManager::getInstance();
		if (!GM->GetFinishActive()) {
			//コントローラチェックして入力があればコマンド呼び出し
			//m_InputHandler.PushHandle(GetThis<Spotlight>());
			MovePlayer();

			auto ptrPosition = GetComponent<Transform>()->GetPosition();

			// キーボードで動く
			auto ptrTrans = GetComponent<Transform>();
			auto pos = ptrTrans->GetPosition();


			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
			if (cntlVec.bConnected)
			{
				if (cntlVec.fThumbLX != 0 || cntlVec.fThumbLY != 0)
				{
					auto stage = GetStage();
					auto main = dynamic_pointer_cast<MainStage>(stage);
					if (main) {
						//MINIDOWN(pos.z, 15.5);

						if (pos.z > 15.5)
						{
							pos.z = 15.49f;
						}
						if (pos.z < -6.5)
						{
							pos.z = -6.49f;
						}
						if (pos.x > 12.5)
						{
							pos.x = 12.49f;
						}
						if (pos.x < -13.5)
						{
							pos.x = -13.49f;
						}
					}
					else {
						// タイトルの時
						if (pos.z > 15.5)
						{
							pos.z = 15.49f;
						}
						if (pos.z < -6.5)
						{
							pos.z = -6.49f;
						}
						if (pos.x > 10.5)
						{
							pos.x = 10.49f;
						}
						if (pos.x < -10.5)
						{
							pos.x = -10.49f;
						}
					}
					// 移動
					pos.x += cntlVec.fThumbLX * m_Speed;//0.05
					pos.z += cntlVec.fThumbLY * m_Speed;//0.05
				}


			}
			// 大きさの変更
			if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			{

				if (m_Big)
				{
					//m_Scale.x = 3.0f;//3.0f
					//m_Scale.y = 3.0f;//3.0f
					m_Big = false;
					m_LightPower = 3;//3
					if (!m_Big) {
						m_Speed = 0.12f;
					}
				}
				else
				{

					//m_Scale.x = 1.50f;
					//m_Scale.y = 1.50f;//1.50f;
					m_Big = true;
					if (!m_Active)
					{
						m_Speed = 0.12f;
					}
					else if (m_Big) {
						m_Speed = 0.05f;
					}
					m_LightPower = 8;//8
				}
			}
			// ライトのオンオフ　タイトルだとこれいらない
			auto stage = GetStage();
			auto main = dynamic_pointer_cast<MainStage>(stage);
			if (main) {
				if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER || cntlVec.wPressedButtons & XINPUT_GAMEPAD_A)
				{
					App::GetApp()->GetXAudio2Manager()->Start(L"lightOnOff.wav", 0, 0.2f);
					if (m_Active)
					{
						//SetDrawActive(false);

						m_Speed = 0.15f;
						//auto ptrDraw = AddComponent<PNTStaticDraw>();
						//ptrDraw->SetTextureResource(L"SpotlightOFF.png");

						m_Active = false;
						m_On = false;
					}
					else
					{
						SetDrawActive(true);

						m_Speed = 0.05f;
						auto ptrDraw = GetComponent<BcPNTStaticDraw>();
						ptrDraw->SetTextureResource(L"Spotlight.png");

						m_Active = true;
						m_On = true;
					}
				}
				// コントローラーが接続されていないときの処理
				else
				{
					auto keyVec = App::GetApp()->GetInputDevice().GetKeyState();
					if (keyVec.m_bPushKeyTbl['W'])
					{
						pos.z += 0.1f;
					}
					if (keyVec.m_bPushKeyTbl['A'])
					{
						pos.x -= 0.1f;
					}
					if (keyVec.m_bPushKeyTbl['S'])
					{
						pos.z -= 0.1f;
					}
					if (keyVec.m_bPushKeyTbl['D'])
					{
						pos.x += 0.1f;
					}
				}
			}
			ptrTrans->SetPosition(pos);

			//今日できなかった奴
			// ライトがオフの時
			if (!m_On)
			{
				// ライトを小さくする
				if (m_Scale.x > 0.0f&& m_Scale.y > 0.0f)
				{
					m_Scale.x -= 0.2f;
					m_Scale.y -= 0.2f;
					m_Scale.z -= 0.2f;

				}
			}
			else {
				// 大きい状態にする
				if (!m_Big)
				{
					// オフまたは小さい状態から大きい状態にする処理
					if (m_Scale.x < 3.0f&& m_Scale.y < 3.0f)
					{
						m_Scale.x += 0.2f;
						m_Scale.y += 0.2f;
						m_Scale.z += 0.2f;
					}

				}
				// 小さい状態にする
				else {
					// 大きい状態から小さい状態にする処理
					if (m_Scale.x > 1.50f&& m_Scale.y > 1.50f)
					{
						m_Scale.x -= 0.2f;
						m_Scale.y -= 0.2f;
						m_Scale.z -= 0.2f;
					}
					// オフの状態から小さい状態にする処理
					if (m_Scale.x < 1.50f&& m_Scale.y < 1.50f)
					{
						m_Scale.x += 0.2f;
						m_Scale.y += 0.2f;
						m_Scale.z += 0.2f;
					}

				}

			}

			ptrTrans->SetScale(m_Scale);

			auto ptrDraw = GetComponent<BcPNTStaticDraw>();

			float defScale = 1.0f - (m_Scale.x - 1.5f) * 0.3f / 1.6f;

			GameManager::getInstance()->SetSpotLightPosition(GetComponent<Transform>()->GetPosition());


			/*
			Vec3 scale = CalcScale();
			
			
			*/

			//スケールはスケールを変更する関数　CalcScale
			//posはposを変更する関数			CalcPos
			//スピードはスピードを変更する関数	CalcSeed
			//lightを変更する関数				CalcLight

		}
	}
}
//end basecross