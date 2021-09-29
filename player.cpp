#include "stdafx.h"
#include "player.h"

HRESULT player::init(const char* _fileName ,float x ,float y)
{
	//_pokemon = new APokemonBase;
	//_pokemon->init();
	_pokemonInventory = new pokemonManger;
	_pokemonInventory->init();
	_tile = new tileClass;
	_tile->init();
	CAMERAMANAGER->setBackScreenSize(1600, 1600);
	IMAGEMANAGER->addFrameDImage("walk", L"img/walk.png", 256, 256, 4, 4);
	IMAGEMANAGER->addFrameDImage("run", L"img/run.png", 256, 256, 4, 4);
	_tile->mapLoad(_fileName);
	_playerX = x;
	_playerY = y;
	_playerRect = RectMakeCenter(_playerX, _playerY, IMAGEMANAGER->findDImage("walk")->getFrameHeight(), IMAGEMANAGER->findDImage("walk")->getFrameWidth());
	_playerOrgin = RectMakeCenter(_playerRectX, _playerRect.bottom, 32, 32);
	_player = IMAGEMANAGER->findDImage("walk");
	_playerRectX = (_playerRect.left + _playerRect.right) / 2;
	_playerRectY = (_playerRect.bottom + _playerRect.top) / 2;
	_playerState = PLAYER_IDLE;


	PLAYERUI->init();
	BATTERGO->init();
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	if (_playerUIOn == false && _battelOn == false)
	{
		keycontrol();
		updtaeFrame();
	}
	_playerRectX = (_playerRect.left + _playerRect.right) / 2;
	_playerRectY = (_playerRect.top + _playerRect.bottom) / 2;
	_playerRect = RectMakeCenter(_playerX, _playerY, IMAGEMANAGER->findDImage("walk")->getFrameHeight(), IMAGEMANAGER->findDImage("walk")->getFrameWidth());
	_playerOrgin = RectMakeCenter(_playerRectX, _playerRect.bottom - 20, 28, 28);

	rectCollison();
	CAMERAMANAGER->updateScreen(_playerX, _playerY);
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		_vPokemon.push_back(_pokemonInventory->GetPokemon(L"이상해꽃"));
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_vPokemon.push_back(_pokemonInventory->GetPokemon(L"이상해풀"));
	}
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_vPokemon.push_back(_pokemonInventory->GetPokemon(L"이상해씨"));
	}
	if (KEYMANAGER->isToggleKey(VK_RETURN))
	{
		_playerUIOn = true;
	}
	else
	{
		_playerUIOn = false;
	}
	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		_vPokemon[0]->damgeHP(3);
	}
	if (_playerUIOn)
	{
		for (int i = 0; i < _vPokemon.size(); i++)
		{
			PLAYERUI->pokemonInven1all(i, _vPokemon[i]->getIconImg(), _vPokemon[i]->getInvenImg(), _vPokemon[i]->getFront(), _vPokemon[i]->getBack(), _vPokemon[i]->getName(), _vPokemon[i]->getType1(), _vPokemon[i]->getType2(),
				_vPokemon[i]->getPersona(), _vPokemon[i]->getLV(), _vPokemon[i]->getExp(), _vPokemon[i]->getSex(), _vPokemon[i]->getMaxHp(), _vPokemon[i]->getHP(), _vPokemon[i]->getAtk(),
				_vPokemon[i]->getDef(), _vPokemon[i]->getMatk(), _vPokemon[i]->getMdef(), _vPokemon[i]->getSpd());


		}



		PLAYERUI->update();

	}
	if (_battelOn == true)
	{
		for (int i = 0; i < _vPokemon.size(); i++)
		{
			BATTERGO->pokemonInven1all(i, _vPokemon[i]->getIconImg(), _vPokemon[i]->getInvenImg(), _vPokemon[i]->getFront(), _vPokemon[i]->getBack(), _vPokemon[i]->getName(), _vPokemon[i]->getType1(), _vPokemon[i]->getType2(),
				_vPokemon[i]->getPersona(), _vPokemon[i]->getLV(), _vPokemon[i]->getExp(), _vPokemon[i]->getSex(), _vPokemon[i]->getMaxHp(), _vPokemon[i]->getHP(), _vPokemon[i]->getAtk(),
				_vPokemon[i]->getDef(), _vPokemon[i]->getMatk(), _vPokemon[i]->getMdef(), _vPokemon[i]->getSpd());
		//	BATTERGO->pokemoSkill(1, _vPokemon[0]->getVSkill()[0]->getskillImg(), _vPokemon[0]->getVSkill()[1]->getskillImg());
		}
		BATTERGO->update();
	}
}
void player::render()
{

	//_player->frameRender(_playerRect.left, _playerRect.top, _playerIndexCountX, _playerIndexCountY);
	//for (int i = 0; i < 2; i++)
	//{
	//	D2DMANAGER->Rectangle(_tile->getTileAll()[tileIndex[i]].rc);
	//}
	//D2DMANAGER->Rectangle(_rcCollision);
	RENDERMANAGER->push_BackFrameRenderInfo(1, _player, _playerRect.left, _playerRect.top, _playerIndexCountX, _playerIndexCountY);


	if (_battelOn == true)
	{
		BATTERGO->render();
	}
	if (KEYMANAGER->isToggleKey('0'))
	{
		_battelOn = true;
	}
	else
	{
		_battelOn = false;
	}
		PLAYERUI->render();
	
}

