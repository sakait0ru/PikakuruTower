
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------

	// �t�@�C������
	void Scene::FindFile(wstring dir) {

		HANDLE hFind;
		WIN32_FIND_DATA win32fd;

		wstring extension = L"*.*";

		wstring fileDir = dir;
		wstring newFileDir = fileDir + extension;
		const wchar_t *fileDirExtension = newFileDir.c_str();

		hFind = FindFirstFile(fileDirExtension, &win32fd);

		// ����ɂ��
		do {
			// ������FILE_ATTRIBUTE_DIRECTORY�Ȃ�
			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				// �f�B���N�g�������擾
				wstring ditectoryName = win32fd.cFileName;
				// �V�����t�H���_�̏ꏊ
				wstring newDateDir = fileDir + ditectoryName + L"/";
				if (ditectoryName.find(L".")) {
					// ���̒�������
					FindFile(newDateDir);
				}
			}
			// ����ȊO�Ȃ�t�@�C��
			else {
				// �t�@�C�������擾
				wstring fileName = win32fd.cFileName;
				// �g���q�����o��
				auto exe = fileName.substr(fileName.find(L"."), fileName.length());

				// �摜�̓ǂݍ���
				if (exe == L".jpg" || exe == L".png" || exe == L".tga") {
					// �t�@�C���̏ꏊ
					wstring strTexture = fileDir + fileName;
					// �e�N�X�`���[��o�^
					App::GetApp()->RegisterTexture(fileName, strTexture);
				}
				if (exe == L".bmf") {
					// ���f���̓ǂݍ���
					auto modelMesh = MeshResource::CreateStaticModelMesh(fileDir, fileName);
					App::GetApp()->RegisterResource(fileName, modelMesh);
				}
				if (exe == L".tbmf") {
					// �^���W�F���g�t�����f���̓ǂݍ���
					auto modelMesh = MeshResource::CreateStaticModelMeshWithTangent(fileDir, fileName);
					App::GetApp()->RegisterResource(fileName, modelMesh);
				}
				if (exe == L".bbmf") {
					// �{�[�����f���̓ǂݍ���
					auto modelMesh = MeshResource::CreateBoneModelMesh(fileDir, fileName);
					App::GetApp()->RegisterResource(fileName, modelMesh);
				}
				if (exe == L".wav")
				{
					// ���̓ǂݍ���
					wstring strSound = fileDir + fileName;
					App::GetApp()->RegisterWav(fileName, strSound);
				}


			}
		} while (FindNextFile(hFind, &win32fd));

		// �㏈��
		FindClose(hFind);
	}


	
	void Scene::OnCreate(){
		try {
			ShowCursor(false);

			// ���f�B�A�f�B���N�g���̈ʒu���擾
			wstring dateDir;
			App::GetApp()->GetDataDirectory(dateDir);
			// �t�@�C���������ă��\�[�X�o�^
			FindFile(dateDir);

			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
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
