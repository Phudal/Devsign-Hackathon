#pragma once
#include "Framework/Base/Scene/Scene.h"

class CMapEditerScene final :
    public CScene
{
private:
    int32 TileMapCountX;
    int32 TileMapCountY;
    int32 TileMapScale;
    float CameraSpeed;

    class CTileMap* TileMap;

public:
    virtual void Initialize() override;
    virtual void Tick(float dt) override;

    static BOOL MapSettingDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    void InputKey(float dt);
};

