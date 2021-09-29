#include "stdafx.h"
#include "APokemonBase.h"

HRESULT APokemonBase::init()
{
	_pokemon.skillManger = new skillManger;
	_pokemon.skillManger->init();
	_pokemon.persona = (PERSONA)RND->getInt(25);
	_pokemon.shiney = RND->getInt(2);
	_pokemon.sex = RND->getInt(2);
	_pokemon.maxHpV = RND->getInt(31);
	_pokemon.atkV = RND->getInt(31);
	_pokemon.defV = RND->getInt(31);
	_pokemon.matkV = RND->getInt(31);
	_pokemon.mdefV = RND->getInt(31);
	_pokemon.spdV = RND->getInt(31);
	_pokemon.maxHpS = 0;
	_pokemon.atkS = 0;
	_pokemon.defS = 0;
	_pokemon.matkS = 0;
	_pokemon.mdefS = 0;
	_pokemon.spdS = 0;
	personaPlus();


	return S_OK;
}

void APokemonBase::release()
{
}

void APokemonBase::update()
{
	if (_pokemon.exp >= _pokemon.maxExp)
	{
		_pokemon.maxExp = _pokemon.maxExp * 2;
		_pokemon.LV++;
	}
	CapabilityValue();


}

void APokemonBase::frontRender(float x, float y)
{
	_pokemon.ftontX = x;
	_pokemon.ftontY = y;
	_pokemon.ftont->frameRender(_pokemon.ftontX, _pokemon.ftontY, _pokemon.FrameX, _pokemon.FrameY);
}

void APokemonBase::backRender(float x, float y)
{
	_pokemon.backX = x;
	_pokemon.backY = y;
	_pokemon.back->frameRender(_pokemon.backX, _pokemon.backY, _pokemon.FrameXb, _pokemon.FrameYb);
}

void APokemonBase::iconRender(float x, float y)
{
	_pokemon.iconX = x;
	_pokemon.iconY = y;
	_pokemon.icon->frameRender(_pokemon.iconX, _pokemon.iconY, _pokemon.iconFrameX, _pokemon.iconFrameY);

}


