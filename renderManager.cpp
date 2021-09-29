#include "stdafx.h"
#include "renderManager.h"

renderManager::renderManager()
{
}

renderManager::~renderManager()
{
}

HRESULT renderManager::init()
{
	 _cameraX = 0.f;
	 _cameraY = 0.f;
	return S_OK;
}

void renderManager::release()
{

}


void renderManager::render()
{
	mergeSort(_zOrder, 0, _zOrder.size() - 1);

	for (_zOrder_vector_iter iter = _zOrder.begin(); iter != _zOrder.end(); ++iter)
	{
		// 프레임 이미지 인가?
		if (iter->second.frameX <= -500)
		{
		D2DMANAGER->setRotation(iter->second.alpha, iter->second.x+32, iter->second.y+64);
		iter->second.img->render(iter->second.x,
			iter->second.y,
			iter->second.sizeWidth,
			iter->second.sizeHeight,
			255);
		D2DMANAGER->resetRotation();
		}
		else if (iter->second.isFrame)
		{
			iter->second.img->frameRender(iter->second.x,
				iter->second.y,
				iter->second.frameX,
				iter->second.frameY,
				iter->second.sizeWidth,
				iter->second.sizeHeight,
				iter->second.alpha);
		}

		else // 응 안써
		{

			iter->second.img->render(iter->second.x,
				iter->second.y,
				iter->second.sizeWidth,
				iter->second.sizeHeight,
				iter->second.alpha);
		}
		
	}
	// 벡터 클리어 및 리사이즈 
	_zOrder.clear();
	_zOrder.resize(0);
}

void renderManager::push_BackRenderInfo(float zOrder_Bottom, dImage* img, float x, float y, float alpha)
{
	tagUnit _unit;
	ZeroMemory(&_unit, sizeof(_unit));

	_unit.x = x;
	_unit.y = y;
	_unit.img = img;
	_unit.alpha = alpha;
	_unit.sizeWidth = _unit.img->getWidth();
	_unit.sizeHeight = _unit.img->getHeight();
	_unit.isFrame = false;

		_zOrder.push_back(make_pair(zOrder_Bottom, _unit));

}

void renderManager::push_BackRenderInfo(float zOrder_Bottom, dImage * img, float x, float y, float sizeWidth, float sizeHeight, float alpha)
{
	tagUnit _unit;
	ZeroMemory(&_unit, sizeof(_unit));

	_unit.x = x;
	_unit.y = y;
	_unit.img = img;
	_unit.alpha = alpha;
	_unit.sizeWidth = sizeWidth;
	_unit.sizeHeight = sizeHeight;
	_unit.isFrame = false;


		_zOrder.push_back(make_pair(zOrder_Bottom, _unit));

}

