#pragma once
#include "gameNode.h"
#include "tileClass.h"
#include "player.h"


class flowerVillage : public gameNode
{

private:
	tileClass* _tile;
	player* _player;




public:
	flowerVillage();
	~flowerVillage();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

