#pragma once
#include "Framework/Base/Object/Object.h"

struct FActionInput final :
    public CObject
{
public :
    vector<int> ActionKeys;

    bool bUpdatedNewInputState;

    bool bPrevInputState;

    bool bIsInput;

public :
    FActionInput() {}
    FActionInput(int actionKey);
    FActionInput(vector<int> actionKeys);

public :
    void UpdateInputActionValue();

    FORCEINLINE bool IsKeyDown()
    {
        if (!bUpdatedNewInputState) return false;
        return bIsInput;
    }

    FORCEINLINE bool IsKeyUp()
    {
        if (!bUpdatedNewInputState) return false;
        return !bIsInput;
    }

    FORCEINLINE bool IsKey()
    {
        return bIsInput;
    }

};

