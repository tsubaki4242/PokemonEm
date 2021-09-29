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


	//_menuRect = RectMake(CAMERAMANAGER->getScreen().left - 1000, CAMERAMANAGER->getScreen().top, IMAGEMANAGER->findDImage("�޴�")->getFrameWidth(), IMAGEMANAGER->findDImage("�޴�")->getFrameHeight());
	for (int i = 0; i < 6; i++)
	{
		_butten[i] = RectMake((CAMERAMANAGER->getScreen().left + 40) + i * 160, CAMERAMANAGER->getScreen().top + 100, IMAGEMANAGER->findDImage("���ϸ�")->getWidth(), IMAGEMANAGER->findDImage("���ϸ�")->getHeight());
	}
	for (int i = 0; i < 8; i++)
	{
		_LeaderGYM[i] = RectMake(CAMERAMANAGER->getScreen().left  + i * 125, CAMERAMANAGER->getScreen().top + 50, IMAGEMANAGER->findDImage("�븻����")->getWidth(), IMAGEMANAGER->findDImage("�븻����")->getHeight());
	}
	for (int i = 0; i < 8; i++)
	{
		_bageGYM[i] = RectMake(CAMERAMANAGER->getScreen().left + i * 125, CAMERAMANAGER->getScreen().top + 320, IMAGEMANAGER->findDImage("�븻����")->getWidth(), IMAGEMANAGER->findDImage("�븻����")->getHeight());
	}
	for (int i = 0; i < 6; i++)
	{


		_buttenPokemonImg[i] = IMAGEMANAGER->findDImage("�������ϸ�޴�");
		_buttenPokemon[i] = RectMake(CAMERAMANAGER->getScreen().right - 405, (CAMERAMANAGER->getScreen().top) + i * 100, IMAGEMANAGER->findDImage("�������ϸ�޴�")->getWidth(), IMAGEMANAGER->findDImage("�������ϸ�޴�")->getHeight());
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
	IMAGEMANAGER->addDImage("����޴�", L"UI/menu/���.png", 291, 311);
	IMAGEMANAGER->addDImage("���ʸ޴�", L"UI/menu/����.png", 500, 600);
	IMAGEMANAGER->addDImage("�����ʸ޴�", L"UI/menu/������.png", 500, 600);
	IMAGEMANAGER->addDImage("�⺻�޴����", L"UI/menu/�⺻�޴����.png", 1000, 600);
	IMAGEMANAGER->addDImage("�޴�", L"UI/menu/menu.png", 1000, 600);
	IMAGEMANAGER->addDImage("�ƿ�", L"UI/menu/fadeOut.png", 1000, 600);
	IMAGEMANAGER->addDImage("�޴�����", L"UI/menu/menuback.png", 1000, 600);

	IMAGEMANAGER->addDImage("���ϸ�", L"UI/menu/pokemon.png", 133, 405);
	IMAGEMANAGER->addDImage("���ϸ�_��", L"UI/menu/pokemon_on.png", 133, 405);
	IMAGEMANAGER->addDImage("����", L"UI/menu/dex.png", 133, 405);
	IMAGEMANAGER->addDImage("����_��", L"UI/menu/dex_on.png", 133, 405);
	IMAGEMANAGER->addDImage("�κ��丮", L"UI/menu/inven.png", 133, 405);
	IMAGEMANAGER->addDImage("�κ��丮_��", L"UI/menu/inven_on.png", 133, 405);
	IMAGEMANAGER->addDImage("Ʈ���̳�ī��", L"UI/menu/card.png", 133, 405);
	IMAGEMANAGER->addDImage("Ʈ���̳�ī��_��", L"UI/menu/card_on.png", 133, 405);
	IMAGEMANAGER->addDImage("�ɼ�", L"UI/menu/opstion.png", 133, 405);
	IMAGEMANAGER->addDImage("�ɼ�_��", L"UI/menu/opstion_on.png", 133, 405);
	IMAGEMANAGER->addDImage("����", L"UI/menu/save.png", 133, 405);
	IMAGEMANAGER->addDImage("����_��", L"UI/menu/save_on.png", 133, 405);

	//Ʈ���̳� ī��
	IMAGEMANAGER->addDImage("�������", L"UI/card/�������.png", 1000, 600);
	IMAGEMANAGER->addDImage("�븻", L"UI/card/�븻.png", 125, 263);
	IMAGEMANAGER->addDImage("�븻����", L"UI/card/�븻_��.png", 125, 263);
	IMAGEMANAGER->addDImage("��", L"UI/card/��.png", 125, 263);
	IMAGEMANAGER->addDImage("������", L"UI/card/��_��.png", 125, 263);
	IMAGEMANAGER->addDImage("�巡��", L"UI/card/�巡��.png", 125, 263);
	IMAGEMANAGER->addDImage("�巡�����", L"UI/card/�巡��_��.png", 125, 263);
	IMAGEMANAGER->addDImage("��", L"UI/card/��.png", 125, 263);
	IMAGEMANAGER->addDImage("������", L"UI/card/��_��.png", 125, 263);
	IMAGEMANAGER->addDImage("��", L"UI/card/��.png", 125, 263);
	IMAGEMANAGER->addDImage("������", L"UI/card/��_��.png", 125, 263);
	IMAGEMANAGER->addDImage("����", L"UI/card/����.png", 125, 263);
	IMAGEMANAGER->addDImage("��������", L"UI/card/����_��.png", 125, 263);
	IMAGEMANAGER->addDImage("����", L"UI/card/����.png", 125, 263);
	IMAGEMANAGER->addDImage("�������", L"UI/card/����_��.png", 125, 263);
	IMAGEMANAGER->addDImage("����", L"UI/card/����.png", 125, 263);
	IMAGEMANAGER->addDImage("�������", L"UI/card/����_��.png", 125, 263);

	//����
	IMAGEMANAGER->addDImage("�븻����", L"UI/card/badges_01.png", 125, 264);
	IMAGEMANAGER->addDImage("�븻��������", L"UI/card/badges2_01.png", 125, 264);
	IMAGEMANAGER->addDImage("������", L"UI/card/badges_02.png", 125, 264);
	IMAGEMANAGER->addDImage("����������", L"UI/card/badges2_02.png", 125, 264);
	IMAGEMANAGER->addDImage("��������", L"UI/card/badges_03.png", 125, 264);
	IMAGEMANAGER->addDImage("������������", L"UI/card/badges2_03.png", 125, 264);
	IMAGEMANAGER->addDImage("�������", L"UI/card/badges_04.png", 125, 264);
	IMAGEMANAGER->addDImage("�����������", L"UI/card/badges2_04.png", 125, 264);
	IMAGEMANAGER->addDImage("������", L"UI/card/badges_05.png", 125, 264);
	IMAGEMANAGER->addDImage("����������", L"UI/card/badges2_05.png", 125, 264);
	IMAGEMANAGER->addDImage("�������", L"UI/card/badges_06.png", 125, 264);
	IMAGEMANAGER->addDImage("�����������", L"UI/card/badges2_06.png", 125, 264);
	IMAGEMANAGER->addDImage("�巡�����", L"UI/card/badges_07.png", 125, 264);
	IMAGEMANAGER->addDImage("�巡���������", L"UI/card/badges2_07.png", 125, 264);
	IMAGEMANAGER->addDImage("������", L"UI/card/badges_08.png", 125, 264);
	IMAGEMANAGER->addDImage("����������", L"UI/card/badges2_08.png", 125, 264);

	_bageIMG[0] = IMAGEMANAGER->findDImage("�븻����");
	_bageIMG[1] = IMAGEMANAGER->findDImage("������");
	_bageIMG[2] = IMAGEMANAGER->findDImage("��������");
	_bageIMG[3] = IMAGEMANAGER->findDImage("�������");
	_bageIMG[4] = IMAGEMANAGER->findDImage("������");
	_bageIMG[5] = IMAGEMANAGER->findDImage("�������");
	_bageIMG[6] = IMAGEMANAGER->findDImage("�巡�����");
	_bageIMG[7] = IMAGEMANAGER->findDImage("������");


	_LeaderIMG[0] = IMAGEMANAGER->findDImage("�븻����");
	_LeaderIMG[1] = IMAGEMANAGER->findDImage("������");
	_LeaderIMG[2] = IMAGEMANAGER->findDImage("��������");
	_LeaderIMG[3] = IMAGEMANAGER->findDImage("�������");
	_LeaderIMG[4] = IMAGEMANAGER->findDImage("������");
	_LeaderIMG[5] = IMAGEMANAGER->findDImage("�������");
	_LeaderIMG[6] = IMAGEMANAGER->findDImage("�巡�����");
	_LeaderIMG[7] = IMAGEMANAGER->findDImage("������");

	for (int i = 0; i < 8; i++)
	{
		_LeaderGYM[i] = RectMake((CAMERAMANAGER->getScreen().left + 40) + i * 160, CAMERAMANAGER->getScreen().top + 50, IMAGEMANAGER->findDImage("�븻����")->getWidth(), IMAGEMANAGER->findDImage("�븻����")->getHeight());
	}
	for (int i = 0; i < 8; i++)
	{
		_bageGYM[i] = RectMake((CAMERAMANAGER->getScreen().left + 40) + i * 160, CAMERAMANAGER->getScreen().top + 50, IMAGEMANAGER->findDImage("�븻����")->getWidth(), IMAGEMANAGER->findDImage("�븻����")->getHeight());
	}



	_alpaScreen = IMAGEMANAGER->findDImage("�ƿ�");


	_buttenImg[0] = IMAGEMANAGER->findDImage("���ϸ�");
	_buttenImg[1] = IMAGEMANAGER->findDImage("����");
	_buttenImg[2] = IMAGEMANAGER->findDImage("�κ��丮");
	_buttenImg[3] = IMAGEMANAGER->findDImage("Ʈ���̳�ī��");
	_buttenImg[4] = IMAGEMANAGER->findDImage("�ɼ�");
	_buttenImg[5] = IMAGEMANAGER->findDImage("����");

	for (int i = 0; i < 6; i++)
	{
		_butten[i] = RectMake((CAMERAMANAGER->getScreen().left + 40) + i * 160, CAMERAMANAGER->getScreen().top + 180, IMAGEMANAGER->findDImage("���ϸ�")->getWidth(), IMAGEMANAGER->findDImage("���ϸ�")->getHeight());
	}


	//���ϸ� �κ��丮 �̹���;
	IMAGEMANAGER->addDImage("���ϸ�޴����", L"UI/menu/���ϸ�޴����.png", 1000, 600);
	IMAGEMANAGER->addDImage("�������ϸ�޴�", L"UI/menu/���� ���ϸ�޴�.png", 405, 100);
	IMAGEMANAGER->addDImage("�������ϸ�޴�����", L"UI/menu/���� ���ϸ�޴� ����.png", 405, 100);
	for (int i = 0; i < 6; i++)
	{
		_buttenPokemon[i] = RectMake(CAMERAMANAGER->getScreen().right - 405, (CAMERAMANAGER->getScreen().top +100)+ i * 100, IMAGEMANAGER->findDImage("�������ϸ�޴�")->getWidth(), IMAGEMANAGER->findDImage("�������ϸ�޴�")->getHeight());

		_pokemonInvenIcon[i] = IMAGEMANAGER->findDImage("iconNull");
		_pokemonInvenFront[i] = IMAGEMANAGER->findDImage("iconNull");
		_pokemonInvenBack[i] = IMAGEMANAGER->findDImage("iconNull");
		_pokemonInvenBase[i] = IMAGEMANAGER->findDImage("iconNull");
	}


	for (int i = 0; i < 6; i++)
	{
		_hpBox[i]= IMAGEMANAGER->findDImage("HP�ڽ�");
		_hpBarBacck[i] = IMAGEMANAGER->findDImage("HP�ڽ�Back");
		_hpBar[i] = IMAGEMANAGER->findDImage("HPbar�׸�");
		_LvImg[i] = IMAGEMANAGER->findDImage("Lv�ڽ�");
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
				9, IMAGEMANAGER->findDImage("�ƿ�"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[0]);

		}
		if (count2 > 70)
		{
			_fadeOut[0] -= 0.2f;
			_invenStart = true;
			invenOn();

		}

		RENDERMANAGER->push_BackRenderInfo(
			7, IMAGEMANAGER->findDImage("���ʸ޴�"),
			CAMERAMANAGER->getScreen().left - _leftHendle, CAMERAMANAGER->getScreen().top);
		RENDERMANAGER->push_BackRenderInfo(
			7, IMAGEMANAGER->findDImage("�����ʸ޴�"),
			CAMERAMANAGER->getScreen().right - _rightHendle, CAMERAMANAGER->getScreen().top);
		RENDERMANAGER->push_BackRenderInfo(
			7, IMAGEMANAGER->findDImage("����޴�"),
			CAMERAMANAGER->getScreen().right - 643, CAMERAMANAGER->getScreen().top + 150, 0.5f);
		RENDERMANAGER->push_BackRenderInfo(
			7, IMAGEMANAGER->findDImage("�⺻�޴����"),
			CAMERAMANAGER->getScreen().left - 50, CAMERAMANAGER->getScreen().top + 10, _menuSizeW, _menuSizeH);

	}
	else
	{
		RENDERMANAGER->push_BackRenderInfo(
			6, IMAGEMANAGER->findDImage("�޴�"),
			CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top + _menuWich);
	}
}

