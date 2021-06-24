#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"

class CGameplayStatics final :
    public CObject
{
public :   
    static float GetTime();

    static FVector GetMousePosition(bool translated = true);

};

