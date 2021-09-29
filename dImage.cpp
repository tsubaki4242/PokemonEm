#include "stdafx.h"
#include "dImage.h"

dImage::dImage()
	: _imageInfo(NULL),
	_fileName(NULL),
	_wicFactory(NULL),
	_bitDecoder(NULL),
	_bitFrame(NULL),
	_wicConverter(NULL)
{
}

dImage::~dImage()
{
}

HRESULT dImage::init(LPCWCHAR fileName, int width, int height)
{
	if (_imageInfo != NULL) release();

	_imageInfo = new IMAGE_INFO;
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = fileName;

	HRESULT hr;

	//WICFactory ����
	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_wicFactory));

	//WICFactory���� �� decoder����(�̹��� ���� ���� ���� �����̳�)
	if (SUCCEEDED(hr)) {
		hr = _wicFactory->CreateDecoderFromFilename(_fileName, nullptr,
			GENERIC_READ, WICDecodeMetadataCacheOnDemand, &_bitDecoder);
	}
	
	//decoder���� �̹��� ������ ����
	if (SUCCEEDED(hr)) {
		hr = _bitDecoder->GetFrame(0, &_bitFrame);
	}

	//������ ����
	if (SUCCEEDED(hr)) {
		hr = _wicFactory->CreateFormatConverter(&_wicConverter);
	}

	//�����Ϳ� ������ �̹��� ������ �־ ��ȯ
	if (SUCCEEDED(hr)) {
		_wicConverter->Initialize(_bitFrame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			nullptr,
			0.0f,
			WICBitmapPaletteTypeCustom
		);
	}

	//���� �׸��� ������ ��Ʈ�� �������� �ε�
	if (SUCCEEDED(hr)) {
		hr = D2DMANAGER->getRenderTarget()->CreateBitmapFromWicBitmap(_wicConverter, nullptr, &_imageInfo->bitMap);
	}

	return S_OK;
}

HRESULT dImage::init(LPCWCHAR fileName, int width, int height, int frameX, int frameY)
{
	if (_imageInfo != NULL) release();

	_imageInfo = new IMAGE_INFO;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	_fileName = fileName;

	HRESULT hr = E_FAIL;

	//WICFactory ����
	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_wicFactory));

	//WICFactory���� �� decoder����(�̹��� ���� ���� ���� �����̳�)
	if (SUCCEEDED(hr)) {
		hr = _wicFactory->CreateDecoderFromFilename(_fileName, nullptr,
			GENERIC_READ, WICDecodeMetadataCacheOnDemand, &_bitDecoder);
	}

	//decoder���� �̹��� ������ ����
	if (SUCCEEDED(hr)) {
		hr = _bitDecoder->GetFrame(0, &_bitFrame);
	}

	//������ ����
	if (SUCCEEDED(hr)) {
		hr = _wicFactory->CreateFormatConverter(&_wicConverter);
	}

	//�����Ϳ� ������ �̹��� ������ �־ ��ȯ
	if (SUCCEEDED(hr)) {
		_wicConverter->Initialize(_bitFrame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			nullptr,
			0.0f,
			WICBitmapPaletteTypeCustom
		);
	}

	//���� �׸��� ������ ��Ʈ�� �������� �ε�
	if (SUCCEEDED(hr)) {
		hr = D2DMANAGER->getRenderTarget()->CreateBitmapFromWicBitmap(_wicConverter, nullptr, &_imageInfo->bitMap);
	}

	return hr;
}

void dImage::release()
{
	if (_imageInfo)
	{
		//�̹��� ���� ����
		SAFE_RELEASE2(_imageInfo->bitMap);
		SAFE_DELETE(_imageInfo);
	}

	//SAFE_DELETE(_fileName);
	//�̹��� �ε�� ��ü ����
	SAFE_RELEASE2(_wicFactory);
	SAFE_RELEASE2(_bitDecoder);
	SAFE_RELEASE2(_bitFrame);
	SAFE_RELEASE2(_wicConverter);
}

