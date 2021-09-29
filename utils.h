#pragma once
#define PI 3.14159f
#define PI2 PI * 2

#define RECT_WIDTH(rc) static_cast<float>(rc.right - rc.left)
#define RECT_HEIGHT(rc) static_cast<float>(rc.bottom - rc.top)
#define RECT_CENTER_X(rc) static_cast<float>((rc.left + rc.right) * 0.5f)
#define RECT_CENTER_Y(rc) static_cast<float>((rc.top + rc.bottom) * 0.5f)

//�̹��� ȸ�� ��ų�� �ޱ� �� ������ ����ϱ� ���� ������
#define PI8		float(PI / 8.0f)
#define PI16	float(PI / 16.0f)
#define PI32	float(PI / 32.0f)
#define PI64	float(PI / 64.0f)
#define PI128	float(PI / 128.0f)


namespace UJN_UTIL
{
	//�Ÿ��������� �Լ�
	float getDistance(float startX, float startY, float endX, float endY);

	float getAngle(float x1, float y1, float x2, float y2);
	wchar_t * ConverCtoWC(char * str);

	//�簢�� ����ü
	typedef struct tagENEMYRECT
	{
		float left;
		float top;
		float right;
		float bottom;

		tagENEMYRECT() : left(0.0f), top(0.0f), right(0.0f), bottom(0.0f) {}
		tagENEMYRECT(float _left, float _top, float _right, float _bottom) :
			left(_left), top(_top), right(_right), bottom(_bottom) {}

		void Move(float dx, float dy)
		{
			left += dx;
			right += dx;
			top += dy;
			bottom += dy;
		}

		void Set(float _left, float _top, float _right, float _bottom)
		{
			left = _left;
			top = _top;
			right = _right;
			bottom = _bottom;
		}

		//����Ʈ ž���� ����
		void SetLeftTopPos(float _left, float _top)
		{
			float width = getWidth();
			float height = getHeight();

			left = _left;
			top = _top;
			right = _left + width;
			bottom = _top + height;
		}

		void SetCenterPos(float centerX, float centerY)
		{
			float halfW = getWidth() * 0.5f;
			float halfH = getHeight() * 0.5f;

			left = centerX - halfW;
			top = centerY - halfH;
			right = centerX + halfW;
			bottom = centerY + halfH;
		}

		float getWidth(void) { return right - left; }
		float getHeight(void) { return bottom - top; }
	}ENEMYRECT, *LPENEMYRECT;

	//�簢���� �簢���� �浹�ߴ�?
	bool IsCollision(const RECT& rc1, const ENEMYRECT& rc2);
	bool IsCollision(const RECT& rc1, const RECT& rc2);
	bool IntersectRectReaction2(RECT*const rcMove, const RECT*const rcHold);

}