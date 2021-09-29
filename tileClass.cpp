#include "stdafx.h"
#include "tileClass.h"



HRESULT tileClass::init()
{
	CAMERAMANAGER->setBackScreenSize(3840, 2160);//������ �� �־������

	menuIMG();
	tileIMG();
	Button();
	x = 0;
	y = 0;
	_groundNum = 0;
	_objectNum = 0;
	setup();

	//_player = new player;
	//_player->init();
	return S_OK;
}

void tileClass::release()
{
}

void tileClass::update()
{


	CAMERAMANAGER->updateScreen(x, y);


	ButtonRenewal();
	setMap();
	updateRect();
	RectCollisn();
	keyControl();
//	_player->update();
	//_playerRECT =_player->getplayerRect();
}


void tileClass::render()
{


	//���� �׸���
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_mapTileImge[_tiles[i].terrainImgIndex]->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

	}
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].terrain2 == TR2_NONE) continue;
		_mapTileImge[_tiles[i].terrainImgIndex2]->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrain2FrameX, _tiles[i].terrain2FrameY);

	}
	//������Ʈ �׸���
	for (int i = 0; i < TILEX * TILEY; ++i)
	{

		

		//cout << playerY << endl;
		//������Ʈ �Ӽ��� �ƴϸ� �׸����ʰԲ� ����ó��
		if (_tiles[i].obj == OBJ_NONE) continue;
		//if (_tiles[_tiles[i].objImgIndex].objImage == nullptr) continue;
		_mapTileImge[_tiles[i].objImgIndex]->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);

		//RENDERMANAGER->push_BackFrameRenderInfo(
		//	_tiles[_tiles[i].buildImgIndex].tileObjZOrder,
		//	_mapTileImge[_tiles[i].objImgIndex],
		//	_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
	}
	//�ǹ�
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[_tiles[i].buildImgIndex].tileObjZOrderBild = 3;
		//�ǹ� �Ӽ��� �ƴϸ� �׸����ʰԲ� ����ó��
		if (_tiles[i].build == BU_NONE) continue;
		//if (_tiles[_tiles[i].buildImgIndex].buildImage == nullptr) continue;
		_mapTileImge[_tiles[i].buildImgIndex]->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].buildFrameX, _tiles[i].buildFrameY);

		//RENDERMANAGER->push_BackFrameRenderInfo(
		//	_tiles[_tiles[i].buildImgIndex].tileObjZOrderBild,
		//	_mapTileImge[_tiles[i].buildImgIndex],
		//	_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].buildFrameX, _tiles[i].buildFrameY);

	}

//	DTDMANAGER->Rectangle(test);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			D2DMANAGER->setBrushColor(ColorF(ColorF::Magenta));
			D2DMANAGER->Rectangle(_tiles[i].rc);
			D2DMANAGER->setBrushColor(ColorF(ColorF::Black));
		}

	}
	if (KEYMANAGER->isToggleKey('2'))
	{
		ToggleKeyIMG();
	}

	if (KEYMANAGER->isToggleKey('1'))
	{
		_UION = true;
		_groundImg->render(_ground.left, _ground.top);
		_groundImg2->render(_ground2.left, _ground2.top);
		_objectImg->render(_object.left, _object.top);
		_waterImg->render(_water.left, _water.top);
		_buildImg->render(_build.left, _build.top);
		_saveImg->render(_save.left, _save.top);
		_loadImg->render(_load.left, _load.top);
		_groundArrowImg->render(_groundArrow.left, _groundArrow.top);
		_objectArrowImg->render(_objectArrow.left, _objectArrow.top);
		_buildArrowImg->render(_buildArrow.left, _buildArrow.top);
		_groundArrowImg2->render(_groundArrow2.left, _groundArrow2.top);
	}
	else
	{
		_UION = false;
		_groundMenuOn = false;
	}
	//�޴�
	if (_groundMenuOn == true)
	{
		_groundMenuImg->render(_groundMenu.left, _groundMenu.top);
		_mapTileImge[_tileSetNum]->render(_mapTileRect[0].left + CAMERAMANAGER->getScreen().left, _mapTileRect[0].top + CAMERAMANAGER->getScreen().top);
		D2DMANAGER->Rectangle(_tileChoice);
	}
	//_player->render();

	//cout << _load.left << endl;
}

void tileClass::maprender(RECT playerRC)
{
	//���� �׸���
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_mapTileImge[_tiles[i].terrainImgIndex]->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

	}
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].terrain2 == TR2_NONE) continue;
		//if (playerRC.bottom >= _tiles[i].rc.bottom)
		//{
		//	_tiles[_tiles[i].buildImgIndex].tileTerrainZOrder = 0;
		//}
		//else
		//{
		//	_tiles[_tiles[i].buildImgIndex].tileTerrainZOrder = 2;
		//}
		
			_mapTileImge[_tiles[i].terrainImgIndex2]->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrain2FrameX, _tiles[i].terrain2FrameY);

		//RENDERMANAGER->push_BackFrameRenderInfo(
		//	_tiles[_tiles[i].buildImgIndex].tileTerrainZOrder,
		//	_mapTileImge[_tiles[i].terrainImgIndex2],
		//	_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrain2FrameX, _tiles[i].terrain2FrameY);

	}
	//������Ʈ �׸���

	for (int i = 0; i < TILEX * TILEY; ++i)
	{


		if (playerRC.bottom >= _tiles[i].rc.bottom)
		{
			_tiles[_tiles[i].buildImgIndex].tileObjZOrder = 0;
		}
		else
		{
			_tiles[_tiles[i].buildImgIndex].tileObjZOrder = 2;
		}
		//cout << playerY << endl;
		//������Ʈ �Ӽ��� �ƴϸ� �׸����ʰԲ� ����ó��
		if (_tiles[i].obj == OBJ_NONE) continue;
		//if (_tiles[_tiles[i].objImgIndex].objImage == nullptr) continue;
		//_mapTileImge[_tiles[i].objImgIndex]->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
		

			RENDERMANAGER->push_BackFrameRenderInfo(
				_tiles[_tiles[i].buildImgIndex].tileObjZOrder, _tiles[i].rc,
				_mapTileImge[_tiles[i].objImgIndex],
				_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
		
	}
	//�ǹ�
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[_tiles[i].buildImgIndex].tileObjZOrderBild = 3;
		//�ǹ� �Ӽ��� �ƴϸ� �׸����ʰԲ� ����ó��
		if (_tiles[i].build == BU_NONE) continue;
		//if (_tiles[_tiles[i].buildImgIndex].buildImage == nullptr) continue;
//		_mapTileImge[_tiles[i].buildImgIndex]->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].buildFrameX, _tiles[i].buildFrameY);


		RENDERMANAGER->push_BackFrameRenderInfo(
			_tiles[_tiles[i].buildImgIndex].tileObjZOrderBild, _tiles[i].rc,
			_mapTileImge[_tiles[i].buildImgIndex],
			_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].buildFrameX, _tiles[i].buildFrameY);

	}

	//	DTDMANAGER->Rectangle(test);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			D2DMANAGER->setBrushColor(ColorF(ColorF::Magenta));
			D2DMANAGER->Rectangle(_tiles[i].rc);
			D2DMANAGER->setBrushColor(ColorF(ColorF::Black));
		}

	}
	if (KEYMANAGER->isToggleKey('2'))
	{
		ToggleKeyIMG();
	}


	else
	{
		_UION = false;
		_groundMenuOn = false;
	}
	//�޴�
	if (_groundMenuOn == true)
	{
		_groundMenuImg->render(_groundMenu.left, _groundMenu.top);
		_mapTileImge[_tileSetNum]->render(_mapTileRect[0].left + CAMERAMANAGER->getScreen().left, _mapTileRect[0].top + CAMERAMANAGER->getScreen().top);
		D2DMANAGER->Rectangle(_tileChoice);
	}
}

void tileClass::setup()
{

	//ó�� ��Ʈ�� ���´� ��������
	_ctrSelect = CTRL_TERRAINDRAW;

	//Ÿ�ϼ� ���� ����
	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_sampleTile[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTile[i * SAMPLETILEX + j].terrainFrameY = i;

			//Ÿ�ϼ¿� ��Ʈ�� ����

			SetRect(&_sampleTile[i * SAMPLETILEX + j].rcTile,
				(_mapTileRect[0].left + CAMERAMANAGER->getScreen().left) + j * TILESIZE,
				(_mapTileRect[0].top + CAMERAMANAGER->getScreen().top) + i * TILESIZE,
				(_mapTileRect[0].left + CAMERAMANAGER->getScreen().left) + j * TILESIZE + TILESIZE,
				(_mapTileRect[0].top + CAMERAMANAGER->getScreen().top) + i * TILESIZE + TILESIZE);

		}
	}

	//Ÿ�� ����
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			SetRect(&_tiles[i * TILEX + j].rc,
				j * TILESIZE,
				i * TILESIZE,
				j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}


	for (int i = 0; i < TILEX * TILEY; ++i)
	{

		_tiles[i].terrainFrameX = 7;
		_tiles[i].terrainFrameY = 6;
		_tiles[i].terrain2FrameX = 0;
		_tiles[i].terrain2FrameY = 0;
		_tiles[i].buildFrameX = 0;
		_tiles[i].buildFrameY = 0;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = TR_MOVE;
		_tiles[i].terrain2 = TR2_NONE;
		_tiles[i].obj = OBJ_NONE;
		_tiles[i].build = BU_NONE;
	}
}

