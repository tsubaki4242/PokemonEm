#pragma once
#include "singletonBase.h"
#include "video.h"
#include <map>

class streamManager : public singletonBase<streamManager>
{
private:
	typedef map<string, video*>				mapVideoList;
	typedef map<string, video*>::iterator	mapVideoIter;

	mapVideoList _mapVideoList;
	video* _currentVideo;

public:
	streamManager();
	~streamManager();
	HRESULT init();
	void release();

	video* addVideo(string strKey, const char* fileName);
	void startVideo(string strKey);
	void closeVideo(string strKey);

	//void getPosition();
	//void getLenthEnd();

	video* findVideo(string strKey);

	BOOL deleteAll();

	long getPosition(string strKey) { video* _video = findVideo(strKey); return _video->getPosition(); }
	long getLenthEnd(string strKey) { video* _video = findVideo(strKey); return _video->getLength(); }
};