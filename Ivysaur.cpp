#include "stdafx.h"
#include "Ivysaur.h"

HRESULT Ivysaur::init()
{
	APokemonBase::init();
	_pokemon.name = L"이상해풀";
	_pokemon.type[0] = LEAF;
	_pokemon.type[1] = POISON;

	_pokemon.ftont = IMAGEMANAGER->findDImage("이상해풀");
	_pokemon.back = IMAGEMANAGER->findDImage("이상해풀 b");
	_pokemon.icon = IMAGEMANAGER->findDImage("이상해풀 I");
	_pokemon.invenImg = IMAGEMANAGER->findDImage("이상해풀 E");
	_pokemon.LV = 1;
	_pokemon.maxExp = 100;
	_pokemon.love = 0;

	_pokemon.maxHpZ = 60;
	_pokemon.atkZ = 62;
	_pokemon.defZ = 63;
	_pokemon.matkZ = 80;
	_pokemon.mdefZ = 80;
	_pokemon.spdZ = 60;
	CapabilityValue();
	_pokemon.hp = _pokemon.maxHp;
	return S_OK;
}

void Ivysaur::release()
{
}

void Ivysaur::update()
{
	APokemonBase::update();

}

void Ivysaur::render()
{
}
