#include "stdafx.h"
#include "batter.h"

batter::batter()
{
}

batter::~batter()
{
}

HRESULT batter::init()
{

	imgAll();
	_playerfrontNum = 0;
	_buttenCount = 0;
	 _fadeOut[0] = 0;
	 _fadeOut[1] = 0;
	 _fadeOut[2] = 1.0f;
	 _fadeOut[4] = 1.0f;
	return S_OK;
}

void batter::release()
{
}

void batter::update()
{


	for (int i = 0; i < 4; i++)
	{

		_buttenRc[i] = RectMake(CAMERAMANAGER->getScreen().left - _buttenX[i], (CAMERAMANAGER->getScreen().top) + i * 94, IMAGEMANAGER->findDImage("배틀버튼")->getWidth(), IMAGEMANAGER->findDImage("배틀버튼")->getHeight());
	}

}

void batter::render()
{
	fadeOut();

}

void batter::imgAll()
{
	IMAGEMANAGER->addFrameDImage("플레이어", L"img/base pale.png", 1750, 392,5,1);
	IMAGEMANAGER->addDImage("포켓볼", L"img/ball_00.png", 64, 128);
	IMAGEMANAGER->addDImage("포켓볼오픈", L"img/ball_00_open.png", 64, 128);

	//애니메이션
	IMAGEMANAGER->addFrameDImage("빠밤", L"Animations/003-Attack01.png", 960, 384, 5, 2);


	IMAGEMANAGER->addDImage("잔디배경", L"Battle/battlebgField.png", 1000, 600);
	IMAGEMANAGER->addDImage("숲배경", L"Battle/battlebgForestEve.png", 1000, 600);
	IMAGEMANAGER->addDImage("플레이어 바닥", L"Battle/playerbaseFieldGrass.png", 568, 256);
	IMAGEMANAGER->addDImage("에너미 바닥", L"Battle/enemybaseCity.png", 272, 128);
	IMAGEMANAGER->addDImage("배틀버튼", L"Battle/UI/Battle.png", 158, 94);
	IMAGEMANAGER->addDImage("포켓몬교환버튼", L"Battle/UI/pokemon.png", 158, 94);
	IMAGEMANAGER->addDImage("도망가기버튼", L"Battle/UI/run.png", 158, 94);
	IMAGEMANAGER->addDImage("가방버튼", L"Battle/UI/bag.png", 158, 94);
	_backGround = IMAGEMANAGER->findDImage("잔디배경");
	_butten[0]= IMAGEMANAGER->findDImage("배틀버튼");
	_butten[1] = IMAGEMANAGER->findDImage("포켓몬교환버튼");
	_butten[2] = IMAGEMANAGER->findDImage("도망가기버튼");
	_butten[3] = IMAGEMANAGER->findDImage("가방버튼");
	for (int i = 0; i < 4; i++)
	{
		_buttenX[i] = 140;
		_buttenRc[i] = RectMake(CAMERAMANAGER->getScreen().left - _buttenX[i], (CAMERAMANAGER->getScreen().top+100) + i * 94, IMAGEMANAGER->findDImage("배틀버튼")->getWidth(), IMAGEMANAGER->findDImage("배틀버튼")->getHeight());
	}
	_ball = IMAGEMANAGER->findDImage("포켓볼");
	_hpBox = IMAGEMANAGER->findDImage("HP박스");
	_hpBarBacck = IMAGEMANAGER->findDImage("HP박스Back");
	_hpBar = IMAGEMANAGER->findDImage("HPbar그린");
	_hpBoxE = IMAGEMANAGER->findDImage("HP박스");
	_hpBarBacckE = IMAGEMANAGER->findDImage("HP박스Back");
	_hpBarE = IMAGEMANAGER->findDImage("HPbar그린");
	_LvImg = IMAGEMANAGER->findDImage("Lv박스");
	for (int i = 0; i < 2; i++)
	{
		_buttenPokemon[i] = RectMake(CAMERAMANAGER->getScreen().right - 405, (CAMERAMANAGER->getScreen().top + 100) + i * 100, IMAGEMANAGER->findDImage("보유포켓몬메뉴")->getWidth(), IMAGEMANAGER->findDImage("보유포켓몬메뉴")->getHeight());
		_buttenPokemonImg[i] = IMAGEMANAGER->findDImage("보유포켓몬메뉴");
	}
}

