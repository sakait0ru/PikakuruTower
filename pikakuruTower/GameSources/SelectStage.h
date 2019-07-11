/*!

@file GameStage.h

@brief �Q�[���X�e�[�W

*/



#pragma once

#include "stdafx.h"

namespace basecross {
	class SelectTriMoveSprite;


	class AnimeSprite : public Sprite {
		float m_LightMove = 25.0f;        
		float m_LightMoveEnd = 300.0f;
		float m_LightQuaMove = 0.0f;

	public:
		AnimeSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~AnimeSprite() {};

		virtual void OnUpdate()override;

		Vec3 GetStartPos() const { return Vec3(m_StartPos.x, m_StartPos.y,0); }
	};


	// ���邢����\������X�v���C�g
	class SelectSpotSprite : public Sprite {
	public:
		SelectSpotSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		~SelectSpotSprite() {}

		bool SelectSpotFlag;

		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		bool GetSelectSpotFlag() { return SelectSpotFlag; }

	};
	//--------------------------------------------------------------------------------------

	//	�Z���N�g�X�e�[�W�N���X

	//--------------------------------------------------------------------------------------

	class SelectStage : public Stage {

		//�r���[�̍쐬
		void CreateViewLight();

		//UI�̍쐬
		void CreateUI();

		vector<shared_ptr<AnimeSprite>> m_SpVec;
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SelectSpotSprite> m_SpotSprite;

		shared_ptr<SelectTriMoveSprite> m_RTriSprite;
		shared_ptr<SelectTriMoveSprite> m_LTriSprite;

		int m_StageNum = 0;            //���I�����Ă�X�e�[�W�ԍ�

		bool m_CntrolLock;             //�X�e�B�b�N����x�|�����烍�b�N

		bool m_FadeSwitch = true;      //�t�F�[�h�̃X�C�b�`

		bool m_Extra = false;
		float m_TotalTime = 0.0f;
		float m_MoveTime = 1.5f;	   // �ړ��ɂ����鎞��

	public:
		//�\�z�Ɣj��
		SelectStage() :Stage(), m_CntrolLock(false)
			, m_SpVec(9)
		{
		}
		virtual ~SelectStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;

		int GetStageNum() { return m_StageNum; } 
		vector<shared_ptr<AnimeSprite>> GetSpVec() const { return m_SpVec; }
	};



	class SelectTriMoveSprite : public Sprite {
	private:

		float m_QuaX = 0.0f;   //�O�p�̕ω���
		float m_MoveX = 1.0f;  //�O�p�̓�������
		float m_MaxX = 20.0f;  //�����ő�l


	public:
		SelectTriMoveSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~SelectTriMoveSprite() {}
		//�X�V
		virtual void OnUpdate()override;

		void RTriMove(bool Avtive);
		void LTriMove(bool Avtive);
	};

}

//end basecross