void dImage::render(float opacity)
{
	D2D1_RECT_F destRect = dRectMake(_imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height);
	
	
	//rendertarget�� �ҷ��ͼ� �̹����� ��Ʈ���� �׷��ش�
	D2DMANAGER->getBitRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect, opacity);
}

void dImage::render(int destX, int destY, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, _imageInfo->width, _imageInfo->height);

	//rendertarget�� �ҷ��ͼ� �̹����� ��Ʈ���� �׷��ش�
	D2DMANAGER->getBitRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect, opacity);

	


}

void dImage::render(int destX, int destY, float sizeX, float sizeY, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, sizeX, sizeY);

	//rendertarget�� �ҷ��ͼ� �̹����� ��Ʈ���� �׷��ش�
	D2DMANAGER->getBitRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect, opacity);
}
void dImage::render(int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, sourWidth, sourHeight);
	D2D1_RECT_F sourRect = dRectMake(sourX, sourY, sourWidth, sourHeight);

	//rendertarget�� �ҷ��ͼ� �̹����� ��Ʈ���� �׷��ش�
	D2DMANAGER->getBitRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect,
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourRect);
	

}

void dImage::frameRender(int destX, int destY, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight);
	D2D1_RECT_F sourRect = dRectMake(
		_imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight,
		_imageInfo->frameWidth, _imageInfo->frameHeight);

	//rendertarget�� �ҷ��ͼ� �̹����� ��Ʈ���� �׷��ش�
	D2DMANAGER->getBitRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect,
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourRect);
}

void dImage::frameRender(int destX, int destY, int currentFrameX, int currentFrameY, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight);
	D2D1_RECT_F sourRect = dRectMake(
currentFrameX * _imageInfo->frameWidth, currentFrameY * _imageInfo->frameHeight,
		_imageInfo->frameWidth, _imageInfo->frameHeight);

	//rendertarget�� �ҷ��ͼ� �̹����� ��Ʈ���� �׷��ش�
	D2DMANAGER->getBitRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect,
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourRect);
}

void dImage::aniRender(int destX, int destY, animation * ani)
{


	render( destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());

}

void dImage::aniRender(int destX, int destY, float angle, animation * ani)
{
	D2D1_POINT_2F pt = { ani->getFrameWidth(),  ani->getFrameHeight() };
	render(destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
	D2DMANAGER->getBitRenderTarget()->SetTransform(Matrix3x2F::Rotation(angle, pt));
	//DTDMANAGER->getBitRenderTarget()->SetTransform(Matrix3x2F::Identity());

}

void dImage::scaleRender(int destX, int destY, float sizeX, float sizeY, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, _imageInfo->width * sizeX, _imageInfo->height* sizeY);

	//rendertarget�� �ҷ��ͼ� �̹����� ��Ʈ���� �׷��ش�
	D2DMANAGER->getBitRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect, opacity);
}

void dImage::scaleRender(int destX, int destY, int sourX, int sourY, int sourwidth, int sourheight, float sizeX, float sizeY, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, sourwidth* sizeX, sourheight* sizeY);
	D2D1_RECT_F sourRect = dRectMake(sourX, sourY, sourwidth* sizeX, sourheight* sizeY);

	//rendertarget�� �ҷ��ͼ� �̹����� ��Ʈ���� �׷��ش�
	D2DMANAGER->getBitRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect,
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourRect);

}

void dImage::frameRender(int destX, int destY, int currentFrameX, int currentFrameY, float sizeX, float sizeY, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, sizeX, sizeY);
	D2D1_RECT_F sourRect = dRectMake(
		currentFrameX * _imageInfo->frameWidth, currentFrameY * _imageInfo->frameHeight,
		_imageInfo->frameWidth, _imageInfo->frameHeight);

	//rendertarget�� �ҷ��ͼ� �̹����� ��Ʈ���� �׷��ش�
	D2DMANAGER->getBitRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect,
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourRect);
}
