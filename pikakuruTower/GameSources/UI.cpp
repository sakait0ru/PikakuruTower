/*!
@file UI.cpp
@brief UI
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

//--------------------------------------------------------------------------------------
///	���C�g�̃X�C�b�`
//--------------------------------------------------------------------------------------

	RightSuitch::RightSuitch(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

	void RightSuitch::OnCreate() {
		float helfSize = 0.5f;
		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-0, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-0, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, -helfSize, 0), Col4(1.0f, 01.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(Vec3(m_StartPos.x, m_StartPos.y, 0.0f));
		// �s�{�b�g���E�[�ɂ���
		ptrTrans->SetPivot(0.0f, 0.0f, 0.0f);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(L"Light_on.png");


		AddTag(L"UI");

		

		SetDrawLayer(11);
		SetAlphaActive(true);

		//�X�v���C�g�̌���		
		ptrDraw->SetDiffuse(Col4(1, 1, 1, 11.1f));
	}


	void RightSuitch::OnUpdate() {

		// �h���[�R���|�[�l���g���擾
		auto ptrDraw = GetComponent<PCTSpriteDraw>();

		// Spotlight.cpp�̂������Ă���
		auto on = GetStage()->GetSharedGameObject<Spotlight>(L"Spotlight")->GetOn();
		if (on) {
			// ���C�g�����Ă�����ON.jpg�ɒ���ւ���
			ptrDraw->SetTextureResource(L"Light_on.png");
		}
		else {
			// ���̑���OFF.jpg�ɒ���ւ���
			ptrDraw->SetTextureResource(L"Light_off.png");
		}

		
	}

	//--------------------------------------------------------------------------------------
	///	HP�Q�[�W�̃X�v���C�g
	//--------------------------------------------------------------------------------------
	HpGage::HpGage(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale, 
			const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale,startPos)
	{}

	void HpGage::OnCreate() {
		float helfSize = 0.5f;
		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-0, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-0, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, -helfSize, 0), Col4(1.0f, 01.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(Vec3(m_StartPos.x,m_StartPos.y,0.0f));
		// �s�{�b�g���E�[�ɂ���
		ptrTrans->SetPivot(0.0f, 0.0f, 0.0f);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_TextureKey);

		AddTag(L"UI");
		
		SetDrawLayer(11);
	}
	void HpGage::OnUpdate() {
					
		{ // �_���[�W���󂯂���
			auto ptrTrans = GetComponent<Transform>();
			auto scale = ptrTrans->GetScale();

			auto GM = GameManager::getInstance();
			int hp = GM->GetWallHp();
			int maxHp = GM->GetMaxWallHp();
			float rate = float(maxHp) / (float)hp;

			scale.x = m_StartScale.x / rate;
			ptrTrans->SetScale(scale);
		}
	}

	//--------------------------------------------------------------------------------------
	///	Hp�Q�[�W�̘g�̃X�v���C�g
	//--------------------------------------------------------------------------------------
	HpGageFrame::HpGageFrame(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

	void HpGageFrame::OnCreate() {
		Sprite::OnCreate();
		SetDrawLayer(11);

	}

	void HpGageFrame::OnUpdate() {

		auto GM = GameManager::getInstance();
		auto maxHp = GM->GetMaxWallHp();
		auto hp = GM->GetWallHp();

		float dis = (float)hp / (float)maxHp;

		auto ptrDraw = GetComponent<PCTSpriteDraw>();

		if (dis < 0.25f) {
			ptrDraw->SetTextureResource(L"UI75__0509.png");
		}
		else if (dis < 0.6f) {
			ptrDraw->SetTextureResource(L"UI50__0509.png");
		}
		else if(dis < 0.8f){
			ptrDraw->SetTextureResource(L"UI25__0509.png");		
		}
		else {
			ptrDraw->SetTextureResource(L"UI0__0509.png");
		}



	}

	//--------------------------------------------------------------------------------------
	///	�A�C�e���A�C�R���̃X�v���C�g
	//--------------------------------------------------------------------------------------
	ItemIcon::ItemIcon(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

	void ItemIcon::OnCreate() {
		Sprite::OnCreate();
		SetDrawLayer(10);
	}

	void ItemIcon::OnUpdate() {

	}

	//--------------------------------------------------------------------------------------
	///	������\������X�v���C�g
	//--------------------------------------------------------------------------------------
	NumberSprite::NumberSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos,
		const int& number) :
		Sprite(stagePtr, textureKey, startScale, startPos),
		m_Number(number)
	{}

	void NumberSprite::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);

		//���_�z��
		vector<VertexPositionNormalTexture> vertices;
		//�C���f�b�N�X���쐬���邽�߂̔z��
		vector<uint16_t> indices;
		//Square�̍쐬(�w���p�[�֐��𗘗p)
		MeshUtill::CreateSquare(1.0f, vertices, indices);

		//UV�l�̕ύX
		float from = ((float)m_Number) / 10.0f;
		float to = from + (1.0f / 10.0f);
		//���㒸�_
		vertices[0].textureCoordinate = Vec2(from, 0);
		//�E�㒸�_
		vertices[1].textureCoordinate = Vec2(to, 0);
		//�������_
		vertices[2].textureCoordinate = Vec2(from, 1.0f);
		//�E�����_	
		vertices[3].textureCoordinate = Vec2(to, 1.0f);

		//���_�̌^��ς����V�������_���쐬
		vector<VertexPositionColorTexture> new_vertices;
		for (auto& v : vertices) {
			VertexPositionColorTexture nv;
			nv.position = v.position;
			nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
			nv.textureCoordinate = v.textureCoordinate;
			new_vertices.push_back(nv);
		}
		SetAlphaActive(true);

		auto ptrDraw = AddComponent<PCTSpriteDraw>(new_vertices, indices);
		ptrDraw->SetTextureResource(m_TextureKey);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);

		SetDrawLayer(10);



	}

	void NumberSprite::OnUpdate() {

	}

	// Nunber�̕\����ύX����
	void NumberSprite::ChangeNumber(int i) {
		m_Number = i;

		//���_�z��
		vector<VertexPositionNormalTexture> vertices;
		//�C���f�b�N�X���쐬���邽�߂̔z��
		vector<uint16_t> indices;
		//Square�̍쐬(�w���p�[�֐��𗘗p)
		MeshUtill::CreateSquare(1.0f, vertices, indices);

		//UV�l�̕ύX
		float from = ((float)m_Number) / 10.0f;
		float to = from + (1.0f / 10.0f);
		//���㒸�_
		vertices[0].textureCoordinate = Vec2(from, 0);
		//�E�㒸�_
		vertices[1].textureCoordinate = Vec2(to, 0);
		//�������_
		vertices[2].textureCoordinate = Vec2(from, 1.0f);
		//�E�����_	
		vertices[3].textureCoordinate = Vec2(to, 1.0f);

		//���_�̌^��ς����V�������_���쐬
		vector<VertexPositionColorTexture> new_vertices;
		for (auto& v : vertices)
		{
			VertexPositionColorTexture nv;
			nv.position = v.position;
			nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
			nv.textureCoordinate = v.textureCoordinate;
			new_vertices.push_back(nv);
		}

		SetAlphaActive(true);


		auto m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);

		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetMeshResource(m_SquareMeshResource);

	}

	//--------------------------------------------------------------------------------------
	///	���݂�Wave��\�����ď�����X�v���C�g
	//--------------------------------------------------------------------------------------
	WaveSprite::WaveSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, Vec2(1254, 256), startPos),
		m_TotalTime(0.0f),
		m_RemoveTime(3.0f)
	{}
	
	void WaveSprite::OnCreate() {
		Sprite::OnCreate();
		SetDrawLayer(10);
		//�T�E���h�̍Đ�
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(L"tugi_Wave.wav", 0, 0.3f);
	}
	void WaveSprite::OnUpdate() {
		// �g�傩��̏k���ŏ�����
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		auto scale = ptrTrans->GetScale();

		auto ptrDraw = GetComponent<PCTSpriteDraw>();

		float removeTimeHalf = m_RemoveTime / 2.0f;

		float dis;
		if (m_TotalTime < removeTimeHalf) {
			dis = m_TotalTime / removeTimeHalf;
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, dis));
		}
		else {
			dis = (m_TotalTime - removeTimeHalf) / removeTimeHalf;
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f- dis));
		}


		if (m_TotalTime > m_RemoveTime) {
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}
	}
	//--------------------------------------------------------------------------------------
	///	���݂�Wave��\������X�v���C�g
	//--------------------------------------------------------------------------------------
	NowWaveSprite::NowWaveSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

	void NowWaveSprite::SetWaveNumber(wstring fileName) {
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		fileName = L"Small" + fileName;
		ptrDraw->SetTextureResource(fileName);
	}

	//--------------------------------------------------------------------------------------
	///	��ɂ���X�v���C�g
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	NightMaskSprite::NightMaskSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos):
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}


	void NightMaskSprite::OnCreate() {
		Sprite::OnCreate();
		SetDrawLayer(2);

		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetDiffuse(Col4(1, 1, 1, 0.6f));
	}


	void NightMaskSprite::OnUpdate() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();

		auto spotLight = GetStage()->GetSharedGameObject<Spotlight>(L"Spotlight");
		spotLight->CalcDevPos();
		Vec3 spotDevPos = spotLight->GetDevPos();


		pos.x = spotDevPos.x * 640;
		pos.y = -spotDevPos.y * 400;
		ptrTrans->SetPosition(pos);

		auto spotActive = spotLight->GetActive();
		auto spotScale = spotLight->GetBig();
		auto ptrDraw = GetComponent<PCTSpriteDraw>();

		// ���Ă��鎞
		if (spotActive) {
			// �傫����
			if (spotScale) {
				ptrDraw->SetTextureResource(L"NightMaskSmall.png");
				
			}
			// ��������
			else{
				ptrDraw->SetTextureResource(L"NightMask.png");
			}
		}
		// ���Ă��Ȃ���
		else {
			ptrDraw->SetTextureResource(L"Black.png");
		}


		//auto mainStageStartTime = GetTypeStage<MainStage>()->GetStartTime();
		//if (mainStageStartTime < 3.0f) {
		//	m_StartAlpha = ((mainStageStartTime / 10.0f) * 2.0f);

		//	auto ptrDraw = GetComponent<PCTSpriteDraw>();
		//	ptrDraw->SetDiffuse(Col4(1, 1, 1, m_StartAlpha));
		//}


		// �X�e�[�W�N���A�����疾�邭�Ȃ�
		if (WaveManager::getInstance()->IsClear()) {

			m_Alpha -= 0.01f;

			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1, 1, 1, m_Alpha));
		}

	}
	
	//--------------------------------------------------------------------------------------
	///	�_���[�W���󂯂����̐Ԃ��X�v���C�g
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	DamegeSprite::DamegeSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}


	void DamegeSprite::OnCreate() {
		Sprite::OnCreate();
		SetDrawLayer(3);

		// ��������
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetDiffuse(Col4(1, 1, 1, 0.6f));
	}

	void DamegeSprite::OnUpdate() {
		// �g�傩��̏k���ŏ�����
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		auto scale = ptrTrans->GetScale();

		auto ptrDraw = GetComponent<PCTSpriteDraw>();

		float removeTimeHalf = m_RemoveTime / 2.0f;

		float dis;
		if (m_TotalTime < removeTimeHalf) {
			dis = m_TotalTime / removeTimeHalf;
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, dis));
		}
		else {
			dis = (m_TotalTime - removeTimeHalf) / removeTimeHalf;
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f - dis));
		}


		if (m_TotalTime > m_RemoveTime) {
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}

	}

	//--------------------------------------------------------------------------------------
	///	Pause��ʗp�̃X�v���C�g
	//--------------------------------------------------------------------------------------
	PauseSprite::PauseSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}


	void PauseSprite::OnCreate() {
		Sprite::OnCreate();
		SetDrawLayer(100);
		AddTag(L"PauseMenu");
		SetDrawActive(false);
		
	}

	void PauseSprite::OnUpdate()
	{


	}
	void PauseSprite::Akarusa(bool flg)
	{
		GetComponent<PCTSpriteDraw>()->SetDiffuse(Col4(1, 1, 1, 1.0f));
	}
}

//end basecross