void tileClass::setMap()
{
	RECT temp;

	_Mouse.Origin.x = _ptMouse.x + CAMERAMANAGER->getScreen().left;
	_Mouse.Origin.y = _ptMouse.y + CAMERAMANAGER->getScreen().top;
	if (_groundMenuOn == true)
	{

		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; ++i)
		{
			if (PtInRect(&_sampleTile[i].rcTile, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{

				_currentTile.startX = _sampleTile[i].terrainFrameX;
				_currentTile.startY = _sampleTile[i].terrainFrameY;
				_startRECT = _sampleTile[i].rcTile;



			}
		}




		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; ++i)
		{
			if (PtInRect(&_sampleTile[i].rcTile, _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				_currentTile.endX = _sampleTile[i].terrainFrameX;
				_currentTile.endY = _sampleTile[i].terrainFrameY;

				_currentTile.sizeX = _currentTile.endX + 1 - _currentTile.startX;
				_currentTile.sizeY = _currentTile.endY + 1 - _currentTile.startY;
				_tiles[i].terrainStartFrameX = _currentTile.startX;

				//cout << _tiles[i].terrainFrameX << endl;
			}
			_tileChoice = RectMake(_startRECT.left + CAMERAMANAGER->getScreen().left, _startRECT.top + CAMERAMANAGER->getScreen().top, 32 * (_currentTile.endX - _currentTile.startX + 1),
				32 * (_currentTile.endY - _currentTile.startY + 1));
		}

	}

	
	if (_UION == false)
	{
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (PtInRect(&_tiles[i].rc, _Mouse.Origin) && KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _groundMenuOn == false)
			{


				if (_ctrSelect == CTRL_TERRAINDRAW)
				{
					for (int j = 0; j < _currentTile.sizeY; j++)
					{
						for (int k = 0; k < _currentTile.sizeX; k++)
						{
							if (i + j * TILEX + k >= TILEX * TILEY) continue;
							_tiles[i + j * TILEX + k].terrainImgIndex = _tileSetNum;
							_tiles[i + j * TILEX + k].terrainFrameX = _currentTile.startX + k;
							_tiles[i + j * TILEX + k].terrainFrameY = _currentTile.startY + j;
							_tiles[i + j * TILEX + k].terrainStartFrameX = _currentTile.startX +k;




							if (_groundNum == 0 )
							{
								_tiles[i + j * TILEX + k].terrain = TR_MOVE;
							}
							if (_groundNum == 1 )
							{
								_tiles[i + j * TILEX + k].terrain = TR_UNMOVE;
							}
							if (_groundNum == 2 )
							{
								_tiles[i + j * TILEX + k].terrain = TR_BOTTOM;
							}
							if (_groundNum == 3 )
							{
								_tiles[i + j * TILEX + k].terrain = TR_TOP;
							}
							if (_groundNum == 4 )
							{
								_tiles[i + j * TILEX + k].terrain = TR_LEFT;
							}
							if (_groundNum == 5 )
							{
								_tiles[i + j * TILEX + k].terrain = TR_RIGHT;
							}
							if (_groundNum == 6 )
							{
								_tiles[i + j * TILEX + k].terrain = TR_RT;
							}
							if (_groundNum == 7 )
							{
								_tiles[i + j * TILEX + k].terrain = TR_RB;
							}

							if (_groundNum == 8  )
							{
								_tiles[i + j * TILEX + k].terrain = TR_LB;
							}
							if (_groundNum == 9  )
							{
								_tiles[i + j * TILEX + k].terrain = TR_LT;
							}
							if (_groundNum == 10  )
							{
								_tiles[i + j * TILEX + k].terrain = TR_TB;
							}
							if (_groundNum == 11  )
							{
								_tiles[i + j * TILEX + k].terrain = TR_LR;
							}
							if (_groundNum == 12  )
							{
								_tiles[i + j * TILEX + k].terrain = TR_BTR;
							}
							if (_groundNum == 13  )
							{
								_tiles[i + j * TILEX + k].terrain = TR_BTL;

							}
							if (_groundNum == 14  )
							{
								_tiles[i + j * TILEX + k].terrain = TR_LTR;
							}
							if (_groundNum == 15  )
							{
								_tiles[i + j * TILEX + k].terrain = TR_LBR;
							}
							if (_groundNum == 16  )
							{
								_tiles[i + j * TILEX + k].terrain = TR_WATER;
							}
							if (_groundNum == 17  )
							{
								_tiles[i + j * TILEX + k].terrain = TR_LIGHT;
							}
							if (_groundNum == 18  )
							{
								_tiles[i + j * TILEX + k].terrain = TR_MOSTER;
							}

						}
					}
					break;
				}
				// ���� ��
				else if (_ctrSelect == CTRL_TERRAINDRAW2)
				{
						for (int j = 0; j < _currentTile.sizeY; j++)
						{
							for (int k = 0; k < _currentTile.sizeX; k++)
							{
								if (i + j * TILEX + k >= TILEX * TILEY) continue;
								_tiles[i + j * TILEX + k].terrainImgIndex2 = _tileSetNum;
								_tiles[i + j * TILEX + k].terrain2FrameX = _currentTile.startX + k;
								_tiles[i + j * TILEX + k].terrain2FrameY = _currentTile.startY + j;
								_tiles[i + j * TILEX + k].terrainStart2FrameX = _currentTile.startX + k;
								if (_groundNum2 == 0)
								{
									_tiles[i + j * TILEX + k].terrain2 = TR2_MOVE;
								}
								if (_groundNum2 == 1)
								{
									_tiles[i + j * TILEX + k].terrain2 = TR2_UNMOVE;
								}
								if (_groundNum2 == 2)
								{
									_tiles[i + j * TILEX + k].terrain2 = TR2_BOTTOM;
								}
								if (_groundNum2 == 3)
								{
									_tiles[i + j * TILEX + k].terrain2 = TR2_TOP;
								}
								if (_groundNum2 == 4)
								{
									_tiles[i + j * TILEX + k].terrain2 = TR2_LEFT;
								}
								if (_groundNum2 == 5)
								{
									_tiles[i + j * TILEX + k].terrain2 = TR2_RIGHT;
								}
								if (_groundNum2 == 6)
								{
									_tiles[i + j * TILEX + k].terrain2  = TR2_RT;
								}
								if (_groundNum2 == 7)
								{
									_tiles[i + j * TILEX + k].terrain2 = TR2_RB;
								}

								if (_groundNum2 == 8)
								{
									_tiles[i + j * TILEX + k].terrain2 = TR2_LB;
								}
								if (_groundNum2 == 9)
								{
									_tiles[i + j * TILEX + k].terrain2 = TR2_LT;
								}
								if (_groundNum2 == 10)
								{
									_tiles[i + j * TILEX + k].terrain2 = TR2_TB;
								}
								if (_groundNum2 == 11)
								{
									_tiles[i + j * TILEX + k].terrain2 = TR2_LR;
								}
								if (_groundNum2 == 12)
								{
									_tiles[i + j * TILEX + k].terrain2 = TR2_BTR2;
								}
								if (_groundNum2 == 13)
								{
									_tiles[i + j * TILEX + k].terrain2 = TR2_BTL;

								}
								if (_groundNum2 == 14)
								{
									_tiles[i + j * TILEX + k].terrain2 = TR2_LTR2;
								}
								if (_groundNum2 == 15)
								{
									_tiles[i + j * TILEX + k].terrain2 = TR2_LBR;
								}
								if (_groundNum2 == 16)
								{
									_tiles[i + j * TILEX + k].terrain2 = TR2_WATER;
								}
								if (_groundNum2 == 17)
								{
									_tiles[i + j * TILEX + k].terrain2 = TR2_LIGHT;
								}
								if (_groundNum2 == 18)
								{
									_tiles[i + j * TILEX + k].terrain2 = TR2_MOSTER;
								}

							}
						}
					break;
				}
				else if (_ctrSelect == CTRL_OBJDRAW)
				{
					for (int j = 0; j < _currentTile.sizeY; j++)
					{
						for (int k = 0; k < _currentTile.sizeX; k++)
						{
							if (i + j * TILEX + k >= TILEX * TILEY) continue;
							_tiles[i + j * TILEX + k].objImgIndex = _tileSetNum;
							_tiles[i + j * TILEX + k].objFrameX = _currentTile.startX + k;
							_tiles[i + j * TILEX + k].objFrameY = _currentTile.startY + j;

							if (_objectNum == 0)
							{
								_tiles[i + j * TILEX + k].obj = OBJ_MOVE;
							}
							if (_objectNum == 1)
							{
								_tiles[i + j * TILEX + k].obj = OBJ_UNMOVE;
							}
							if (_objectNum == 2)
							{
								_tiles[i + j * TILEX + k].obj = OBJ_BOTTOM;
							}
							if (_objectNum == 3)
							{
								_tiles[i + j * TILEX + k].obj = OBJ_TOP;
							}
							if (_objectNum == 4)
							{
								_tiles[i + j * TILEX + k].obj = OBJ_LEFT;
							}
							if (_objectNum == 5)
							{
								_tiles[i + j * TILEX + k].obj = OBJ_RIGHT;
							}
							if (_objectNum == 6)
							{
								_tiles[i + j * TILEX + k].obj = OBJ_RT;
							}
							if (_objectNum == 7)
							{
								_tiles[i + j * TILEX + k].obj = OBJ_RB;
							}

							if (_objectNum == 8)
							{
								_tiles[i + j * TILEX + k].obj = OBJ_LB;
							}
							if (_objectNum == 9)
							{
								_tiles[i + j * TILEX + k].obj = OBJ_LT;
							}
							if (_objectNum == 10)
							{
								_tiles[i + j * TILEX + k].obj = OBJ_TB;
							}
							if (_objectNum == 11)
							{
								_tiles[i + j * TILEX + k].obj = OBJ_LR;
							}
							if (_objectNum == 12)
							{
								_tiles[i + j * TILEX + k].obj = OBJ_BTR;
							}
							if (_objectNum == 13)
							{
								_tiles[i + j * TILEX + k].obj = OBJ_BTL;

							}
							if (_objectNum == 14)
							{
								_tiles[i + j * TILEX + k].obj = OBJ_LTR;
							}
							if (_objectNum == 15)
							{
								_tiles[i + j * TILEX + k].obj = OBJ_LBR;
							}
							if (_objectNum == 16)
							{
								_tiles[i + j * TILEX + k].obj = OBJ_MOSTER;
							}
						}
					}
					break;
				}
				else if (_ctrSelect == CTRL_BUILD)
				{
					for (int j = 0; j < _currentTile.sizeY; j++)
					{
						for (int k = 0; k < _currentTile.sizeX; k++)
						{
							if (i + j * TILEX + k >= TILEX * TILEY) continue;
							_tiles[i + j * TILEX + k].buildImgIndex = _tileSetNum;
							_tiles[i + j * TILEX + k].buildFrameX = _currentTile.startX + k;
							_tiles[i + j * TILEX + k].buildFrameY = _currentTile.startY + j;


							if (_buildNum == 0)
							{
								_tiles[i + j * TILEX + k].build = BU_MOVE;
							}
							if (_buildNum == 1)
							{
								_tiles[i + j * TILEX + k].build = BU_UNMOVE;
							}
							if (_buildNum == 2)
							{
								_tiles[i + j * TILEX + k].build = BU_BOTTOM;
							}
							if (_buildNum == 3)
							{
								_tiles[i + j * TILEX + k].build = BU_TOP;
							}
							if (_buildNum == 4)
							{
								_tiles[i + j * TILEX + k].build = BU_LEFT;
							}
							if (_buildNum == 5)
							{
								_tiles[i + j * TILEX + k].build = BU_RIGHT;
							}
							if (_buildNum == 6)
							{
								_tiles[i + j * TILEX + k].build = BU_RT;
							}
							if (_buildNum == 7)
							{
								_tiles[i + j * TILEX + k].build = BU_RB;
							}

							if (_buildNum == 8)
							{
								_tiles[i + j * TILEX + k].build = BU_LB;
							}
							if (_buildNum == 9)
							{
								_tiles[i + j * TILEX + k].build = BU_LT;
							}
							if (_buildNum == 10)
							{
								_tiles[i + j * TILEX + k].build = BU_TB;
							}
							if (_buildNum == 11)
							{
								_tiles[i + j * TILEX + k].build = BU_LR;
							}
							if (_buildNum == 12)
							{
								_tiles[i + j * TILEX + k].build = BU_BTR;
							}
							if (_buildNum == 13)
							{
								_tiles[i + j * TILEX + k].build = BU_BTL;

							}
							if (_buildNum == 14)
							{
								_tiles[i + j * TILEX + k].build = BU_LTR;
							}
							if (_buildNum == 15)
							{
								_tiles[i + j * TILEX + k].build = BU_LBR;
							}
						}
					}
					break;
				}
				else if (_ctrSelect == CTRL_ERASER)
				{
					for (int j = 0; j < _currentTile.sizeY; j++)
					{
						for (int k = 0; k < _currentTile.sizeX; k++)
						{
							_tiles[i + j * TILEX + k].terrain2FrameX = NULL;
							_tiles[i + j * TILEX + k].terrain2FrameY = NULL;
							_tiles[i + j * TILEX + k].terrain2 = TR2_NONE;
							_tiles[i + j * TILEX + k].build = BU_NONE;
							_tiles[i + j * TILEX + k].objFrameX = NULL;
							_tiles[i + j * TILEX + k].objFrameY = NULL;
							_tiles[i + j * TILEX + k].obj = OBJ_NONE;
							_tiles[i + j * TILEX + k].buildFrameX = NULL;
							_tiles[i + j * TILEX + k].buildFrameY = NULL;
							_tiles[i + j * TILEX + k].build = BU_NONE;

						}
					}
					break;
				}
				InvalidateRect(_hWnd, NULL, false);
				break;

			}
		}
	}
}

