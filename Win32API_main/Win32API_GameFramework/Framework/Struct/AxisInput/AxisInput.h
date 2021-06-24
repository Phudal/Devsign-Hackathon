#pragma once
#include "Framework/Base/Object/Object.h"

struct FAxisInput final :
    public CObject
{
public :
    float AxisValue;

    vector<int> LowKey, HighKey;

public :
    FAxisInput() {}
    FAxisInput(int lowKey, int highKey);
    FAxisInput(vector<int> lowKeys, vector<int> highKeys);

public :
    void UpdateInputAxisValue();
};

