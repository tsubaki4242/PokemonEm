#include "stdafx.h"
#include "title.h"

title::title()
{
}

title::~title()
{
}

HRESULT title::init()
{
	CAMERAMANAGER->setBackScreenSize(1600, 1600);
	STREAMMANAGER->addVideo("title", "movi/title.wmv");
	STREAMMANAGER->findVideo("title")->playVideo();
	return S_OK;
}

void title::release()
{
}

void title::update()
{
	if (STREAMMANAGER->getPosition("title") >= STREAMMANAGER->getLenthEnd("title"))
	{

		STREAMMANAGER->deleteAll();
		SCENEMANAGER->changeScene("main");

	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{

		STREAMMANAGER->deleteAll();
		SCENEMANAGER->changeScene("main");


	}
}

void title::render()
{
}
