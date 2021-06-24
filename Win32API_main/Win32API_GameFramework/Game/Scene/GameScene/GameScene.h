#pragma once
#include "Framework/Base/Scene/Scene.h"

class CGameScene final :
    public CScene
{
private:
    class CTileMap* TileMap;
    class CAudioObject* AudioObject;

public :
    virtual void Initialize() override;

public:
    FORCEINLINE class CAudioObject* GetAudioObject() const
    {
        return AudioObject;
    }

    FORCEINLINE class CTileMap* GetTileMap() const
    {
        return TileMap;
    }
};

