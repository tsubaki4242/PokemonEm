#pragma once
#include "singletonBase.h"

class printManager : public singletonBase<printManager>
{
private:
	char _text[128];
	bool _debug;

public:
	printManager() {};
	~printManager() {};

	HRESULT init();
	void release();

	void setDebug(bool debug) { _debug = debug; }
	bool isDebug() { return _debug; }
};
