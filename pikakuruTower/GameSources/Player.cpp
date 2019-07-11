/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	IMPLEMENT_SINGLETON_INSTANCE(Vibration);

	void Vibration::SetVibration(float time, float left, float right, int CntNum)
	{
		if (!m_isVib[CntNum])
		{
			m_isVib[CntNum] = true;
			m_VibInterval[CntNum] = time;

			const WORD MAX_VIB = 65535;

			XINPUT_VIBRATION state;
			state.wLeftMotorSpeed = (WORD)(MAX_VIB * left);
			state.wRightMotorSpeed = (WORD)(MAX_VIB * right);

			XInputSetState(CntNum, &state);
		}
	}

	void Vibration::Update()
	{
		for (int i = 0; i < ARRAYSIZE(m_isVib); i++)
		{
			if (m_isVib[i])
			{
				float delta = App::GetApp()->GetElapsedTime();
				m_VibCount[i] += delta;

				if (m_VibCount[i] > m_VibInterval[i])
				{
					m_isVib[i] = false;
					m_VibCount[i] = 0;

					XINPUT_VIBRATION state;
					state.wLeftMotorSpeed = 0;
					state.wRightMotorSpeed = 0;
					XInputSetState(0, &state);
				}
			}
		}
	}

	//--------------------------------------------------------------------------------------
	// �M���ʂ𔭎˂���{��
	//--------------------------------------------------------------------------------------
	Player::Player(const shared_ptr<Stage>& stagePtr) :
		MyGameObject(stagePtr)
	{
	}
	Player::Player(const shared_ptr<Stage>& stagePtr, const Vec3 & scale, const Vec3 & rotation, const Vec3 & position) :
		MyGameObject(stagePtr)
	{
	}
	//���ݔ��ˑ��u�@= Player
	void Player::OnCreate()
	{
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(0.55f, 0.75f, 0.55f);	//���a25�Z���`�̋���
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(0, 0.525f, -6.1f);

		//�G�t�F�N�g�̏�����
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\fire.efk";
		auto ShEfkInterface = GetTypeStage<MainStage>()->GetEfkInterface();
		m_EfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);

	}

	void Player::OnUpdate()
	{
		m_InputHandler.PushHandle(GetThis<Player>());

		// �C���^�[�o����ԂȂ�
		if (!m_IsFlashItem) {
			m_FlashItemTime += App::GetApp()->GetElapsedTime();
			if (m_FlashItemTime > m_FlashItemIntervalTime) {
				m_IsFlashItem = true;
				m_FlashItemTime = 0.0f;
			}
		}
	}

	//A�{�^��
	void Player::OnPushA() {

	}
	//B�{�^��
	void Player::OnPushB()
	{

		// �M���ʂ��g���邩�@�C���^�[�o����ԂłȂ����`�F�b�N
		if (m_IsFlashItem) {
			auto GM = GameManager::getInstance();
			// �M���ʂ��g���邩
			if (GameManager::getInstance()->UseFlashItem())
			{
				// �M���ʂ𐶐�
				auto ptrTrans = GetComponent<Transform>();
				Vec3 pos = ptrTrans->GetPosition();
				GetStage()->AddGameObject<FlashSprite>(L"senkoudama.jpg", Vec3(1, 1, 1), Vec3(0, 0, 0), pos);

				// UI�̍X�V
				auto numberSprite = GetStage()->GetSharedGameObject<NumberSprite>(L"NumberSprite");
				auto number = GM->GetFlashItem();
				numberSprite->ChangeNumber(number);

				// �C���^�[�o���J�n
				m_IsFlashItem = false;
				m_FlashItemTime = 0.0f;
			}
		}

	}

	//--------------------------------------------------------------------------------------
	// �M���ʖ{��
	//--------------------------------------------------------------------------------------
	FlashSprite::FlashSprite(const shared_ptr<Stage>& stagePtr, const wstring& textureKey,
		const Vec3& startScale,
		const Vec3& startRotaiton,
		const Vec3& startPos) :
		MyGameObject(stagePtr),
		m_Scale(startScale),
		m_Rotation(startRotaiton),
		m_Position(startPos),
		m_ScaleSpanMat(0.75f)
	{}

	void FlashSprite::OnCreate()
	{

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(m_ScaleSpanMat),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		SetAlphaActive(true);

		//auto ptrDraw = AddComponent<PNTStaticDraw>();
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"FlashBan.bmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		auto ptrShadow = AddComponent<Shadowmap>();


		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"FlashBan.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//�G�t�F�N�g�̏�����
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		//wstring TestEffectStr = DataDir + L"Effects\\zonbinowdamage.efk";
		wstring TestEffectStr = DataDir + L"Effects\\flashbangtest.efk";
		//wstring TestEffectStr = DataDir + L"Effects\\senkouhanabi.efk";

		auto ShEfkInterface = GetTypeStage<MainStage>()->GetEfkInterface();
		m_EfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);


	}

	void FlashSprite::OnUpdate()
	{
		//Stop���ĉ������Ȃ��Ń��^�[��
		if (m_Stoped)
		{
			return;
		}

		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;
		//m_TotalTime��2�b�ȏ�ɂȂ��������
		if (m_TotalTime > 2.0f)
		{
			auto gameobjectVec = GetStage()->GetGameObjectVec();
			App::GetApp()->GetXAudio2Manager()->Start(L"flash.wav", 0, 0.1f);

			for (auto& object : gameobjectVec)
			{
				if (object->FindTag(L"Enemy") && !(object->FindTag(L"Start")))
				{
					auto enemy = dynamic_pointer_cast<Enemy>(object);
					if (enemy) {
						enemy->IsStunCheck();
					}
				}
			}

			// �G�t�F�N�g�e�X�g
			auto Ptr = GetComponent<Transform>();
			//�G�t�F�N�g�̃v���C
			m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, Ptr->GetPosition());


			GetStage()->AddGameObject<FlashMaskSprite>(L"spark.png");
			//GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
			SetDrawActive(false);
			m_Stoped = true;
		}

		// �C�[�W���O�̏����A�ʂ̊֐��ɂ���
		Easing<Vec3> easing;
		
		auto tgtPos = easing.EaseOut(EasingType::Exponential, m_Position, Vec3(0.0f, 3.5f, -1.5f), m_TotalTime, 3.0f);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(tgtPos);
		auto spin = m_Spin += 0.4f;
