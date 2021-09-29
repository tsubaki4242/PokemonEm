#include "stdafx.h"
#include "playerUI.h"

playerUI::playerUI()
{
}

playerUI::~playerUI()
{
}

HRESULT playerUI::init()
{

	IMGALL();
	_buttenPokemonNum = 0;
	_buttenNum = 0;
	_menuSizeW = 1500;
	_menuSizeH = 580;
	 _leftHendle = 0;
	 _rightHendle = 500;
	 _menuWich = 600;;
	 _fadeOut[1] = 0;
	 _fadeOut[2] = 1.0f;
	 _fadeOut[3] = 0;
	 _fadeOut[4] = 1.0f;
	 _fadeOut[6] = 1.0f;
	 _fadeOut[7] = 0;
	 _fadeOut[8] = 1.0f;
	 _fadeOut[10] = 1.0f;
	return S_OK;
}

void playerUI::release()
{
}

void playerUI::update()
{


	//_menuRect = RectMake(CAMERAMANAGER->getScreen().left - 1000, CAMERAMANAGER->getScreen().top, IMAGEMANAGER->findDImage("메뉴")->getFrameWidth(), IMAGEMANAGER->findDImage("메뉴")->getFrameHeight());
	for (int i = 0; i < 6; i++)
	{
		_butten[i] = RectMake((CAMERAMANAGER->getScreen().left + 40) + i * 160, CAMERAMANAGER->getScreen().top + 100, IMAGEMANAGER->findDImage("포켓몬")->getWidth(), IMAGEMANAGER->findDImage("포켓몬")->getHeight());
	}
	for (int i = 0; i < 8; i++)
	{
		_LeaderGYM[i] = RectMake(CAMERAMANAGER->getScreen().left  + i * 125, CAMERAMANAGER->getScreen().top + 50, IMAGEMANAGER->findDImage("노말없음")->getWidth(), IMAGEMANAGER->findDImage("노말없음")->getHeight());
	}
	for (int i = 0; i < 8; i++)
	{
		_bageGYM[i] = RectMake(CAMERAMANAGER->getScreen().left + i * 125, CAMERAMANAGER->getScreen().top + 320, IMAGEMANAGER->findDImage("노말뱃지")->getWidth(), IMAGEMANAGER->findDImage("노말뱃지")->getHeight());
	}
	for (int i = 0; i < 6; i++)
	{


		_buttenPokemonImg[i] = IMAGEMANAGER->findDImage("보유포켓몬메뉴");
		_buttenPokemon[i] = RectMake(CAMERAMANAGER->getScreen().right - 405, (CAMERAMANAGER->getScreen().top) + i * 100, IMAGEMANAGER->findDImage("보유포켓몬메뉴")->getWidth(), IMAGEMANAGER->findDImage("보유포켓몬메뉴")->getHeight());
	}
	card();
	menuPokemon();

}

void playerUI::render()
{

	if (KEYMANAGER->isToggleKey(VK_RETURN))
	{
	
		menuOn();
		_menuOn = false;
		_fadeOut[1] = 0;
		_fadeOut[2] = 1.0f;
	}
	else
	{
		menuOff();
		_menuOrgin = false;
		count2 = 0;
		_fadeOut[0] = 0;
		_cardOn = false;
	}


}

