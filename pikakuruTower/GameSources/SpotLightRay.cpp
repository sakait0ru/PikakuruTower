#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
//	���C�g�̌`
//--------------------------------------------------------------------------------------
	SpotLightRay::SpotLightRay(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		MyGameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}

	//������
	void SpotLightRay::OnCreate() {

		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//�^�O������
		AddTag(L"ConeObject");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateCone(1.0f, 1, 18, vertices, indices);
		m_MeshResource = MeshResource::CreateMeshResource(vertices, indices, true);

		ptrDraw->SetMeshResource(m_MeshResource);
		ptrDraw->SetDiffuse(Col4(0.05, 0.05, 0.05, 0.05));
		ptrDraw->SetBlendState(BlendState::Additive);
		SetAlphaActive(true);
		SetDrawLayer(100);




	}

	void SpotLightRay::OnUpdate() {
		// Spotlight�̈ʒu�Ɉړ�����
		auto spotLight = GetStage()->GetSharedGameObject<Spotlight>(L"Spotlight");
		auto spotTrans = spotLight->GetComponent<Transform>();
		auto spotPos = spotTrans->GetPosition();
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos.x = spotPos.x;
		pos.z = spotPos.z;
		ptrTrans->SetPosition(pos);

		// Spotlight�̑傫���ɕω�����
		auto spotScale = spotTrans->GetScale();
		ptrTrans->SetScale(Vec3(spotScale.x, 2.0f, spotScale.z));
		if (spotScale.x < 0.0f) {
			SetDrawActive(false);
		}
		else {
			SetDrawActive(true);
		}

		// Spotlight�̑傫���ɂ���Ė��邳��ς���
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		if (spotLight->GetBig()) {
			ptrDraw->SetDiffuse(Col4(0.15, 0.15, 0.15, 0.15));
		}
		else {
			ptrDraw->SetDiffuse(Col4(0.005f, 0.005f, 0.005f, 0.005f));

		}


		Vec3 towerPos = Vec3(0, 0, 8.5);
		pos += towerPos;

		auto& verVec = m_MeshResource->GetBackupVerteces<VertexPositionNormalTexture>();
		vector<uint16_t>& indexVec = m_MeshResource->GetBackupIndices<VertexPositionNormalTexture>();
		for (int i = 0; i < indexVec.size(); i++) {
			if (verVec[indexVec[i]].position.y >= 0.5f) {
				verVec[indexVec[i]].position.z = -pos.z / spotScale.z;
				verVec[indexVec[i]].position.x = -pos.x / spotScale.x;
				verVec[indexVec[i]].position.y = 0.75f;
			}
		}
		m_MeshResource->UpdateVirtexBuffer(verVec);

	}

}