void tileClass::save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("tileSave.map", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);




	CloseHandle(file);

}

void tileClass::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("tileSave.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);




	CloseHandle(file);
}

void tileClass::mapLoad(const char * _fileName)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(_fileName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);




	CloseHandle(file);

}

void tileClass::keyControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		y -= 50;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		y += 50;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		x -= 50;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		x += 50;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_BACK) && _groundMenuOn == true)
	{
		_groundMenuOn = false;
	}




	if (_groundMenuOn == true)
	{
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			_tileSetNum++;

		}
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			_tileSetNum--;

		}
	}
	if (_tileSetNum > TILEIMGNUM-1)
	{
		_tileSetNum = 0;
	}
	if (_tileSetNum < 0  )
	{
		_tileSetNum = TILEIMGNUM-1;
	}
}

void tileClass::Button()
{
	IMAGEMANAGER->addDImage("������Ʈ_������ư", L"UI/������Ʈ_������ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������Ʈ_���͹�ư", L"UI/������Ʈ_���͹�ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������Ʈ_����ư", L"UI/������Ʈ_����ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������Ʈ_�Ʒ���ư", L"UI/������Ʈ_�Ʒ���ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������Ʈ_�Ʒ���������", L"UI/������Ʈ_�Ʒ���������.png", 32, 32);
	IMAGEMANAGER->addDImage("������Ʈ_������", L"UI/������Ʈ_������.png", 32, 32);
	IMAGEMANAGER->addDImage("������Ʈ_�����ʾƷ���ư", L"UI/������Ʈ_�����ʾƷ���ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������Ʈ_����������ư", L"UI/������Ʈ_����������ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������Ʈ_���ʹ�ư", L"UI/������Ʈ_���ʹ�ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������Ʈ_���ʾƷ���ư", L"UI/������Ʈ_���ʾƷ���ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������Ʈ_���ʾƷ�������", L"UI/������Ʈ_���ʾƷ�������.png", 32, 32);
	IMAGEMANAGER->addDImage("������Ʈ_���ʾƷ���", L"UI/������Ʈ_���ʾƷ���.png", 32, 32);
	IMAGEMANAGER->addDImage("������Ʈ_��������ư", L"UI/������Ʈ_��������ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������Ʈ_�����������ʹ�ư", L"UI/������Ʈ_�����������ʹ�ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������Ʈ_����ư", L"UI/������Ʈ_����ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������Ʈ_���Ʒ���ư", L"UI/������Ʈ_���Ʒ���ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������Ʈ_�¿��ư", L"UI/������Ʈ_�¿��ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������Ʈ_�����ư", L"UI/������Ʈ_�����ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������Ʈ_����Ұ�", L"UI/������Ʈ_����Ұ�.png", 32, 32);

	//����
	IMAGEMANAGER->addDImage("������ư_������ư", L"UI/������ư_������ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������ư_���͹�ư", L"UI/������ư_���͹�ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������ư_����ư", L"UI/������ư_����ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������ư_�Ʒ���ư", L"UI/������ư_�Ʒ���ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������ư_�Ʒ���������", L"UI/������ư_�Ʒ���������.png", 32, 32);
	IMAGEMANAGER->addDImage("������ư_������", L"UI/������ư_������.png", 32, 32);
	IMAGEMANAGER->addDImage("������ư_�����ʾƷ���ư", L"UI/������ư_�����ʾƷ���ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������ư_����������ư", L"UI/������ư_����������ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������ư_���ʹ�ư", L"UI/������ư_���ʹ�ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������ư_���ʾƷ���ư", L"UI/������ư_���ʾƷ���ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������ư_���ʾƷ�������", L"UI/������ư_���ʾƷ�������.png", 32, 32);
	IMAGEMANAGER->addDImage("������ư_���ʾƷ���", L"UI/������ư_���ʾƷ���.png", 32, 32);
	IMAGEMANAGER->addDImage("������ư_��������ư", L"UI/������ư_��������ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������ư_�����������ʹ�ư", L"UI/������ư_�����������ʹ�ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������ư_����ư", L"UI/������ư_����ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������ư_���Ʒ���ư", L"UI/������ư_���Ʒ���ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������ư_�¿��ư", L"UI/������ư_�¿��ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������ư_�����ư", L"UI/������ư_�����ư.png", 32, 32);
	IMAGEMANAGER->addDImage("������ư_����Ұ�", L"UI/������ư_����Ұ�.png", 32, 32);


	//���
		IMAGEMANAGER->addDImage("�����ư_������ư", L"UI/�����ư_������ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�����ư_���͹�ư", L"UI/�����ư_���͹�ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�����ư_����ư", L"UI/�����ư_����ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�����ư_�Ʒ���ư", L"UI/�����ư_�Ʒ���ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�����ư_�Ʒ���������", L"UI/�����ư_�Ʒ���������.png", 32, 32);
		IMAGEMANAGER->addDImage("�����ư_������", L"UI/�����ư_������.png", 32, 32);
		IMAGEMANAGER->addDImage("�����ư_�����ʾƷ���ư", L"UI/�����ư_�����ʾƷ���ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�����ư_����������ư", L"UI/�����ư_����������ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�����ư_���ʹ�ư", L"UI/�����ư_���ʹ�ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�����ư_���ʾƷ���ư", L"UI/�����ư_���ʾƷ���ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�����ư_���ʾƷ�������", L"UI/�����ư_���ʾƷ�������.png", 32, 32);
		IMAGEMANAGER->addDImage("�����ư_���ʾƷ���", L"UI/�����ư_���ʾƷ���.png", 32, 32);
		IMAGEMANAGER->addDImage("�����ư_��������ư", L"UI/�����ư_��������ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�����ư_�����������ʹ�ư", L"UI/�����ư_�����������ʹ�ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�����ư_����ư", L"UI/�����ư_����ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�����ư_���Ʒ���ư", L"UI/�����ư_���Ʒ���ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�����ư_�¿��ư", L"UI/�����ư_�¿��ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�����ư_�����ư", L"UI/�����ư_�����ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�����ư_����Ұ�", L"UI/�����ư_����Ұ�.png", 32, 32);


	//���๰
		IMAGEMANAGER->addDImage("�ǹ���ư_������ư", L"UI/�ǹ���ư_������ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�ǹ���ư_���͹�ư", L"UI/�ǹ���ư_���͹�ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�ǹ���ư_����ư", L"UI/�ǹ���ư_����ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�ǹ���ư_�Ʒ���ư", L"UI/�ǹ���ư_�Ʒ���ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�ǹ���ư_�Ʒ���������", L"UI/�ǹ���ư_�Ʒ���������.png", 32, 32);
		IMAGEMANAGER->addDImage("�ǹ���ư_������", L"UI/�ǹ���ư_������.png", 32, 32);
		IMAGEMANAGER->addDImage("�ǹ���ư_�����ʾƷ���ư", L"UI/�ǹ���ư_�����ʾƷ���ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�ǹ���ư_����������ư", L"UI/�ǹ���ư_����������ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�ǹ���ư_���ʹ�ư", L"UI/�ǹ���ư_���ʹ�ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�ǹ���ư_���ʾƷ���ư", L"UI/�ǹ���ư_���ʾƷ���ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�ǹ���ư_���ʾƷ�������", L"UI/�ǹ���ư_���ʾƷ�������.png", 32, 32);
		IMAGEMANAGER->addDImage("�ǹ���ư_���ʾƷ���", L"UI/�ǹ���ư_���ʾƷ���.png", 32, 32);
		IMAGEMANAGER->addDImage("�ǹ���ư_��������ư", L"UI/�ǹ���ư_��������ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�ǹ���ư_�����������ʹ�ư", L"UI/�ǹ���ư_�����������ʹ�ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�ǹ���ư_����ư", L"UI/�ǹ���ư_����ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�ǹ���ư_���Ʒ���ư", L"UI/�ǹ���ư_���Ʒ���ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�ǹ���ư_�¿��ư", L"UI/�ǹ���ư_�¿��ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�ǹ���ư_�����ư", L"UI/�ǹ���ư_�����ư.png", 32, 32);
		IMAGEMANAGER->addDImage("�ǹ���ư_����Ұ�", L"UI/�ǹ���ư_����Ұ�.png", 32, 32);



	IMAGEMANAGER->addDImage("��ư", L"UI/��ư.png", 281, 85);
	IMAGEMANAGER->addDImage("������ư", L"UI/������ư.png", 281, 85);
	IMAGEMANAGER->addDImage("�����ư", L"UI/�����ư.png", 281, 85);
	IMAGEMANAGER->addDImage("������Ʈ��ư", L"UI/������Ʈ ��ư.png", 281, 85);
	IMAGEMANAGER->addDImage("�ٴٹ�ư", L"UI/�ٴٹ�ư.png", 281, 85);
	IMAGEMANAGER->addDImage("���๰��ư", L"UI/���๰��ư.png", 281, 85);
	IMAGEMANAGER->addDImage("�����ư", L"UI/�����ư.png", 281, 85);
	IMAGEMANAGER->addDImage("�ҷ������ư", L"UI/�ҷ����� ��ư.png", 281, 85);

	//4����
	IMAGEMANAGER->addDImage("�Ʒ�", L"UI/�Ʒ���ư.png", 86, 85);
	IMAGEMANAGER->addDImage("��", L"UI/����ư.png", 86, 85);
	IMAGEMANAGER->addDImage("����", L"UI/���ʹ�ư.png", 86, 85);
	IMAGEMANAGER->addDImage("������", L"UI/�����ʹ�ư.png", 86, 85);

	//�밢��
	IMAGEMANAGER->addDImage("�����ʾƷ�", L"UI/�����ʾƷ���ư.png", 86, 85);
	IMAGEMANAGER->addDImage("��������", L"UI/����������ư.png", 86, 85);
	IMAGEMANAGER->addDImage("���ʾƷ�", L"UI/���ʾƷ���ư.png", 86, 85);
	IMAGEMANAGER->addDImage("������", L"UI/��������ư.png", 86, 85);

	//�ϰ���
	IMAGEMANAGER->addDImage("���Ʒ�", L"UI/���Ʒ���ư.png", 86, 85);
	IMAGEMANAGER->addDImage("�¿�", L"UI/�¿��ư.png", 86, 85);

	//�����
	IMAGEMANAGER->addDImage("�Ʒ���������", L"UI/�Ʒ���������.png", 86, 85);
	IMAGEMANAGER->addDImage("���ʾƷ���", L"UI/���ʾƷ���.png", 86, 85);
	IMAGEMANAGER->addDImage("�����������ʹ�ư", L"UI/�����������ʹ�ư.png", 86, 85);
	IMAGEMANAGER->addDImage("���ʾƷ�������", L"UI/���ʾƷ�������.png", 86, 85);

	//Ư��
	IMAGEMANAGER->addDImage("����ư", L"UI/����ư.png", 86, 85);
	IMAGEMANAGER->addDImage("������ư", L"UI/������ư.png", 86, 85);
	IMAGEMANAGER->addDImage("���͹�ư", L"UI/���͹�ư.png", 86, 85);

	//====================================================================================
	//�⺻
	IMAGEMANAGER->addDImage("�����ư", L"UI/�����ư.png", 86, 85);
	IMAGEMANAGER->addDImage("����Ұ���ư", L"UI/����Ұ���ư.png", 86, 85);
	//4����
	IMAGEMANAGER->addDImage("�Ʒ� 1", L"UI/�Ʒ���ư1.png", 86, 85);
	IMAGEMANAGER->addDImage("�� 1", L"UI/����ư1.png", 86, 85);
	IMAGEMANAGER->addDImage("���� 1", L"UI/���ʹ�ư1.png", 86, 85);
	IMAGEMANAGER->addDImage("������ 1", L"UI/�����ʹ�ư1.png", 86, 85);

	//�밢��
	IMAGEMANAGER->addDImage("�����ʾƷ� 1", L"UI/�����ʾƷ���ư1.png", 86, 85);
	IMAGEMANAGER->addDImage("�������� 1", L"UI/����������ư1.png", 86, 85);
	IMAGEMANAGER->addDImage("���ʾƷ� 1", L"UI/���ʾƷ���ư1.png", 86, 85);
	IMAGEMANAGER->addDImage("������ 1", L"UI/��������ư1.png", 86, 85);

	//�ϰ���
	IMAGEMANAGER->addDImage("���Ʒ� 1", L"UI/���Ʒ���ư1.png", 86, 85);
	IMAGEMANAGER->addDImage("�¿� 1", L"UI/�¿��ư1.png", 86, 85);

	//�����
	IMAGEMANAGER->addDImage("�Ʒ��������� 1", L"UI/�Ʒ���������1.png", 86, 85);
	IMAGEMANAGER->addDImage("���ʾƷ��� 1", L"UI/���ʾƷ���1.png", 86, 85);
	IMAGEMANAGER->addDImage("�����������ʹ�ư 1", L"UI/�����������ʹ�ư1.png", 86, 85);
	IMAGEMANAGER->addDImage("���ʾƷ������� 1", L"UI/���ʾƷ�������1.png", 86, 85);

	//�⺻
	IMAGEMANAGER->addDImage("�����ư 1", L"UI/�����ư1.png", 86, 85);
	IMAGEMANAGER->addDImage("����Ұ���ư 1", L"UI/����Ұ���ư1.png", 86, 85);

	//Ư��
	IMAGEMANAGER->addDImage("����ư1", L"UI/����ư1.png", 86, 85);
	IMAGEMANAGER->addDImage("������ư1", L"UI/������ư1.png", 86, 85);
	IMAGEMANAGER->addDImage("���͹�ư1", L"UI/���͹�ư1.png", 86, 85);


	_groundImg = IMAGEMANAGER->findDImage("������ư");
	_groundImg2 = IMAGEMANAGER->findDImage("�����ư");
	_objectImg = IMAGEMANAGER->findDImage("������Ʈ��ư");
	_waterImg = IMAGEMANAGER->findDImage("�ٴٹ�ư");
	_buildImg = IMAGEMANAGER->findDImage("���๰��ư");
	_saveImg = IMAGEMANAGER->findDImage("�����ư");
	_loadImg = IMAGEMANAGER->findDImage("�ҷ������ư");



	_ground = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top, IMAGEMANAGER->findDImage("������ư")->getWidth(),
		IMAGEMANAGER->findDImage("������ư")->getHeight());
	_groundArrow = RectMake(CAMERAMANAGER->getScreen().right - 368, CAMERAMANAGER->getScreen().top, IMAGEMANAGER->findDImage("�����ư")->getWidth(),
		IMAGEMANAGER->findDImage("�����ư")->getHeight());

	_ground2 = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 85, IMAGEMANAGER->findDImage("�����ư")->getWidth(),
		IMAGEMANAGER->findDImage("�����ư")->getHeight());
	_groundArrow2 = RectMake(CAMERAMANAGER->getScreen().right - 368, CAMERAMANAGER->getScreen().top + 85, IMAGEMANAGER->findDImage("�����ư")->getWidth(),
		IMAGEMANAGER->findDImage("�����ư")->getHeight());


	_object = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 170, IMAGEMANAGER->findDImage("������Ʈ��ư")->getWidth(),
		IMAGEMANAGER->findDImage("������Ʈ��ư")->getHeight());
	_objectArrow = RectMake(CAMERAMANAGER->getScreen().right - 368, CAMERAMANAGER->getScreen().top + 170, IMAGEMANAGER->findDImage("�����ư")->getWidth(),
		IMAGEMANAGER->findDImage("�����ư")->getHeight());


	_water = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 255, IMAGEMANAGER->findDImage("�ٴٹ�ư")->getWidth(),
		IMAGEMANAGER->findDImage("�ٴٹ�ư")->getHeight());

	_build = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 340, IMAGEMANAGER->findDImage("���๰��ư")->getWidth(),
		IMAGEMANAGER->findDImage("���๰��ư")->getHeight());
	_buildArrow = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 340, IMAGEMANAGER->findDImage("�����ư")->getWidth(),
		IMAGEMANAGER->findDImage("�����ư")->getHeight());

	_save = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 425, IMAGEMANAGER->findDImage("�����ư")->getWidth(),
		IMAGEMANAGER->findDImage("�����ư")->getHeight());
	_load = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 510, IMAGEMANAGER->findDImage("�ҷ������ư")->getWidth(),
		IMAGEMANAGER->findDImage("�ҷ������ư")->getHeight());
}