void playerUI::IMGALL()
{
	IMAGEMANAGER->addDImage("가운데메뉴", L"UI/menu/가운데.png", 291, 311);
	IMAGEMANAGER->addDImage("왼쪽메뉴", L"UI/menu/왼쪽.png", 500, 600);
	IMAGEMANAGER->addDImage("오른쪽메뉴", L"UI/menu/오른쪽.png", 500, 600);
	IMAGEMANAGER->addDImage("기본메뉴배경", L"UI/menu/기본메뉴배경.png", 1000, 600);
	IMAGEMANAGER->addDImage("메뉴", L"UI/menu/menu.png", 1000, 600);
	IMAGEMANAGER->addDImage("아웃", L"UI/menu/fadeOut.png", 1000, 600);
	IMAGEMANAGER->addDImage("메뉴시작", L"UI/menu/menuback.png", 1000, 600);

	IMAGEMANAGER->addDImage("포켓몬", L"UI/menu/pokemon.png", 133, 405);
	IMAGEMANAGER->addDImage("포켓몬_온", L"UI/menu/pokemon_on.png", 133, 405);
	IMAGEMANAGER->addDImage("도감", L"UI/menu/dex.png", 133, 405);
	IMAGEMANAGER->addDImage("도감_온", L"UI/menu/dex_on.png", 133, 405);
	IMAGEMANAGER->addDImage("인벤토리", L"UI/menu/inven.png", 133, 405);
	IMAGEMANAGER->addDImage("인벤토리_온", L"UI/menu/inven_on.png", 133, 405);
	IMAGEMANAGER->addDImage("트레이너카드", L"UI/menu/card.png", 133, 405);
	IMAGEMANAGER->addDImage("트레이너카드_온", L"UI/menu/card_on.png", 133, 405);
	IMAGEMANAGER->addDImage("옵션", L"UI/menu/opstion.png", 133, 405);
	IMAGEMANAGER->addDImage("옵션_온", L"UI/menu/opstion_on.png", 133, 405);
	IMAGEMANAGER->addDImage("저장", L"UI/menu/save.png", 133, 405);
	IMAGEMANAGER->addDImage("저장_온", L"UI/menu/save_on.png", 133, 405);

	//트리이너 카드
	IMAGEMANAGER->addDImage("뱃지배경", L"UI/card/뱃지배경.png", 1000, 600);
	IMAGEMANAGER->addDImage("노말", L"UI/card/노말.png", 125, 263);
	IMAGEMANAGER->addDImage("노말없음", L"UI/card/노말_흑.png", 125, 263);
	IMAGEMANAGER->addDImage("독", L"UI/card/독.png", 125, 263);
	IMAGEMANAGER->addDImage("독없음", L"UI/card/독_흑.png", 125, 263);
	IMAGEMANAGER->addDImage("드래곤", L"UI/card/드래곤.png", 125, 263);
	IMAGEMANAGER->addDImage("드래곤없음", L"UI/card/드래곤_흑.png", 125, 263);
	IMAGEMANAGER->addDImage("땅", L"UI/card/땅.png", 125, 263);
	IMAGEMANAGER->addDImage("땅없음", L"UI/card/땅_흑.png", 125, 263);
	IMAGEMANAGER->addDImage("물", L"UI/card/물.png", 125, 263);
	IMAGEMANAGER->addDImage("물없음", L"UI/card/물_흑.png", 125, 263);
	IMAGEMANAGER->addDImage("벌레", L"UI/card/벌레.png", 125, 263);
	IMAGEMANAGER->addDImage("벌레없음", L"UI/card/벌레_흑.png", 125, 263);
	IMAGEMANAGER->addDImage("비행", L"UI/card/비행.png", 125, 263);
	IMAGEMANAGER->addDImage("비행없음", L"UI/card/비행_흑.png", 125, 263);
	IMAGEMANAGER->addDImage("전기", L"UI/card/전기.png", 125, 263);
	IMAGEMANAGER->addDImage("전기없음", L"UI/card/전기_흑.png", 125, 263);

	//뱃지
	IMAGEMANAGER->addDImage("노말뱃지", L"UI/card/badges_01.png", 125, 264);
	IMAGEMANAGER->addDImage("노말뱃지없음", L"UI/card/badges2_01.png", 125, 264);
	IMAGEMANAGER->addDImage("독뱃지", L"UI/card/badges_02.png", 125, 264);
	IMAGEMANAGER->addDImage("독뱃지없음", L"UI/card/badges2_02.png", 125, 264);
	IMAGEMANAGER->addDImage("벌레뱃지", L"UI/card/badges_03.png", 125, 264);
	IMAGEMANAGER->addDImage("벌레뱃지없음", L"UI/card/badges2_03.png", 125, 264);
	IMAGEMANAGER->addDImage("전기뱃지", L"UI/card/badges_04.png", 125, 264);
	IMAGEMANAGER->addDImage("전기뱃지없음", L"UI/card/badges2_04.png", 125, 264);
	IMAGEMANAGER->addDImage("땅뱃지", L"UI/card/badges_05.png", 125, 264);
	IMAGEMANAGER->addDImage("땅뱃지없음", L"UI/card/badges2_05.png", 125, 264);
	IMAGEMANAGER->addDImage("비행뱃지", L"UI/card/badges_06.png", 125, 264);
	IMAGEMANAGER->addDImage("비행뱃지없음", L"UI/card/badges2_06.png", 125, 264);
	IMAGEMANAGER->addDImage("드래곤뱃지", L"UI/card/badges_07.png", 125, 264);
	IMAGEMANAGER->addDImage("드래곤뱃지없음", L"UI/card/badges2_07.png", 125, 264);
	IMAGEMANAGER->addDImage("물뱃지", L"UI/card/badges_08.png", 125, 264);
	IMAGEMANAGER->addDImage("물뱃지없음", L"UI/card/badges2_08.png", 125, 264);

	_bageIMG[0] = IMAGEMANAGER->findDImage("노말뱃지");
	_bageIMG[1] = IMAGEMANAGER->findDImage("독뱃지");
	_bageIMG[2] = IMAGEMANAGER->findDImage("벌레뱃지");
	_bageIMG[3] = IMAGEMANAGER->findDImage("전기뱃지");
	_bageIMG[4] = IMAGEMANAGER->findDImage("땅뱃지");
	_bageIMG[5] = IMAGEMANAGER->findDImage("비행뱃지");
	_bageIMG[6] = IMAGEMANAGER->findDImage("드래곤뱃지");
	_bageIMG[7] = IMAGEMANAGER->findDImage("물뱃지");


	_LeaderIMG[0] = IMAGEMANAGER->findDImage("노말없음");
	_LeaderIMG[1] = IMAGEMANAGER->findDImage("독없음");
	_LeaderIMG[2] = IMAGEMANAGER->findDImage("벌레없음");
	_LeaderIMG[3] = IMAGEMANAGER->findDImage("전기없음");
	_LeaderIMG[4] = IMAGEMANAGER->findDImage("땅없음");
	_LeaderIMG[5] = IMAGEMANAGER->findDImage("비행없음");
	_LeaderIMG[6] = IMAGEMANAGER->findDImage("드래곤없음");
	_LeaderIMG[7] = IMAGEMANAGER->findDImage("물없음");

	for (int i = 0; i < 8; i++)
	{
		_LeaderGYM[i] = RectMake((CAMERAMANAGER->getScreen().left + 40) + i * 160, CAMERAMANAGER->getScreen().top + 50, IMAGEMANAGER->findDImage("노말없음")->getWidth(), IMAGEMANAGER->findDImage("노말없음")->getHeight());
	}
	for (int i = 0; i < 8; i++)
	{
		_bageGYM[i] = RectMake((CAMERAMANAGER->getScreen().left + 40) + i * 160, CAMERAMANAGER->getScreen().top + 50, IMAGEMANAGER->findDImage("노말뱃지")->getWidth(), IMAGEMANAGER->findDImage("노말뱃지")->getHeight());
	}



	_alpaScreen = IMAGEMANAGER->findDImage("아웃");


	_buttenImg[0] = IMAGEMANAGER->findDImage("포켓몬");
	_buttenImg[1] = IMAGEMANAGER->findDImage("도감");
	_buttenImg[2] = IMAGEMANAGER->findDImage("인벤토리");
	_buttenImg[3] = IMAGEMANAGER->findDImage("트레이너카드");
	_buttenImg[4] = IMAGEMANAGER->findDImage("옵션");
	_buttenImg[5] = IMAGEMANAGER->findDImage("저장");

	for (int i = 0; i < 6; i++)
	{
		_butten[i] = RectMake((CAMERAMANAGER->getScreen().left + 40) + i * 160, CAMERAMANAGER->getScreen().top + 180, IMAGEMANAGER->findDImage("포켓몬")->getWidth(), IMAGEMANAGER->findDImage("포켓몬")->getHeight());
	}


	//포켓몬 인벤토리 이미지;
	IMAGEMANAGER->addDImage("포켓몬메뉴배경", L"UI/menu/포켓몬메뉴배경.png", 1000, 600);
	IMAGEMANAGER->addDImage("보유포켓몬메뉴", L"UI/menu/보유 포켓몬메뉴.png", 405, 100);
	IMAGEMANAGER->addDImage("보유포켓몬메뉴선택", L"UI/menu/보유 포켓몬메뉴 선택.png", 405, 100);
	for (int i = 0; i < 6; i++)
	{
		_buttenPokemon[i] = RectMake(CAMERAMANAGER->getScreen().right - 405, (CAMERAMANAGER->getScreen().top +100)+ i * 100, IMAGEMANAGER->findDImage("보유포켓몬메뉴")->getWidth(), IMAGEMANAGER->findDImage("보유포켓몬메뉴")->getHeight());

		_pokemonInvenIcon[i] = IMAGEMANAGER->findDImage("iconNull");
		_pokemonInvenFront[i] = IMAGEMANAGER->findDImage("iconNull");
		_pokemonInvenBack[i] = IMAGEMANAGER->findDImage("iconNull");
		_pokemonInvenBase[i] = IMAGEMANAGER->findDImage("iconNull");
	}


	for (int i = 0; i < 6; i++)
	{
		_hpBox[i]= IMAGEMANAGER->findDImage("HP박스");
		_hpBarBacck[i] = IMAGEMANAGER->findDImage("HP박스Back");
		_hpBar[i] = IMAGEMANAGER->findDImage("HPbar그린");
		_LvImg[i] = IMAGEMANAGER->findDImage("Lv박스");
	}
}

