#include "GameInstance.h"
#include "Framework/Single/SceneManager/SceneManager.h"
#include "Framework/Single/CollisionManager/CollisionManager.h"
#include "Framework/Single/InputManager/InputManager.h"

CGameInstance::CGameInstance()
{
}

void CGameInstance::Initialize()
{
	super::Initialize();

	Hdc = ::GetDC(Hwnd);
	GameInstance = this;


	RegisterManagerClass<CCollisionManager>();
	RegisterManagerClass<CInputManager>();
	RegisterManagerClass<CSceneManager>();
}

void CGameInstance::Release()
{
	super::Release();

	for (auto iter = ManagerClasses.begin();
		iter != ManagerClasses.end(); ++iter)
	{
		iter->second->ReleaseManagerClass();

		delete iter->second;
		iter->second = nullptr;
	}

	ManagerClasses.clear();

	GameInstance = nullptr;
	ReleaseDC(Hwnd, Hdc);
}
