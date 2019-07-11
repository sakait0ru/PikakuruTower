/*!
@file FadeSquare.cpp
@brief Fade�̎l�p��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// �l�p��Fade 
	//--------------------------------------------------------------------------------------
	FadeSquareSprite::FadeSquareSprite(const shared_ptr<Stage>& stagePtr,
		const FadeType& fadeType,
		const wstring& stageString):
		Sprite(stagePtr, L"Black.png", Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f)),
		m_Type(fadeType),
		m_StageString(stageString)
	{}

	void FadeSquareSprite::OnCreate() {
		Sprite::OnCreate();
		// �^�O�ݒ�
		AddTag(L"Fade");
		// �s�����x�̐ݒ�
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		switch (m_Type)
		{
		case FadeIn:
			ptrDraw->SetDiffuse(Col4(1.0f,1.0f,1.0f,1.0f));
			break;
		case FadeOut:
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.0f));
			break;
		default:
			break;
		}
	}

	void FadeSquareSprite::OnUpdate() {

		const float dis = 0.01f;

		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		Col4 color = ptrDraw->GetDiffuse();
		//m_Type�ɂ���ē�����ς���
		switch (m_Type)
		{
		case FadeIn:
			color.w -= dis;
			ptrDraw->SetDiffuse(color);
			if (color.w < 0.0f) {
				GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
			}
			break;
		case FadeOut:
			color.w += dis;
			ptrDraw->SetDiffuse(color);
			if (color.w > 1.0f) {
				GetStage()->PostEvent(0.0f,GetThis<ObjectInterface>(),App::GetApp()->GetScene<Scene>(),m_StageString);
				GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
			}
			break;
		default:
			break;
		}
		
	}

}