void playerUI::menuOn()
{

	if (_menuWich >= 10)
	{
		_menuWich -= 30;
	}
	else
	{
		_menuOrgin = true;
	}

	if (_menuOrgin == true)
	{

		count2++;
		if (count2 > 10)
		{
			if (_leftHendle < 500 && _rightHendle > 0)
			{
				_leftHendle += 8;
				_rightHendle -= 8;
			}

		}
		if (count2 > 50)
		{
			_fadeOut[0] += 0.1f;
			RENDERMANAGER->push_BackRenderInfo(
				9, IMAGEMANAGER->findDImage("아웃"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[0]);

		}
		if (count2 > 70)
		{
			_fadeOut[0] -= 0.2f;
			_invenStart = true;
			invenOn();

		}

		RENDERMANAGER->push_BackRenderInfo(
			7, IMAGEMANAGER->findDImage("왼쪽메뉴"),
			CAMERAMANAGER->getScreen().left - _leftHendle, CAMERAMANAGER->getScreen().top);
		RENDERMANAGER->push_BackRenderInfo(
			7, IMAGEMANAGER->findDImage("오른쪽메뉴"),
			CAMERAMANAGER->getScreen().right - _rightHendle, CAMERAMANAGER->getScreen().top);
		RENDERMANAGER->push_BackRenderInfo(
			7, IMAGEMANAGER->findDImage("가운데메뉴"),
			CAMERAMANAGER->getScreen().right - 643, CAMERAMANAGER->getScreen().top + 150, 0.5f);
		RENDERMANAGER->push_BackRenderInfo(
			7, IMAGEMANAGER->findDImage("기본메뉴배경"),
			CAMERAMANAGER->getScreen().left - 50, CAMERAMANAGER->getScreen().top + 10, _menuSizeW, _menuSizeH);

	}
	else
	{
		RENDERMANAGER->push_BackRenderInfo(
			6, IMAGEMANAGER->findDImage("메뉴"),
			CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top + _menuWich);
	}
}

void playerUI::menuOff()
{
	if (_invenStart == true)
	{
		_fadeOut[1] += 0.1f;
		RENDERMANAGER->push_BackRenderInfo(
			10, IMAGEMANAGER->findDImage("아웃"),
			CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[1]);
		RENDERMANAGER->push_BackRenderInfo(
			10, IMAGEMANAGER->findDImage("메뉴시작"),
			CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top);

	}
	if (_fadeOut[1] > 1.0f)
	{
		_invenStart = false;
		_fadeOut[2] -= 0.05f;
		RENDERMANAGER->push_BackRenderInfo(
			8, IMAGEMANAGER->findDImage("아웃"),
			CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[2]);
	}

	count2++;
	if (_leftHendle > 0 && _rightHendle < 500)
	{
		_leftHendle -= 8;
		_rightHendle += 8;
		
	}
	if (_leftHendle  == 0 && _rightHendle == 500)
	{
		_menuOn = true;
	}

	if (_menuOn == true)
	{
		RENDERMANAGER->push_BackRenderInfo(
			6, IMAGEMANAGER->findDImage("메뉴"),
			CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top + _menuWich);
		if (_menuWich < 600)
		{
			_menuWich += 30;
		}
	}
	else
	{

		RENDERMANAGER->push_BackRenderInfo(
			7, IMAGEMANAGER->findDImage("왼쪽메뉴"),
			CAMERAMANAGER->getScreen().left - _leftHendle, CAMERAMANAGER->getScreen().top);
		RENDERMANAGER->push_BackRenderInfo(
			7, IMAGEMANAGER->findDImage("오른쪽메뉴"),
			CAMERAMANAGER->getScreen().right - _rightHendle, CAMERAMANAGER->getScreen().top);
		RENDERMANAGER->push_BackRenderInfo(
			7, IMAGEMANAGER->findDImage("가운데메뉴"),
			CAMERAMANAGER->getScreen().right - 643, CAMERAMANAGER->getScreen().top + 150, 0.5f);
		RENDERMANAGER->push_BackRenderInfo(
			7, IMAGEMANAGER->findDImage("기본메뉴배경"),
			CAMERAMANAGER->getScreen().left - 50, CAMERAMANAGER->getScreen().top + 10, _menuSizeW, _menuSizeH);
	}
}

void playerUI::invenOn()
{
	keyControl();
	RENDERMANAGER->push_BackRenderInfo(
		8, IMAGEMANAGER->findDImage("메뉴시작"),
		CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top);
	for (int i = 0; i < 6; i++)
	{
		RENDERMANAGER->push_BackRenderInfo(
			9, _buttenImg[i],
			_butten[i].left, _butten[i].top);
	}

	if (_buttenNum == 0)
	{
		_buttenImg[0] = IMAGEMANAGER->findDImage("포켓몬_온");
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{

			_pokemonMenuOn = true;
			_fadeOut[9] = 0;
			_fadeOut[10] = 1.0f;
		}
		if (KEYMANAGER->isOnceKeyDown('X') && _pokemonMenuOn == true)
		{


			_Go[2] = true;

		}
		if (_Go[2])
		{
			_fadeOut[9] += 0.1f;
			RENDERMANAGER->push_BackRenderInfo(
				15, IMAGEMANAGER->findDImage("아웃"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[9]);

		}
		if (_fadeOut[9] > 1.0f)
		{
			_Go[2] = false;
			_fadeOut[10] -= 0.1f;
			RENDERMANAGER->push_BackRenderInfo(
				15, IMAGEMANAGER->findDImage("아웃"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[10]);
			_pokemonMenuOn = false;
			_fadeOut[7] = 0;
			_fadeOut[8] = 1.0f;
		}


	}
	else
	{
		_buttenImg[0] = IMAGEMANAGER->findDImage("포켓몬");
	}
	if (_buttenNum == 1)
	{
		_buttenImg[1] = IMAGEMANAGER->findDImage("도감_온");

	}
	else
	{
		_buttenImg[1] = IMAGEMANAGER->findDImage("도감");
	}
	if (_buttenNum == 2)
	{
		_buttenImg[2] = IMAGEMANAGER->findDImage("인벤토리_온");

	}
	else
	{
		_buttenImg[2] = IMAGEMANAGER->findDImage("인벤토리");
	}
	if (_buttenNum == 3)
	{
		_buttenImg[3] = IMAGEMANAGER->findDImage("트레이너카드_온");
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{

			_cardOn = true;
			_fadeOut[5] = 0;
			_fadeOut[6] = 1.0f;
		}
		if (KEYMANAGER->isOnceKeyDown('X') && _cardOn ==true)
		{


			_Go[1] = true;

		}
		if (_Go[1])
		{
			_fadeOut[5] += 0.1f;
			RENDERMANAGER->push_BackRenderInfo(
				11, IMAGEMANAGER->findDImage("아웃"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[5]);

		}
		if (_fadeOut[5] > 1.0f)
		{
			_Go[1] = false;
			_fadeOut[6] -= 0.1f;
			RENDERMANAGER->push_BackRenderInfo(
				11, IMAGEMANAGER->findDImage("아웃"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[6]);
			_cardOn = false;
			_fadeOut[3] = 0;
			_fadeOut[4] = 1.0f;
		}
	}
	else
	{
		_buttenImg[3] = IMAGEMANAGER->findDImage("트레이너카드");
	}
	if (_buttenNum == 4)
	{
		_buttenImg[4] = IMAGEMANAGER->findDImage("옵션_온");

	}
	else
	{
		_buttenImg[4] = IMAGEMANAGER->findDImage("옵션");
	}
	if (_buttenNum == 5)
	{
		_buttenImg[5] = IMAGEMANAGER->findDImage("저장_온");
	}
	else
	{
		_buttenImg[5] = IMAGEMANAGER->findDImage("저장");
	}
	if(_buttenNum > 5)
	{
		_buttenNum = 5;
	}
	if (_buttenNum < 0)
	{
		_buttenNum = 0;
	}
}

void playerUI::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && _pokemonMenuOn ==false && _cardOn ==false)
	{
		_buttenNum--;

	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _pokemonMenuOn == false && _cardOn == false)
	{
		_buttenNum++;

	}

}

void playerUI::card()
{
	if (_cardOn == true)
	{
		_fadeOut[3] += 0.1f;
		if (_fadeOut[3] < 1.0f)
		{
			RENDERMANAGER->push_BackRenderInfo(
				11, IMAGEMANAGER->findDImage("아웃"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[3]);
		}
		if (_fadeOut[3] > 1.0f)
		{

			_fadeOut[4] -= 0.1f;
			RENDERMANAGER->push_BackRenderInfo(
				11, IMAGEMANAGER->findDImage("아웃"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[4]);

			for (int i = 0; i < 8; i++)
			{
				RENDERMANAGER->push_BackRenderInfo(
					10, _LeaderIMG[i],
					_LeaderGYM[i].left, _LeaderGYM[i].top);
			}
			//for (int i = 0; i < 1; i++)
			//{
			//	RENDERMANAGER->push_BackRenderInfo(
			//		10, _bageIMG[i],
			//		_bageGYM[i].left, _bageGYM[i].top);
			//}
			RENDERMANAGER->push_BackRenderInfo(
				10, IMAGEMANAGER->findDImage("뱃지배경"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top);




		}






	}


}

void playerUI::menuPokemon()
{
	_txtLV[64] = _itoa_s(_pokemonInvenNameLv[0], _txtLV, sizeof(&_txtLV), 10);
	_txtLV1[64] = _itoa_s(_pokemonInvenNameLv[1], _txtLV1, sizeof(&_txtLV1), 10);
	_txtLV2[64] = _itoa_s(_pokemonInvenNameLv[2], _txtLV2, sizeof(&_txtLV2), 10);
	_txtLV3[64] = _itoa_s(_pokemonInvenNameLv[3], _txtLV3, sizeof(&_txtLV3), 10);
	_txtLV4[64] = _itoa_s(_pokemonInvenNameLv[4], _txtLV4, sizeof(&_txtLV4), 10);
	_txtLV5[64] = _itoa_s(_pokemonInvenNameLv[5], _txtLV5, sizeof(&_txtLV5), 10);

	if (_pokemonMenuOn == true)
	{

		_fadeOut[7] += 0.1f;
		if (_fadeOut[7] < 1.0f)
		{
			RENDERMANAGER->push_BackRenderInfo(
				15, IMAGEMANAGER->findDImage("아웃"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[7]);
		}
		if (_fadeOut[7] > 1.0f)
		{

			_fadeOut[8] -= 0.1f;
			RENDERMANAGER->push_BackRenderInfo(
				15, IMAGEMANAGER->findDImage("아웃"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[8]);
			RENDERMANAGER->push_BackRenderInfo(
				11, IMAGEMANAGER->findDImage("포켓몬메뉴배경"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top);
			pokemonInvenUpdate();
			for (int i = 0; i < 6; i++)
			{
				RENDERMANAGER->push_BackRenderInfo(
					12, _buttenPokemonImg[i],
					_buttenPokemon[i].left, _buttenPokemon[i].top);
			}
			
				RENDERMANAGER->push_BackFrameRenderInfo(
					13, _pokemonInvenIcon[0],
					CAMERAMANAGER->getScreen().right - 380, CAMERAMANAGER->getScreen().top+10,0,0);
				RENDERMANAGER->push_BackFrameRenderInfo(
					13, _pokemonInvenIcon[1],
					CAMERAMANAGER->getScreen().right - 380, CAMERAMANAGER->getScreen().top +110, 0, 0);
				RENDERMANAGER->push_BackFrameRenderInfo(
					13, _pokemonInvenIcon[2],
					CAMERAMANAGER->getScreen().right - 380, CAMERAMANAGER->getScreen().top + 210, 0, 0);
				RENDERMANAGER->push_BackFrameRenderInfo(
					13, _pokemonInvenIcon[3],
					CAMERAMANAGER->getScreen().right - 380, CAMERAMANAGER->getScreen().top+ 310, 0, 0);
				RENDERMANAGER->push_BackFrameRenderInfo(
					13, _pokemonInvenIcon[4],
					CAMERAMANAGER->getScreen().right - 380, CAMERAMANAGER->getScreen().top + 410, 0, 0);
				RENDERMANAGER->push_BackFrameRenderInfo(
					13, _pokemonInvenIcon[5],
					CAMERAMANAGER->getScreen().right - 380, CAMERAMANAGER->getScreen().top + 510, 0, 0);
				if (_pokemonInvenNameLv[0] > 0)
				{
					RENDERMANAGER->push_BackRenderInfo(
						14, _hpBox[0],
						CAMERAMANAGER->getScreen().right - 290, CAMERAMANAGER->getScreen().top + 45);
					RENDERMANAGER->push_BackRenderInfo(
						14, _hpBar[0],
						CAMERAMANAGER->getScreen().right - 230, CAMERAMANAGER->getScreen().top + 49, (float)_pokemonInvenNameHp[0] / (float)_pokemonInvenNameMaxHp[0]* 208,16);
					RENDERMANAGER->push_BackRenderInfo(
						14, _hpBarBacck[0],
						CAMERAMANAGER->getScreen().right - 230, CAMERAMANAGER->getScreen().top + 49);
					RENDERMANAGER->push_BackRenderInfo(
						14, _LvImg[0],
						CAMERAMANAGER->getScreen().right - 290, CAMERAMANAGER->getScreen().top + 15);
		
					TXTRENDERMANGER->push_BackRenderInfo(0, ConverCtoWC(_txtLV), CAMERAMANAGER->getScreen().right - 240,
						CAMERAMANAGER->getScreen().top+7, 34);
				}
				if (_pokemonInvenNameLv[1] > 0)
				{
					RENDERMANAGER->push_BackRenderInfo(
						14, _hpBox[1],
						CAMERAMANAGER->getScreen().right - 290, CAMERAMANAGER->getScreen().top + 145);
					RENDERMANAGER->push_BackRenderInfo(
						14, _hpBar[1],
						CAMERAMANAGER->getScreen().right - 230, CAMERAMANAGER->getScreen().top + 149, (float)_pokemonInvenNameHp[1] / (float)_pokemonInvenNameMaxHp[1] * 208, 16);
					RENDERMANAGER->push_BackRenderInfo(
						14, _hpBarBacck[1],
						CAMERAMANAGER->getScreen().right - 230, CAMERAMANAGER->getScreen().top + 149);
					RENDERMANAGER->push_BackRenderInfo(
						14, _LvImg[1],
						CAMERAMANAGER->getScreen().right - 290, CAMERAMANAGER->getScreen().top + 115);

					TXTRENDERMANGER->push_BackRenderInfo(0, ConverCtoWC(_txtLV1), CAMERAMANAGER->getScreen().right - 240,
						CAMERAMANAGER->getScreen().top + 107, 34);
				}
				if (_pokemonInvenNameLv[2] > 0)
				{
					RENDERMANAGER->push_BackRenderInfo(
						14, _hpBox[2],
						CAMERAMANAGER->getScreen().right - 290, CAMERAMANAGER->getScreen().top + 245);
					RENDERMANAGER->push_BackRenderInfo(
						14, _hpBar[2],
						CAMERAMANAGER->getScreen().right - 230, CAMERAMANAGER->getScreen().top + 249, (float)_pokemonInvenNameHp[2] / (float)_pokemonInvenNameMaxHp[2] * 208, 16);
					RENDERMANAGER->push_BackRenderInfo(
						14, _hpBarBacck[1],
						CAMERAMANAGER->getScreen().right - 230, CAMERAMANAGER->getScreen().top + 249);
					RENDERMANAGER->push_BackRenderInfo(
						14, _LvImg[1],
						CAMERAMANAGER->getScreen().right - 290, CAMERAMANAGER->getScreen().top + 215);

					TXTRENDERMANGER->push_BackRenderInfo(0, ConverCtoWC(_txtLV2), CAMERAMANAGER->getScreen().right - 240,
						CAMERAMANAGER->getScreen().top + 207, 34);
				}
				if (_pokemonInvenNameLv[3] > 0)
				{
					RENDERMANAGER->push_BackRenderInfo(
						14, _hpBox[3],
						CAMERAMANAGER->getScreen().right - 290, CAMERAMANAGER->getScreen().top + 345);
					RENDERMANAGER->push_BackRenderInfo(
						14, _hpBar[3],
						CAMERAMANAGER->getScreen().right - 230, CAMERAMANAGER->getScreen().top + 349, (float)_pokemonInvenNameHp[3] / (float)_pokemonInvenNameMaxHp[3] * 208, 16);
					RENDERMANAGER->push_BackRenderInfo(
						14, _hpBarBacck[3],
						CAMERAMANAGER->getScreen().right - 230, CAMERAMANAGER->getScreen().top + 349);
					RENDERMANAGER->push_BackRenderInfo(
						14, _LvImg[3],
						CAMERAMANAGER->getScreen().right - 290, CAMERAMANAGER->getScreen().top + 315);

					TXTRENDERMANGER->push_BackRenderInfo(0, ConverCtoWC(_txtLV3), CAMERAMANAGER->getScreen().right - 240,
						CAMERAMANAGER->getScreen().top + 307, 34);
				}
				if (_pokemonInvenNameLv[4] > 0)
				{
					RENDERMANAGER->push_BackRenderInfo(
						14, _hpBox[4],
						CAMERAMANAGER->getScreen().right - 290, CAMERAMANAGER->getScreen().top + 445);
					RENDERMANAGER->push_BackRenderInfo(
						14, _hpBar[4],
						CAMERAMANAGER->getScreen().right - 230, CAMERAMANAGER->getScreen().top + 449, (float)_pokemonInvenNameHp[4] / (float)_pokemonInvenNameMaxHp[4] * 208, 16);
					RENDERMANAGER->push_BackRenderInfo(
						14, _hpBarBacck[4],
						CAMERAMANAGER->getScreen().right - 230, CAMERAMANAGER->getScreen().top + 449);
					RENDERMANAGER->push_BackRenderInfo(
						14, _LvImg[4],
						CAMERAMANAGER->getScreen().right - 290, CAMERAMANAGER->getScreen().top + 415);

					TXTRENDERMANGER->push_BackRenderInfo(0, ConverCtoWC(_txtLV4), CAMERAMANAGER->getScreen().right - 240,
						CAMERAMANAGER->getScreen().top + 407, 34);
				}
				if (_pokemonInvenNameLv[5] > 0)
				{
					RENDERMANAGER->push_BackRenderInfo(
						14, _hpBox[5],
						CAMERAMANAGER->getScreen().right - 290, CAMERAMANAGER->getScreen().top + 545);
					RENDERMANAGER->push_BackRenderInfo(
						14, _hpBar[5],
						CAMERAMANAGER->getScreen().right - 230, CAMERAMANAGER->getScreen().top + 549, (float)_pokemonInvenNameHp[5] / (float)_pokemonInvenNameMaxHp[5] * 208, 16);
					RENDERMANAGER->push_BackRenderInfo(
						14, _hpBarBacck[5],
						CAMERAMANAGER->getScreen().right - 230, CAMERAMANAGER->getScreen().top + 549);
					RENDERMANAGER->push_BackRenderInfo(
						14, _LvImg[5],
						CAMERAMANAGER->getScreen().right - 290, CAMERAMANAGER->getScreen().top + 515);

					TXTRENDERMANGER->push_BackRenderInfo(0, ConverCtoWC(_txtLV5), CAMERAMANAGER->getScreen().right - 240,
						CAMERAMANAGER->getScreen().top + 507, 34);
				}
		}



	}


}

void playerUI::pokemonInvenUpdate()
{
	_frontRect = RectMakeCenter(CAMERAMANAGER->getScreen().left+60, CAMERAMANAGER->getScreen().top+60, 495, 473);
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_buttenPokemonNum--;

	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_buttenPokemonNum++;

	}
	if (_buttenPokemonNum > 5)
	{
		_buttenPokemonNum = 5;
	}
	if (_buttenPokemonNum < 0)
	{
		_buttenPokemonNum = 0;
	}

	if (_buttenPokemonNum == 0)
	{
		_buttenPokemonImg[0] = IMAGEMANAGER->findDImage("보유포켓몬메뉴선택");
		RENDERMANAGER->push_BackRenderInfo(
			14, _pokemonInvenBase[0],
			(_frontRect.left + _frontRect.right) /2, (_frontRect.top + _frontRect.bottom) / 2);
		type1Img(_pokemonInvenType1[0]);
		type2Img(_pokemonInvenType2[0]);
		RENDERMANAGER->push_BackRenderInfo(
			15, _pokemontype1,
			CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().bottom - 56);
		RENDERMANAGER->push_BackRenderInfo(
			15, _pokemontype2,
			CAMERAMANAGER->getScreen().left +135, CAMERAMANAGER->getScreen().bottom - 56);
		TXTRENDERMANGER->push_BackRenderInfo(0, _pokemonInvenName[0], CAMERAMANAGER->getScreen().left+ 10,
			CAMERAMANAGER->getScreen().top,50);







	}
	else
	{
		_buttenPokemonImg[0] = IMAGEMANAGER->findDImage("보유포켓몬메뉴");

	}
	if (_buttenPokemonNum == 1)
	{
		_buttenPokemonImg[1] = IMAGEMANAGER->findDImage("보유포켓몬메뉴선택");
		RENDERMANAGER->push_BackRenderInfo(
			14, _pokemonInvenBase[1],
			(_frontRect.left + _frontRect.right) / 2, (_frontRect.top + _frontRect.bottom) / 2);
		type1Img(_pokemonInvenType1[1]);
		type2Img(_pokemonInvenType2[1]);
		RENDERMANAGER->push_BackRenderInfo(
			15, _pokemontype1,
			CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().bottom - 56);
		RENDERMANAGER->push_BackRenderInfo(
			15, _pokemontype2,
			CAMERAMANAGER->getScreen().left + 135, CAMERAMANAGER->getScreen().bottom - 56);
		TXTRENDERMANGER->push_BackRenderInfo(0, _pokemonInvenName[1], CAMERAMANAGER->getScreen().left + 10,
			CAMERAMANAGER->getScreen().top, 50);
	}
	else
	{
		_buttenPokemonImg[1] = IMAGEMANAGER->findDImage("보유포켓몬메뉴");
	}
	if (_buttenPokemonNum == 2)
	{
		_buttenPokemonImg[2] = IMAGEMANAGER->findDImage("보유포켓몬메뉴선택");
		RENDERMANAGER->push_BackRenderInfo(
			14, _pokemonInvenBase[2],
			(_frontRect.left + _frontRect.right) / 2, (_frontRect.top + _frontRect.bottom) / 2);
		type1Img(_pokemonInvenType1[2]);
		type2Img(_pokemonInvenType2[2]);
		RENDERMANAGER->push_BackRenderInfo(
			15, _pokemontype1,
			CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().bottom - 56);
		RENDERMANAGER->push_BackRenderInfo(
			15, _pokemontype2,
			CAMERAMANAGER->getScreen().left + 135, CAMERAMANAGER->getScreen().bottom - 56);
		TXTRENDERMANGER->push_BackRenderInfo(0, _pokemonInvenName[2], CAMERAMANAGER->getScreen().left + 10,
			CAMERAMANAGER->getScreen().top, 50);
	}
	else
	{
		_buttenPokemonImg[2] = IMAGEMANAGER->findDImage("보유포켓몬메뉴");
	}
	if (_buttenPokemonNum == 3)
	{
		_buttenPokemonImg[3] = IMAGEMANAGER->findDImage("보유포켓몬메뉴선택");
		RENDERMANAGER->push_BackRenderInfo(
			14, _pokemonInvenBase[3],
			(_frontRect.left + _frontRect.right) / 2, (_frontRect.top + _frontRect.bottom) / 2);
		type1Img(_pokemonInvenType1[3]);
		type2Img(_pokemonInvenType2[3]);
		RENDERMANAGER->push_BackRenderInfo(
			15, _pokemontype1,
			CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().bottom - 56);
		RENDERMANAGER->push_BackRenderInfo(
			15, _pokemontype2,
			CAMERAMANAGER->getScreen().left + 135, CAMERAMANAGER->getScreen().bottom - 56);
		TXTRENDERMANGER->push_BackRenderInfo(0, _pokemonInvenName[3], CAMERAMANAGER->getScreen().left + 10,
			CAMERAMANAGER->getScreen().top, 50);
	}
	else
	{
		_buttenPokemonImg[3] = IMAGEMANAGER->findDImage("보유포켓몬메뉴");
	}
	if (_buttenPokemonNum == 4)
	{
		_buttenPokemonImg[4] = IMAGEMANAGER->findDImage("보유포켓몬메뉴선택");
		RENDERMANAGER->push_BackRenderInfo(
			14, _pokemonInvenBase[4],
			(_frontRect.left + _frontRect.right) / 2, (_frontRect.top + _frontRect.bottom) / 2);
		type1Img(_pokemonInvenType1[4]);
		type2Img(_pokemonInvenType2[4]);
		RENDERMANAGER->push_BackRenderInfo(
			15, _pokemontype1,
			CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().bottom - 56);
		RENDERMANAGER->push_BackRenderInfo(
			15, _pokemontype2,
			CAMERAMANAGER->getScreen().left + 135, CAMERAMANAGER->getScreen().bottom - 56);
		TXTRENDERMANGER->push_BackRenderInfo(0, _pokemonInvenName[4], CAMERAMANAGER->getScreen().left + 10,
			CAMERAMANAGER->getScreen().top, 50);
	}
	else
	{
		_buttenPokemonImg[4] = IMAGEMANAGER->findDImage("보유포켓몬메뉴");
	}
	if (_buttenPokemonNum == 5)
	{
		_buttenPokemonImg[5] = IMAGEMANAGER->findDImage("보유포켓몬메뉴선택");
		RENDERMANAGER->push_BackRenderInfo(
			14, _pokemonInvenBase[5],
			(_frontRect.left + _frontRect.right) / 2, (_frontRect.top + _frontRect.bottom) / 2);
		type1Img(_pokemonInvenType1[5]);
		type2Img(_pokemonInvenType2[5]);
		RENDERMANAGER->push_BackRenderInfo(
			15, _pokemontype1,
			CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().bottom - 56);
		RENDERMANAGER->push_BackRenderInfo(
			15, _pokemontype2,
			CAMERAMANAGER->getScreen().left + 135, CAMERAMANAGER->getScreen().bottom - 56);
		TXTRENDERMANGER->push_BackRenderInfo(0, _pokemonInvenName[5], CAMERAMANAGER->getScreen().left + 10,
			CAMERAMANAGER->getScreen().top, 50);
	}
	else
	{
		_buttenPokemonImg[5] = IMAGEMANAGER->findDImage("보유포켓몬메뉴");
	}
}

void playerUI::type1Img(TYPE type1)
{
	if (type1 == NOMRAL)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("노말");
	}
	if (type1 == FIRE)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("불");
	}
	if (type1 == WATER)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("물");
	}
	if (type1 == LEAF)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("풀");
	}
	if (type1 == ROCK)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("바위");
	}
	if (type1 == GROUND)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("땅");
	}
	if (type1 == ICE)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("얼음");
	}
	if (type1 == DARK)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("악");
	}
	if (type1 == ESPER)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("에스퍼");
	}
	if (type1 == BUG)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("벌레");
	}
	if (type1 == ELECTRICITY)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("전기");
	}
	if (type1 == METAL)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("강철");
	}
	if (type1 == COMBAT)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("격투");
	}
	if (type1 == GHOST)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("고스트");
	}
	if (type1 == POISON)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("독");
	}
	if (type1 == FLYING)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("비행");
	}
	if (type1 == FAIRY)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("페어리");
	}
	if (type1 == DRAGON)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("드래곤");
	}
	if (type1 == NOT)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("iconNull");
	}
}

