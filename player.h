#pragma once
#include "gameNode.h"
#include "tileClass.h"
#include "APokemonBase.h"
#include "pokemonManger.h"
#include <vector>

enum playerstat
{
	PLAYER_IDLE,
	PLAYER_LEFTIDLE,
	PLAYER_RIGHTIDLE,
	PLAYER_LEFT,
	PLAYER_RIGHT,
	PLAYER_TOP,
	PLAYER_BOTTOM,
	PLAYER_BACKIDLE,
	PLAYER_RUNLEFT,
	PLAYER_RUNRIGHT,
	PLAYER_RUNTOP,
	PLAYER_RUNBOTTOM
};



class player : public gameNode
{

private:
	vector<APokemonBase*>				_vPokemon;
	vector<APokemonBase*>::iterator		_viPokemon;


	tileClass* _tile;
	//APokemonBase* _pokemon;
	pokemonManger* _pokemonInventory;

	bool _moveSwich;
	dImage* _player;
	playerstat _playerState;
	RECT	_playerRect;
	RECT	_playerOrgin;
	RECT	_rcCollision;
	int tileIndex[2];
	int _tileX, _tileY;
	float _playerX, _playerY;
	float _playerRectX, _playerRectY;

	int _playerFrameCount;
	int _playerIndexCountX;
	int _playerIndexCountY;

	bool _playerUIOn;
	bool _leftSwich;
	bool _RightSwich;
	bool _topSwich;
	bool _bottomSwich;

	//น่ฦฒ
	bool _battelOn;
	int _countBattle;
public:

	virtual HRESULT init(const char* _fileName,float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void updtaeFrame();
	void keycontrol();

	void rectCollison();

	RECT getplayerRect() { return _playerRect; }
	RECT getplayerRectOrgin() { return _playerOrgin; }



};


