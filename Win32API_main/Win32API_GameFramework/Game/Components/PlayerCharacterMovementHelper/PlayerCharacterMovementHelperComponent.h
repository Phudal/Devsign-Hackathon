#pragma once
#include "Framework/Base/Component/Component.h"
#include "Framework/Enum/Direction.h"

class CPlayerCharacterMovementHelperComponent final :
    public CComponent
{
private:
    class CPlayerCharacter* PlayerCharacter;
    class CMovementComponent* Movement;

    class CTileMap* TileMap;

    EDirection LookDirection;

    int32 TileMapIndexX;
    int32 TileMapIndexY;

    bool bCheckHorizontalTile;

    bool bCheckVerticalTile;

public:
    CPlayerCharacterMovementHelperComponent();

public:
    virtual void Initialize() override;
    virtual void Start() override;
    virtual void Tick(float dt);

public:
    void SetTileMap(class CTileMap* tileMap);

private:
    void UpdateLookDirection();

public:
    FORCEINLINE EDirection GetLookDirection() const
    { return LookDirection; }

    void UpdateTileMapIndex();

    void CheckBlockingTile();

};

