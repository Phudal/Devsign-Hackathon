#pragma once
#include "CharDefine.h"

// 디버깅 모드
#define GAME_DEBUG_MODE				true

#ifdef UNICODE
#define CONSOLE_LINKER "/entry:wWinMainCRTStartup /subsystem:console"
#else
#define CONSOLE_LINKER "/entry:WinMainCRTStartup /subsystem:console"
#endif

#if GAME_DEBUG_MODE == true
#pragma comment (linker, CONSOLE_LINKER)
#endif

#ifdef UNICODE
#define tcout wcout
#else 
#define tcout cout
#endif

// 로그 출력용 함수
#define LOGF(log) if (GAME_DEBUG_MODE) { tcout << TEXT("PATH : ") << __FILE__ << TEXT("[ LINE ") << __LINE__ << TEXT(" ] ") << \
			log << endl; }
#define LOG(log) if(GAME_DEBUG_MODE) { tcout << TEXT("[ LINE ") << __LINE__ << TEXT(" ] ") << log << endl; }