void renderManager::push_BackFrameRenderInfo(float zOrder_Bottom, dImage * img, float x, float y, float _alpha)
{
	tagUnit _unit;
	ZeroMemory(&_unit, sizeof(_unit));

	_unit.x = x;
	_unit.y = y;
	_unit.frameX = 0;
	_unit.frameY = 0;
	_unit.alpha = _alpha;
	_unit.img = img;
	_unit.sizeWidth = _unit.img->getWidth();
	_unit.sizeHeight = _unit.img->getHeight();
	_unit.isFrame = true;

		_zOrder.push_back(make_pair(zOrder_Bottom, _unit));

}
void renderManager::push_BackFrameRenderRoteshionInfo(float zOrder_Bottom, dImage * img, float x, float y, float angle, int size)
{
	tagUnit _unit;
	ZeroMemory(&_unit, sizeof(_unit));

	_unit.x = x;
	_unit.y = y;
	_unit.frameX = size;
	_unit.frameY = 0;
	_unit.alpha = angle;
	_unit.img = img;
	_unit.sizeWidth = _unit.img->getWidth();
	_unit.sizeHeight = _unit.img->getHeight();
	_unit.isFrame = true;

	_zOrder.push_back(make_pair(zOrder_Bottom, _unit));

}
void renderManager::push_BackFrameRenderInfo(float zOrder_Bottom, dImage * img, float x, float y, int currentFrameX, int currentFrameY, float _alpha)
{
	tagUnit _unit;
	ZeroMemory(&_unit, sizeof(_unit));

	_unit.x = x;
	_unit.y = y;
	_unit.frameX = currentFrameX;
	_unit.frameY = currentFrameY;
	_unit.alpha = _alpha;
	_unit.img = img;
	_unit.sizeWidth = _unit.img->getFrameWidth();
	_unit.sizeHeight = _unit.img->getFrameHeight();
	_unit.isFrame = true;


		_zOrder.push_back(make_pair(zOrder_Bottom, _unit));

}
void renderManager::push_BackFrameRenderInfo(float zOrder_Bottom, RECT rc, dImage * img, float x, float y, int currentFrameX, int currentFrameY,float _alpha)
{
	tagUnit _unit;
	ZeroMemory(&_unit, sizeof(_unit));

	_unit.x = x;
	_unit.y = y;
	_unit.frameX = currentFrameX;
	_unit.frameY = currentFrameY;
	_unit.alpha = _alpha;
	_unit.img = img;
	_unit.rc = rc;
	_unit.sizeWidth = _unit.img->getFrameWidth();
	_unit.sizeHeight = _unit.img->getFrameHeight();
	_unit.isFrame = true;
	RECT cam = CAMERAMANAGER->getScreen();
	cam.left -= 30;
	cam.right += 30;
	cam.top -= 30;
	cam.bottom += 30;
	if (cam.left < rc.left && cam.right > rc.right && cam.top < rc.top && cam.bottom > rc.bottom)
	{
		_zOrder.push_back(make_pair(zOrder_Bottom, _unit));
	}

}
void renderManager::push_BackFrameRenderInfoSizeUp(float zOrder_Bottom, dImage * img, float x, float y, int currentFrameX, int currentFrameY, int size, float _alpha)
{
	tagUnit _unit;
	ZeroMemory(&_unit, sizeof(_unit));

	_unit.x = x;
	_unit.y = y;
	_unit.frameX = currentFrameX;
	_unit.frameY = currentFrameY;
	_unit.alpha = _alpha;
	_unit.img = img;
	_unit.sizeWidth = _unit.img->getFrameWidth()* size;
	_unit.sizeHeight = _unit.img->getFrameHeight() *size;
	_unit.isFrame = true;


	_zOrder.push_back(make_pair(zOrder_Bottom, _unit));

}
void renderManager::push_BackFrameRenderInfo(float zOrder_Bottom, dImage * img, float x, float y, int currentFrameX, int currentFrameY, float sizeWidth, float sizeHeight, float _alpha)
{
	tagUnit _unit;
	ZeroMemory(&_unit, sizeof(_unit));

	_unit.x = x;
	_unit.y = y;
	_unit.frameX = currentFrameX;
	_unit.frameY = currentFrameY;
	_unit.alpha = _alpha;
	_unit.img = img;
	_unit.sizeWidth = sizeWidth;
	_unit.sizeHeight = sizeHeight;
	_unit.isFrame = true;


		_zOrder.push_back(make_pair(zOrder_Bottom, _unit));

}
void renderManager::mergeSort(vector<pair<float, tagUnit>>& v, int s, int e)
{
	if (s >= e) return;

	int m = (s + e) / 2;
	// divide 분할
	mergeSort(v, s, m); // s ~ m
	mergeSort(v, m + 1, e); // m+1 ~ e

	// conquer
	merge(v, s, e, m);
}

void renderManager::merge(vector<pair<float, tagUnit>>& v, int s, int e, int m)
{
	vector<pair<float, tagUnit>> ret(e + 1);
	int ret_idx = 0; //리턴 인덱스
	int firstidx = s; //맨 첫 인덱스
	int secondidx = m + 1; //


	while (firstidx <= m && secondidx <= e)
	{
		if (v[firstidx].first < v[secondidx].first) ret[ret_idx++] = v[firstidx++];
		else ret[ret_idx++] = v[secondidx++];
	}

	while (firstidx <= m) ret[ret_idx++] = v[firstidx++];
	while (secondidx <= e) ret[ret_idx++] = v[secondidx++];

	for (int k = s, ret_idx = 0; k <= e; k++, ret_idx++)
		v[k] = ret[ret_idx];
}