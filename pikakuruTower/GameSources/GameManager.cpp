/*!
@file GameManager.cpp
@brief �Q�[���S�̂��Ǘ�����}�l�[�W���[
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	�Q�[���S�̂��Ǘ�����}�l�[�W���[
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
	///	Wave�}�l�[�W���[
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