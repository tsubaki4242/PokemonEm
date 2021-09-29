#include "stdafx.h"
#include "skillManger.h"

HRESULT skillManger::init()
{
	_bodyAtteck = new bodyAtteck;
	_bodyAtteck -> init();
	_speedDash = new speedDash;
	_speedDash->init();

	vSkill.push_back(_bodyAtteck);
	vSkill.push_back(_speedDash);

	return S_OK;
}

void skillManger::release()
{
}

void skillManger::update()
{

}

void skillManger::render()
{
}

skillBase* skillManger::getSkill(string name)
{
	for (int i = 0; i < vSkill.size(); i++)
	{
		if (vSkill[i]->getName() == name)
		{
			return vSkill[i];
		}
	}
	return nullptr;


}
