#include "ActionInput.h"

FActionInput::FActionInput(int actionKey)
{
	bUpdatedNewInputState = bPrevInputState = bIsInput = false;
	ActionKeys.push_back(actionKey);
}

FActionInput::FActionInput(vector<int> actionKeys)
{
	bUpdatedNewInputState = bPrevInputState = bIsInput = false;
	ActionKeys = actionKeys;
}

void FActionInput::UpdateInputActionValue()
{
	bUpdatedNewInputState = (bUpdatedNewInputState) ? false : false;

	bPrevInputState = bIsInput;

	for (auto iter = ActionKeys.begin(); iter != ActionKeys.end(); ++iter)
	{
		if (GetAsyncKeyState(*iter))
		{
			bIsInput = true;
			bUpdatedNewInputState = (bPrevInputState != bIsInput);

			return;
		}
	}

	bIsInput = false;
	bUpdatedNewInputState = (bPrevInputState != bIsInput);
}
