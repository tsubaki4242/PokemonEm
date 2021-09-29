#include "stdafx.h"
#include "Venusaur.h"

HRESULT Venusaur::init()
{
	APokemonBase::init();
	_pokemon.name = L"�̻��ز�";
	_pokemon.type[0] = LEAF;
	_pokemon.type[1] = POISON;

	_pokemon.ftont = IMAGEMANAGER->findDImage("�̻��ز�");
	_pokemon.back = IMAGEMANAGER->findDImage("�̻��ز� b");
	_pokemon.icon = IMAGEMANAGER->findDImage("�̻��ز� I");
	_pokemon.invenImg = IMAGEMANAGER->findDImage("�̻��ز� E");

	_pokemon.LV = 1;
	_pokemon.maxExp = 100;
	_pokemon.love = 0;

	_pokemon.maxHpZ = 80;
	_pokemon.atkZ = 82;
	_pokemon.defZ = 83;
	_pokemon.matkZ = 100;
	_pokemon.mdefZ = 100;
	_pokemon.spdZ = 80;
	CapabilityValue();
	_pokemon.hp = _pokemon.maxHp;
	return S_OK;
}

void Venusaur::release()
{
}

void Venusaur::update()
{
	APokemonBase::update();
}

void Venusaur::render()
{
}
