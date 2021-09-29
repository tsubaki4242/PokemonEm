#pragma once
#include "skillBase.h"

class speedDash : public skillBase
{




public:

	virtual HRESULT init();
	virtual void release();
	virtual void update(float x, float y);

	virtual void render();

};

