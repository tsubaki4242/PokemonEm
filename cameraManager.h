#pragma once
#include "singletonBase.h"
#include "dimage.h"

#define FADE	300

enum CAMERAFADE {
	FADEOUT = -1,
	NORMAL,
	FADEIN,
	ENDFADE
};

class cameraManager : public singletonBase<cameraManager>
{
private:
	//ī�޶� ���ߴ� ȭ�� ũ��(WINSIZEX, WINSIZEY)�� ��ǥ(left, right, top, bottom)
	RECT _screen;
	RECT _divScreen;

	int _backWidth, _backHeight;	//backDC ũ��
	int _frontWidth, _frontHeight;	//frontDC ũ��
	//fade
	dImage* _fadeIMG;
	RECT _fadeRect;
	float _alpha;
	int _fade;

	//ī�޶� ������
	float _count;	//������ �� ����ϴ� count
	float _ratioX;	//�߽��� ��ġ ���� (x)
	float _ratioY;	//�߽��� ��ġ ���� (y)
	float _zoom;	//Ȯ����
	float _camY;	//ī�޶� �ø��� ������
	bool _onMove;	//ī�޶� �ø��� ������ �Ǻ�
	float x;
	float y;
	float _playerY;


public:
	cameraManager();
	~cameraManager();

	HRESULT init(int width, int height);
	void release();

	//ī�޶� ��ġ(screen) ����
	void updateScreen(float standardX, float standardY);
	void updateScreen2(float standardX, float standardY, RECT rc);
	void moveCam(int direct);
	void resetCam();

	//FadeIN, FadeOUT
	void fadeIn();
	void fadeOut();

	//ī�޶� ����
	void vibrateScreen(float standardX, float standardY,
		float magnitude = 5.0f, float interval = 0);
	void vibrateScreenOut(float standardX, float standardY,
		float magnitude = 5.0f, float interval = 0);

	//ī�޶� ���
	void render(HDC frontDC, int destX, int destY, HDC backDC, int ver = 1);

	//ī�޶� ����ó��
	void onWindow(float& x, float& y);
	void onWindow2(float& x, float& y, float initX, float endX, float initY, float endY);

	void setBackScreenSize(float width, float height);

	//============ ������ ============//
	RECT getScreen() { return _screen; }
	RECT getDivScreen() { return _divScreen; }

	//void setFrontScreenSize(float width, float height) { _frontWidth = width, _frontHeight = height; }
	float getBackScreenWidth() { return _backWidth; }
	float getBackScreenHeight() { return _backHeight; }

	float getAlpha() { return _alpha; }

	void setFade(int fade) { _fade = fade; }
	int getFade() { return _fade; }

	void setRatioX(float ratio) { _ratioX = ratio; }
	float getRatioX() { return _ratioX; }
	void setRatioY(float ratio) { _ratioY = ratio; }
	float getRatioY() { return _ratioY; }

	void setZoom(float zoom) { _zoom = zoom; }
	float getZoom() { return _zoom; }

	void setCamY(float count) { _camY = count; }
	float getCamY() { return _camY; }

	void setMove(bool b) { _onMove = b; }
	bool getMove() { return _onMove; }

	void setY(float playerY) { _playerY = playerY; }
	bool getY() { return _playerY; }
};