void tileClass::ButtonRenewal()
{
	//����
	if (_groundNum == 0)
	{
		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("�����ư 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("�����ư");
		}

	}
	if (_groundNum == 1)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("����Ұ���ư 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("����Ұ���ư");
		}
	}
	if (_groundNum == 2)
	{
		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("�Ʒ� 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("�Ʒ�");
		}
	}
	if (_groundNum == 3)
	{
		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("�� 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("��");
		}
	}
	if (_groundNum == 4)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("���� 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("����");
		}
	}
	if (_groundNum == 5)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("������ 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("������");
		}
	}
	if (_groundNum == 6)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("�������� 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("��������");
		}
	}
	if (_groundNum == 7)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("�����ʾƷ� 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("�����ʾƷ�");
		}
	}
	if (_groundNum == 8)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("���ʾƷ� 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("���ʾƷ�");
		}
	}
	if (_groundNum == 9)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("������ 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("������");
		}
	}
	if (_groundNum == 10)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("���Ʒ� 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("���Ʒ�");
		}
	}
	if (_groundNum == 11)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("�¿� 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("�¿�");
		}
	}
	if (_groundNum == 12)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("�Ʒ��������� 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("�Ʒ���������");
		}
	}
	if (_groundNum == 13)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("���ʾƷ��� 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("���ʾƷ���");
		}
	}
	if (_groundNum == 14)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("�����������ʹ�ư 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("�����������ʹ�ư");
		}
	}
	if (_groundNum == 15)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("���ʾƷ������� 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("���ʾƷ�������");
		}
	}
	if (_groundNum == 16)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("����ư1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("����ư");
		}
	}
	if (_groundNum == 17)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("������ư1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("������ư");
		}
	}
	if (_groundNum == 18)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("���͹�ư1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("���͹�ư");
		}
	}
	if (_groundNum > 18)
	{
		_groundNum = 0;
	}
	if (_groundNum < 0)
	{
		_groundNum = 18;
	}

	//����2
	if (_groundNum2 == 0)
	{
		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("�����ư 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("�����ư");
		}

	}
	if (_groundNum2 == 1)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("����Ұ���ư 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("����Ұ���ư");
		}
	}
	if (_groundNum2 == 2)
	{
		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("�Ʒ� 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("�Ʒ�");
		}
	}
	if (_groundNum2 == 3)
	{
		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("�� 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("��");
		}
	}
	if (_groundNum2 == 4)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("���� 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("����");
		}
	}
	if (_groundNum2 == 5)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("������ 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("������");
		}
	}
	if (_groundNum2 == 6)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("�������� 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("��������");
		}
	}
	if (_groundNum2 == 7)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("�����ʾƷ� 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("�����ʾƷ�");
		}
	}
	if (_groundNum2 == 8)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("���ʾƷ� 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("���ʾƷ�");
		}
	}
	if (_groundNum2 == 9)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("������ 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("������");
		}
	}
	if (_groundNum2 == 10)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("���Ʒ� 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("���Ʒ�");
		}
	}
	if (_groundNum2 == 11)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("�¿� 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("�¿�");
		}
	}
	if (_groundNum2 == 12)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("�Ʒ��������� 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("�Ʒ���������");
		}
	}
	if (_groundNum2 == 13)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("���ʾƷ��� 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("���ʾƷ���");
		}
	}
	if (_groundNum2 == 14)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("�����������ʹ�ư 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("�����������ʹ�ư");
		}
	}
	if (_groundNum2 == 15)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("���ʾƷ������� 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("���ʾƷ�������");
		}
	}
	if (_groundNum2 == 16)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("����ư1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("����ư");
		}
	}
	if (_groundNum2 == 17)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("������ư1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("������ư");
		}
	}
	if (_groundNum2 == 18)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("���͹�ư1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("���͹�ư");
		}
	}
	if (_groundNum2 > 18)
	{
		_groundNum2 = 0;
	}
	if (_groundNum2 < 0)
	{
		_groundNum2 = 18;
	}


	//���๰ ��ư
	if (_buildNum == 0)
	{
		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("�����ư 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("�����ư");
		}

	}
	if (_buildNum == 1)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("����Ұ���ư 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("����Ұ���ư");
		}
	}
	if (_buildNum == 2)
	{
		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("�Ʒ� 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("�Ʒ�");
		}
	}
	if (_buildNum == 3)
	{
		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("�� 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("��");
		}
	}
	if (_buildNum == 4)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("���� 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("����");
		}
	}
	if (_buildNum == 5)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("������ 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("������");
		}
	}
	if (_buildNum == 6)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("�������� 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("��������");
		}
	}
	if (_buildNum == 7)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("�����ʾƷ� 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("�����ʾƷ�");
		}
	}
	if (_buildNum == 8)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("���ʾƷ� 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("���ʾƷ�");
		}
	}
	if (_buildNum == 9)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("������ 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("������");
		}
	}
	if (_buildNum == 10)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("���Ʒ� 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("���Ʒ�");
		}
	}
	if (_buildNum == 11)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("�¿� 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("�¿�");
		}
	}
	if (_buildNum == 12)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("�Ʒ��������� 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("�Ʒ���������");
		}
	}
	if (_buildNum == 13)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("���ʾƷ��� 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("���ʾƷ���");
		}
	}
	if (_buildNum == 14)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("�����������ʹ�ư 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("�����������ʹ�ư");
		}
	}
	if (_buildNum == 15)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("���ʾƷ������� 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("���ʾƷ�������");
		}
	}
	if (_buildNum > 15)
	{
		_buildNum = 0;
	}
	if (_buildNum < 0)
	{
		_buildNum = 15;
	}
	// ������Ʈ ��ư

	if (_objectNum == 0)
	{
		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("�����ư 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("�����ư");
		}

	}
	if (_objectNum == 1)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("����Ұ���ư 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("����Ұ���ư");
		}
	}
	if (_objectNum == 2)
	{
		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("�Ʒ� 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("�Ʒ�");
		}
	}
	if (_objectNum == 3)
	{
		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("�� 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("��");
		}
	}
	if (_objectNum == 4)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("���� 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("����");
		}
	}
	if (_objectNum == 5)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("������ 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("������");
		}
	}
	if (_objectNum == 6)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("�������� 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("��������");
		}
	}
	if (_objectNum == 7)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("�����ʾƷ� 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("�����ʾƷ�");
		}
	}
	if (_objectNum == 8)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("���ʾƷ� 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("���ʾƷ�");
		}
	}
	if (_objectNum == 9)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("������ 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("������");
		}
	}
	if (_objectNum == 10)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("���Ʒ� 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("���Ʒ�");
		}
	}
	if (_objectNum == 11)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("�¿� 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("�¿�");
		}
	}
	if (_objectNum == 12)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("�Ʒ��������� 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("�Ʒ���������");
		}
	}
	if (_objectNum == 13)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("���ʾƷ��� 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("���ʾƷ���");
		}
	}
	if (_objectNum == 14)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("�����������ʹ�ư 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("�����������ʹ�ư");
		}
	}
	if (_objectNum == 15)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("���ʾƷ������� 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("���ʾƷ�������");
		}
	}
	if (_objectNum == 16)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("���͹�ư1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("���͹�ư");
		}
	}
	if (_objectNum > 16)
	{
		_objectNum = 0;
	}
	if (_objectNum < 0)
	{
		_objectNum = 16;
	}
}

