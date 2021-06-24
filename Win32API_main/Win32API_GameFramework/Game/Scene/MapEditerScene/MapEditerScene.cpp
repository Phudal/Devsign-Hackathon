#include "MapEditerScene.h"
#include "Framework/Single/SceneManager/SceneManager.h"
#include "Framework/Single/InputManager/InputManager.h"

#include "Game/GameObject/TileMap/TileMap.h"
#include "resource.h"

void CMapEditerScene::Initialize()
{
	super::Initialize();

	TileMap = NewGameObject<CTileMap>();

	TileMapCountX = 0;
	TileMapCountY = 0;
	CameraSpeed = 1.0f;
}

void CMapEditerScene::Tick(float dt)
{
	super::Tick(dt);

	if (TileMapCountX == 0 || TileMapCountY == 0)
	{
		if (DialogBox(HInstance, MAKEINTRESOURCE(IDD_DIALOG_MAP_SETTING),
			Hwnd, (DLGPROC)&CMapEditerScene::MapSettingDlgProc) == IDOK)
		{
			TileMap->SetTileMapXY(TileMapCountX, TileMapCountY);

			TileMap->SetTileMapScale(TileMapScale);

			TileMap->MakeTileMap();
		}

	}

	InputKey(dt);
}

BOOL CMapEditerScene::MapSettingDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CMapEditerScene* mapEditerScene = 
		Cast<CMapEditerScene>(CSceneManager::Instance()->GetActiveScene());

	switch (msg)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemInt(hWnd, IDC_EDIT_MAPSIZEX, mapEditerScene->TileMapCountX, FALSE);
		SetDlgItemInt(hWnd, IDC_EDIT_MAPSIZEY, mapEditerScene->TileMapCountY, FALSE);
		SetDlgItemInt(hWnd, IDC_EDIT_MAP_SCALE, mapEditerScene->TileMapScale, FALSE);

		return FALSE;
	}

		case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDC_BUTTON_SET)
			{				
				mapEditerScene->TileMapCountX = GetDlgItemInt(hWnd, IDC_EDIT_MAPSIZEX, NULL, FALSE);
				mapEditerScene->TileMapCountY = GetDlgItemInt(hWnd, IDC_EDIT_MAPSIZEY, NULL, FALSE);
				mapEditerScene->TileMapScale = GetDlgItemInt(hWnd, IDC_EDIT_MAP_SCALE, NULL, FALSE);				

				EndDialog(hWnd, IDOK);
			}
			return FALSE;
		}

	case WM_CLOSE:
		EndDialog(hWnd, IDCANCEL);
		return FALSE;
	}
	return FALSE;
}

void CMapEditerScene::InputKey(float dt)
{
	float wheelAxis = CInput::GetAxis(TEXT("MouseWheel"));
	bool bIsWheelKeyInput = !FMath::Approximately(wheelAxis, 0.0f);

	if (bIsWheelKeyInput)
	{
		CameraSpeed += wheelAxis * 0.5f;
		CameraSpeed = FMath::Clamp(CameraSpeed, 0.1f, 50.0f);
	}

	FVector cameraVelocity = FVector(
		CInput::GetAxis(TEXT("Horizontal")),
		CInput::GetAxis(TEXT("Vertical")));
	cameraVelocity *= -100.0f * CameraSpeed * dt;

	MoveCamera(cameraVelocity);
}
