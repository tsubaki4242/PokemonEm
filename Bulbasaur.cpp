#include "stdafx.h"
#include "Bulbasaur.h"

HRESULT Bulbasaur::init()
{

	APokemonBase::init();
	_pokemon.name = L"ÀÌ»óÇØ¾¾";
	_pokemon.type[0] = LEAF;
	_pokemon.type[1] = POISON;

	_pokemon.ftont = IMAGEMANAGER->findDImage("ÀÌ»óÇØ¾¾");
	_pokemon.back = IMAGEMANAGER->findDImage("ÀÌ»óÇØ¾¾ b");
	_pokemon.icon = IMAGEMANAGER->findDImage("ÀÌ»óÇØ¾¾ I");
	_pokemon.invenImg = IMAGEMANAGER->findDImage("ÀÌ»óÇØ¾¾ E");
	_pokemon.LV = 1;
	_pokemon.maxExp = 100;
	_pokemon.love = 0;

	_pokemon.maxHpZ = 45;
	_pokemon.atkZ = 49;
	_pokemon.defZ = 49;
	_pokemon.matkZ = 65;
	_pokemon.mdefZ = 65;
	_pokemon.spdZ = 45;
	CapabilityValue();
	_pokemon.hp = _pokemon.maxHp;
	_pokemon.vSkill.push_back(_pokemon.skillManger->getSkill("¸öÅë¹ÚÄ¡±â"));
	return S_OK;
}

void Bulbasaur::release()
{

}

void Bulbasaur::update()
{
	APokemonBase::update();



}

void Bulbasaur::render()
{
}
