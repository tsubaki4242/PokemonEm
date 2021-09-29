#include "stdafx.h"
#include "playGround.h"
#include "tileClass.h"
#include "title.h"
#include "main.h"
#include "flowerVillage.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ��� ����
HRESULT playGround::init()
{	

	gameNode::init(true);
	IMGALL();

	IMAGEMANAGER->addDImage("�ƿ�", L"UI/menu/fadeOut.png", 1000, 600);



	SCENEMANAGER->addScene("test", new tileClass);
	SCENEMANAGER->addScene("flowerVillage", new flowerVillage);
	SCENEMANAGER->addScene("title", new title);
	SCENEMANAGER->addScene("main", new main);
	SCENEMANAGER->changeScene("flowerVillage");


	_debug = false;

	return S_OK;
}

//�޸� ������ ����� �ϼ��� ����
void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown(VK_TAB)) {
		_debug = !_debug;
		PRINTMANAGER->setDebug(_debug);
	}

	SCENEMANAGER->update();

}


void playGround::render()
{
	if (SCENEMANAGER->getSeanName() == "title")
	{
		SCENEMANAGER->render();
	}
	else
	{


		D2DMANAGER->beginDraw();
		SCENEMANAGER->render();
		RENDERMANAGER->render();
		TXTRENDERMANGER->render();
		D2DMANAGER->endDraw();
		D2DMANAGER->render();
	}

}

void playGround::IMGALL()
{
	IMAGEMANAGER->addDImage("����", L"img/title.png", 1000, 600);
	//hp
		//hpbar
	IMAGEMANAGER->addDImage("Lv�ڽ�", L"UI/menu/overlay_lv.png", 44, 28);
	IMAGEMANAGER->addDImage("HP�ڽ�", L"UI/menu/invenHpBar.png", 276, 28);
	IMAGEMANAGER->addDImage("HP�ڽ�Back", L"UI/menu/invenHpBarBack.png", 208, 16);
	IMAGEMANAGER->addDImage("HPbar�׸�", L"UI/menu/invenHpBarGreen.png", 208, 16);
	IMAGEMANAGER->addDImage("HPbar������", L"UI/menu/invenHpBarOrenge.png", 208, 16);
	IMAGEMANAGER->addDImage("HPbar����", L"UI/menu/invenHpBarRed.png", 208, 16);

	//Ÿ��
	IMAGEMANAGER->addDImage("�븻", L"pokemon/type/�븻.png", 128, 56);
	IMAGEMANAGER->addDImage("��", L"pokemon/type/��.png", 128, 56);
	IMAGEMANAGER->addDImage("��", L"pokemon/type/��.png", 128, 56);
	IMAGEMANAGER->addDImage("����", L"pokemon/type/����.png", 128, 56);
	IMAGEMANAGER->addDImage("Ǯ", L"pokemon/type/Ǯ.png", 128, 56);
	IMAGEMANAGER->addDImage("����", L"pokemon/type/����.png", 128, 56);
	IMAGEMANAGER->addDImage("��ö", L"pokemon/type/��ö.png", 128, 56);
	IMAGEMANAGER->addDImage("��Ʈ", L"pokemon/type/��Ʈ.png", 128, 56);
	IMAGEMANAGER->addDImage("������", L"pokemon/type/������.png", 128, 56);
	IMAGEMANAGER->addDImage("����", L"pokemon/type/����.png", 128, 56);
	IMAGEMANAGER->addDImage("����", L"pokemon/type/����.png", 128, 56);
	IMAGEMANAGER->addDImage("��", L"pokemon/type/��.png", 128, 56);
	IMAGEMANAGER->addDImage("����", L"pokemon/type/����.png", 128, 56);
	IMAGEMANAGER->addDImage("����", L"pokemon/type/����.png", 128, 56);
	IMAGEMANAGER->addDImage("��", L"pokemon/type/��.png", 128, 56);
	IMAGEMANAGER->addDImage("�巡��", L"pokemon/type/�巡��.png", 128, 56);
	IMAGEMANAGER->addDImage("��", L"pokemon/type/��.png", 128, 56);
	IMAGEMANAGER->addDImage("��", L"pokemon/type/��.png", 128, 56);
	IMAGEMANAGER->addFrameDImage("���ͳ�����", L"Battle/���� ������.png", 14000, 600, 14, 1);
	IMAGEMANAGER->addDImage("�ƿ�", L"UI/menu/fadeOut.png", 1000, 600);

	IMAGEMANAGER->addFrameDImage("iconNull", L"pokemon/icon/iconNull.png", 128, 64, 2, 1);
	//�κ��丮 �׸�
	IMAGEMANAGER->addDImage("�̻��ؾ� E", L"UI/invenPokemon/001.png", 480, 480);
	IMAGEMANAGER->addDImage("�̻���Ǯ E", L"UI/invenPokemon/002.png", 480, 480);
	IMAGEMANAGER->addDImage("�̻��ز� E", L"UI/invenPokemon/003.png", 480, 480);

	//������
	IMAGEMANAGER->addFrameDImage("�̻��ؾ� I", L"pokemon/icon/icon001.png", 128, 64, 2, 1);
	IMAGEMANAGER->addFrameDImage("�̻���Ǯ I", L"pokemon/icon/icon002.png", 128, 64, 2, 1);
	IMAGEMANAGER->addFrameDImage("�̻��ز� I", L"pokemon/icon/icon003.png", 128, 64, 2, 1);
	//�տ� �̹���
	IMAGEMANAGER->addFrameDImage("�̻��ؾ�", L"pokemon/Front/001.png", 3762, 38, 99, 1);
	IMAGEMANAGER->addFrameDImage("�̻���Ǯ", L"pokemon/Front/002.png", 6438, 58, 111, 1);
	IMAGEMANAGER->addFrameDImage("�̻��ز�", L"pokemon/Front/003.png", 14362, 86, 167, 1);

	//�ڿ� �̹���
	IMAGEMANAGER->addFrameDImage("�̻��ؾ� b", L"pokemon/Back/001b.png", 3762, 38, 99, 1);
	IMAGEMANAGER->addFrameDImage("�̻���Ǯ b", L"pokemon/Back/002b.png", 6327, 57, 111, 1);
	IMAGEMANAGER->addFrameDImage("�̻��ز� b", L"pokemon/Back/003b.png", 14863, 89, 167, 1);
	
	//��ų�̹���
	IMAGEMANAGER->addFrameDImage("�����ġ��", L"pokemon/Animations/003-Attack01.png", 960, 384, 5,2);
	IMAGEMANAGER->addFrameDImage("������ȭ", L"pokemon/Animations/Light1.png", 960, 576, 5, 3);

}
