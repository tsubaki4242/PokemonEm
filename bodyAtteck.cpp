#include "stdafx.h"
#include "bodyAtteck.h"

HRESULT bodyAtteck::init()
{
	_skill.skill[0] = IMAGEMANAGER->findDImage("¸öÅë¹ÚÄ¡±â");
	_skill.name = "¸öÅë¹ÚÄ¡±â";
	_skill.skillCount = 30;
	_skill.atteckType = false;
	_skill.type = NOMRAL;
	_skill.damge = 60;
	_skill.aime = 80;
	_skill.FrameX = 0;
	_skill.FrameY = 0;

	return S_OK;
}

void bodyAtteck::release()
{
}

void bodyAtteck::update(float x, float y)
{
	_skill.count++;
	_skill.imgX[0] = x;
	_skill.imgY[0] = y;

	if (_skill.count % 5 == 0)
	{
		_skill.index++;
		_skill.FrameX = _skill.index;
		_skill.FrameY = 0;

	}




}

void bodyAtteck::render()
{

	_skill.skill[0]->frameRender(_skill.imgX[0], _skill.imgY[0], _skill.FrameX, _skill.FrameY);

}
