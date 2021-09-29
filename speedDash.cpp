#include "stdafx.h"
#include "speedDash.h"

HRESULT speedDash::init()
{
	_skill.skill[0] = IMAGEMANAGER->findDImage("Àü±¤¼®È­");
	_skill.skillCount = 25;
	_skill.atteckType = false;
	_skill.type = NOMRAL;
	_skill.damge = 30;
	_skill.aime = 100;
	_skill.speed = 1;
	_skill.FrameX = 0;
	_skill.FrameY = 0;

	return S_OK;
}

void speedDash::release()
{
}

void speedDash::update(float x, float y)
{
	_skill.count++;
	_skill.imgX[0] = x;
	_skill.imgY[0] = y;

	if (_skill.count % 5 == 0)
	{
		_skill.index++;
		_skill.FrameX = _skill.index;
		_skill.FrameY = _skill.indey;

		if (_skill.index > 5)
		{
			_skill.index=0;
			_skill.indey++;
		}

	}

}

void speedDash::render()
{
	_skill.skill[0]->frameRender(_skill.imgX[0], _skill.imgY[0], _skill.FrameX, _skill.FrameY);
}
