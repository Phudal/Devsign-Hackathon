#pragma once

#include <Windows.h>
#include <iostream>

#include <combaseapi.h>
#include <functional>

#include <vector>
#include <map>
#include <list>
#include <fmod.h>

#include <fstream>

#include "DeclHelper.h"
#include "GameDefine.h"
#include "GameDebug.h"

#pragma comment (lib, "msimg32.lib")
#pragma comment (lib, "fmod_vc.lib")

using namespace std;






#define WND_DEFAULT_TITLE		TEXT("Win32Api GameFramework")

#define WND_WIDTH				800
#define WND_HEIGHT				600

#define SCREEN_CENTER_X			(1920 * 0.5f)
#define SCREEN_CENTER_Y			(1080 * 0.5f)


extern HWND Hwnd;
extern float GameStartTime;
extern HINSTANCE HInstance;
extern FMOD_SYSTEM* SoundSystem;






/*
	Framework: 게임 개발에 필요한 기능
	Object
	GameInstance : 게임 전체를 관리하는 객체
		SubManager : 객체들을 카테고리별로 나눠 관리할 때 사용될 클래스
		PlayerManager : 플레이어와 관련된 데이터를 관리하게 될 객체
		SceneManager : 씬과 관련된 데이터들을 관리하게 될 객체
		CollisionManager : 충돌체와 관련된 데이터들을 관리하게 될 객체
	Scene : 하나의 스테이지를 나타낼 때 사용될 클래스
	GameObject : 하나의 스테이지를 구성하는 물체의 단위로 사용될 클래스
	
	Component : GameObject 객체를 모듈화 시킬 때 사용될 클래스
	RenderComponent : 화면에 그리는 기능을 제공하게 될 컴포넌트
	AudioComponent : 소리 재생과 관련된 기능을 제공하게 될 컴포넌트
	[FMOD 외부 라이브러리 사용]
	
	Bitmap : 이미지를 출력하는 기능을 제공하는 클래스
	
	
	Game : 게임 개발에 필요한 내용


	규칙
	모든 클래스, 구조체, 열거 형식, 인터페이스 이름 앞에는 접두어를 사용할 것
	/// - 클래스 : C
	/// - 구조체 : F
	/// - 인터페이스 : I
	/// - 열거 형식 : E
	/// - 이러한 접두어는 파일명에는 사용하지 않습니다.

*/