void batter::fadeOut()
{
	_count[0]++;
	if (_count[0] < 50)
	{
		_fadeOut[0] += 0.2f;
		RENDERMANAGER->push_BackRenderInfo(
			40, IMAGEMANAGER->findDImage("아웃"),
			CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[0]);

		if (_fadeOut[0] >= 1.0f)
		{
			_fadeOut[0] = 0;;
		}
	}
	if (_count[0] > 50)
	{
		_fadeOut[1] += 0.1f;
		if (_fadeOut[1] < 1.0f)
		{
			RENDERMANAGER->push_BackRenderInfo(
				40, IMAGEMANAGER->findDImage("아웃"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[1]);
		}
		if (_fadeOut[1] >= 1.0f)
		{
			_fadeOut[2] -= 0.1f;
			RENDERMANAGER->push_BackRenderInfo(
				40, IMAGEMANAGER->findDImage("아웃"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[2]);

			_count[1]++;
			if (_count[1] % 3 ==0)
			{
				if (IMAGEMANAGER->findDImage("몬스터나오기")->getMaxFrameX() > _frameX[0])
				{
					if (_fadeOut[2] < 0)  _frameX[0]++;
				}
			}

			RENDERMANAGER->push_BackFrameRenderInfo(
				30, IMAGEMANAGER->findDImage("몬스터나오기"),
				CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _frameX[0], 0);
			if (IMAGEMANAGER->findDImage("몬스터나오기")->getMaxFrameX() <= _frameX[0])
			{

				if (_fadeOut[3] <= 1.0f)
				{
					_fadeOut[3] += 0.1f;
					RENDERMANAGER->push_BackRenderInfo(
						40, IMAGEMANAGER->findDImage("아웃"),
						CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[3]);
				}
				if (_fadeOut[3] >= 1.0f)
				{
					_count[2]++;
					_fadeOut[4] -= 0.1f;
					RENDERMANAGER->push_BackRenderInfo(
						40, IMAGEMANAGER->findDImage("아웃"),
						CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, _fadeOut[4]);
					RENDERMANAGER->push_BackFrameRenderInfoSizeUp(
						33, _pokemonInvenFront[1],
						CAMERAMANAGER->getScreen().right - 280, CAMERAMANAGER->getScreen().top + 150, 0, 0, 3);
					RENDERMANAGER->push_BackRenderInfo(
						31, _backGround,
						CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top);
					RENDERMANAGER->push_BackRenderInfo(
						32, IMAGEMANAGER->findDImage("플레이어 바닥"),
						CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top+430);
					RENDERMANAGER->push_BackRenderInfo(
						32, IMAGEMANAGER->findDImage("에너미 바닥"),
						CAMERAMANAGER->getScreen().right-350, CAMERAMANAGER->getScreen().top + 200);
					RENDERMANAGER->push_BackFrameRenderInfo(
						33, IMAGEMANAGER->findDImage("플레이어"),
						CAMERAMANAGER->getScreen().left+50 - _playerX, CAMERAMANAGER->getScreen().top + 220, _playerfrontNum,0);
					//적 hp바
					RENDERMANAGER->push_BackRenderInfo(
						34, _hpBoxE,
						CAMERAMANAGER->getScreen().right -360, CAMERAMANAGER->getScreen().top + 100);
					RENDERMANAGER->push_BackRenderInfo(
						34, _hpBarE,
						CAMERAMANAGER->getScreen().right - 300, CAMERAMANAGER->getScreen().top + 100, (float)_pokemonInvenNameHp[1] / (float)_pokemonInvenNameMaxHp[1] * 208, 16);
					RENDERMANAGER->push_BackRenderInfo(
						34, _hpBarBacckE,
						CAMERAMANAGER->getScreen().right - 300, CAMERAMANAGER->getScreen().top + 100);
					TXTRENDERMANGER->push_BackRenderInfo(1, L"이상해씨", CAMERAMANAGER->getScreen().right - 300,
						CAMERAMANAGER->getScreen().top + 60, 34);
					for (int i = 0; i < 4; i++)
					{
						RENDERMANAGER->push_BackRenderInfo(
							33, _butten[i],
							_buttenRc[i].left, _buttenRc[i].top);

					}
					if (_count[2] > 100)
					{
						_count[3]++;
						if (_count[3] % 10 == 0)
						{
							if (_playerfrontNum <= 3)_playerfrontNum++;
						}

					}
					if (IMAGEMANAGER->findDImage("플레이어")->getMaxFrameX() <= _playerfrontNum)
					{
						if(_playerX < 500)_playerX+=5;
						_ballAngle+=10;
						if (_ballY < 100)
						{
							_ballY++;
							RENDERMANAGER->push_BackFrameRenderRoteshionInfo(
								40, _ball,
								CAMERAMANAGER->getScreen().left + 300, CAMERAMANAGER->getScreen().top + 400 - _ballY, _ballAngle, -800);
						}
						else
						{

							_count[4]++;
							if (_count[4] % 4 == 0)
							{
								_ball = IMAGEMANAGER->findDImage("포켓볼오픈");
								if (_frameX[1] < 5)_frameX[1]++;
							}
							if(_frameX[1] > 4)
							{
								_ball = IMAGEMANAGER->findDImage("iconNull");
								RENDERMANAGER->push_BackFrameRenderInfoSizeUp(
								33, _pokemonInvenBack[0],
								CAMERAMANAGER->getScreen().left + 200, CAMERAMANAGER->getScreen().top + 500 - _ballY, 0, 0, 4);
							}
							RENDERMANAGER->push_BackFrameRenderInfoSizeUp(
								33, IMAGEMANAGER->findDImage("빠밤"),
								CAMERAMANAGER->getScreen().left + 40, CAMERAMANAGER->getScreen().top+100, _frameX[1], 0, 3);

							RENDERMANAGER->push_BackRenderInfo(
								33, _ball,
								CAMERAMANAGER->getScreen().left + 300, CAMERAMANAGER->getScreen().top + 400 - _ballY);
							RENDERMANAGER->push_BackRenderInfo(
								34, _hpBox,
								CAMERAMANAGER->getScreen().left , CAMERAMANAGER->getScreen().top + 390);
							RENDERMANAGER->push_BackRenderInfo(
								34, _hpBar,
								CAMERAMANAGER->getScreen().left + 60, CAMERAMANAGER->getScreen().top + 390, (float)_pokemonInvenNameHp[0] / (float)_pokemonInvenNameMaxHp[0] * 208, 16);
							RENDERMANAGER->push_BackRenderInfo(
								34, _hpBarBacck,
								CAMERAMANAGER->getScreen().left + 60, CAMERAMANAGER->getScreen().top + 390);
							TXTRENDERMANGER->push_BackRenderInfo(1, L"이상해씨", CAMERAMANAGER->getScreen().left + 50,
								CAMERAMANAGER->getScreen().top + 350, 34);

							for (int i = 0; i < 2; i++)
							{
								RENDERMANAGER->push_BackRenderInfo(
									36, _buttenPokemonImg[i],
									_buttenPokemon[i].left, _buttenPokemon[i].top +400);
							}
							TXTRENDERMANGER->push_BackRenderInfo(1, L"몸통박치기", CAMERAMANAGER->getScreen().right- 380,
								CAMERAMANAGER->getScreen().top + 420, 34);
							TXTRENDERMANGER->push_BackRenderInfo(1, L"전광석화", CAMERAMANAGER->getScreen().right - 380,
								CAMERAMANAGER->getScreen().top + 520, 34);


						}

					}

					keyButten();
					buttenUpdtae();

				}
			}


			
		}
	}
}

void batter::buttenUpdtae()
{
	if (_buttenCount == 0)
	{
		
		if (_buttenX[0] <= 0)
		{

		}
		else
		{
			_buttenX[0] -= 10;
		}
	}
	else
	{
		_buttenX[0] = 140;
	}
	if (_buttenCount == 1)
	{

		if (_buttenX[1] <= 0)
		{

		}
		else
		{
			_buttenX[1] -= 10;
		}
	}
	else
	{
		_buttenX[1] = 140;
	}
	if (_buttenCount == 2)
	{

		if (_buttenX[2] <= 0)
		{

		}
		else
		{
			_buttenX[2] -= 10;
		}
	}
	else
	{
		_buttenX[2] = 140;
	}
	if (_buttenCount == 3)
	{

		if (_buttenX[3] <= 0)
		{

		}
		else
		{
			_buttenX[3] -= 10;
		}
	}
	else
	{
		_buttenX[3] = 140;
	}
	if (_buttenCount > 3)
	{
		_buttenCount = 0;
	}
	if (_buttenCount < 0)
	{
		_buttenCount = 3;
	}
}

void batter::keyButten()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		//_buttenX[0]++;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_buttenCount--;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_buttenCount++;
	}
}

void batter::pokemonInven1all(int max, dImage * pokemon, dImage * inven, dImage * front, dImage * back, wstring name, TYPE type1, TYPE type2, PERSONA persona, int Lv, int exp, bool sex, int MaxHp, int hp, int atk, int def, int matk, int mdef, int spd)
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

void batter::pokemoSkill(int max, dImage * skill1, dImage * skill2)
{
	_skillImg[0] = skill1;
	_skillImg[1] = skill2;


}
