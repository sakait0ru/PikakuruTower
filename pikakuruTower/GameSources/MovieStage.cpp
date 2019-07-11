#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ムービーステージクラス
	//--------------------------------------------------------------------------------------
	//初期化
	void MyMovieStage::OnCreate() {
		MovieStage::OnCreate();
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring strMovie = dataDir + L"Movie\\PV.mp4";
		SetMovieFileName(strMovie);
		//再生
		Play();
	}

	void MyMovieStage::OnUpdate() {
		// ボタンを押したらTitleに移動
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cntlVec.wButtons) {
			AddGameObject<FadeSquareSprite>(FadeType::FadeOut, L"ToTitleStage");
		}
	}

}