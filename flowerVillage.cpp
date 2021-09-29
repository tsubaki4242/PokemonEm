#include "stdafx.h"
#include "flowerVillage.h"

flowerVillage::flowerVillage()
{
}

flowerVillage::~flowerVillage()
{
}

HRESULT flowerVillage::init()
{

	_tile = new tileClass;
	_tile->init();
	_tile->mapLoad("field/flowerVillage.map");
	CAMERAMANAGER->setBackScreenSize(1600, 1600);
	_player = new player;
	_player->init("field/flowerVillage.map",200,400);


	return S_OK;
}

void flowerVillage::release()
{


}

void flowerVillage::update()
{
	_tile->update();
	_tile->imgGO();
	_player->update();

}

void flowerVillage::render()
{
	_tile->maprender(_player->getplayerRect());
	_player->render();

}
