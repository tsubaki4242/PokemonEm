#pragma once
#include "APokemonBase.h"

class Venusaur : public APokemonBase
{

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

