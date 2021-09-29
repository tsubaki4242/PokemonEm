#include "stdafx.h"
#include "playGround.h"
#include "tileClass.h"
#include "title.h"
#include "main.h"
#include "flowerVillage.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{	

	gameNode::init(true);
	IMGALL();

	IMAGEMANAGER->addDImage("아웃", L"UI/menu/fadeOut.png", 1000, 600);



	SCENEMANAGER->addScene("test", new tileClass);
	SCENEMANAGER->addScene("flowerVillage", new flowerVillage);
	SCENEMANAGER->addScene("title", new title);
	SCENEMANAGER->addScene("main", new main);
	SCENEMANAGER->changeScene("flowerVillage");


	_debug = false;

	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown(VK_TAB)) {
		_debug = !_debug;
		PRINTMANAGER->setDebug(_debug);
	}

	SCENEMANAGER->update();

}


void playGround::render()
{
	if (SCENEMANAGER->getSeanName() == "title")
	{
		SCENEMANAGER->render();
	}
	else
	{


		D2DMANAGER->beginDraw();
		SCENEMANAGER->render();
		RENDERMANAGER->render();
		TXTRENDERMANGER->render();
		D2DMANAGER->endDraw();
		D2DMANAGER->render();
	}

}

void playGround::IMGALL()
{
	IMAGEMANAGER->addDImage("메인", L"img/title.png", 1000, 600);
	//hp
		//hpbar
	IMAGEMANAGER->addDImage("Lv박스", L"UI/menu/overlay_lv.png", 44, 28);
	IMAGEMANAGER->addDImage("HP박스", L"UI/menu/invenHpBar.png", 276, 28);
	IMAGEMANAGER->addDImage("HP박스Back", L"UI/menu/invenHpBarBack.png", 208, 16);
	IMAGEMANAGER->addDImage("HPbar그린", L"UI/menu/invenHpBarGreen.png", 208, 16);
	IMAGEMANAGER->addDImage("HPbar오렌지", L"UI/menu/invenHpBarOrenge.png", 208, 16);
	IMAGEMANAGER->addDImage("HPbar레드", L"UI/menu/invenHpBarRed.png", 208, 16);

	//타입
	IMAGEMANAGER->addDImage("노말", L"pokemon/type/노말.png", 128, 56);
	IMAGEMANAGER->addDImage("불", L"pokemon/type/불.png", 128, 56);
	IMAGEMANAGER->addDImage("물", L"pokemon/type/물.png", 128, 56);
	IMAGEMANAGER->addDImage("전기", L"pokemon/type/전기.png", 128, 56);
	IMAGEMANAGER->addDImage("풀", L"pokemon/type/풀.png", 128, 56);
	IMAGEMANAGER->addDImage("얼음", L"pokemon/type/얼음.png", 128, 56);
	IMAGEMANAGER->addDImage("강철", L"pokemon/type/강철.png", 128, 56);
	IMAGEMANAGER->addDImage("고스트", L"pokemon/type/고스트.png", 128, 56);
	IMAGEMANAGER->addDImage("에스퍼", L"pokemon/type/에스퍼.png", 128, 56);
	IMAGEMANAGER->addDImage("격투", L"pokemon/type/격투.png", 128, 56);
	IMAGEMANAGER->addDImage("비행", L"pokemon/type/비행.png", 128, 56);
	IMAGEMANAGER->addDImage("땅", L"pokemon/type/땅.png", 128, 56);
	IMAGEMANAGER->addDImage("바위", L"pokemon/type/바위.png", 128, 56);
	IMAGEMANAGER->addDImage("벌레", L"pokemon/type/벌레.png", 128, 56);
	IMAGEMANAGER->addDImage("악", L"pokemon/type/악.png", 128, 56);
	IMAGEMANAGER->addDImage("드래곤", L"pokemon/type/드래곤.png", 128, 56);
	IMAGEMANAGER->addDImage("독", L"pokemon/type/독.png", 128, 56);
	IMAGEMANAGER->addDImage("페어리", L"pokemon/type/페어리.png", 128, 56);
	IMAGEMANAGER->addFrameDImage("몬스터나오기", L"Battle/몬스터 나오기.png", 14000, 600, 14, 1);
	IMAGEMANAGER->addDImage("아웃", L"UI/menu/fadeOut.png", 1000, 600);

	IMAGEMANAGER->addFrameDImage("iconNull", L"pokemon/icon/iconNull.png", 128, 64, 2, 1);
	//인벤토리 그림
	IMAGEMANAGER->addDImage("이상해씨 E", L"UI/invenPokemon/001.png", 480, 480);
	IMAGEMANAGER->addDImage("이상해풀 E", L"UI/invenPokemon/002.png", 480, 480);
	IMAGEMANAGER->addDImage("이상해꽃 E", L"UI/invenPokemon/003.png", 480, 480);

	//아이콘
	IMAGEMANAGER->addFrameDImage("이상해씨 I", L"pokemon/icon/icon001.png", 128, 64, 2, 1);
	IMAGEMANAGER->addFrameDImage("이상해풀 I", L"pokemon/icon/icon002.png", 128, 64, 2, 1);
	IMAGEMANAGER->addFrameDImage("이상해꽃 I", L"pokemon/icon/icon003.png", 128, 64, 2, 1);
	//앞에 이미지
	IMAGEMANAGER->addFrameDImage("이상해씨", L"pokemon/Front/001.png", 3762, 38, 99, 1);
	IMAGEMANAGER->addFrameDImage("이상해풀", L"pokemon/Front/002.png", 6438, 58, 111, 1);
	IMAGEMANAGER->addFrameDImage("이상해꽃", L"pokemon/Front/003.png", 14362, 86, 167, 1);

	//뒤에 이미지
	IMAGEMANAGER->addFrameDImage("이상해씨 b", L"pokemon/Back/001b.png", 3762, 38, 99, 1);
	IMAGEMANAGER->addFrameDImage("이상해풀 b", L"pokemon/Back/002b.png", 6327, 57, 111, 1);
	IMAGEMANAGER->addFrameDImage("이상해꽃 b", L"pokemon/Back/003b.png", 14863, 89, 167, 1);
	
	//스킬이미지
	IMAGEMANAGER->addFrameDImage("몸통박치기", L"pokemon/Animations/003-Attack01.png", 960, 384, 5,2);
	IMAGEMANAGER->addFrameDImage("전광석화", L"pokemon/Animations/Light1.png", 960, 576, 5, 3);

}
