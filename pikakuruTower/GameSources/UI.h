/*!
@file UI.h
@brief UI
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	///	ライトのスイッチ
	//--------------------------------------------------------------------------------------

	class RightSuitch : public Sprite {

	public:
		RightSuitch(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~RightSuitch() {}

		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate()override;

	};

	//--------------------------------------------------------------------------------------
	///	HPゲージのスプライト
	//--------------------------------------------------------------------------------------
	class HpGage : public Sprite {
	public:
		HpGage(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& startScale, 
			const Vec2& startPos);

		virtual ~HpGage() {}

		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	///	HPゲージの枠のスプライト
	//--------------------------------------------------------------------------------------
	class HpGageFrame : public Sprite {
	public:
		HpGageFrame(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~HpGageFrame() {}

		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};


	//--------------------------------------------------------------------------------------
	///	アイテムアイコンのスプライト
	//--------------------------------------------------------------------------------------
	class ItemIcon : public Sprite {
	public:
		ItemIcon(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~ItemIcon() {}

		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};


	//--------------------------------------------------------------------------------------
	///	数字を表示するスプライト
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

		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate()override;

		void ChangeNumber(int i);

		int GetNumber() const { return m_Number; }
	};

	//--------------------------------------------------------------------------------------
	///	現在のWaveを表示して消えるスプライト
	//--------------------------------------------------------------------------------------
	class WaveSprite : public Sprite {
	private:
		float m_TotalTime;
		// 現れてから消えるまでの時間
		float m_RemoveTime;
	public:
		WaveSprite(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& startPos);

		virtual ~WaveSprite() {}

		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	///	現在のWaveを表示するスプライト
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
	///	夜にするスプライト
	//--------------------------------------------------------------------------------------
	class NightMaskSprite : public Sprite {
		float m_Alpha = 0.6f;

		float m_StartAlpha = 0.0f;
	public:
		//構築と破棄
		NightMaskSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~NightMaskSprite() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	///	ダメージを受けた時の赤いスプライト
	//--------------------------------------------------------------------------------------
	class DamegeSprite : public Sprite {
		float m_TotalTime = 0.0f;
		float m_RemoveTime = 0.25f;

	public:
		//構築と破棄
		DamegeSprite(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~DamegeSprite() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};

	//--------------------------------------------------------------------------------------
	///	Pause画面用のスプライト
	//--------------------------------------------------------------------------------------
	class PauseSprite : public Sprite {
	public:
		//構築と破棄
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