#include "AxisInput.h"

FAxisInput::FAxisInput(int lowKey, int highKey)
{
	LowKey.push_back(lowKey);
	HighKey.push_back(highKey);
	AxisValue = 0.0f;
}

FAxisInput::FAxisInput(vector<int> lowKeys, vector<int> highKeys)
{
	LowKey = lowKeys;
	HighKey = highKeys;
	AxisValue = 0.0f;
}

void FAxisInput::UpdateInputAxisValue()
{
	AxisValue = 0.0f;

	for (int lowKey : LowKey)
	{
		if (GetAsyncKeyState(lowKey))
		{
			AxisValue -= 1.0f;
			break;
		}
	}

	for (int highKey : HighKey)
	{
		if (GetAsyncKeyState(highKey))
		{
			AxisValue += 1.0f;
			break;
		}
	}

}