void playerUI::type2Img(TYPE type2)
{
	if (type2 == NOMRAL)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("노말");
	}
	if (type2 == FIRE)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("불");
	}
	if (type2 == WATER)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("물");
	}
	if (type2 == LEAF)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("풀");
	}
	if (type2 == ROCK)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("바위");
	}
	if (type2 == GROUND)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("땅");
	}
	if (type2 == ICE)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("얼음");
	}
	if (type2 == DARK)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("악");
	}
	if (type2 == ESPER)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("에스퍼");
	}
	if (type2 == BUG)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("벌레");
	}
	if (type2 == ELECTRICITY)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("전기");
	}
	if (type2 == METAL)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("강철");
	}
	if (type2 == COMBAT)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("격투");
	}
	if (type2 == GHOST)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("고스트");
	}
	if (type2 == POISON)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("독");
	}
	if (type2 == FLYING)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("비행");
	}
	if (type2 == FAIRY)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("페어리");
	}
	if (type2 == DRAGON)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("드래곤");
	}
	if (type2 == NOT)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("iconNull");
	}
}



void playerUI::pokemonInven1all(int max, dImage * pokemon, dImage * inven, dImage * front, dImage * back, wstring name, TYPE type1, TYPE type2, PERSONA persona, int Lv, int exp, bool sex, int MaxHp, int hp, int atk, int def, int matk, int mdef, int spd)
{
	_pokemonInvenBase[max] = inven;
	_pokemonInvenIcon[max] = pokemon;
	_pokemonInvenFront[max] = front;
	_pokemonInvenBack[max] = back;
	_pokemonInvenName[max] = name;
	_pokemonInvenType1[max] = type1;
	_pokemonInvenType2[max] = type2;
	_pokemonInvenPersona[max] = persona;
	_pokemonInvenSex[max] = sex;
	_pokemonInvenNameLv[max] = Lv;
	_pokemonInvenNameExp[max] = exp;
	_pokemonInvenNameMaxHp[max] = MaxHp;
	_pokemonInvenNameHp[max] = hp;
	_pokemonInvenNamAtk[max] = atk;
	_pokemonInvenNameDef[max] = def;
	_pokemonInvenNameMatk[max] = matk;
	_pokemonInvenNameMdef[max] = mdef;
	_pokemonInvenNameSpd[max] = spd;
}

void playerUI::fadeIn()
{
	if (_alpa < 1.0f)
	{
		_alpa += 0.1f;
	}
	RENDERMANAGER->push_BackRenderInfo(
		11, _alpaScreen,
		CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _alpa);
}

void playerUI::fadeOut()
{
	if (_alpa < 0)
	{
		_alpa -= 0.1f;
	}
	RENDERMANAGER->push_BackRenderInfo(
		11, _alpaScreen,
		CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _alpa);
}