void tileClass::RectCollisn()
{
	RECT temp;
	
	if (_UION == true)
	{
		//���� �Ӽ�
		if (PtInRect(&_groundArrow, _Mouse.Origin))
		{

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_groendOn = true;


			}
		}
		if (PtInRect(&_groundArrow2, _Mouse.Origin))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_groendOn2 = true;


			}
		}
		//�ǹ� �Ӽ�
		if (PtInRect(&_buildArrow, _Mouse.Origin))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_buildOn = true;
			}
		}
		//������Ʈ �Ӽ� CTRL_ERASER
		if (PtInRect(&_objectArrow, _Mouse.Origin))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_objectOn = true;


			}
		}
		if (PtInRect(&_ground, _Mouse.Origin))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_groundMenuOn = true;
				_ctrSelect = CTRL_TERRAINDRAW;
				_objectNum = 0;
				_buildNum = 0;
				_groundNum2 = 0;
			}
		}
		if (PtInRect(&_water, _Mouse.Origin))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{

				_ctrSelect = CTRL_ERASER;

			}
		}
		if (PtInRect(&_ground2, _Mouse.Origin))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_groundMenuOn = true;
				_ctrSelect = CTRL_TERRAINDRAW2;
				_objectNum = 0;
				_buildNum = 0;
				_groundNum = 0;

			}
		}
		if (PtInRect(&_object, _Mouse.Origin))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_groundMenuOn = true;
				_ctrSelect = CTRL_OBJDRAW;

				_buildNum = 0;
				_groundNum = 0;
				_groundNum2 = 0;
			}
		}
		if (PtInRect(&_build, _Mouse.Origin))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_groundMenuOn = true;
				_ctrSelect = CTRL_BUILD;
				_objectNum = 0;

				_groundNum = 0;
				_groundNum2 = 0;
			}
		}

		if (PtInRect(&_save, _Mouse.Origin))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				save();
			}
		}
		if (PtInRect(&_load, _Mouse.Origin))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				load();
			}
		}


		if (PtInRect(&_objectArrow, _Mouse.Origin))
		{
			if (KEYMANAGER->isOnceKeyDown('Q'))
			{
				_objectNum--;
				_objectOn = false;

			}
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				_objectNum++;
				_objectOn = false;

			}

		}
		if (PtInRect(&_buildArrow, _Mouse.Origin))
		{
			if (KEYMANAGER->isOnceKeyDown('Q'))
			{
				_buildNum--;
				_buildOn = false;

			}
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				_buildNum++;
				_buildOn = false;

			}

		}
		if (PtInRect(&_groundArrow, _Mouse.Origin))
		{
			if (KEYMANAGER->isOnceKeyDown('Q'))
			{
				_groundNum--;
				_groendOn = false;

			}
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				_groundNum++;
				_groendOn = false;

			}


		}
		if (PtInRect(&_groundArrow2, _Mouse.Origin))
		{
			if (KEYMANAGER->isOnceKeyDown('Q'))
			{
				_groundNum2--;
				_groendOn2 = false;

			}
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				_groundNum2++;
				_groendOn2 = false;

			}

		}
	}
}

