#include "Include/DefaultInclude.h"

#include "Framework/Single/GameInstance/GameInstance.h"
#include "Framework/Single/CollisionManager/CollisionManager.h"
#include "Framework/Single/SceneManager/SceneManager.h"
#include "Framework/Single/InputManager/InputManager.h"

/*
* TODO...
* SpriteRendererComponent
* AI - BehaviorControllerComponent, AIBehavior
* AudioComponent
* 
* Game 을 위한 구조
* 
* 
		RPG
		뷰 : TopDown
		
		필요한 요소들
		던전
		몬스터
			AI
		
		상호작용 가능한 객체들
			Npc
		UI
			상점	인벤토리
*/


HWND Hwnd;
HINSTANCE HInstance;

// GameInstance
DEF_GAMEINSTANCECLASS* GameInstance;
float GameStartTime;
FMOD_SYSTEM* SoundSystem;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPTSTR		lpszCmdParam,
	int			nCmdShow)
{
	srand(GameStartTime = GetTickCount64());

	WNDCLASS wndClass;

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.cbClsExtra = wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = HInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = TEXT("WndClass");
	wndClass.lpszMenuName = NULL;

	RegisterClass(&wndClass);
	Hwnd = CreateWindow(
		wndClass.lpszClassName,
		WND_DEFAULT_TITLE,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		WND_WIDTH, WND_HEIGHT,
		NULL, NULL,
		wndClass.hInstance,
		NULL);

	ShowWindow(Hwnd, nCmdShow);

	FMOD_System_Create(&SoundSystem);

	FMOD_System_Init(SoundSystem, 32, FMOD_INIT_NORMAL, NULL);

	GameInstance = CObject::NewObject<DEF_GAMEINSTANCECLASS>();

	float targetDS = 1.0f / TARGET_FPS;

	float totalDS = 0.0f;
	float functionCallDelta;

	LARGE_INTEGER Second;
	LARGE_INTEGER Counter;

	QueryPerformanceFrequency(&Second);	
	
	QueryPerformanceCounter(&Counter);

	MSG msg;
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{			
			LARGE_INTEGER currentClock;
			QueryPerformanceCounter(&currentClock);

			functionCallDelta = (currentClock.QuadPart - Counter.QuadPart) / (float)Second.QuadPart;
			Counter = currentClock;

			if (totalDS >= targetDS)
			{
				CInputManager::Instance()->UpdateInputValue();

				CCollisionManager::Instance()->DoCollisionTest();

				CSceneManager::Instance()->Tick(totalDS);

				CSceneManager::Instance()->Render(GameInstance->GetDC());

				CInputManager::Instance()->MouseWheelAxis = 0;

				totalDS = 0.0f;
			}

			totalDS += functionCallDelta;

		}

	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		RECT wndRC = { 0, 0, WND_WIDTH, WND_HEIGHT };
		AdjustWindowRect(&wndRC, WS_OVERLAPPEDWINDOW, FALSE);

		float wndLeft = SCREEN_CENTER_X - (WND_WIDTH * 0.5f);
		float wndTop = SCREEN_CENTER_Y - (WND_HEIGHT * 0.5f);
		MoveWindow(hwnd, 
			wndLeft, wndTop, 
			wndRC.right - wndRC.left, 
			wndRC.bottom - wndRC.top, 
			false);

		return 0;
	}

	case WM_MOUSEWHEEL:
	{
		SHORT wheelAxis = FMath::Sign((SHORT)HIWORD(wParam));		
		CInput::Instance()->MouseWheelAxis = wheelAxis;

		return 0;
	}

	case WM_DESTROY:
		
		FMOD_System_Close(SoundSystem);

		FMOD_System_Release(SoundSystem);

		CObject::DeleteObject(GameInstance);

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
