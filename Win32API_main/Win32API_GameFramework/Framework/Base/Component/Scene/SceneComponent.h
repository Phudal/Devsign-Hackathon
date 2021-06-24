#pragma once
#include "Framework/Base/Component/Component.h"

class CSceneComponent :
    public CComponent
{
public :
    FVector RelativePosition;

    FVector RelativeScale;

public :
    CSceneComponent();

public :
    virtual FVector GetComponentPosition() const;
};