void tileClass::ToggleKeyIMG()
{
	for (int i = 0; i < TILEX * TILEY; ++i)
	{

		//	if(_tiles[i].obj == OBJ_MOVE)DTDMANAGER->Rectangle(_tiles[i].rc);
		if (_tiles[i].terrain == TR_LIGHT)IMAGEMANAGER->findDImage("������ư_������ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.30f);
		if (_tiles[i].terrain == TR_MOSTER)IMAGEMANAGER->findDImage("������ư_���͹�ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_WATER)IMAGEMANAGER->findDImage("������ư_����ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_BOTTOM)IMAGEMANAGER->findDImage("������ư_�Ʒ���ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_BTR)IMAGEMANAGER->findDImage("������ư_�Ʒ���������")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_RIGHT)IMAGEMANAGER->findDImage("������ư_������")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_RB)IMAGEMANAGER->findDImage("������ư_�����ʾƷ���ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_RT)IMAGEMANAGER->findDImage("������ư_����������ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_LEFT)IMAGEMANAGER->findDImage("������ư_���ʹ�ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_LB)IMAGEMANAGER->findDImage("������ư_���ʾƷ���ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_LBR)IMAGEMANAGER->findDImage("������ư_���ʾƷ�������")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_BTL)IMAGEMANAGER->findDImage("������ư_���ʾƷ���")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_LT)IMAGEMANAGER->findDImage("������ư_��������ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_LTR)IMAGEMANAGER->findDImage("������ư_�����������ʹ�ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_TOP)IMAGEMANAGER->findDImage("������ư_����ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_TB)IMAGEMANAGER->findDImage("������ư_���Ʒ���ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_LR)IMAGEMANAGER->findDImage("������ư_�¿��ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_MOVE)IMAGEMANAGER->findDImage("������ư_�����ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_UNMOVE)IMAGEMANAGER->findDImage("������ư_����Ұ�")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);


		if (_tiles[i].terrain2 == TR2_LIGHT)IMAGEMANAGER->findDImage("�����ư_������ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.30f);
		if (_tiles[i].terrain2 == TR2_MOSTER)IMAGEMANAGER->findDImage("�����ư_���͹�ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == OBJ_WATER)IMAGEMANAGER->findDImage("�����ư_����ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_BOTTOM)IMAGEMANAGER->findDImage("�����ư_�Ʒ���ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_BTR2)IMAGEMANAGER->findDImage("�����ư_�Ʒ���������")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_RIGHT)IMAGEMANAGER->findDImage("�����ư_������")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_RB)IMAGEMANAGER->findDImage("�����ư_�����ʾƷ���ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_RT)IMAGEMANAGER->findDImage("�����ư_����������ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_LEFT)IMAGEMANAGER->findDImage("�����ư_���ʹ�ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_LB)IMAGEMANAGER->findDImage("�����ư_���ʾƷ���ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_LBR)IMAGEMANAGER->findDImage("�����ư_���ʾƷ�������")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_BTL)IMAGEMANAGER->findDImage("�����ư_���ʾƷ���")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_LT)IMAGEMANAGER->findDImage("�����ư_��������ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_LTR2)IMAGEMANAGER->findDImage("�����ư_�����������ʹ�ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_TOP)IMAGEMANAGER->findDImage("�����ư_����ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_TB)IMAGEMANAGER->findDImage("�����ư_���Ʒ���ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_LR)IMAGEMANAGER->findDImage("�����ư_�¿��ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_MOVE)IMAGEMANAGER->findDImage("�����ư_�����ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_UNMOVE)IMAGEMANAGER->findDImage("�����ư_����Ұ�")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);


		if (_tiles[i].build == BU_WATER)IMAGEMANAGER->findDImage("�ǹ���ư_����ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_BOTTOM)IMAGEMANAGER->findDImage("�ǹ���ư_�Ʒ���ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_BTR)IMAGEMANAGER->findDImage("�ǹ���ư_�Ʒ���������")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_RIGHT)IMAGEMANAGER->findDImage("�ǹ���ư_������")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_RB)IMAGEMANAGER->findDImage("�ǹ���ư_�����ʾƷ���ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_RT)IMAGEMANAGER->findDImage("�ǹ���ư_����������ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_LEFT)IMAGEMANAGER->findDImage("�ǹ���ư_���ʹ�ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_LB)IMAGEMANAGER->findDImage("�ǹ���ư_���ʾƷ���ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_LBR)IMAGEMANAGER->findDImage("�ǹ���ư_���ʾƷ�������")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_BTL)IMAGEMANAGER->findDImage("�ǹ���ư_���ʾƷ���")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_LT)IMAGEMANAGER->findDImage("�ǹ���ư_��������ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_LTR)IMAGEMANAGER->findDImage("�ǹ���ư_�����������ʹ�ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_TOP)IMAGEMANAGER->findDImage("�ǹ���ư_����ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_TB)IMAGEMANAGER->findDImage("�ǹ���ư_���Ʒ���ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_LR)IMAGEMANAGER->findDImage("�ǹ���ư_�¿��ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_MOVE)IMAGEMANAGER->findDImage("�ǹ���ư_�����ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_UNMOVE)IMAGEMANAGER->findDImage("�ǹ���ư_����Ұ�")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);

		if (_tiles[i].obj == OBJ_MOSTER)IMAGEMANAGER->findDImage("������Ʈ_���͹�ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_WATER)IMAGEMANAGER->findDImage("������Ʈ_����ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_BOTTOM)IMAGEMANAGER->findDImage("������Ʈ_�Ʒ���ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_BTR)IMAGEMANAGER->findDImage("������Ʈ_�Ʒ���������")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_RIGHT)IMAGEMANAGER->findDImage("������Ʈ_������")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_RB)IMAGEMANAGER->findDImage("������Ʈ_�����ʾƷ���ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_RT)IMAGEMANAGER->findDImage("������Ʈ_����������ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_LEFT)IMAGEMANAGER->findDImage("������Ʈ_���ʹ�ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_LB)IMAGEMANAGER->findDImage("������Ʈ_���ʾƷ���ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_LBR)IMAGEMANAGER->findDImage("������Ʈ_���ʾƷ�������")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_BTL)IMAGEMANAGER->findDImage("������Ʈ_���ʾƷ���")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_LT)IMAGEMANAGER->findDImage("������Ʈ_��������ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_LTR)IMAGEMANAGER->findDImage("������Ʈ_�����������ʹ�ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_TOP)IMAGEMANAGER->findDImage("������Ʈ_����ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_TB)IMAGEMANAGER->findDImage("������Ʈ_���Ʒ���ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_LR)IMAGEMANAGER->findDImage("������Ʈ_�¿��ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_MOVE)IMAGEMANAGER->findDImage("������Ʈ_�����ư")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_UNMOVE)IMAGEMANAGER->findDImage("������Ʈ_����Ұ�")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			









	}

}