void playerUI::menuOff()
{
	if (_invenStart == true)
	{
		_fadeOut[1] += 0.1f;
		RENDERMANAGER->push_BackRenderInfo(
			10, IMAGEMANAGER->findDImage("�ƿ�"),
			CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[1]);
		RENDERMANAGER->push_BackRenderInfo(
			10, IMAGEMANAGER->findDImage("�޴�����"),
			CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top);

	}
	if (_fadeOut[1] > 1.0f)
	{
		_invenStart = false;
		_fadeOut[2] -= 0.05f;
		RENDERMANAGER->push_BackRenderInfo(
			8, IMAGEMANAGER->findDImage("�ƿ�"),
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
			6, IMAGEMANAGER->findDImage("�޴�"),
			CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top + _menuWich);
		if (_menuWich < 600)
		{
			_menuWich += 30;
		}
	}
	else
	{

		RENDERMANAGER->push_BackRenderInfo(
			7, IMAGEMANAGER->findDImage("���ʸ޴�"),
			CAMERAMANAGER->getScreen().left - _leftHendle, CAMERAMANAGER->getScreen().top);
		RENDERMANAGER->push_BackRenderInfo(
			7, IMAGEMANAGER->findDImage("�����ʸ޴�"),
			CAMERAMANAGER->getScreen().right - _rightHendle, CAMERAMANAGER->getScreen().top);
		RENDERMANAGER->push_BackRenderInfo(
			7, IMAGEMANAGER->findDImage("����޴�"),
			CAMERAMANAGER->getScreen().right - 643, CAMERAMANAGER->getScreen().top + 150, 0.5f);
		RENDERMANAGER->push_BackRenderInfo(
			7, IMAGEMANAGER->findDImage("�⺻�޴����"),
			CAMERAMANAGER->getScreen().left - 50, CAMERAMANAGER->getScreen().top + 10, _menuSizeW, _menuSizeH);
	}
}

