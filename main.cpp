#include "stdafx.h"
#include "main.h"

main::main()
{
}

main::~main()
{
}

HRESULT main::init()
{
	CAMERAMANAGER->setBackScreenSize(1600, 1600);
	_alpa = 1.0f;
	return S_OK;
}

void main::release()
{
}

void main::update()
{
	_count++;
		if (_count % 30 == 0)
		{
			if (_alpa >= 1.0f)
			{
				_alpa--;
			}
			else if (_alpa <= 0)
			{
				_alpa++;
			}
		}
}

void main::render()
{
	IMAGEMANAGER->findDImage("¸ÞÀÎ")->render(0, 0);
	TXTRENDERMANGER->push_BackRenderInfo(0, L"Press the 'Z' key.", WINSIZEX / 2 -120, WINSIZEY -100, 30, _alpa);
}
