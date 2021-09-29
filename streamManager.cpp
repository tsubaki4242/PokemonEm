#include "stdafx.h"
#include "streamManager.h"


streamManager::streamManager()
{
}


streamManager::~streamManager()
{
}

HRESULT streamManager::init()
{
	_currentVideo = NULL;

	return S_OK;
}

void streamManager::release()
{
	deleteAll();
}

video* streamManager::addVideo(string strKey, const char * fileName)
{
	video* _video = findVideo(strKey);
	if (_video) return _video;
	_video = new video;
	//_video->setVideo(fileName);
	if (FAILED(_video->setVideo(fileName)))
	{
		SAFE_DELETE(_video);

		return nullptr;
	}

	_mapVideoList.insert(make_pair(strKey, _video));

	return _video;

}

void streamManager::startVideo(string strKey)
{
	_currentVideo = findVideo(strKey);

	for (mapVideoIter iter = _mapVideoList.begin(); iter != _mapVideoList.end(); iter++)
	{
		if (_currentVideo != iter->second)
			iter->second->closeVideo();
	}

	_currentVideo->playVideo();
}

void streamManager::closeVideo(string strKey)
{
	video* _video = findVideo(strKey);
	_currentVideo->closeVideo();
	//_video->deletVideo();
	_mapVideoList.erase(strKey);
}


video * streamManager::findVideo(string strKey)
{
	mapVideoIter key = _mapVideoList.find(strKey);

	if (key != _mapVideoList.end())
	{
		return key->second;
	}

	return nullptr;
}

BOOL streamManager::deleteAll()
{
	mapVideoIter iter = _mapVideoList.begin();

	for (; iter != _mapVideoList.end();)
	{
		//�������̳ʾȿ� �̹����� �ִٸ�
		if (iter->second != nullptr)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mapVideoList.erase(iter);
		}
		else ++iter;
	}

	_mapVideoList.clear();

	return false;
}