void playerUI::invenOn()
{
	keyControl();
	RENDERMANAGER->push_BackRenderInfo(
		8, IMAGEMANAGER->findDImage("�޴�����"),
		CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top);
	for (int i = 0; i < 6; i++)
	{
		RENDERMANAGER->push_BackRenderInfo(
			9, _buttenImg[i],
			_butten[i].left, _butten[i].top);
	}

	if (_buttenNum == 0)
	{
		_buttenImg[0] = IMAGEMANAGER->findDImage("���ϸ�_��");
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
				15, IMAGEMANAGER->findDImage("�ƿ�"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[9]);

		}
		if (_fadeOut[9] > 1.0f)
		{
			_Go[2] = false;
			_fadeOut[10] -= 0.1f;
			RENDERMANAGER->push_BackRenderInfo(
				15, IMAGEMANAGER->findDImage("�ƿ�"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[10]);
			_pokemonMenuOn = false;
			_fadeOut[7] = 0;
			_fadeOut[8] = 1.0f;
		}


	}
	else
	{
		_buttenImg[0] = IMAGEMANAGER->findDImage("���ϸ�");
	}
	if (_buttenNum == 1)
	{
		_buttenImg[1] = IMAGEMANAGER->findDImage("����_��");

	}
	else
	{
		_buttenImg[1] = IMAGEMANAGER->findDImage("����");
	}
	if (_buttenNum == 2)
	{
		_buttenImg[2] = IMAGEMANAGER->findDImage("�κ��丮_��");

	}
	else
	{
		_buttenImg[2] = IMAGEMANAGER->findDImage("�κ��丮");
	}
	if (_buttenNum == 3)
	{
		_buttenImg[3] = IMAGEMANAGER->findDImage("Ʈ���̳�ī��_��");
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
				11, IMAGEMANAGER->findDImage("�ƿ�"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[5]);

		}
		if (_fadeOut[5] > 1.0f)
		{
			_Go[1] = false;
			_fadeOut[6] -= 0.1f;
			RENDERMANAGER->push_BackRenderInfo(
				11, IMAGEMANAGER->findDImage("�ƿ�"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[6]);
			_cardOn = false;
			_fadeOut[3] = 0;
			_fadeOut[4] = 1.0f;
		}
	}
	else
	{
		_buttenImg[3] = IMAGEMANAGER->findDImage("Ʈ���̳�ī��");
	}
	if (_buttenNum == 4)
	{
		_buttenImg[4] = IMAGEMANAGER->findDImage("�ɼ�_��");

	}
	else
	{
		_buttenImg[4] = IMAGEMANAGER->findDImage("�ɼ�");
	}
	if (_buttenNum == 5)
	{
		_buttenImg[5] = IMAGEMANAGER->findDImage("����_��");
	}
	else
	{
		_buttenImg[5] = IMAGEMANAGER->findDImage("����");
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
				11, IMAGEMANAGER->findDImage("�ƿ�"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[3]);
		}
		if (_fadeOut[3] > 1.0f)
		{

			_fadeOut[4] -= 0.1f;
			RENDERMANAGER->push_BackRenderInfo(
				11, IMAGEMANAGER->findDImage("�ƿ�"),
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
				10, IMAGEMANAGER->findDImage("�������"),
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
				15, IMAGEMANAGER->findDImage("�ƿ�"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[7]);
		}
		if (_fadeOut[7] > 1.0f)
		{

			_fadeOut[8] -= 0.1f;
			RENDERMANAGER->push_BackRenderInfo(
				15, IMAGEMANAGER->findDImage("�ƿ�"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[8]);
			RENDERMANAGER->push_BackRenderInfo(
				11, IMAGEMANAGER->findDImage("���ϸ�޴����"),
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
		_buttenPokemonImg[0] = IMAGEMANAGER->findDImage("�������ϸ�޴�����");
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
		_buttenPokemonImg[0] = IMAGEMANAGER->findDImage("�������ϸ�޴�");

	}
	if (_buttenPokemonNum == 1)
	{
		_buttenPokemonImg[1] = IMAGEMANAGER->findDImage("�������ϸ�޴�����");
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
		_buttenPokemonImg[1] = IMAGEMANAGER->findDImage("�������ϸ�޴�");
	}
	if (_buttenPokemonNum == 2)
	{
		_buttenPokemonImg[2] = IMAGEMANAGER->findDImage("�������ϸ�޴�����");
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
		_buttenPokemonImg[2] = IMAGEMANAGER->findDImage("�������ϸ�޴�");
	}
	if (_buttenPokemonNum == 3)
	{
		_buttenPokemonImg[3] = IMAGEMANAGER->findDImage("�������ϸ�޴�����");
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
		_buttenPokemonImg[3] = IMAGEMANAGER->findDImage("�������ϸ�޴�");
	}
	if (_buttenPokemonNum == 4)
	{
		_buttenPokemonImg[4] = IMAGEMANAGER->findDImage("�������ϸ�޴�����");
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
		_buttenPokemonImg[4] = IMAGEMANAGER->findDImage("�������ϸ�޴�");
	}
	if (_buttenPokemonNum == 5)
	{
		_buttenPokemonImg[5] = IMAGEMANAGER->findDImage("�������ϸ�޴�����");
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
		_buttenPokemonImg[5] = IMAGEMANAGER->findDImage("�������ϸ�޴�");
	}
}

void playerUI::type1Img(TYPE type1)
{
	if (type1 == NOMRAL)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("�븻");
	}
	if (type1 == FIRE)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("��");
	}
	if (type1 == WATER)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("��");
	}
	if (type1 == LEAF)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("Ǯ");
	}
	if (type1 == ROCK)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("����");
	}
	if (type1 == GROUND)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("��");
	}
	if (type1 == ICE)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("����");
	}
	if (type1 == DARK)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("��");
	}
	if (type1 == ESPER)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("������");
	}
	if (type1 == BUG)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("����");
	}
	if (type1 == ELECTRICITY)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("����");
	}
	if (type1 == METAL)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("��ö");
	}
	if (type1 == COMBAT)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("����");
	}
	if (type1 == GHOST)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("��Ʈ");
	}
	if (type1 == POISON)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("��");
	}
	if (type1 == FLYING)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("����");
	}
	if (type1 == FAIRY)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("��");
	}
	if (type1 == DRAGON)
	{
		_pokemontype1 = IMAGEMANAGER->findDImage("�巡��");
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
		_pokemontype2 = IMAGEMANAGER->findDImage("�븻");
	}
	if (type2 == FIRE)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("��");
	}
	if (type2 == WATER)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("��");
	}
	if (type2 == LEAF)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("Ǯ");
	}
	if (type2 == ROCK)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("����");
	}
	if (type2 == GROUND)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("��");
	}
	if (type2 == ICE)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("����");
	}
	if (type2 == DARK)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("��");
	}
	if (type2 == ESPER)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("������");
	}
	if (type2 == BUG)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("����");
	}
	if (type2 == ELECTRICITY)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("����");
	}
	if (type2 == METAL)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("��ö");
	}
	if (type2 == COMBAT)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("����");
	}
	if (type2 == GHOST)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("��Ʈ");
	}
	if (type2 == POISON)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("��");
	}
	if (type2 == FLYING)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("����");
	}
	if (type2 == FAIRY)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("��");
	}
	if (type2 == DRAGON)
	{
		_pokemontype2 = IMAGEMANAGER->findDImage("�巡��");
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
