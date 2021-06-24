#include "InputManager.h"

void CInputManager::InitializeManagerClass()
{
#pragma region Horizontal Axis ...
	vector<int> horizontalLow;
	horizontalLow.push_back(VK_LEFT);
	horizontalLow.push_back(VK_A);

	vector<int> horizontalHigh;
	horizontalHigh.push_back(VK_RIGHT);
	horizontalHigh.push_back(VK_D);

	AddAxis(TEXT("Horizontal"), horizontalLow, horizontalHigh);
#pragma endregion

#pragma region Vertical Axis ...
	vector<int> verticalLow;
	verticalLow.push_back(VK_UP);
	verticalLow.push_back(VK_W);

	vector<int> verticalHigh;
	verticalHigh.push_back(VK_DOWN);
	verticalHigh.push_back(VK_S);

	AddAxis(TEXT("Vertical"), verticalLow, verticalHigh);
#pragma endregion

#pragma region Action ...
	AddAction(TEXT("Space"), VK_SPACE);
	AddAction(TEXT("FireBullet"), VK_LBUTTON);
#pragma endregion
}

void CInputManager::AddAxis(tstring axisName, int lowKey, int highKey)
{
	vector<int> lowKeys;
	lowKeys.push_back(lowKey);
	vector<int> highKeys;
	highKeys.push_back(highKey);

	AddAxis(axisName, lowKeys, highKeys);
}

void CInputManager::AddAxis(tstring axisName, vector<int> lowKeys, vector<int> highKeys)
{
	AxisInputs.insert(make_pair(axisName, FAxisInput(lowKeys, highKeys)));
}

void CInputManager::AddAction(tstring actionName, int actionKey)
{
	ActionInputs.insert(make_pair(actionName, FActionInput(actionKey)));
}

void CInputManager::AddAction(tstring actionName, vector<int> actionKeys)
{
	ActionInputs.insert(make_pair(actionName, FActionInput(actionKeys)));
}

void CInputManager::UpdateInputValue()
{
	for (auto iter = AxisInputs.begin(); iter != AxisInputs.end(); ++iter)
		iter->second.UpdateInputAxisValue();

	for (auto iter = ActionInputs.begin(); iter != ActionInputs.end(); ++iter)
		iter->second.UpdateInputActionValue();
}

float CInputManager::GetAxis(tstring axisName)
{
	if (axisName == TEXT("MouseWheel"))
		return (float)Instance()->MouseWheelAxis;

	return Instance()->AxisInputs[axisName].AxisValue;
}

bool CInputManager::GetKeyDown(tstring actionName)
{
	return Instance()->ActionInputs[actionName].IsKeyDown();
}

bool CInputManager::GetKeyUp(tstring actionName)
{
	return Instance()->ActionInputs[actionName].IsKeyUp();
}

bool CInputManager::GetKey(tstring actionName)
{
	return Instance()->ActionInputs[actionName].IsKey();
}