void player::updtaeFrame()
{
	_playerFrameCount++;
	if (_playerFrameCount % 5 == 0)
	{
		if (_playerState == PLAYER_IDLE)
		{
			_player = IMAGEMANAGER->findDImage("walk");
			_playerIndexCountX = 0;
			_playerIndexCountY = 0;

		}
		if (_playerState == PLAYER_BACKIDLE)
		{
			_player = IMAGEMANAGER->findDImage("walk");
			_playerIndexCountX = 0;
			_playerIndexCountY = 3;

		}
		if (_playerState == PLAYER_LEFTIDLE)
		{
			_player = IMAGEMANAGER->findDImage("walk");
			_playerIndexCountX = 0;
			_playerIndexCountY = 2;

		}
		if (_playerState == PLAYER_RIGHTIDLE)
		{
			_player = IMAGEMANAGER->findDImage("walk");
			_playerIndexCountX = 0;
			_playerIndexCountY = 1;

		}
		if (_playerState == PLAYER_RIGHT)
		{
			_player = IMAGEMANAGER->findDImage("walk");
			_playerIndexCountX++;
			_playerIndexCountY = 2;
			_player->setFrameX(_playerIndexCountX);
			_player->setFrameY(_playerIndexCountY);

			if (_playerIndexCountX >= 4)
			{
				_playerIndexCountX = 0;
			}

		}
		if (_playerState == PLAYER_LEFT)
		{
			_player = IMAGEMANAGER->findDImage("walk");
			_playerIndexCountX++;
			_playerIndexCountY = 1;
			_player->setFrameX(_playerIndexCountX);
			_player->setFrameY(_playerIndexCountY);

			if (_playerIndexCountX >= 4)
			{
				_playerIndexCountX = 0;
			}

		}
		if (_playerState == PLAYER_BOTTOM)
		{
			_player = IMAGEMANAGER->findDImage("walk");
			_playerIndexCountX++;
			_playerIndexCountY = 0;
			_player->setFrameX(_playerIndexCountX);
			_player->setFrameY(_playerIndexCountY);

			if (_playerIndexCountX > 3)
			{
				_playerIndexCountX = 0;
			}

		}
		if (_playerState == PLAYER_TOP)
		{
			_player = IMAGEMANAGER->findDImage("walk");
			_playerIndexCountX++;
			_playerIndexCountY = 3;
			_player->setFrameX(_playerIndexCountX);
			_player->setFrameY(_playerIndexCountY);

			if (_playerIndexCountX >= 4)
			{
				_playerIndexCountX = 0;
			}

		}

		if (_playerState == PLAYER_RUNRIGHT)
		{
			_player = IMAGEMANAGER->findDImage("run");
			_playerIndexCountX++;
			_playerIndexCountY = 2;
			_player->setFrameX(_playerIndexCountX);
			_player->setFrameY(_playerIndexCountY);

			if (_playerIndexCountX >= 4)
			{
				_playerIndexCountX = 0;
			}

		}
		if (_playerState == PLAYER_RUNLEFT)
		{
			_player = IMAGEMANAGER->findDImage("run");
			_playerIndexCountX++;
			_playerIndexCountY = 1;
			_player->setFrameX(_playerIndexCountX);
			_player->setFrameY(_playerIndexCountY);

			if (_playerIndexCountX >= 4)
			{
				_playerIndexCountX = 0;
			}

		}
		if (_playerState == PLAYER_RUNBOTTOM)
		{
			_player = IMAGEMANAGER->findDImage("run");
			_playerIndexCountX++;
			_playerIndexCountY = 0;
			_player->setFrameX(_playerIndexCountX);
			_player->setFrameY(_playerIndexCountY);

			if (_playerIndexCountX > 3)
			{
				_playerIndexCountX = 0;
			}

		}
		if (_playerState == PLAYER_RUNTOP)
		{
			_player = IMAGEMANAGER->findDImage("run");
			_playerIndexCountX++;
			_playerIndexCountY = 3;
			_player->setFrameX(_playerIndexCountX);
			_player->setFrameY(_playerIndexCountY);

			if (_playerIndexCountX >= 4)
			{
				_playerIndexCountX = 0;
			}

		}
		_playerFrameCount = 0;
	}


}

