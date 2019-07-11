
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------

	// ファイル検索
	void Scene::FindFile(wstring dir) {

		HANDLE hFind;
		WIN32_FIND_DATA win32fd;

		wstring extension = L"*.*";

		wstring fileDir = dir;
		wstring newFileDir = fileDir + extension;
		const wchar_t *fileDirExtension = newFileDir.c_str();

		hFind = FindFirstFile(fileDirExtension, &win32fd);

		// 一回先にやる
		do {
			// 属性がFILE_ATTRIBUTE_DIRECTORYなら
			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				// ディレクトリ名を取得
				wstring ditectoryName = win32fd.cFileName;
				// 新しいフォルダの場所
				wstring newDateDir = fileDir + ditectoryName + L"/";
				if (ditectoryName.find(L".")) {
					// その中を検索
					FindFile(newDateDir);
				}
			}
			// それ以外ならファイル
			else {
				// ファイル名を取得
				wstring fileName = win32fd.cFileName;
				// 拡張子を取り出す
				auto exe = fileName.substr(fileName.find(L"."), fileName.length());

				// 画像の読み込み
				if (exe == L".jpg" || exe == L".png" || exe == L".tga") {
					// ファイルの場所
					wstring strTexture = fileDir + fileName;
					// テクスチャーを登録
					App::GetApp()->RegisterTexture(fileName, strTexture);
				}
				if (exe == L".bmf") {
					// モデルの読み込み
					auto modelMesh = MeshResource::CreateStaticModelMesh(fileDir, fileName);
					App::GetApp()->RegisterResource(fileName, modelMesh);
				}
				if (exe == L".tbmf") {
					// タンジェント付きモデルの読み込み
					auto modelMesh = MeshResource::CreateStaticModelMeshWithTangent(fileDir, fileName);
					App::GetApp()->RegisterResource(fileName, modelMesh);
				}
				if (exe == L".bbmf") {
					// ボーンモデルの読み込み
					auto modelMesh = MeshResource::CreateBoneModelMesh(fileDir, fileName);
					App::GetApp()->RegisterResource(fileName, modelMesh);
				}
				if (exe == L".wav")
				{
					// 音の読み込み
					wstring strSound = fileDir + fileName;
					App::GetApp()->RegisterWav(fileName, strSound);
				}


			}
		} while (FindNextFile(hFind, &win32fd));

		// 後処理
		FindClose(hFind);
	}


	
	void Scene::OnCreate(){
		try {
			ShowCursor(false);

			// メディアディレクトリの位置を取得
			wstring dateDir;
			App::GetApp()->GetDataDirectory(dateDir);
			// ファイル検索してリソース登録
			FindFile(dateDir);

			//クリアする色を設定
			Col4 Col;
			Col.set(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"CopyrightStage");
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"MovieStage") {
			m_MovieActive = true;

			ResetActiveStage<MyMovieStage>();
		}
		if (event->m_MsgStr == L"CopyrightStage") {
			m_MovieActive = false;

			ResetActiveStage<CopyrightStage>();
		}
		else if (event->m_MsgStr == L"ToTitleStage") {
			m_MovieActive = false;

			ResetActiveStage<TitleStage>();
		}
		else if (event->m_MsgStr == L"ToLoadingStage") {
			m_MovieActive = false;

			ResetActiveStage<LoadingStage>();
		}
		else if (event->m_MsgStr == L"ToSelectStage") {
			m_MovieActive = false;

			ResetActiveStage<SelectStage>();
		}
		else if (event->m_MsgStr == L"ToMainStage") {
			m_MovieActive = false;

			ResetActiveStage<MainStage>();
		}
		else if (event->m_MsgStr == L"ToClearStage") {
			m_MovieActive = false;

			ResetActiveStage<ClearStage>();
		}
		else if (event->m_MsgStr == L"ToGameoverStage") {
			m_MovieActive = false;

			ResetActiveStage<GameoverStage>();
		}
		
	}

}
//end basecross
