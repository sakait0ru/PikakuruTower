/*!
@file GameManager.cpp
@brief ゲーム全体を管理するマネージャー
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	ゲーム全体を管理するマネージャー
	//--------------------------------------------------------------------------------------
	GameManager* GameManager::m_GM = nullptr;

	void GameManager::CreateGM() {
		m_GM = new GameManager();
	}

	GameManager* GameManager::getInstance() {
		if (m_GM == nullptr) {
			m_GM = new GameManager();
		}
		return m_GM;
	}

	//--------------------------------------------------------------------------------------
	///	Waveマネージャー
	//--------------------------------------------------------------------------------------
	WaveManager* WaveManager::m_WM = nullptr;

	void WaveManager::CreateWM() {
		m_WM = new WaveManager();
	}

	WaveManager* WaveManager::getInstance() {
		if (m_WM == nullptr) {
			m_WM = new WaveManager();
		}
		return m_WM;
	}

}