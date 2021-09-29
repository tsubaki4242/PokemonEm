#pragma once
#include "singletonBase.h"



struct tagUnit2
{




	// 그려줄 위치
	wstring text;
	float x, y;
	int size;
	// blend val
	float alpha;


};
class txtRenderManger : public singletonBase<txtRenderManger>
{
private:
	typedef vector<pair<float, tagUnit2>> _zOrder_vector;
	typedef vector<pair<float, tagUnit2>>::iterator _zOrder_vector_iter;
private:
	_zOrder_vector _zOrder;
	vector<dImage> _noneZOrder;
	float _cameraX;
	float _cameraY;
public:
	txtRenderManger();
	~txtRenderManger();

	HRESULT init();
	void release();
	void render();

	void push_BackRenderInfo(float zOrder_Bottom, wstring txt, float x, float y,int size, float alpha = 1.f);

	void mergeSort(vector<pair<float, tagUnit2>>& v, int s, int e);
	void merge(vector<pair<float, tagUnit2>>& v, int s, int e, int m);
};