//		Vec3 tgtRot(0, m_Spin,0);
		auto tgtRot = easing.EaseOut(EasingType::Exponential, Vec3(0,0,0), Vec3(0.0f,spin /*20.0f*/, 0.0f), m_TotalTime, 3.0f);
		ptrTrans->SetRotation(tgtRot);

	}


	//--------------------------------------------------------------------------------------
	//	�}�X�L���O�X�v���C�g
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	FlashMaskSprite::FlashMaskSprite(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureKey) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_ScaleSpeed(0.3f),
		m_AlphaNum(0.7f)
	{}

	FlashMaskSprite::~FlashMaskSprite() {}

	void FlashMaskSprite::OnCreate() {
		SetDrawLayer(3);
		float HelfSize = 0.5f;
		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-1.0, 1.0, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//���b�V���̍쐬�i�ύX�ł���j
		m_SpriteMesh = MeshResource::CreateMeshResource(vertices, indices, true);


		SetAlphaActive(true);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(1.0f, 1.0f, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(0, 0, 0);
	}

	void FlashMaskSprite::OnUpdate()
	{

	}

	void FlashMaskSprite::OnDraw() {

		auto dev = App::GetApp()->GetDeviceResources();
		auto pID3D11DeviceContext = dev->GetD3DDeviceContext();
		auto renderStatePtr = dev->GetRenderState();
		pID3D11DeviceContext->OMSetBlendState(renderStatePtr->GetAlphaBlendEx(), nullptr, 0xffffffff);
		pID3D11DeviceContext->OMSetDepthStencilState(renderStatePtr->GetDepthNone(), 0);
		pID3D11DeviceContext->RSSetState(renderStatePtr->GetCullNone());
		ID3D11SamplerState* pSampler = nullptr;
		pSampler = renderStatePtr->GetLinearClamp();
		pID3D11DeviceContext->PSSetSamplers(0, 1, &pSampler);
		//�V�F�[�_�̐ݒ�
		//���_�V�F�[�_
		pID3D11DeviceContext->VSSetShader(VSPCTSprite::GetPtr()->GetShader(), nullptr, 0);
		//�C���v�b�g���C�A�E�g�̐ݒ�
		pID3D11DeviceContext->IASetInputLayout(VSPCTSprite::GetPtr()->GetInputLayout());
		//�s�N�Z���V�F�[�_
		pID3D11DeviceContext->PSSetShader(PSPCTSprite::GetPtr()->GetShader(), nullptr, 0);
		//�ʏ���
		SpriteConstants sb;
		//�R���X�^���g�o�b�t�@�̍쐬
		//�s��̎擾
		auto ptrTrans = GetComponent<Transform>();
		//�s��̒�`
		bsm::Mat4x4 World;
		World = ptrTrans->Get2DWorldMatrix();
		//�G�~�b�V�u
		sb.Emissive = Col4(0, 0, 0, 1);

		//��FlashMaskSprite�̑傫���Ȃ��ē����ɂȂ��Ă�������
		auto scale = ptrTrans->GetScale();
		scale += m_ScaleSpeed;
		ptrTrans->SetScale(scale);
		//scale.x ��9.0f�ȏ�ɂȂ����Ƃ�
		if (scale.x > 5.0f)
		{
			m_AlphaNum -= 0.006f;

			if (m_AlphaNum < 0.0f)
			{
				GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
			}
		}
		//scale.x��0.0f�̂ق����傫���Ȃ�����
		if (scale.x < 0.0f)
		{
			//m_ScaleSpeed��0.0f�ɂ���
			m_ScaleSpeed = 0.0f;
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}

		//�f�t�B�[�Y�͂��ׂĒʂ�
		sb.Diffuse = Col4(1, 1, 1, m_AlphaNum);
		//�s��̐ݒ�
		sb.World = World;
		//�e�N�X�`��
		auto shTex = App::GetApp()->GetResource<TextureResource>(m_TextureKey);
		pID3D11DeviceContext->PSSetShaderResources(0, 1, shTex->GetShaderResourceView().GetAddressOf());
		//�R���X�^���g�o�b�t�@�̍X�V
		pID3D11DeviceContext->UpdateSubresource(CBSprite::GetPtr()->GetBuffer(), 0, nullptr, &sb, 0, 0);
		//�R���X�^���g�o�b�t�@�̐ݒ�
		ID3D11Buffer* pConstantBuffer = CBSprite::GetPtr()->GetBuffer();
		//���_�V�F�[�_�ɓn��
		pID3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		//�s�N�Z���V�F�[�_�ɓn��
		pID3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
		//�X�g���C�h�ƃI�t�Z�b�g
		UINT stride = m_SpriteMesh->GetNumStride();
		UINT offset = 0;
		//�`����@�̃Z�b�g
		pID3D11DeviceContext->IASetPrimitiveTopology(m_SpriteMesh->GetPrimitiveTopology());
		//���_�o�b�t�@�̃Z�b�g
		pID3D11DeviceContext->IASetVertexBuffers(0, 1, m_SpriteMesh->GetVertexBuffer().GetAddressOf(), &stride, &offset);
		//�C���f�b�N�X�o�b�t�@�̃Z�b�g
		pID3D11DeviceContext->IASetIndexBuffer(m_SpriteMesh->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);
		//�`��
		pID3D11DeviceContext->DrawIndexed(m_SpriteMesh->GetNumIndicis(), 0, 0);
		//��n��
		dev->InitializeStates();
	}


	//end basecross
}
