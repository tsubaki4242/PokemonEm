#pragma once

#define RENDERCOUNT		0.05
#define RENDERCOUNT2	RENDERCOUNT * 2
enum CTRL
{
	CTRL_SAVE,			//���̺�		��ư
	CTRL_LOAD,			//�ε�		��ư
	CTRL_TERRAINDRAW,	//����		��ư
	CTRL_TERRAINDRAW2,	//����2		��ư
	CTRL_BUILD,			//�ǹ� ��ư
	CTRL_OBJDRAW,		//������Ʈ	��ư
	CTRL_ERASER,		//���찳		��ư
	CTRL_END
};

class gameNode
{
private:
	bool _managerInit;

public:
	gameNode();
	virtual ~gameNode();
	int _ctrSelect;
	//HRESULT ���� ���� ��ȯ�����ε�
	//S_OK, E_FAIL, SUCCEDED
	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� �Լ�
	virtual void render();			//�׸��� �Լ�

	void cursorOnWindow();
	//����� ������
	//void setBackBufferSize(float width, float height){ _backBuffer->setwidth}

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};