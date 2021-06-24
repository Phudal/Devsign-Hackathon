#include "DebugDrawInfo.h"

#include "Framework/Single/SceneManager/SceneManager.h"

#include "Framework/Statics/GameplayStatics.h"

#include "Framework/Base/Scene/Scene.h"

void FDebugDrawInfo::Initialize()
{
	super::Initialize();
	HBrush = HPen = NULL;
}

void FDebugDrawInfo::Release()
{
	super::Release();

	if (HBrush)
	{
		if (bFill)
			::DeleteObject(HBrush);
		HBrush = NULL;
	}

	if (HPen)
	{
		::DeleteObject(HPen);
		HPen = NULL;
	}
}

void FDebugDrawInfo::InitializeDebugDrawInfo(
	EDebugDrawType debugDrawType, 
	FVector vec1, 
	FVector vec2,
	COLORREF color, 
	float duration,
	bool bFill)
{
	DebugDrawType = debugDrawType;
	Vec1 = vec1;
	Vec2 = vec2;
	Color = color;
	DrawStartTime = CGameplayStatics::GetTime();
	Duration = duration;
	this->bFill = bFill;


	switch (DebugDrawType)
	{
	case EDebugDrawType::DT_Rect:
		HBrush = (bFill) ? CreateSolidBrush(Color) : GetStockObject(NULL_BRUSH);
		HPen = CreatePen(PS_SOLID, 1, Color);
		FnDraw = [this](HDC hdc)
		{
			CScene* acitveScene = CSceneManager::Instance()->GetActiveScene();

			Rectangle(hdc,
				Vec1.X - (Vec2.X * 0.5f) - acitveScene->CameraPosition.X,
				Vec1.Y - (Vec2.Y * 0.5f) - acitveScene->CameraPosition.Y,
				Vec1.X + (Vec2.X * 0.5f) - acitveScene->CameraPosition.X,
				Vec1.Y + (Vec2.Y * 0.5f) - acitveScene->CameraPosition.Y);
		};

		break;

	case EDebugDrawType::DT_Circle:
		HBrush = (bFill) ? CreateSolidBrush(Color) : GetStockObject(NULL_BRUSH);
		HPen = CreatePen(PS_SOLID, 1, Color);
		FnDraw = [this](HDC hdc)
		{
			CScene* acitveScene = CSceneManager::Instance()->GetActiveScene();

			Ellipse(hdc,
				Vec1.X - (Vec2.X * 0.5f) - acitveScene->CameraPosition.X,
				Vec1.Y - (Vec2.Y * 0.5f) - acitveScene->CameraPosition.Y,
				Vec1.X + (Vec2.X * 0.5f) - acitveScene->CameraPosition.X,
				Vec1.Y + (Vec2.Y * 0.5f) - acitveScene->CameraPosition.Y);
		};
		break;

	case EDebugDrawType::DT_LINE:
		HPen = CreatePen(PS_SOLID, 1, Color);
		FnDraw = [this](HDC hdc)
		{
			CScene* acitveScene = CSceneManager::Instance()->GetActiveScene();

			MoveToEx(hdc, 
				Vec1.X - acitveScene->CameraPosition.X,
				Vec1.Y - acitveScene->CameraPosition.Y,
				NULL);
			LineTo(hdc, 
				Vec2.X - acitveScene->CameraPosition.X,
				Vec2.Y - acitveScene->CameraPosition.Y);
		};
		break;
	}
}

void FDebugDrawInfo::Draw(HDC hdc) const
{
	HGDIOBJ oldBrush = NULL;
	HGDIOBJ oldPen = NULL;

	if (HBrush != NULL) oldBrush	= SelectObject(hdc, HBrush);
	if (HPen != NULL)	oldPen		= SelectObject(hdc, HPen);

	FnDraw(hdc);

	if (HBrush != NULL) SelectObject(hdc, oldBrush);
	if (HPen != NULL)	SelectObject(hdc, oldPen);
}