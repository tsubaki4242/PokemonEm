#pragma once
#include "animation.h"


class dImage
{
public:
	//�̹����� �ҷ��ü� �ִ� ����
	enum DIMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,		//���ҽ� ���Ϸκ���
		LOAD_FILE,			//�̹��� ���Ϸκ���
		LOAD_EMPTY,			//�� ��Ʈ�� �̹����� �����߰ڴ�
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		//���ҽ��� ���ؼ� �̹��� ó���Ҷ� �긦 ����
		ID2D1Bitmap	*bitMap;//�̹��� ��Ʈ��
		ID2D1HwndRenderTarget	*_dRenderTarget;
		ID2D1BitmapRenderTarget	*_dBitRenderTarget;
		float x;			//�̹��� x��ǥ
		float y;			//�̹��� y��ǥ
		int width;			//�̹��� ��ü ����ũ��
		int height;			//�̹��� ��ü ����ũ��
		int currentFrameX;	//���� ������ ��ȣ(����)
		int currentFrameY;	//���� ������ ��ȣ(����)
		int maxFrameX;		//�ִ� ������ ��ȣ(����)
		int maxFrameY;		//�ִ� ������ ��ȣ(����)
		int frameWidth;		//1������ �� ����ũ��
		int frameHeight;	//1������ �� ����ũ��
		BYTE loadType;

		tagImageInfo()
		{
			resID = 0;
			bitMap = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	const WCHAR*	_fileName;		//���� �̸�
	tagImageInfo *_imgBitmap;

	//�̹��� �ε带 ���� ��ü
	IWICImagingFactory		*_wicFactory;
	IWICBitmapDecoder		*_bitDecoder;
	IWICBitmapFrameDecode	*_bitFrame;
	IWICFormatConverter		*_wicConverter;



public:
	dImage();
	~dImage();

	HRESULT init(LPCWCHAR fileName, int width, int height);
	HRESULT init(LPCWCHAR fileName, int width, int height, int frameX, int frameY);
	/*				��				��			��			��			��								*/
	/*				��				��			��			��			��������	 �̹��� ������ ��(y��)		*/
	/*				��				��			��			��											*/
	/*				��				��			��			��������	 �̹��� ������ ��(x��)					*/
	/*				��				��			��														*/
	/*				��				��			��������	 �̹��� ������(y��)									*/
	/*				��				��																	*/
	/*				��				��������	 �̹��� ������(x��)												*/
	/*				��																					*/
	/*				�������� ���ϸ� (ex. L"sample.png" // �ݵ�� ���ϸ� �տ� L�� �ٿ� �� ��)					*/
	void release();

	void render(float opacity = 1.0);
	void render(int destX, int destY, float opacity = 1.0);
	void render(int destX, int destY, float sizeX, float sizeY, float opacity = 1.0);
	void render(int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, float opacity = 1.0);
	/*				��			��			��			��			��			��				��					*/
	/*				��			��			��			��			��			��				��������	 ����			*/
	/*				��			��			��			��			��			��									*/
	/*				��			��			��			��			��			��������	 �̹������� �����ؿ� ������(y��)	*/
	/*				��			��			��			��			��												*/
	/*				��			��			��			��			��������	 �̹������� �����ؿ� ������(x��)				*/
	/*				��			��			��			��															*/
	/*				��			��			��			��������	 �̹������� �����ؿ� ������ǥ(y��)							*/
	/*				��			��			��																		*/
	/*				��			��			��������	 �̹������� �����ؿ� ������ǥ(x��)										*/
	/*				��			��																					*/
	/*				��			��������	 ����� ��ǥ(y��)																	*/
	/*				��																								*/
	/*				�������� ����� ��ǥ(x��)																				*/

	void frameRender(int destX, int destY, float opacity = 1.0);
	void frameRender(int destX, int destY,	int currentFrameX, int currentFrameY, float opacity = 1.0);
	/*					��			��				��				��					��				*/
	/*					��			��				��				��					��������	 ����		*/
	/*					��			��				��				��									*/
	/*					��			��				��				��������	 ���� ������(y��)					*/
	/*					��			��				��													*/
	/*					��			��				��������	 ���� ������(x��)									*/
	/*					��			��																	*/
	/*					��			��������	 ����� ��ǥ(y��)													*/
	/*					��																				*/
	/*					�������� ����� ��ǥ(x��)																*/


	void aniRender(int destX, int destY, animation* ani);
	void aniRender(int destX, int destY, float angle, animation* ani);
	void scaleRender(int destX, int destY, float sizeX, float sizeY, float opacity = 1.0f);
	void scaleRender(int destX, int destY, int sourX, int sourY, int sourwidth, int sourheight, float sizeX, float sizeY, float opacity = 1.0f);
	void frameRender(int destX, int destY, int currentFrameX, int currentFrameY, float sizeX, float sizeY, float opacity = 1.0); //z������
	//===============================================
	// ## �̹��� ���� ������ ������ ##
	//=============================================

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ?
			_imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ?
			_imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;

		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;

		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	ID2D1HwndRenderTarget* getRenderTarget() { return _imgBitmap->_dRenderTarget; }
	ID2D1BitmapRenderTarget* getBitRenderTarget() { return _imgBitmap->_dBitRenderTarget; }

	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }

	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }
};