void tileClass::imgGO()
{

		for (int i = 0; i < TILEX * TILEY; ++i)
		{

			if (_tiles[i].terrain == TR_WATER)
			{
				_tiles[i].count++;
				if (_tiles[i].count % 5 == 0)
				{
					_tiles[i].terrainFrameX += 3;

					//cout << _tiles[i].terrainFrameX << endl;
					if (_tiles[i].terrainFrameX > 23)
					{

						_tiles[i].terrainFrameX = _tiles[i].terrainStartFrameX;

					}
				}

			}
			if (_tiles[i].terrain2 == TR2_WATER)
			{
				_tiles[i].count++;
				if (_tiles[i].count % 5 == 0)
				{
					_tiles[i].terrain2FrameX += 3;

					//cout << _tiles[i].terrainFrameX << endl;
					if (_tiles[i].terrain2FrameX > 23)
					{

						_tiles[i].terrain2FrameX = _tiles[i].terrainStart2FrameX;

					}
				}

			}

		}
	
}





void tileClass::menuIMG()
{
	IMAGEMANAGER->addDImage("�����޴�", L"UI/�����޴�.png", 800, 800);

	// ����
	_groundMenuImg = IMAGEMANAGER->findDImage("�����޴�");
	//��Ʈ
	_groundMenu = RectMake(CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, IMAGEMANAGER->findDImage("�����޴�")->getWidth(),
		IMAGEMANAGER->findDImage("�����޴�")->getHeight());

	_GMx = (_groundMenu.left + _groundMenu.right) / 2;
	_GMy = (_groundMenu.top + _groundMenu.bottom) / 2;
}

