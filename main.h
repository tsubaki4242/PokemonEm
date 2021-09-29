#pragma once
#include "gameNode.h"
class main : public gameNode
{

private:


	float _alpa;
	int _count;

public:
	main();
	~main();

	HRESULT init();
	void release();
	void update();
	void render();

};