void APokemonBase::personaPlus()
{
	if (_pokemon.persona == Lonely)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.1f;
		_pokemon.defP = 0.9f;
		_pokemon.matkP = 1.0f;
		_pokemon.mdefP = 1.0f;
		_pokemon.spdP = 1.0f;
	}
	if (_pokemon.persona == Adamant)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.1f;
		_pokemon.defP = 1.0f;
		_pokemon.matkP = 0.9f;
		_pokemon.mdefP = 1.0f;
		_pokemon.spdP = 1.0f;
	}
	if (_pokemon.persona == Naughty)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.1f;
		_pokemon.defP = 1.0f;
		_pokemon.matkP = 1.0f;
		_pokemon.mdefP = 0.9f;
		_pokemon.spdP = 1.0f;
	}
	if (_pokemon.persona == Brave)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.1f;
		_pokemon.defP = 1.0f;
		_pokemon.matkP = 1.0f;
		_pokemon.mdefP = 1.0f;
		_pokemon.spdP = 0.9f;
	}
	if (_pokemon.persona == Bold)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 0.9f;
		_pokemon.defP = 1.1f;
		_pokemon.matkP = 1.0f;
		_pokemon.mdefP = 1.0f;
		_pokemon.spdP = 1.0f;
	}
	if (_pokemon.persona == Impish)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.0f;
		_pokemon.defP = 1.1f;
		_pokemon.matkP = 0.9f;
		_pokemon.mdefP = 1.0f;
		_pokemon.spdP = 1.0f;
	}
	if (_pokemon.persona == Lax)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.0f;
		_pokemon.defP = 1.1f;
		_pokemon.matkP = 1.0f;
		_pokemon.mdefP = 0.9f;
		_pokemon.spdP = 1.0f;
	}
	if (_pokemon.persona == Relaxed)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.0f;
		_pokemon.defP = 1.1f;
		_pokemon.matkP = 1.0f;
		_pokemon.mdefP = 1.0f;
		_pokemon.spdP = 0.9f;
	}
	if (_pokemon.persona == Modest)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 0.9f;
		_pokemon.defP = 1.0f;
		_pokemon.matkP = 1.1f;
		_pokemon.mdefP = 1.0f;
		_pokemon.spdP = 1.0f;
	}
	if (_pokemon.persona == Mild)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.0f;
		_pokemon.defP = 0.9f;
		_pokemon.matkP = 1.1f;
		_pokemon.mdefP = 1.0f;
		_pokemon.spdP = 1.0f;
	}
	if (_pokemon.persona == Rash)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.0f;
		_pokemon.defP = 1.0f;
		_pokemon.matkP = 1.1f;
		_pokemon.mdefP = 0.9f;
		_pokemon.spdP = 1.0f;
	}
	if (_pokemon.persona == Quiet)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.0f;
		_pokemon.defP = 1.0f;
		_pokemon.matkP = 1.1f;
		_pokemon.mdefP = 1.0f;
		_pokemon.spdP = 0.9f;
	}
	if (_pokemon.persona == Calm)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 0.9f;
		_pokemon.defP = 1.0f;
		_pokemon.matkP = 1.0f;
		_pokemon.mdefP = 1.1f;
		_pokemon.spdP = 1.0f;
	}
	if (_pokemon.persona == Gentle)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.0f;
		_pokemon.defP = 0.9f;
		_pokemon.matkP = 1.0f;
		_pokemon.mdefP = 1.1f;
		_pokemon.spdP = 1.0f;
	}
	if (_pokemon.persona == Careful)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.0f;
		_pokemon.defP = 1.0f;
		_pokemon.matkP = 0.9f;
		_pokemon.mdefP = 1.1f;
		_pokemon.spdP = 1.0f;
	}
	if (_pokemon.persona == Sassy)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.0f;
		_pokemon.defP = 1.0f;
		_pokemon.matkP = 1.0f;
		_pokemon.mdefP = 1.1f;
		_pokemon.spdP = 0.9f;
	}
	if (_pokemon.persona == Timid)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 0.9f;
		_pokemon.defP = 1.0f;
		_pokemon.matkP = 1.0f;
		_pokemon.mdefP = 1.0f;
		_pokemon.spdP = 1.1f;
	}
	if (_pokemon.persona == Hasty)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.0f;
		_pokemon.defP = 0.9f;
		_pokemon.matkP = 1.0f;
		_pokemon.mdefP = 1.0f;
		_pokemon.spdP = 1.1f;
	}
	if (_pokemon.persona == Jolly)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.0f;
		_pokemon.defP = 1.0f;
		_pokemon.matkP = 0.9f;
		_pokemon.mdefP = 1.0f;
		_pokemon.spdP = 1.1f;
	}
	if (_pokemon.persona == Naive)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.0f;
		_pokemon.defP = 1.0f;
		_pokemon.matkP = 1.00f;
		_pokemon.mdefP = 0.9f;
		_pokemon.spdP = 1.1f;
	}
	if (_pokemon.persona == Bashful)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.0f;
		_pokemon.defP = 1.0f;
		_pokemon.matkP = 1.00f;
		_pokemon.mdefP = 1.0f;
		_pokemon.spdP = 1.0f;
	}

	if (_pokemon.persona == Hardy)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.0f;
		_pokemon.defP = 1.0f;
		_pokemon.matkP = 1.00f;
		_pokemon.mdefP = 1.0f;
		_pokemon.spdP = 1.0f;
	}
	if (_pokemon.persona == Docile)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.0f;
		_pokemon.defP = 1.0f;
		_pokemon.matkP = 1.00f;
		_pokemon.mdefP = 1.0f;
		_pokemon.spdP = 1.0f;
	}
	if (_pokemon.persona == Quirky)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.0f;
		_pokemon.defP = 1.0f;
		_pokemon.matkP = 1.00f;
		_pokemon.mdefP = 1.0f;
		_pokemon.spdP = 1.0f;
	}
	if (_pokemon.persona == Serious)
	{
		_pokemon.maxHpP = 1.0f;
		_pokemon.atkP = 1.0f;
		_pokemon.defP = 1.0f;
		_pokemon.matkP = 1.00f;
		_pokemon.mdefP = 1.0f;
		_pokemon.spdP = 1.0f;
	}
}

void APokemonBase::CapabilityValue()
{

	_pokemon.maxHp = (((_pokemon.maxHpZ * 2) + _pokemon.maxHpV + (_pokemon.maxHpS / 4)) * (_pokemon.LV / 100))+10+ _pokemon.LV;
	_pokemon.atk = (((_pokemon.atkZ * 2) + _pokemon.atkV + (_pokemon.atkS / 4)) * (_pokemon.LV / 100)+5)*_pokemon.atkP;
	_pokemon.def = (((_pokemon.defZ * 2) + _pokemon.defV + (_pokemon.defS / 4)) * (_pokemon.LV / 100) + 5)*_pokemon.defP;
	_pokemon.matk = (((_pokemon.matkZ * 2) + _pokemon.matkV + (_pokemon.matkS / 4)) * (_pokemon.LV / 100) + 5)*_pokemon.matkP;
	_pokemon.mdef = (((_pokemon.mdefZ * 2) + _pokemon.mdefV + (_pokemon.mdefS / 4)) * (_pokemon.LV / 100) + 5)*_pokemon.mdefP;
	_pokemon.spd = (((_pokemon.spdZ * 2) + _pokemon.spdV + (_pokemon.spdS / 4)) * (_pokemon.LV / 100) + 5)*_pokemon.spdP;





}


