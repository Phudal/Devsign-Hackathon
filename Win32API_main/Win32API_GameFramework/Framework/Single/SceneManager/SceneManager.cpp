#include "SceneManager.h"

#include "Game/Scene/GameScene/GameScene.h"
#include "Game/Scene/MapEditerScene/MapEditerScene.h"

CSceneManager::CSceneManager()
{
	CurrentScene = NextScene = nullptr;

	LoadScene<DEF_SCENE>();
}

void CSceneManager::ReleaseManagerClass()
{
	super::ReleaseManagerClass();

	CObject::DeleteObject(CurrentScene);
	CObject::DeleteObject(NextScene);
}

void CSceneManager::Tick(float deltaSeconds)
{
	if (NextScene != nullptr)
	{
		if (CurrentScene != nullptr)
			CGameObject::DeleteObject(CurrentScene);

		CurrentScene = NextScene;
		NextScene = nullptr;
	}

	if (CurrentScene != nullptr)
		CurrentScene->Tick(deltaSeconds);
}

void CSceneManager::Render(HDC hdc)
{
	if (CurrentScene != nullptr)
		CurrentScene->Render(hdc);
}
