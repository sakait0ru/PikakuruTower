#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���[�r�[�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	//������
	void MyMovieStage::OnCreate() {
		MovieStage::OnCreate();
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring strMovie = dataDir + L"Movie\\PV.mp4";
		SetMovieFileName(strMovie);
		//�Đ�
		Play();
	}

	void MyMovieStage::OnUpdate() {
		// �{�^������������Title�Ɉړ�
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cntlVec.wButtons) {
			AddGameObject<FadeSquareSprite>(FadeType::FadeOut, L"ToTitleStage");
		}
	}

}