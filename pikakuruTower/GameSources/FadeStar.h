#pragma once
#include "stdafx.h"

namespace basecross {

	enum FadeType
	{
		FadeIn,
		FadeOut
	};

	class FadeStarSprite : public Sprite {

        float FadeSpeed = 0.05f;  //�t�F�[�h���Ă�������




		FadeType m_FadeType;
		wstring m_StageString = L"";

	public:
		FadeStarSprite(
			const shared_ptr<Stage>& stagePtr,
			const FadeType& fadeType,
			const wstring& stageString = L"");

		virtual ~FadeStarSprite() {};

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};

	//--------------------------------------------------------------------------------------
	// ���C����Clear�������Ԑl��
	//--------------------------------------------------------------------------------------
	class MainStageHuman : public MyGameObject {
	private:
		Vec3 m_Position;
	public:
		MainStageHuman(const shared_ptr<Stage>& stagePtr,const Vec3 position);
		~MainStageHuman() {};

		virtual void OnCreate();
		virtual void OnUpdate();
	};
}