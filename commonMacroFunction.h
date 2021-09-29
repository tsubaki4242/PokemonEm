#pragma once

//============================================
// ## 21.04.23 ## commonMacroFunction ##
//============================================

//Point
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };

	return pt;
}

//          선긋기함수(그려줄DC, 시작좌표X, 시작좌표Y, 끝좌표 X, 끝좌표Y)
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//RECT
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };

	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height/ 2) };

	return rc;
}


//사각형 
inline void Rectangle(HDC hdc, RECT& rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//x, y축을 기준으로 하는 사각형이 생성됨
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//x, y 좌표를 중점으로 크기만큼의 사각형이 생성됨
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

//원
inline void Ellipse(HDC hdc, RECT& rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}
//x, y축을 기준으로 하는 원이 생성됨
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//x, y 좌표를 중점으로 크기만큼의 원이 생성됨
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline bool INTERSECTION_RECT(D2D1_RECT_F& temp, D2D1_RECT_F& _rc, D2D1_RECT_F& _rc2)
{
	if (_rc.right > _rc2.left && _rc.left < _rc2.right &&
		_rc.top    < _rc2.bottom && _rc.bottom > _rc2.top)
	{
		if (_rc.top < _rc2.top)
		{
			temp = { _rc2.left, _rc2.top, _rc2.left + _rc.right - _rc2.left, _rc2.top + _rc.bottom - _rc2.top };
		}
		else
			temp = { _rc2.left, _rc.top, _rc2.left + _rc.right - _rc2.left, _rc.top + _rc2.bottom - _rc.top };

		return true;
	}
	else
		return false;

}

//RECT



inline D2D1_RECT_F dRectMake(float x, float y, float width, float height) {
	D2D1_RECT_F rc = { x, y, x + width, y + height };

	return rc;
}

inline D2D1_RECT_F dRectMakeCenter(float x, float y, float width, float height) {
	D2D1_RECT_F rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };

	return rc;
}