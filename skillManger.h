#pragma once
#include "gameNode.h"
#include "bodyAtteck.h"
#include "speedDash.h"

#include <vector>

class skillManger :public gameNode
{


private:

	vector<skillBase*>				vSkill;
	vector<skillBase*>::iterator	viSkill;


	bodyAtteck* _bodyAtteck;
	speedDash* _speedDash;


public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();

	virtual void render();

	skillBase* getSkill(string name);
};