void tileClass::tileIMG()
{


	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�1", L"map/Ÿ�ϼ�1.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�2", L"map/Ÿ�ϼ�2.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�3", L"map/Ÿ�ϼ�3.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�4", L"map/Ÿ�ϼ�4.png", 768, 768, SAMPLETILEX, SAMPLETILEY);

	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�5", L"map/Ÿ�ϼ�5.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�6", L"map/Ÿ�ϼ�6.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�7", L"map/Ÿ�ϼ�7.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�8", L"map/Ÿ�ϼ�8.png", 768, 768, SAMPLETILEX, SAMPLETILEY);

	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�9", L"map/Ÿ�ϼ�9.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�10", L"map/Ÿ�ϼ�10.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�11", L"map/Ÿ�ϼ�11.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�12", L"map/Ÿ�ϼ�12.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�13", L"map/Ÿ�ϼ�13.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�14", L"map/Ÿ�ϼ�14.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�15", L"map/Ÿ�ϼ�15.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�16", L"map/Ÿ�ϼ�16.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�17", L"map/Ÿ�ϼ�17.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�18", L"map/Ÿ�ϼ�18.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�19", L"map/Ÿ�ϼ�19.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�20", L"map/Ÿ�ϼ�20.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�21", L"map/Ÿ�ϼ�21.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�22", L"map/Ÿ�ϼ�22.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�23", L"map/Ÿ�ϼ�23.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�24", L"map/Ÿ�ϼ�24.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�25", L"map/Ÿ�ϼ�25.png", 768, 768, SAMPLETILEX, SAMPLETILEY);

	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�26", L"map/Ÿ�ϼ�26.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�27", L"map/Ÿ�ϼ�27.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�28", L"map/Ÿ�ϼ�28.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�29", L"map/Ÿ�ϼ�29.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�30", L"map/Ÿ�ϼ�30.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�31", L"map/Ÿ�ϼ�31.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�32", L"map/Ÿ�ϼ�32.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�33", L"map/Ÿ�ϼ�33.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�34", L"map/Ÿ�ϼ�34.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�35", L"map/Ÿ�ϼ�35.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�36", L"map/Ÿ�ϼ�36.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�37", L"map/Ÿ�ϼ�37.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�38", L"map/Ÿ�ϼ�38.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�39", L"map/Ÿ�ϼ�39.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�40", L"map/Ÿ�ϼ�40.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�41", L"map/Ÿ�ϼ�41.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�42", L"map/Ÿ�ϼ�42.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�43", L"map/Ÿ�ϼ�43.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�44", L"map/Ÿ�ϼ�44.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�45", L"map/Ÿ�ϼ�45.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�46", L"map/Ÿ�ϼ�46.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�47", L"map/Ÿ�ϼ�47.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�48", L"map/Ÿ�ϼ�48.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Ÿ�ϼ�49", L"map/Ÿ�ϼ�49.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	// ����
	_mapTileImge[0] = IMAGEMANAGER->findDImage("Ÿ�ϼ�1");
	_mapTileImge[1] = IMAGEMANAGER->findDImage("Ÿ�ϼ�2");
	_mapTileImge[2] = IMAGEMANAGER->findDImage("Ÿ�ϼ�3");
	_mapTileImge[3] = IMAGEMANAGER->findDImage("Ÿ�ϼ�4");
	_mapTileImge[4] = IMAGEMANAGER->findDImage("Ÿ�ϼ�5");
	_mapTileImge[5] = IMAGEMANAGER->findDImage("Ÿ�ϼ�6");
	_mapTileImge[6] = IMAGEMANAGER->findDImage("Ÿ�ϼ�7");
	_mapTileImge[7] = IMAGEMANAGER->findDImage("Ÿ�ϼ�8");
	_mapTileImge[8] = IMAGEMANAGER->findDImage("Ÿ�ϼ�9");
	_mapTileImge[9] = IMAGEMANAGER->findDImage("Ÿ�ϼ�10");
	_mapTileImge[10] = IMAGEMANAGER->findDImage("Ÿ�ϼ�11");
	_mapTileImge[11] = IMAGEMANAGER->findDImage("Ÿ�ϼ�12");
	_mapTileImge[12] = IMAGEMANAGER->findDImage("Ÿ�ϼ�13");
	_mapTileImge[13] = IMAGEMANAGER->findDImage("Ÿ�ϼ�14");
	_mapTileImge[14] = IMAGEMANAGER->findDImage("Ÿ�ϼ�15");
	_mapTileImge[15] = IMAGEMANAGER->findDImage("Ÿ�ϼ�16");
	_mapTileImge[16] = IMAGEMANAGER->findDImage("Ÿ�ϼ�17");
	_mapTileImge[17] = IMAGEMANAGER->findDImage("Ÿ�ϼ�18");
	_mapTileImge[18] = IMAGEMANAGER->findDImage("Ÿ�ϼ�19");
	_mapTileImge[19] = IMAGEMANAGER->findDImage("Ÿ�ϼ�20");
	_mapTileImge[20] = IMAGEMANAGER->findDImage("Ÿ�ϼ�21");
	_mapTileImge[21] = IMAGEMANAGER->findDImage("Ÿ�ϼ�22");
	_mapTileImge[22] = IMAGEMANAGER->findDImage("Ÿ�ϼ�23");
	_mapTileImge[23] = IMAGEMANAGER->findDImage("Ÿ�ϼ�24");
	_mapTileImge[24] = IMAGEMANAGER->findDImage("Ÿ�ϼ�25");
	_mapTileImge[25] = IMAGEMANAGER->findDImage("Ÿ�ϼ�26");
	_mapTileImge[26] = IMAGEMANAGER->findDImage("Ÿ�ϼ�27");
	_mapTileImge[27] = IMAGEMANAGER->findDImage("Ÿ�ϼ�28");
	_mapTileImge[28] = IMAGEMANAGER->findDImage("Ÿ�ϼ�29");
	_mapTileImge[29] = IMAGEMANAGER->findDImage("Ÿ�ϼ�30");
	_mapTileImge[30] = IMAGEMANAGER->findDImage("Ÿ�ϼ�31");
	_mapTileImge[31] = IMAGEMANAGER->findDImage("Ÿ�ϼ�32");
	_mapTileImge[32] = IMAGEMANAGER->findDImage("Ÿ�ϼ�33");
	_mapTileImge[33] = IMAGEMANAGER->findDImage("Ÿ�ϼ�34");
	_mapTileImge[34] = IMAGEMANAGER->findDImage("Ÿ�ϼ�35");
	_mapTileImge[35] = IMAGEMANAGER->findDImage("Ÿ�ϼ�36");
	_mapTileImge[36] = IMAGEMANAGER->findDImage("Ÿ�ϼ�37");
	_mapTileImge[37] = IMAGEMANAGER->findDImage("Ÿ�ϼ�38");
	_mapTileImge[38] = IMAGEMANAGER->findDImage("Ÿ�ϼ�39");
	_mapTileImge[39] = IMAGEMANAGER->findDImage("Ÿ�ϼ�40");
	_mapTileImge[40] = IMAGEMANAGER->findDImage("Ÿ�ϼ�41");
	_mapTileImge[41] = IMAGEMANAGER->findDImage("Ÿ�ϼ�42");
	_mapTileImge[42] = IMAGEMANAGER->findDImage("Ÿ�ϼ�43");
	_mapTileImge[43] = IMAGEMANAGER->findDImage("Ÿ�ϼ�44");
	_mapTileImge[44] = IMAGEMANAGER->findDImage("Ÿ�ϼ�45");
	_mapTileImge[45] = IMAGEMANAGER->findDImage("Ÿ�ϼ�46");
	_mapTileImge[46] = IMAGEMANAGER->findDImage("Ÿ�ϼ�47");
	_mapTileImge[47] = IMAGEMANAGER->findDImage("Ÿ�ϼ�48");
	_mapTileImge[48] = IMAGEMANAGER->findDImage("Ÿ�ϼ�49");

	_tileSetNum = 0;
	//��Ʈ
	_mapTileRect[0] = RectMakeCenter(_GMx, _GMy, IMAGEMANAGER->findDImage("Ÿ�ϼ�1")->getWidth(),
		IMAGEMANAGER->findDImage("Ÿ�ϼ�1")->getHeight());

}

void tileClass::updateRect()
{
	_ground = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top, IMAGEMANAGER->findDImage("������ư")->getWidth(),
		IMAGEMANAGER->findDImage("������ư")->getHeight());
	_groundArrow = RectMake(CAMERAMANAGER->getScreen().right - 368, CAMERAMANAGER->getScreen().top, IMAGEMANAGER->findDImage("�����ư")->getWidth(),
		IMAGEMANAGER->findDImage("�����ư")->getHeight());

	_ground2 = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 85, IMAGEMANAGER->findDImage("�����ư")->getWidth(),
		IMAGEMANAGER->findDImage("�����ư")->getHeight());
	_groundArrow2 = RectMake(CAMERAMANAGER->getScreen().right - 368, CAMERAMANAGER->getScreen().top + 85, IMAGEMANAGER->findDImage("�����ư")->getWidth(),
		IMAGEMANAGER->findDImage("�����ư")->getHeight());


	_object = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 170, IMAGEMANAGER->findDImage("������Ʈ��ư")->getWidth(),
		IMAGEMANAGER->findDImage("������Ʈ��ư")->getHeight());
	_objectArrow = RectMake(CAMERAMANAGER->getScreen().right - 368, CAMERAMANAGER->getScreen().top + 170, IMAGEMANAGER->findDImage("�����ư")->getWidth(),
		IMAGEMANAGER->findDImage("�����ư")->getHeight());


	_water = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 255, IMAGEMANAGER->findDImage("�ٴٹ�ư")->getWidth(),
		IMAGEMANAGER->findDImage("�ٴٹ�ư")->getHeight());

	_build = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 340, IMAGEMANAGER->findDImage("���๰��ư")->getWidth(),
		IMAGEMANAGER->findDImage("���๰��ư")->getHeight());
	_buildArrow = RectMake(CAMERAMANAGER->getScreen().right - 368, CAMERAMANAGER->getScreen().top + 340, IMAGEMANAGER->findDImage("�����ư")->getWidth(),
		IMAGEMANAGER->findDImage("�����ư")->getHeight());

	_save = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 425, IMAGEMANAGER->findDImage("�����ư")->getWidth(),
		IMAGEMANAGER->findDImage("�����ư")->getHeight());
	_load = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 510, IMAGEMANAGER->findDImage("�ҷ������ư")->getWidth(),
		IMAGEMANAGER->findDImage("�ҷ������ư")->getHeight());
	_mapTileRect[0] = RectMakeCenter(_GMx, _GMy, IMAGEMANAGER->findDImage("Ÿ�ϼ�1")->getWidth(),
		IMAGEMANAGER->findDImage("Ÿ�ϼ�1")->getHeight());
	_groundMenu = RectMake(CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, IMAGEMANAGER->findDImage("�����޴�")->getWidth(),
		IMAGEMANAGER->findDImage("�����޴�")->getHeight());
	test = RectMakeCenter(_ptMouse.x + CAMERAMANAGER->getScreen().left, _ptMouse.y + CAMERAMANAGER->getScreen().top, 10, 10);



}






