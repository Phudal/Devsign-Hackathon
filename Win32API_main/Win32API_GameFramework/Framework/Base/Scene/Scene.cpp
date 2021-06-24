#include "Scene.h"

#include "Bitmap/Bitmap.h"

#include "Statics/GameplayStatics.h"

#include "Base/GameObject/ScreenObject/ScreenObject.h"

void CScene::SortRenderComponent()
{
	while (bDoSortRenderComponent)
	{
		if (bNeedSort)
		{
			UsedRenderComponents.sort([](CRenderComponent* first, CRenderComponent* second)
				{ return first->GetSortingOrder() < second->GetSortingOrder(); });

			bNeedSort = false;
		}
	}
}

void CScene::Initialize()
{
	super::Initialize();

	BackBuffer = CBitmap::LoadBmp(NewObject<CBitmap>(), TEXT("Resources/Default/Black.bmp"), false, TEXT("BackBuffer"));
	Eraser = CBitmap::LoadBmp(NewObject<CBitmap>(), TEXT("Resources/Default/Black.bmp"), false, TEXT("Eraser"));

	bNeedSort = false;
	CameraPosition = FVector::ZeroVector();

	bDoSortRenderComponent = true;
	SortingOrderThread = new FThread(&CScene::SortRenderComponent, this);

	Screen = NewGameObject<CScreenObject>();
}

void CScene::Tick(float deltaSecond)
{
	if (CreatedGameObjectList.size() > 0)
	{
		for (auto createdGameObject : CreatedGameObjectList)
			UsedGameObjectList.push_back(createdGameObject);
		CreatedGameObjectList.clear();
	}

	if (DestroyedGameObjectList.size() > 0)
	{
		for (auto destroyedGameObject : DestroyedGameObjectList)
		{
			UsedGameObjectList.remove(destroyedGameObject);

			CObject::DeleteObject(destroyedGameObject);
		}
		DestroyedGameObjectList.clear();
	}

	if (CreatedRenderComponents.size() > 0)
	{	
		for (auto createdRenderComponent : CreatedRenderComponents)
			UsedRenderComponents.push_back(createdRenderComponent);
		CreatedRenderComponents.clear();

		bNeedSort = true;
	}

	if (DestroyedRenderComponents.size() > 0)
	{
		for (auto destroyedRenderComponent : DestroyedRenderComponents)
			UsedRenderComponents.remove(destroyedRenderComponent);
		DestroyedRenderComponents.clear();
	}


	if (UsedGameObjectList.size() > 0)
	{
		for (auto gameObject : UsedGameObjectList)
		{
			if (gameObject->bBeDestroy) continue;

			if (!gameObject->bIsStarted)
				gameObject->Start();

			if (gameObject->bCanEverTick)
				gameObject->Tick(deltaSecond);
		}
	}
}

void CScene::Render(HDC hdc)
{
	

	BitBlt(BackBuffer->GetDC(), 0, 0, WND_WIDTH, WND_HEIGHT, Eraser->GetDC(), 0, 0, SRCCOPY);

	for (auto renderComponent : UsedRenderComponents)
	{
		if (renderComponent->bBeDestroy) continue;
		if (renderComponent->Owner->bBeDestroy) continue;
		if (!renderComponent->bUseRender) continue;
		if (!renderComponent->bIsStarted) continue;

		renderComponent->Render(BackBuffer->GetDC());
	}

#if GAME_DEBUG_MODE == true
	for (auto debugDrawInfo : DebugDrawInfos)
		debugDrawInfo->Draw(BackBuffer->GetDC());

	for (auto iter = DebugDrawInfos.begin(); iter != DebugDrawInfos.end(); ++iter)
	{
		if (CGameplayStatics::GetTime() - (*iter)->DrawStartTime >= (*iter)->Duration)
			CObject::DeleteObject(*iter);
	}

	DebugDrawInfos.remove_if([](FDebugDrawInfo* debugDrawInfo) 
		{ return debugDrawInfo == nullptr; });
#endif


	BitBlt(hdc, 0, 0, WND_WIDTH, WND_HEIGHT, BackBuffer->GetDC(), 0, 0, SRCCOPY);
}

void CScene::Release()
{
	bDoSortRenderComponent = false;
	SortingOrderThread->join();
	delete SortingOrderThread;
	SortingOrderThread = nullptr;	


#if GAME_DEBUG_MODE == true
	for (auto iter = DebugDrawInfos.begin(); iter != DebugDrawInfos.end(); ++iter)
		CObject::DeleteObject(*iter);
	DebugDrawInfos.clear();
#endif


	if (CreatedGameObjectList.size() > 0)
	{
		for (auto createdGameObject : CreatedGameObjectList)
			Destroy(createdGameObject);
	}

	if (UsedGameObjectList.size() > 0)
	{
		for (auto gameObject : UsedGameObjectList)
			Destroy(gameObject);
	}

	if (DestroyedGameObjectList.size() > 0)
	{
		for (auto destroyedGameObject : DestroyedGameObjectList)
			CGameObject::DeleteObject(destroyedGameObject);
	}

	CreatedGameObjectList.clear();
	UsedGameObjectList.clear();
	DestroyedGameObjectList.clear();

	CBitmap::ReleaseAllBmp();
	BackBuffer = Eraser = nullptr;

	super::Release();
}

void CScene::Destroy(CGameObject* gameObject)
{
	if (gameObject->bBeDestroy) return;

	gameObject->bBeDestroy = true;

	gameObject->OnDestroy();

	DestroyedGameObjectList.push_back(gameObject);
}

void CScene::AddDebugDraw(
	EDebugDrawType debugDrawType, 
	FVector vec1, 
	FVector vec2, 
	COLORREF color, 
	float duration,
	bool bFill)
{
#if GAME_DEBUG_MODE == true

	FDebugDrawInfo* newDebugDrawInfo = CObject::NewObject<FDebugDrawInfo>();

	newDebugDrawInfo->InitializeDebugDrawInfo(
		debugDrawType, vec1, vec2, color, duration, bFill);

	DebugDrawInfos.push_back(newDebugDrawInfo);

#endif
}
