#include "stdafx.h"
#include "txtRenderManger.h"
txtRenderManger::txtRenderManger()
{
}

txtRenderManger::~txtRenderManger()
{
}

HRESULT txtRenderManger::init()
{
	_cameraX = 0.f;
	_cameraY = 0.f;
	return S_OK;
}

void txtRenderManger::release()
{

}


void txtRenderManger::render()
{
	mergeSort(_zOrder, 0, _zOrder.size() - 1);

	for (_zOrder_vector_iter iter = _zOrder.begin(); iter != _zOrder.end(); ++iter)
	{
		D2DMANAGER->RenderText(iter->second.x, iter->second.y, iter->second.text, ColorF::White, iter->second.alpha, iter->second.size);

	}
	// 벡터 클리어 및 리사이즈 
	_zOrder.clear();
	_zOrder.resize(0);
}

void txtRenderManger::push_BackRenderInfo(float zOrder_Bottom, wstring txt, float x, float y, int size,float alpha)
{
	tagUnit2 _unit;


	_unit.x = x;
	_unit.y = y;
	_unit.text = txt;
	_unit.alpha = alpha;
	_unit.size = size;

	_zOrder.push_back(make_pair(zOrder_Bottom, _unit));

}


void txtRenderManger::mergeSort(vector<pair<float, tagUnit2>>& v, int s, int e)
{
	if (s >= e) return;

	int m = (s + e) / 2;
	// divide 분할
	mergeSort(v, s, m); // s ~ m
	mergeSort(v, m + 1, e); // m+1 ~ e

	// conquer
	merge(v, s, e, m);
}

void txtRenderManger::merge(vector<pair<float, tagUnit2>>& v, int s, int e, int m)
{
	vector<pair<float, tagUnit2>> ret(e + 1);
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