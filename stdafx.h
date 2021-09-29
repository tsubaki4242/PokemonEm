#pragma once

// D2D 사용을 위한 lib
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "WindowsCodecs.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "Comdlg32.lib")


#include "targetver.h"



#define WIN32_LEAN_AND_MEAN   // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <cassert>

// C 런타임 헤더 파일입니다.
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>

#include <vector>
#include <map>


enum class Pivot : int
{
	LeftTop, Center, Bottom
};


namespace Direction
{
	enum Enum : int
	{
		Left = 1,
		Top = 2,
		Right = 4,
		Bottom = 8,
		LeftTop = Left | Top,
		LeftBottom = Left | Bottom,
		RightTop = Right | Top,
		RightBottom = Right | Bottom,
		End = 0
	};

};
enum PERSONA
{
	Lonely = 1,
	Adamant = 2,
	Naughty = 3,
	Brave = 4,
	Bold = 5,
	Impish = 6,
	Lax = 7,
	Relaxed = 8,
	Modest = 9,
	Mild = 10,
	Rash = 11,
	Quiet = 12,
	Calm = 13,
	Gentle = 14,
	Careful = 15,
	Sassy = 16,
	Timid = 17,
	Hasty = 18,
	Jolly = 19,
	Naive = 20,
	Bashful = 21,
	Hardy = 22,
	Docile = 23,
	Quirky = 24,
	Serious = 25




};

enum TYPE
{
	NOT, //1
	FIRE,	//2
	WATER, //3
	LEAF, //4
	ROCK, //5
	GROUND,//6
	ICE,//7
	DARK,//8
	ESPER,//9
	BUG, //10
	ELECTRICITY,//11
	METAL, //12
	COMBAT, //13
	GHOST, //14
	POISON,//15
	FLYING,//16
	FAIRY,//17
	DRAGON,//18
	NOMRAL
};
// D2D Header Files
#include <D2D1.h>
#include <d2d1helper.h>
#include <d2d1.h>
#include <d2d1_1.h> //색상 비트맵
#include <dwrite.h>
#include <wincodec.h>



//GDI Plus


//d2d추가 유틸 =====================

#include "Vector2.h"
#include "Math.h"
#include "FloatRect.h"
#include "Figure.h"

#include <iostream>
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "utils.h"
#include "txtData.h"
#include "timeManager.h"
#include "effectManager.h"
#include "sceneManager.h"
#include "soundManager.h"
#include "iniDataManager.h"
#include "cameraManager.h"
#include "imageManager.h"
#include "keyAniManager.h"
#include "dtdManager.h"
#include "printManager.h"
#include "streamManager.h"
#include "ParticleManeager.h"
#include "renderManager.h"
#include "playerUI.h"
#include "txtRenderManger.h"
#include "batter.h"

using namespace std;
using namespace UJN_UTIL;
using namespace D2D1;
using namespace Figure;



extern int WinsizeX;
extern int WinsizeY;

//==================================
// ## 매크로 처리 ## 21.04.23 ##
//==================================

#define WINNAME (LPTSTR)(TEXT("D2D프레임워크"))

#define WINSTARTX 50	//윈도우 창 시작좌표 (left)
#define WINSTARTY 50	//윈도우 창 시작좌표 (top)
#define ORIGINWINSIZEX 1000 	//윈도우 가로크기
#define ORIGINWINSIZEY 600	//윈도우 세로크기
#define WINSIZEX WinsizeX	//윈도우 가로크기
#define WINSIZEY WinsizeY	//윈도우 세로크기
#define MAPSIZEX 6753
#define MAPSIZEY 1000

#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define RND				randomFunction::getSingleton()
#define KEYMANAGER		keyManager::getSingleton()
#define TIMEMANAGER		timeManager::getSingleton()
#define EFFECTMANAGER	effectManager::getSingleton()
#define SCENEMANAGER	sceneManager::getSingleton()
#define SOUNDMANAGER	soundManager::getSingleton()
#define KEYANIMANAGER	keyAniManager::getSingleton()
#define TXTDATA			txtData::getSingleton()
#define INIDATA			iniDataManager::getSingleton()
#define CAMERAMANAGER	cameraManager::getSingleton()
#define IMAGEMANAGER	imageManager::getSingleton()
#define D2DMANAGER		dtdManager::getSingleton()
#define PRINTMANAGER	printManager::getSingleton()
#define STREAMMANAGER	streamManager::getSingleton()
#define PARTICLEMANAGER	ParticleManeager::getSingleton()
#define RENDERMANAGER	renderManager::getSingleton()
#define PLAYERUI		playerUI::getSingleton()
#define TXTRENDERMANGER txtRenderManger::getSingleton()
#define BATTERGO		batter::getSingleton()


#define SAFE_DELETE(p) {if(p) {delete(p); (p) = nullptr;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p) = NULL;}}
#define SAFE_RELEASE2(p) { if(p) { (p)->Release(); (p) = NULL; } }
#define NEW_SAFE_RELEASE(p) {if(p){p->Release(); (p) = NULL;}}


#define Synthesize(ValueType,ValueName,FuncName) \
protected: ValueType ValueName;\
public: inline ValueType Get##FuncName(void) const{return ValueName;}\
public: inline void Set##FuncName(ValueType value){ValueName = value;}

//==================================
// ## extern ## 21.04.28 ##
//==================================

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;

extern ID2D1Device *mp_device;
extern ID2D1DeviceContext *mp_dc;
extern ID2D1Bitmap1 *mp_dc_bitmap;
