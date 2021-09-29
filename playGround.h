#pragma once
#include "gameNode.h"

class playGround : public gameNode
{
private:
	//Player* _player;

	bool _debug;
	dImage* _back;
	dImage* _moveImg;
public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	virtual void IMGALL();
};