void player::keycontrol()
{
	if (_RightSwich == false && _topSwich == false && _bottomSwich == false)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_leftSwich = true;
			_playerX -= 5;

			_playerState = PLAYER_LEFT;
			if (KEYMANAGER->isStayKeyDown('Z'))
			{
				_playerState = PLAYER_RUNLEFT;
				_playerX -= 5;
			}
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_playerState = PLAYER_RIGHTIDLE;
		_leftSwich = false;
	}
	if (_topSwich == false && _leftSwich == false && _bottomSwich == false)
	{
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_RightSwich = true;
			_playerX += 5;
			_playerState = PLAYER_RIGHT;
			if (KEYMANAGER->isStayKeyDown('Z'))
			{
				_playerState = PLAYER_RUNRIGHT;
				_playerX += 5;
			}
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_playerState = PLAYER_LEFTIDLE;
		_RightSwich = false;
	}
	if (_RightSwich == false && _leftSwich == false && _bottomSwich == false)
	{

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_topSwich = true;
			_playerY -= 5;
			_playerState = PLAYER_TOP;
			if (KEYMANAGER->isStayKeyDown('Z'))
			{
				_playerState = PLAYER_RUNTOP;
				_playerY -= 5;
			}
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		_topSwich = false;
		_playerState = PLAYER_BACKIDLE;
	}

	if (_RightSwich == false && _leftSwich == false && _topSwich == false)
	{
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_bottomSwich = true;
			_playerY += 5;
			_playerState = PLAYER_BOTTOM;
			if (KEYMANAGER->isStayKeyDown('Z'))
			{
				_playerState = PLAYER_RUNBOTTOM;
				_playerY += 5;
			}
		}

	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		_bottomSwich = false;
		_playerState = PLAYER_IDLE;
	}
}

