#pragma once
#include "Framework/Single/ManagerClassBase/ManagerClassBase.h"

#include "Framework/Struct/AxisInput/AxisInput.h"
#include "Framework/Struct/ActionInput/ActionInput.h"

#ifndef VK_KEY_DEF
#define VK_KEY_DEF

#define VK_A        0x41
#define VK_D        0x44
#define VK_S        0x53
#define VK_W        0x57

#endif

typedef class CInputManager final :
    public CManagerClassBase<CInputManager>
{
public:
    int32 MouseWheelAxis;

private :
    map<tstring, FAxisInput> AxisInputs;

    map<tstring, FActionInput> ActionInputs;

public :
    virtual void InitializeManagerClass() override;

private :
    void AddAxis(tstring axisName, int lowKey, int highKey);
    void AddAxis(tstring axisName, vector<int> lowKeys, vector<int> highKeys);

    void AddAction(tstring actionName, int actionKey);
    void AddAction(tstring actionName, vector<int> actionKeys);

public :
    void UpdateInputValue();

public :
    static float GetAxis(tstring axisName);

    static bool GetKeyDown(tstring actionName);
    static bool GetKeyUp(tstring actionName);
    static bool GetKey(tstring actionName);

} CInput;

