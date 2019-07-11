/*!
@file UI.h
@brief UI
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	///	���C�g�̃X�C�b�`
	//--------------------------------------------------------------------------------------

	class RightSuitch : public Sprite {

	public:
		RightSuitch(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~RightSuitch() {}

		//������
		virtual void OnCreate() override;
		virtual void OnUpdate()override;

	};

	//--------------------------------------------------------------------------------------
	///	HP�Q�[�W�̃X�v���C�g
	//--------------------------------------------------------------------------------------
	class HpGage : public Sprite {
	public:
		HpGage(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& startScale, 
			const Vec2& startPos);

		virtual ~HpGage() {}

		//������
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	///	HP�Q�[�W�̘g�̃X�v���C�g
	//--------------------------------------------------------------------------------------
	class HpGageFrame : public Sprite {
	public:
		HpGageFrame(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~HpGageFrame() {}

		//������
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};


	//--------------------------------------------------------------------------------------
	///	�A�C�e���A�C�R���̃X�v���C�g
	//--------------------------------------------------------------------------------------
	class ItemIcon : public Sprite {
	public:
		ItemIcon(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~ItemIcon() {}

		//������
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};


	//--------------------------------------------------------------------------------------
	///	������\������X�v���C�g
	//--------------------------------------------------------------------------------------
	class NumberSprite : public Sprite {
	private:
		int m_Number;
	public:
		NumberSprite(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& startScale,
			const Vec2& startPos,
			const int& number);

		virtual ~NumberSprite() {}

		//������
		virtual void OnCreate() override;
		virtual void OnUpdate()override;

		void ChangeNumber(int i);

		int GetNumber() const { return m_Number; }
	};

	//--------------------------------------------------------------------------------------
	///	���݂�Wave��\�����ď�����X�v���C�g
	//--------------------------------------------------------------------------------------
	class WaveSprite : public Sprite {
	private:
		float m_TotalTime;
		// ����Ă��������܂ł̎���
		float m_RemoveTime;
	public:
		WaveSprite(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& startPos);

		virtual ~WaveSprite() {}

		//������
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	///	���݂�Wave��\������X�v���C�g
	//--------------------------------------------------------------------------------------
	class NowWaveSprite : public Sprite {
	public:
		NowWaveSprite(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~NowWaveSprite() {}

		void SetWaveNumber(wstring fileName);
	};

	//--------------------------------------------------------------------------------------
	///	��ɂ���X�v���C�g
	//--------------------------------------------------------------------------------------
	class NightMaskSprite : public Sprite {
		float m_Alpha = 0.6f;

		float m_StartAlpha = 0.0f;
	public:
		//�\�z�Ɣj��
		NightMaskSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~NightMaskSprite() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	///	�_���[�W���󂯂����̐Ԃ��X�v���C�g
	//--------------------------------------------------------------------------------------
	class DamegeSprite : public Sprite {
		float m_TotalTime = 0.0f;
		float m_RemoveTime = 0.25f;

	public:
		//�\�z�Ɣj��
		DamegeSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~DamegeSprite() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};

	//--------------------------------------------------------------------------------------
	///	Pause��ʗp�̃X�v���C�g
	//--------------------------------------------------------------------------------------
	class PauseSprite : public Sprite {
	public:
		//�\�z�Ɣj��
		PauseSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		bool m_cntlrock;

		virtual ~PauseSprite() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void Akarusa(bool flg);
	};
}