void player::rectCollison()
{
	RECT temp;
	_rcCollision = _playerOrgin;
	_rcCollision.left += 2;
	_rcCollision.top += 2;
	_rcCollision.right -= 2;
	_rcCollision.bottom -= 2;
	_tileX = _rcCollision.left / TILESIZE;
	_tileY = _rcCollision.top / TILESIZE;
	switch (_playerState)
	{
	case PLAYER_LEFT:
		tileIndex[0] = _tileX + (_tileY * TILEX);
		tileIndex[1] = _tileX + (_tileY + 1) * TILEX;
		break;
	case PLAYER_TOP:
		tileIndex[0] = _tileX + _tileY * TILEX;
		tileIndex[1] = (_tileX + 1) + _tileY * TILEX;
		break;
	case PLAYER_RIGHT:
		tileIndex[0] = (_tileX + _tileY * TILEX) + 1;
		tileIndex[1] = (_tileX + (_tileY + 1) * TILEX) + 1;
		break;
	case PLAYER_BOTTOM:
		tileIndex[0] = (_tileX + _tileY * TILEX) + TILEX;
		tileIndex[1] = (_tileX + 1 + _tileY * TILEX) + TILEX;
		break;

	case PLAYER_RUNLEFT:
		tileIndex[0] = _tileX + (_tileY * TILEX);
		tileIndex[1] = _tileX + (_tileY + 1) * TILEX;
		break;
	case PLAYER_RUNTOP:
		tileIndex[0] = _tileX + _tileY * TILEX;
		tileIndex[1] = (_tileX + 1) + _tileY * TILEX;
		break;
	case PLAYER_RUNRIGHT:
		tileIndex[0] = (_tileX + _tileY * TILEX) + 1;
		tileIndex[1] = (_tileX + (_tileY + 1) * TILEX) + 1;
		break;
	case PLAYER_RUNBOTTOM:
		tileIndex[0] = (_tileX + _tileY * TILEX) + TILEX;
		tileIndex[1] = (_tileX + 1 + _tileY * TILEX) + TILEX;
		break;

	}
	//지형 속성================================================================================================================================================
	for (int i = 0; i <2; ++i)
	{

		if (IntersectRect(&temp, &_tile->getTileAll()[tileIndex[i]].rc, &_rcCollision) && (_tile->getTileAll()[tileIndex[i]].terrain & TR_UNMOVE) == TR_UNMOVE)
		{



			
			switch (_playerState)
			{
			case PLAYER_LEFT:
				_playerOrgin.left = _tile->getTileAll()[tileIndex[i]].rc.right;
				_playerOrgin.right = _playerOrgin.left + 32;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_TOP:
				_playerOrgin.top = _tile->getTileAll()[tileIndex[i]].rc.bottom;
				_playerOrgin.bottom = _playerOrgin.top + 5;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;

				break;
			case PLAYER_RIGHT:
				_playerOrgin.right = _tile->getTileAll()[tileIndex[i]].rc.left;
				_playerOrgin.left = _playerOrgin.right - 32;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_BOTTOM:
				_playerOrgin.bottom = _tile->getTileAll()[tileIndex[i]].rc.top;
				_playerOrgin.top = _playerOrgin.bottom - 50;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;
				break;
			case PLAYER_RUNLEFT:
				_playerOrgin.left = _tile->getTileAll()[tileIndex[i]].rc.right;
				_playerOrgin.right = _playerOrgin.left + 35;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_RUNTOP:
				_playerOrgin.top = _tile->getTileAll()[tileIndex[i]].rc.bottom;
				_playerOrgin.bottom = _playerOrgin.top + 10;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;

				break;
			case PLAYER_RUNRIGHT:
				_playerOrgin.right = _tile->getTileAll()[tileIndex[i]].rc.left;
				_playerOrgin.left = _playerOrgin.right - 35;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_RUNBOTTOM:
				_playerOrgin.bottom = _tile->getTileAll()[tileIndex[i]].rc.top;
				_playerOrgin.top = _playerOrgin.bottom - 64;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;
				break;

			}
				
		}
		
	}
	for (int i = 0; i < 2; ++i)
	{

		if (IntersectRect(&temp, &_tile->getTileAll()[tileIndex[i]].rc, &_rcCollision) && (_tile->getTileAll()[tileIndex[i]].terrain & TR_WATER) == TR_WATER)
		{



			switch (_playerState)
			{
			case PLAYER_LEFT:
				_playerOrgin.left = _tile->getTileAll()[tileIndex[i]].rc.right;
				_playerOrgin.right = _playerOrgin.left + 32;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_TOP:
				_playerOrgin.top = _tile->getTileAll()[tileIndex[i]].rc.bottom;
				_playerOrgin.bottom = _playerOrgin.top + 5;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;

				break;
			case PLAYER_RIGHT:
				_playerOrgin.right = _tile->getTileAll()[tileIndex[i]].rc.left;
				_playerOrgin.left = _playerOrgin.right - 32;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_BOTTOM:
				_playerOrgin.bottom = _tile->getTileAll()[tileIndex[i]].rc.top;
				_playerOrgin.top = _playerOrgin.bottom - 50;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;
				break;
			case PLAYER_RUNLEFT:
				_playerOrgin.left = _tile->getTileAll()[tileIndex[i]].rc.right;
				_playerOrgin.right = _playerOrgin.left + 35;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_RUNTOP:
				_playerOrgin.top = _tile->getTileAll()[tileIndex[i]].rc.bottom;
				_playerOrgin.bottom = _playerOrgin.top + 10;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;

				break;
			case PLAYER_RUNRIGHT:
				_playerOrgin.right = _tile->getTileAll()[tileIndex[i]].rc.left;
				_playerOrgin.left = _playerOrgin.right - 35;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_RUNBOTTOM:
				_playerOrgin.bottom = _tile->getTileAll()[tileIndex[i]].rc.top;
				_playerOrgin.top = _playerOrgin.bottom - 64;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;
				break;

			}

		}

	}
	//언덕 속성================================================================================================================================================
	for (int i = 0; i < 2; ++i)
	{

		if (IntersectRect(&temp, &_tile->getTileAll()[tileIndex[i]].rc, &_rcCollision) && (_tile->getTileAll()[tileIndex[i]].terrain2 & TR2_UNMOVE) == TR2_UNMOVE)
		{




			switch (_playerState)
			{
			case PLAYER_LEFT:
				_playerOrgin.left = _tile->getTileAll()[tileIndex[i]].rc.right;
				_playerOrgin.right = _playerOrgin.left + 32;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_TOP:
				_playerOrgin.top = _tile->getTileAll()[tileIndex[i]].rc.bottom;
				_playerOrgin.bottom = _playerOrgin.top + 5;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;

				break;
			case PLAYER_RIGHT:
				_playerOrgin.right = _tile->getTileAll()[tileIndex[i]].rc.left;
				_playerOrgin.left = _playerOrgin.right - 32;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_BOTTOM:
				_playerOrgin.bottom = _tile->getTileAll()[tileIndex[i]].rc.top;
				_playerOrgin.top = _playerOrgin.bottom - 50;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;
				break;
			case PLAYER_RUNLEFT:
				_playerOrgin.left = _tile->getTileAll()[tileIndex[i]].rc.right;
				_playerOrgin.right = _playerOrgin.left + 35;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_RUNTOP:
				_playerOrgin.top = _tile->getTileAll()[tileIndex[i]].rc.bottom;
				_playerOrgin.bottom = _playerOrgin.top + 10;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;

				break;
			case PLAYER_RUNRIGHT:
				_playerOrgin.right = _tile->getTileAll()[tileIndex[i]].rc.left;
				_playerOrgin.left = _playerOrgin.right - 35;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_RUNBOTTOM:
				_playerOrgin.bottom = _tile->getTileAll()[tileIndex[i]].rc.top;
				_playerOrgin.top = _playerOrgin.bottom - 64;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;
				break;

			}

		}

	}
	for (int i = 0; i < 2; ++i)
	{

		if (IntersectRect(&temp, &_tile->getTileAll()[tileIndex[i]].rc, &_rcCollision) && (_tile->getTileAll()[tileIndex[i]].terrain2 & TR2_WATER) == TR2_WATER)
		{




			switch (_playerState)
			{
			case PLAYER_LEFT:
				_playerOrgin.left = _tile->getTileAll()[tileIndex[i]].rc.right;
				_playerOrgin.right = _playerOrgin.left + 32;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_TOP:
				_playerOrgin.top = _tile->getTileAll()[tileIndex[i]].rc.bottom;
				_playerOrgin.bottom = _playerOrgin.top + 5;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;

				break;
			case PLAYER_RIGHT:
				_playerOrgin.right = _tile->getTileAll()[tileIndex[i]].rc.left;
				_playerOrgin.left = _playerOrgin.right - 32;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_BOTTOM:
				_playerOrgin.bottom = _tile->getTileAll()[tileIndex[i]].rc.top;
				_playerOrgin.top = _playerOrgin.bottom - 50;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;
				break;
			case PLAYER_RUNLEFT:
				_playerOrgin.left = _tile->getTileAll()[tileIndex[i]].rc.right;
				_playerOrgin.right = _playerOrgin.left + 35;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_RUNTOP:
				_playerOrgin.top = _tile->getTileAll()[tileIndex[i]].rc.bottom;
				_playerOrgin.bottom = _playerOrgin.top + 10;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;

				break;
			case PLAYER_RUNRIGHT:
				_playerOrgin.right = _tile->getTileAll()[tileIndex[i]].rc.left;
				_playerOrgin.left = _playerOrgin.right - 35;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_RUNBOTTOM:
				_playerOrgin.bottom = _tile->getTileAll()[tileIndex[i]].rc.top;
				_playerOrgin.top = _playerOrgin.bottom - 64;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;
				break;

			}

		}

	}
	//건축물 속성================================================================================================================================================
	for (int i = 0; i < 2; ++i)
	{

		if (IntersectRect(&temp, &_tile->getTileAll()[tileIndex[i]].rc, &_rcCollision) && (_tile->getTileAll()[tileIndex[i]].build & BU_UNMOVE) == BU_UNMOVE)
		{




			switch (_playerState)
			{
			case PLAYER_LEFT:
				_playerOrgin.left = _tile->getTileAll()[tileIndex[i]].rc.right;
				_playerOrgin.right = _playerOrgin.left + 32;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_TOP:
				_playerOrgin.top = _tile->getTileAll()[tileIndex[i]].rc.bottom;
				_playerOrgin.bottom = _playerOrgin.top + 5;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;

				break;
			case PLAYER_RIGHT:
				_playerOrgin.right = _tile->getTileAll()[tileIndex[i]].rc.left;
				_playerOrgin.left = _playerOrgin.right - 32;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_BOTTOM:
				_playerOrgin.bottom = _tile->getTileAll()[tileIndex[i]].rc.top;
				_playerOrgin.top = _playerOrgin.bottom - 50;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;
				break;
			case PLAYER_RUNLEFT:
				_playerOrgin.left = _tile->getTileAll()[tileIndex[i]].rc.right;
				_playerOrgin.right = _playerOrgin.left + 35;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_RUNTOP:
				_playerOrgin.top = _tile->getTileAll()[tileIndex[i]].rc.bottom;
				_playerOrgin.bottom = _playerOrgin.top + 10;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;

				break;
			case PLAYER_RUNRIGHT:
				_playerOrgin.right = _tile->getTileAll()[tileIndex[i]].rc.left;
				_playerOrgin.left = _playerOrgin.right - 35;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_RUNBOTTOM:
				_playerOrgin.bottom = _tile->getTileAll()[tileIndex[i]].rc.top;
				_playerOrgin.top = _playerOrgin.bottom - 64;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;
				break;

			}

		}

	}
	//오브젝트 속성================================================================================================================================================
	for (int i = 0; i < 2; ++i)
	{

		if (IntersectRect(&temp, &_tile->getTileAll()[tileIndex[i]].rc, &_rcCollision) && _tile->getTileAll()[tileIndex[i]].obj  == OBJ_UNMOVE)
		{




			switch (_playerState)
			{
			case PLAYER_LEFT:
				_playerOrgin.left = _tile->getTileAll()[tileIndex[i]].rc.right;
				_playerOrgin.right = _playerOrgin.left + 32;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_TOP:
				_playerOrgin.top = _tile->getTileAll()[tileIndex[i]].rc.bottom;
				_playerOrgin.bottom = _playerOrgin.top + 5;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;

				break;
			case PLAYER_RIGHT:
				_playerOrgin.right = _tile->getTileAll()[tileIndex[i]].rc.left;
				_playerOrgin.left = _playerOrgin.right - 32;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_BOTTOM:
				_playerOrgin.bottom = _tile->getTileAll()[tileIndex[i]].rc.top;
				_playerOrgin.top = _playerOrgin.bottom - 50;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;
				break;
			case PLAYER_RUNLEFT:
				_playerOrgin.left = _tile->getTileAll()[tileIndex[i]].rc.right;
				_playerOrgin.right = _playerOrgin.left + 35;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_RUNTOP:
				_playerOrgin.top = _tile->getTileAll()[tileIndex[i]].rc.bottom;
				_playerOrgin.bottom = _playerOrgin.top + 10;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;

				break;
			case PLAYER_RUNRIGHT:
				_playerOrgin.right = _tile->getTileAll()[tileIndex[i]].rc.left;
				_playerOrgin.left = _playerOrgin.right - 35;

				_playerX = (_playerOrgin.left + _playerOrgin.right) / 2;
				break;
			case PLAYER_RUNBOTTOM:
				_playerOrgin.bottom = _tile->getTileAll()[tileIndex[i]].rc.top;
				_playerOrgin.top = _playerOrgin.bottom - 64;

				_playerY = (_playerOrgin.top + _playerOrgin.bottom) / 2;
				break;

			}

		}

	}

	for (int i = 0; i < 2; ++i)
	{

		if (IntersectRect(&temp, &_tile->getTileAll()[tileIndex[i]].rc, &_rcCollision) && _tile->getTileAll()[tileIndex[i]].obj  == OBJ_MOSTER)
		{
			_countBattle = RND->getInt(100);



			switch (_playerState)
			{
			case PLAYER_LEFT:

				if (_countBattle == 5)
				{
					_battelOn = true;
				}



				break;
			case PLAYER_TOP:

				if (_countBattle == 5)
				{
					_battelOn = true;
				}
				break;
			case PLAYER_RIGHT:
				if (_countBattle == 5)
				{
					_battelOn = true;
				}


				break;
			case PLAYER_BOTTOM:
				if (_countBattle == 5)
				{
					_battelOn = true;
				}
				break;
			case PLAYER_RUNLEFT:
				if (_countBattle == 5)
				{
					_battelOn = true;
				}
				break;
			case PLAYER_RUNTOP:
				if (_countBattle == 5)
				{
					_battelOn = true;
				}

				break;
			case PLAYER_RUNRIGHT:
				if (_countBattle == 5)
				{
					_battelOn = true;
				}
				break;
			case PLAYER_RUNBOTTOM:
				if (_countBattle == 5)
				{
					_battelOn = true;
				}
				break;

			}

		}

	}






	_rcCollision = RectMakeCenter(_playerX, _playerY + 20, 25, 25);

}
