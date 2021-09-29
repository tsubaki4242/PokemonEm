#include "stdafx.h"
#include "tileClass.h"



HRESULT tileClass::init()
{
	CAMERAMANAGER->setBackScreenSize(3840, 2160);//씬마다 꼭 넣어줘야함

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


	//지형 그리기
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_mapTileImge[_tiles[i].terrainImgIndex]->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

	}
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].terrain2 == TR2_NONE) continue;
		_mapTileImge[_tiles[i].terrainImgIndex2]->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrain2FrameX, _tiles[i].terrain2FrameY);

	}
	//오브젝트 그리기
	for (int i = 0; i < TILEX * TILEY; ++i)
	{

		

		//cout << playerY << endl;
		//오브젝트 속성이 아니면 그리지않게끔 예외처리
		if (_tiles[i].obj == OBJ_NONE) continue;
		//if (_tiles[_tiles[i].objImgIndex].objImage == nullptr) continue;
		_mapTileImge[_tiles[i].objImgIndex]->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);

		//RENDERMANAGER->push_BackFrameRenderInfo(
		//	_tiles[_tiles[i].buildImgIndex].tileObjZOrder,
		//	_mapTileImge[_tiles[i].objImgIndex],
		//	_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
	}
	//건물
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[_tiles[i].buildImgIndex].tileObjZOrderBild = 3;
		//건물 속성이 아니면 그리지않게끔 예외처리
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
	//메뉴
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
	//지형 그리기
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
	//오브젝트 그리기

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
		//오브젝트 속성이 아니면 그리지않게끔 예외처리
		if (_tiles[i].obj == OBJ_NONE) continue;
		//if (_tiles[_tiles[i].objImgIndex].objImage == nullptr) continue;
		//_mapTileImge[_tiles[i].objImgIndex]->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
		

			RENDERMANAGER->push_BackFrameRenderInfo(
				_tiles[_tiles[i].buildImgIndex].tileObjZOrder, _tiles[i].rc,
				_mapTileImge[_tiles[i].objImgIndex],
				_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
		
	}
	//건물
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[_tiles[i].buildImgIndex].tileObjZOrderBild = 3;
		//건물 속성이 아니면 그리지않게끔 예외처리
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
	//메뉴
	if (_groundMenuOn == true)
	{
		_groundMenuImg->render(_groundMenu.left, _groundMenu.top);
		_mapTileImge[_tileSetNum]->render(_mapTileRect[0].left + CAMERAMANAGER->getScreen().left, _mapTileRect[0].top + CAMERAMANAGER->getScreen().top);
		D2DMANAGER->Rectangle(_tileChoice);
	}
}

void tileClass::setup()
{

	//처음 컨트롤 상태는 지형으로
	_ctrSelect = CTRL_TERRAINDRAW;

	//타일셋 먼저 세팅
	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_sampleTile[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTile[i * SAMPLETILEX + j].terrainFrameY = i;

			//타일셋에 렉트를 씌움

			SetRect(&_sampleTile[i * SAMPLETILEX + j].rcTile,
				(_mapTileRect[0].left + CAMERAMANAGER->getScreen().left) + j * TILESIZE,
				(_mapTileRect[0].top + CAMERAMANAGER->getScreen().top) + i * TILESIZE,
				(_mapTileRect[0].left + CAMERAMANAGER->getScreen().left) + j * TILESIZE + TILESIZE,
				(_mapTileRect[0].top + CAMERAMANAGER->getScreen().top) + i * TILESIZE + TILESIZE);

		}
	}

	//타일 영역
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
				// 지형 투
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
	IMAGEMANAGER->addDImage("오브젝트_광원버튼", L"UI/오브젝트_광원버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("오브젝트_몬스터버튼", L"UI/오브젝트_몬스터버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("오브젝트_물버튼", L"UI/오브젝트_물버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("오브젝트_아래버튼", L"UI/오브젝트_아래버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("오브젝트_아래오른쪽위", L"UI/오브젝트_아래오른쪽위.png", 32, 32);
	IMAGEMANAGER->addDImage("오브젝트_오른쪽", L"UI/오브젝트_오른쪽.png", 32, 32);
	IMAGEMANAGER->addDImage("오브젝트_오른쪽아래버튼", L"UI/오브젝트_오른쪽아래버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("오브젝트_오른쪽위버튼", L"UI/오브젝트_오른쪽위버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("오브젝트_왼쪽버튼", L"UI/오브젝트_왼쪽버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("오브젝트_왼쪽아래버튼", L"UI/오브젝트_왼쪽아래버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("오브젝트_왼쪽아래오른쪽", L"UI/오브젝트_왼쪽아래오른쪽.png", 32, 32);
	IMAGEMANAGER->addDImage("오브젝트_왼쪽아래위", L"UI/오브젝트_왼쪽아래위.png", 32, 32);
	IMAGEMANAGER->addDImage("오브젝트_왼쪽위버튼", L"UI/오브젝트_왼쪽위버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("오브젝트_왼쪽위오른쪽버튼", L"UI/오브젝트_왼쪽위오른쪽버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("오브젝트_위버튼", L"UI/오브젝트_위버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("오브젝트_위아래버튼", L"UI/오브젝트_위아래버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("오브젝트_좌우버튼", L"UI/오브젝트_좌우버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("오브젝트_진행버튼", L"UI/오브젝트_진행버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("오브젝트_진행불가", L"UI/오브젝트_진행불가.png", 32, 32);

	//지형
	IMAGEMANAGER->addDImage("지형버튼_광원버튼", L"UI/지형버튼_광원버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("지형버튼_몬스터버튼", L"UI/지형버튼_몬스터버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("지형버튼_물버튼", L"UI/지형버튼_물버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("지형버튼_아래버튼", L"UI/지형버튼_아래버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("지형버튼_아래오른쪽위", L"UI/지형버튼_아래오른쪽위.png", 32, 32);
	IMAGEMANAGER->addDImage("지형버튼_오른쪽", L"UI/지형버튼_오른쪽.png", 32, 32);
	IMAGEMANAGER->addDImage("지형버튼_오른쪽아래버튼", L"UI/지형버튼_오른쪽아래버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("지형버튼_오른쪽위버튼", L"UI/지형버튼_오른쪽위버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("지형버튼_왼쪽버튼", L"UI/지형버튼_왼쪽버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("지형버튼_왼쪽아래버튼", L"UI/지형버튼_왼쪽아래버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("지형버튼_왼쪽아래오른쪽", L"UI/지형버튼_왼쪽아래오른쪽.png", 32, 32);
	IMAGEMANAGER->addDImage("지형버튼_왼쪽아래위", L"UI/지형버튼_왼쪽아래위.png", 32, 32);
	IMAGEMANAGER->addDImage("지형버튼_왼쪽위버튼", L"UI/지형버튼_왼쪽위버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("지형버튼_왼쪽위오른쪽버튼", L"UI/지형버튼_왼쪽위오른쪽버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("지형버튼_위버튼", L"UI/지형버튼_위버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("지형버튼_위아래버튼", L"UI/지형버튼_위아래버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("지형버튼_좌우버튼", L"UI/지형버튼_좌우버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("지형버튼_진행버튼", L"UI/지형버튼_진행버튼.png", 32, 32);
	IMAGEMANAGER->addDImage("지형버튼_진행불가", L"UI/지형버튼_진행불가.png", 32, 32);


	//언덕
		IMAGEMANAGER->addDImage("언덕버튼_광원버튼", L"UI/언덕버튼_광원버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("언덕버튼_몬스터버튼", L"UI/언덕버튼_몬스터버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("언덕버튼_물버튼", L"UI/언덕버튼_물버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("언덕버튼_아래버튼", L"UI/언덕버튼_아래버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("언덕버튼_아래오른쪽위", L"UI/언덕버튼_아래오른쪽위.png", 32, 32);
		IMAGEMANAGER->addDImage("언덕버튼_오른쪽", L"UI/언덕버튼_오른쪽.png", 32, 32);
		IMAGEMANAGER->addDImage("언덕버튼_오른쪽아래버튼", L"UI/언덕버튼_오른쪽아래버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("언덕버튼_오른쪽위버튼", L"UI/언덕버튼_오른쪽위버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("언덕버튼_왼쪽버튼", L"UI/언덕버튼_왼쪽버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("언덕버튼_왼쪽아래버튼", L"UI/언덕버튼_왼쪽아래버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("언덕버튼_왼쪽아래오른쪽", L"UI/언덕버튼_왼쪽아래오른쪽.png", 32, 32);
		IMAGEMANAGER->addDImage("언덕버튼_왼쪽아래위", L"UI/언덕버튼_왼쪽아래위.png", 32, 32);
		IMAGEMANAGER->addDImage("언덕버튼_왼쪽위버튼", L"UI/언덕버튼_왼쪽위버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("언덕버튼_왼쪽위오른쪽버튼", L"UI/언덕버튼_왼쪽위오른쪽버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("언덕버튼_위버튼", L"UI/언덕버튼_위버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("언덕버튼_위아래버튼", L"UI/언덕버튼_위아래버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("언덕버튼_좌우버튼", L"UI/언덕버튼_좌우버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("언덕버튼_진행버튼", L"UI/언덕버튼_진행버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("언덕버튼_진행불가", L"UI/언덕버튼_진행불가.png", 32, 32);


	//건축물
		IMAGEMANAGER->addDImage("건물버튼_광원버튼", L"UI/건물버튼_광원버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("건물버튼_몬스터버튼", L"UI/건물버튼_몬스터버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("건물버튼_물버튼", L"UI/건물버튼_물버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("건물버튼_아래버튼", L"UI/건물버튼_아래버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("건물버튼_아래오른쪽위", L"UI/건물버튼_아래오른쪽위.png", 32, 32);
		IMAGEMANAGER->addDImage("건물버튼_오른쪽", L"UI/건물버튼_오른쪽.png", 32, 32);
		IMAGEMANAGER->addDImage("건물버튼_오른쪽아래버튼", L"UI/건물버튼_오른쪽아래버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("건물버튼_오른쪽위버튼", L"UI/건물버튼_오른쪽위버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("건물버튼_왼쪽버튼", L"UI/건물버튼_왼쪽버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("건물버튼_왼쪽아래버튼", L"UI/건물버튼_왼쪽아래버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("건물버튼_왼쪽아래오른쪽", L"UI/건물버튼_왼쪽아래오른쪽.png", 32, 32);
		IMAGEMANAGER->addDImage("건물버튼_왼쪽아래위", L"UI/건물버튼_왼쪽아래위.png", 32, 32);
		IMAGEMANAGER->addDImage("건물버튼_왼쪽위버튼", L"UI/건물버튼_왼쪽위버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("건물버튼_왼쪽위오른쪽버튼", L"UI/건물버튼_왼쪽위오른쪽버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("건물버튼_위버튼", L"UI/건물버튼_위버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("건물버튼_위아래버튼", L"UI/건물버튼_위아래버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("건물버튼_좌우버튼", L"UI/건물버튼_좌우버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("건물버튼_진행버튼", L"UI/건물버튼_진행버튼.png", 32, 32);
		IMAGEMANAGER->addDImage("건물버튼_진행불가", L"UI/건물버튼_진행불가.png", 32, 32);



	IMAGEMANAGER->addDImage("버튼", L"UI/버튼.png", 281, 85);
	IMAGEMANAGER->addDImage("지형버튼", L"UI/지형버튼.png", 281, 85);
	IMAGEMANAGER->addDImage("언덕버튼", L"UI/언덕버튼.png", 281, 85);
	IMAGEMANAGER->addDImage("오브젝트버튼", L"UI/오브젝트 버튼.png", 281, 85);
	IMAGEMANAGER->addDImage("바다버튼", L"UI/바다버튼.png", 281, 85);
	IMAGEMANAGER->addDImage("건축물버튼", L"UI/건축물버튼.png", 281, 85);
	IMAGEMANAGER->addDImage("저장버튼", L"UI/저장버튼.png", 281, 85);
	IMAGEMANAGER->addDImage("불러오기버튼", L"UI/불러오기 버튼.png", 281, 85);

	//4방향
	IMAGEMANAGER->addDImage("아래", L"UI/아래버튼.png", 86, 85);
	IMAGEMANAGER->addDImage("위", L"UI/위버튼.png", 86, 85);
	IMAGEMANAGER->addDImage("왼쪽", L"UI/왼쪽버튼.png", 86, 85);
	IMAGEMANAGER->addDImage("오른쪽", L"UI/오른쪽버튼.png", 86, 85);

	//대각선
	IMAGEMANAGER->addDImage("오른쪽아래", L"UI/오른쪽아래버튼.png", 86, 85);
	IMAGEMANAGER->addDImage("오른쪽위", L"UI/오른쪽위버튼.png", 86, 85);
	IMAGEMANAGER->addDImage("왼쪽아래", L"UI/왼쪽아래버튼.png", 86, 85);
	IMAGEMANAGER->addDImage("왼쪽위", L"UI/왼쪽위버튼.png", 86, 85);

	//일각선
	IMAGEMANAGER->addDImage("위아래", L"UI/위아래버튼.png", 86, 85);
	IMAGEMANAGER->addDImage("좌우", L"UI/좌우버튼.png", 86, 85);

	//삼방향
	IMAGEMANAGER->addDImage("아래오른쪽위", L"UI/아래오른쪽위.png", 86, 85);
	IMAGEMANAGER->addDImage("왼쪽아래위", L"UI/왼쪽아래위.png", 86, 85);
	IMAGEMANAGER->addDImage("왼쪽위오른쪽버튼", L"UI/왼쪽위오른쪽버튼.png", 86, 85);
	IMAGEMANAGER->addDImage("왼쪽아래오른쪽", L"UI/왼쪽아래오른쪽.png", 86, 85);

	//특수
	IMAGEMANAGER->addDImage("물버튼", L"UI/물버튼.png", 86, 85);
	IMAGEMANAGER->addDImage("광원버튼", L"UI/광원버튼.png", 86, 85);
	IMAGEMANAGER->addDImage("몬스터버튼", L"UI/몬스터버튼.png", 86, 85);

	//====================================================================================
	//기본
	IMAGEMANAGER->addDImage("진행버튼", L"UI/진행버튼.png", 86, 85);
	IMAGEMANAGER->addDImage("진행불가버튼", L"UI/진행불가버튼.png", 86, 85);
	//4방향
	IMAGEMANAGER->addDImage("아래 1", L"UI/아래버튼1.png", 86, 85);
	IMAGEMANAGER->addDImage("위 1", L"UI/위버튼1.png", 86, 85);
	IMAGEMANAGER->addDImage("왼쪽 1", L"UI/왼쪽버튼1.png", 86, 85);
	IMAGEMANAGER->addDImage("오른쪽 1", L"UI/오른쪽버튼1.png", 86, 85);

	//대각선
	IMAGEMANAGER->addDImage("오른쪽아래 1", L"UI/오른쪽아래버튼1.png", 86, 85);
	IMAGEMANAGER->addDImage("오른쪽위 1", L"UI/오른쪽위버튼1.png", 86, 85);
	IMAGEMANAGER->addDImage("왼쪽아래 1", L"UI/왼쪽아래버튼1.png", 86, 85);
	IMAGEMANAGER->addDImage("왼쪽위 1", L"UI/왼쪽위버튼1.png", 86, 85);

	//일각선
	IMAGEMANAGER->addDImage("위아래 1", L"UI/위아래버튼1.png", 86, 85);
	IMAGEMANAGER->addDImage("좌우 1", L"UI/좌우버튼1.png", 86, 85);

	//삼방향
	IMAGEMANAGER->addDImage("아래오른쪽위 1", L"UI/아래오른쪽위1.png", 86, 85);
	IMAGEMANAGER->addDImage("왼쪽아래위 1", L"UI/왼쪽아래위1.png", 86, 85);
	IMAGEMANAGER->addDImage("왼쪽위오른쪽버튼 1", L"UI/왼쪽위오른쪽버튼1.png", 86, 85);
	IMAGEMANAGER->addDImage("왼쪽아래오른쪽 1", L"UI/왼쪽아래오른쪽1.png", 86, 85);

	//기본
	IMAGEMANAGER->addDImage("진행버튼 1", L"UI/진행버튼1.png", 86, 85);
	IMAGEMANAGER->addDImage("진행불가버튼 1", L"UI/진행불가버튼1.png", 86, 85);

	//특수
	IMAGEMANAGER->addDImage("물버튼1", L"UI/물버튼1.png", 86, 85);
	IMAGEMANAGER->addDImage("광원버튼1", L"UI/광원버튼1.png", 86, 85);
	IMAGEMANAGER->addDImage("몬스터버튼1", L"UI/몬스터버튼1.png", 86, 85);


	_groundImg = IMAGEMANAGER->findDImage("지형버튼");
	_groundImg2 = IMAGEMANAGER->findDImage("언덕버튼");
	_objectImg = IMAGEMANAGER->findDImage("오브젝트버튼");
	_waterImg = IMAGEMANAGER->findDImage("바다버튼");
	_buildImg = IMAGEMANAGER->findDImage("건축물버튼");
	_saveImg = IMAGEMANAGER->findDImage("저장버튼");
	_loadImg = IMAGEMANAGER->findDImage("불러오기버튼");



	_ground = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top, IMAGEMANAGER->findDImage("지형버튼")->getWidth(),
		IMAGEMANAGER->findDImage("지형버튼")->getHeight());
	_groundArrow = RectMake(CAMERAMANAGER->getScreen().right - 368, CAMERAMANAGER->getScreen().top, IMAGEMANAGER->findDImage("진행버튼")->getWidth(),
		IMAGEMANAGER->findDImage("진행버튼")->getHeight());

	_ground2 = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 85, IMAGEMANAGER->findDImage("언덕버튼")->getWidth(),
		IMAGEMANAGER->findDImage("언덕버튼")->getHeight());
	_groundArrow2 = RectMake(CAMERAMANAGER->getScreen().right - 368, CAMERAMANAGER->getScreen().top + 85, IMAGEMANAGER->findDImage("진행버튼")->getWidth(),
		IMAGEMANAGER->findDImage("진행버튼")->getHeight());


	_object = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 170, IMAGEMANAGER->findDImage("오브젝트버튼")->getWidth(),
		IMAGEMANAGER->findDImage("오브젝트버튼")->getHeight());
	_objectArrow = RectMake(CAMERAMANAGER->getScreen().right - 368, CAMERAMANAGER->getScreen().top + 170, IMAGEMANAGER->findDImage("진행버튼")->getWidth(),
		IMAGEMANAGER->findDImage("진행버튼")->getHeight());


	_water = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 255, IMAGEMANAGER->findDImage("바다버튼")->getWidth(),
		IMAGEMANAGER->findDImage("바다버튼")->getHeight());

	_build = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 340, IMAGEMANAGER->findDImage("건축물버튼")->getWidth(),
		IMAGEMANAGER->findDImage("건축물버튼")->getHeight());
	_buildArrow = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 340, IMAGEMANAGER->findDImage("진행버튼")->getWidth(),
		IMAGEMANAGER->findDImage("진행버튼")->getHeight());

	_save = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 425, IMAGEMANAGER->findDImage("저장버튼")->getWidth(),
		IMAGEMANAGER->findDImage("저장버튼")->getHeight());
	_load = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 510, IMAGEMANAGER->findDImage("불러오기버튼")->getWidth(),
		IMAGEMANAGER->findDImage("불러오기버튼")->getHeight());
}

void tileClass::ButtonRenewal()
{
	//방향
	if (_groundNum == 0)
	{
		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("진행버튼 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("진행버튼");
		}

	}
	if (_groundNum == 1)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("진행불가버튼 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("진행불가버튼");
		}
	}
	if (_groundNum == 2)
	{
		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("아래 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("아래");
		}
	}
	if (_groundNum == 3)
	{
		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("위 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("위");
		}
	}
	if (_groundNum == 4)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("왼쪽 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("왼쪽");
		}
	}
	if (_groundNum == 5)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("오른쪽 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("오른쪽");
		}
	}
	if (_groundNum == 6)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("오른쪽위 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("오른쪽위");
		}
	}
	if (_groundNum == 7)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("오른쪽아래 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("오른쪽아래");
		}
	}
	if (_groundNum == 8)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("왼쪽아래 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("왼쪽아래");
		}
	}
	if (_groundNum == 9)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("왼쪽위 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("왼쪽위");
		}
	}
	if (_groundNum == 10)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("위아래 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("위아래");
		}
	}
	if (_groundNum == 11)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("좌우 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("좌우");
		}
	}
	if (_groundNum == 12)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("아래오른쪽위 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("아래오른쪽위");
		}
	}
	if (_groundNum == 13)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("왼쪽아래위 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("왼쪽아래위");
		}
	}
	if (_groundNum == 14)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("왼쪽위오른쪽버튼 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("왼쪽위오른쪽버튼");
		}
	}
	if (_groundNum == 15)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("왼쪽아래오른쪽 1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("왼쪽아래오른쪽");
		}
	}
	if (_groundNum == 16)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("물버튼1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("물버튼");
		}
	}
	if (_groundNum == 17)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("광원버튼1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("광원버튼");
		}
	}
	if (_groundNum == 18)
	{

		if (_groendOn == true)
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("몬스터버튼1");
		}
		else
		{
			_groundArrowImg = IMAGEMANAGER->findDImage("몬스터버튼");
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

	//방향2
	if (_groundNum2 == 0)
	{
		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("진행버튼 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("진행버튼");
		}

	}
	if (_groundNum2 == 1)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("진행불가버튼 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("진행불가버튼");
		}
	}
	if (_groundNum2 == 2)
	{
		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("아래 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("아래");
		}
	}
	if (_groundNum2 == 3)
	{
		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("위 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("위");
		}
	}
	if (_groundNum2 == 4)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("왼쪽 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("왼쪽");
		}
	}
	if (_groundNum2 == 5)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("오른쪽 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("오른쪽");
		}
	}
	if (_groundNum2 == 6)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("오른쪽위 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("오른쪽위");
		}
	}
	if (_groundNum2 == 7)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("오른쪽아래 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("오른쪽아래");
		}
	}
	if (_groundNum2 == 8)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("왼쪽아래 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("왼쪽아래");
		}
	}
	if (_groundNum2 == 9)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("왼쪽위 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("왼쪽위");
		}
	}
	if (_groundNum2 == 10)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("위아래 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("위아래");
		}
	}
	if (_groundNum2 == 11)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("좌우 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("좌우");
		}
	}
	if (_groundNum2 == 12)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("아래오른쪽위 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("아래오른쪽위");
		}
	}
	if (_groundNum2 == 13)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("왼쪽아래위 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("왼쪽아래위");
		}
	}
	if (_groundNum2 == 14)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("왼쪽위오른쪽버튼 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("왼쪽위오른쪽버튼");
		}
	}
	if (_groundNum2 == 15)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("왼쪽아래오른쪽 1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("왼쪽아래오른쪽");
		}
	}
	if (_groundNum2 == 16)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("물버튼1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("물버튼");
		}
	}
	if (_groundNum2 == 17)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("광원버튼1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("광원버튼");
		}
	}
	if (_groundNum2 == 18)
	{

		if (_groendOn2 == true)
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("몬스터버튼1");
		}
		else
		{
			_groundArrowImg2 = IMAGEMANAGER->findDImage("몬스터버튼");
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


	//건축물 버튼
	if (_buildNum == 0)
	{
		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("진행버튼 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("진행버튼");
		}

	}
	if (_buildNum == 1)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("진행불가버튼 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("진행불가버튼");
		}
	}
	if (_buildNum == 2)
	{
		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("아래 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("아래");
		}
	}
	if (_buildNum == 3)
	{
		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("위 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("위");
		}
	}
	if (_buildNum == 4)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("왼쪽 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("왼쪽");
		}
	}
	if (_buildNum == 5)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("오른쪽 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("오른쪽");
		}
	}
	if (_buildNum == 6)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("오른쪽위 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("오른쪽위");
		}
	}
	if (_buildNum == 7)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("오른쪽아래 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("오른쪽아래");
		}
	}
	if (_buildNum == 8)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("왼쪽아래 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("왼쪽아래");
		}
	}
	if (_buildNum == 9)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("왼쪽위 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("왼쪽위");
		}
	}
	if (_buildNum == 10)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("위아래 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("위아래");
		}
	}
	if (_buildNum == 11)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("좌우 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("좌우");
		}
	}
	if (_buildNum == 12)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("아래오른쪽위 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("아래오른쪽위");
		}
	}
	if (_buildNum == 13)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("왼쪽아래위 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("왼쪽아래위");
		}
	}
	if (_buildNum == 14)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("왼쪽위오른쪽버튼 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("왼쪽위오른쪽버튼");
		}
	}
	if (_buildNum == 15)
	{

		if (_buildOn == true)
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("왼쪽아래오른쪽 1");
		}
		else
		{
			_buildArrowImg = IMAGEMANAGER->findDImage("왼쪽아래오른쪽");
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
	// 오브젝트 버튼

	if (_objectNum == 0)
	{
		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("진행버튼 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("진행버튼");
		}

	}
	if (_objectNum == 1)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("진행불가버튼 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("진행불가버튼");
		}
	}
	if (_objectNum == 2)
	{
		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("아래 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("아래");
		}
	}
	if (_objectNum == 3)
	{
		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("위 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("위");
		}
	}
	if (_objectNum == 4)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("왼쪽 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("왼쪽");
		}
	}
	if (_objectNum == 5)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("오른쪽 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("오른쪽");
		}
	}
	if (_objectNum == 6)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("오른쪽위 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("오른쪽위");
		}
	}
	if (_objectNum == 7)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("오른쪽아래 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("오른쪽아래");
		}
	}
	if (_objectNum == 8)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("왼쪽아래 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("왼쪽아래");
		}
	}
	if (_objectNum == 9)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("왼쪽위 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("왼쪽위");
		}
	}
	if (_objectNum == 10)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("위아래 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("위아래");
		}
	}
	if (_objectNum == 11)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("좌우 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("좌우");
		}
	}
	if (_objectNum == 12)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("아래오른쪽위 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("아래오른쪽위");
		}
	}
	if (_objectNum == 13)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("왼쪽아래위 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("왼쪽아래위");
		}
	}
	if (_objectNum == 14)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("왼쪽위오른쪽버튼 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("왼쪽위오른쪽버튼");
		}
	}
	if (_objectNum == 15)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("왼쪽아래오른쪽 1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("왼쪽아래오른쪽");
		}
	}
	if (_objectNum == 16)
	{

		if (_objectOn == true)
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("몬스터버튼1");
		}
		else
		{
			_objectArrowImg = IMAGEMANAGER->findDImage("몬스터버튼");
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
		//지형 속성
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
		//건물 속성
		if (PtInRect(&_buildArrow, _Mouse.Origin))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_buildOn = true;
			}
		}
		//오브젝트 속성 CTRL_ERASER
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
		if (_tiles[i].terrain == TR_LIGHT)IMAGEMANAGER->findDImage("지형버튼_광원버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.30f);
		if (_tiles[i].terrain == TR_MOSTER)IMAGEMANAGER->findDImage("지형버튼_몬스터버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_WATER)IMAGEMANAGER->findDImage("지형버튼_물버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_BOTTOM)IMAGEMANAGER->findDImage("지형버튼_아래버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_BTR)IMAGEMANAGER->findDImage("지형버튼_아래오른쪽위")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_RIGHT)IMAGEMANAGER->findDImage("지형버튼_오른쪽")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_RB)IMAGEMANAGER->findDImage("지형버튼_오른쪽아래버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_RT)IMAGEMANAGER->findDImage("지형버튼_오른쪽위버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_LEFT)IMAGEMANAGER->findDImage("지형버튼_왼쪽버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_LB)IMAGEMANAGER->findDImage("지형버튼_왼쪽아래버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_LBR)IMAGEMANAGER->findDImage("지형버튼_왼쪽아래오른쪽")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_BTL)IMAGEMANAGER->findDImage("지형버튼_왼쪽아래위")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_LT)IMAGEMANAGER->findDImage("지형버튼_왼쪽위버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_LTR)IMAGEMANAGER->findDImage("지형버튼_왼쪽위오른쪽버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_TOP)IMAGEMANAGER->findDImage("지형버튼_위버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_TB)IMAGEMANAGER->findDImage("지형버튼_위아래버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_LR)IMAGEMANAGER->findDImage("지형버튼_좌우버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_MOVE)IMAGEMANAGER->findDImage("지형버튼_진행버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain == TR_UNMOVE)IMAGEMANAGER->findDImage("지형버튼_진행불가")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);


		if (_tiles[i].terrain2 == TR2_LIGHT)IMAGEMANAGER->findDImage("언덕버튼_광원버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.30f);
		if (_tiles[i].terrain2 == TR2_MOSTER)IMAGEMANAGER->findDImage("언덕버튼_몬스터버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == OBJ_WATER)IMAGEMANAGER->findDImage("언덕버튼_물버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_BOTTOM)IMAGEMANAGER->findDImage("언덕버튼_아래버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_BTR2)IMAGEMANAGER->findDImage("언덕버튼_아래오른쪽위")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_RIGHT)IMAGEMANAGER->findDImage("언덕버튼_오른쪽")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_RB)IMAGEMANAGER->findDImage("언덕버튼_오른쪽아래버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_RT)IMAGEMANAGER->findDImage("언덕버튼_오른쪽위버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_LEFT)IMAGEMANAGER->findDImage("언덕버튼_왼쪽버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_LB)IMAGEMANAGER->findDImage("언덕버튼_왼쪽아래버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_LBR)IMAGEMANAGER->findDImage("언덕버튼_왼쪽아래오른쪽")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_BTL)IMAGEMANAGER->findDImage("언덕버튼_왼쪽아래위")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_LT)IMAGEMANAGER->findDImage("언덕버튼_왼쪽위버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_LTR2)IMAGEMANAGER->findDImage("언덕버튼_왼쪽위오른쪽버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_TOP)IMAGEMANAGER->findDImage("언덕버튼_위버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_TB)IMAGEMANAGER->findDImage("언덕버튼_위아래버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_LR)IMAGEMANAGER->findDImage("언덕버튼_좌우버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_MOVE)IMAGEMANAGER->findDImage("언덕버튼_진행버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].terrain2 == TR2_UNMOVE)IMAGEMANAGER->findDImage("언덕버튼_진행불가")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);


		if (_tiles[i].build == BU_WATER)IMAGEMANAGER->findDImage("건물버튼_물버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_BOTTOM)IMAGEMANAGER->findDImage("건물버튼_아래버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_BTR)IMAGEMANAGER->findDImage("건물버튼_아래오른쪽위")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_RIGHT)IMAGEMANAGER->findDImage("건물버튼_오른쪽")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_RB)IMAGEMANAGER->findDImage("건물버튼_오른쪽아래버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_RT)IMAGEMANAGER->findDImage("건물버튼_오른쪽위버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_LEFT)IMAGEMANAGER->findDImage("건물버튼_왼쪽버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_LB)IMAGEMANAGER->findDImage("건물버튼_왼쪽아래버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_LBR)IMAGEMANAGER->findDImage("건물버튼_왼쪽아래오른쪽")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_BTL)IMAGEMANAGER->findDImage("건물버튼_왼쪽아래위")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_LT)IMAGEMANAGER->findDImage("건물버튼_왼쪽위버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_LTR)IMAGEMANAGER->findDImage("건물버튼_왼쪽위오른쪽버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_TOP)IMAGEMANAGER->findDImage("건물버튼_위버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_TB)IMAGEMANAGER->findDImage("건물버튼_위아래버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_LR)IMAGEMANAGER->findDImage("건물버튼_좌우버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_MOVE)IMAGEMANAGER->findDImage("건물버튼_진행버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].build == BU_UNMOVE)IMAGEMANAGER->findDImage("건물버튼_진행불가")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);

		if (_tiles[i].obj == OBJ_MOSTER)IMAGEMANAGER->findDImage("오브젝트_몬스터버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_WATER)IMAGEMANAGER->findDImage("오브젝트_물버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_BOTTOM)IMAGEMANAGER->findDImage("오브젝트_아래버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_BTR)IMAGEMANAGER->findDImage("오브젝트_아래오른쪽위")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_RIGHT)IMAGEMANAGER->findDImage("오브젝트_오른쪽")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_RB)IMAGEMANAGER->findDImage("오브젝트_오른쪽아래버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_RT)IMAGEMANAGER->findDImage("오브젝트_오른쪽위버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_LEFT)IMAGEMANAGER->findDImage("오브젝트_왼쪽버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_LB)IMAGEMANAGER->findDImage("오브젝트_왼쪽아래버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_LBR)IMAGEMANAGER->findDImage("오브젝트_왼쪽아래오른쪽")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_BTL)IMAGEMANAGER->findDImage("오브젝트_왼쪽아래위")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_LT)IMAGEMANAGER->findDImage("오브젝트_왼쪽위버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_LTR)IMAGEMANAGER->findDImage("오브젝트_왼쪽위오른쪽버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_TOP)IMAGEMANAGER->findDImage("오브젝트_위버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_TB)IMAGEMANAGER->findDImage("오브젝트_위아래버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_LR)IMAGEMANAGER->findDImage("오브젝트_좌우버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_MOVE)IMAGEMANAGER->findDImage("오브젝트_진행버튼")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
		if (_tiles[i].obj == OBJ_UNMOVE)IMAGEMANAGER->findDImage("오브젝트_진행불가")->render(_tiles[i].rc.left, _tiles[i].rc.top, 0.50f);
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			









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
	IMAGEMANAGER->addDImage("지형메뉴", L"UI/지형메뉴.png", 800, 800);

	// 설정
	_groundMenuImg = IMAGEMANAGER->findDImage("지형메뉴");
	//렉트
	_groundMenu = RectMake(CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, IMAGEMANAGER->findDImage("지형메뉴")->getWidth(),
		IMAGEMANAGER->findDImage("지형메뉴")->getHeight());

	_GMx = (_groundMenu.left + _groundMenu.right) / 2;
	_GMy = (_groundMenu.top + _groundMenu.bottom) / 2;
}

void tileClass::tileIMG()
{


	IMAGEMANAGER->addFrameDImage("타일셋1", L"map/타일셋1.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋2", L"map/타일셋2.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋3", L"map/타일셋3.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋4", L"map/타일셋4.png", 768, 768, SAMPLETILEX, SAMPLETILEY);

	IMAGEMANAGER->addFrameDImage("타일셋5", L"map/타일셋5.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋6", L"map/타일셋6.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋7", L"map/타일셋7.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋8", L"map/타일셋8.png", 768, 768, SAMPLETILEX, SAMPLETILEY);

	IMAGEMANAGER->addFrameDImage("타일셋9", L"map/타일셋9.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋10", L"map/타일셋10.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋11", L"map/타일셋11.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋12", L"map/타일셋12.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋13", L"map/타일셋13.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋14", L"map/타일셋14.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋15", L"map/타일셋15.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋16", L"map/타일셋16.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋17", L"map/타일셋17.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋18", L"map/타일셋18.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋19", L"map/타일셋19.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋20", L"map/타일셋20.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋21", L"map/타일셋21.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋22", L"map/타일셋22.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋23", L"map/타일셋23.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋24", L"map/타일셋24.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋25", L"map/타일셋25.png", 768, 768, SAMPLETILEX, SAMPLETILEY);

	IMAGEMANAGER->addFrameDImage("타일셋26", L"map/타일셋26.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋27", L"map/타일셋27.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋28", L"map/타일셋28.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋29", L"map/타일셋29.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋30", L"map/타일셋30.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋31", L"map/타일셋31.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋32", L"map/타일셋32.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋33", L"map/타일셋33.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋34", L"map/타일셋34.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋35", L"map/타일셋35.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋36", L"map/타일셋36.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋37", L"map/타일셋37.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋38", L"map/타일셋38.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋39", L"map/타일셋39.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋40", L"map/타일셋40.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋41", L"map/타일셋41.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋42", L"map/타일셋42.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋43", L"map/타일셋43.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋44", L"map/타일셋44.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋45", L"map/타일셋45.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋46", L"map/타일셋46.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋47", L"map/타일셋47.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋48", L"map/타일셋48.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("타일셋49", L"map/타일셋49.png", 768, 768, SAMPLETILEX, SAMPLETILEY);
	// 설정
	_mapTileImge[0] = IMAGEMANAGER->findDImage("타일셋1");
	_mapTileImge[1] = IMAGEMANAGER->findDImage("타일셋2");
	_mapTileImge[2] = IMAGEMANAGER->findDImage("타일셋3");
	_mapTileImge[3] = IMAGEMANAGER->findDImage("타일셋4");
	_mapTileImge[4] = IMAGEMANAGER->findDImage("타일셋5");
	_mapTileImge[5] = IMAGEMANAGER->findDImage("타일셋6");
	_mapTileImge[6] = IMAGEMANAGER->findDImage("타일셋7");
	_mapTileImge[7] = IMAGEMANAGER->findDImage("타일셋8");
	_mapTileImge[8] = IMAGEMANAGER->findDImage("타일셋9");
	_mapTileImge[9] = IMAGEMANAGER->findDImage("타일셋10");
	_mapTileImge[10] = IMAGEMANAGER->findDImage("타일셋11");
	_mapTileImge[11] = IMAGEMANAGER->findDImage("타일셋12");
	_mapTileImge[12] = IMAGEMANAGER->findDImage("타일셋13");
	_mapTileImge[13] = IMAGEMANAGER->findDImage("타일셋14");
	_mapTileImge[14] = IMAGEMANAGER->findDImage("타일셋15");
	_mapTileImge[15] = IMAGEMANAGER->findDImage("타일셋16");
	_mapTileImge[16] = IMAGEMANAGER->findDImage("타일셋17");
	_mapTileImge[17] = IMAGEMANAGER->findDImage("타일셋18");
	_mapTileImge[18] = IMAGEMANAGER->findDImage("타일셋19");
	_mapTileImge[19] = IMAGEMANAGER->findDImage("타일셋20");
	_mapTileImge[20] = IMAGEMANAGER->findDImage("타일셋21");
	_mapTileImge[21] = IMAGEMANAGER->findDImage("타일셋22");
	_mapTileImge[22] = IMAGEMANAGER->findDImage("타일셋23");
	_mapTileImge[23] = IMAGEMANAGER->findDImage("타일셋24");
	_mapTileImge[24] = IMAGEMANAGER->findDImage("타일셋25");
	_mapTileImge[25] = IMAGEMANAGER->findDImage("타일셋26");
	_mapTileImge[26] = IMAGEMANAGER->findDImage("타일셋27");
	_mapTileImge[27] = IMAGEMANAGER->findDImage("타일셋28");
	_mapTileImge[28] = IMAGEMANAGER->findDImage("타일셋29");
	_mapTileImge[29] = IMAGEMANAGER->findDImage("타일셋30");
	_mapTileImge[30] = IMAGEMANAGER->findDImage("타일셋31");
	_mapTileImge[31] = IMAGEMANAGER->findDImage("타일셋32");
	_mapTileImge[32] = IMAGEMANAGER->findDImage("타일셋33");
	_mapTileImge[33] = IMAGEMANAGER->findDImage("타일셋34");
	_mapTileImge[34] = IMAGEMANAGER->findDImage("타일셋35");
	_mapTileImge[35] = IMAGEMANAGER->findDImage("타일셋36");
	_mapTileImge[36] = IMAGEMANAGER->findDImage("타일셋37");
	_mapTileImge[37] = IMAGEMANAGER->findDImage("타일셋38");
	_mapTileImge[38] = IMAGEMANAGER->findDImage("타일셋39");
	_mapTileImge[39] = IMAGEMANAGER->findDImage("타일셋40");
	_mapTileImge[40] = IMAGEMANAGER->findDImage("타일셋41");
	_mapTileImge[41] = IMAGEMANAGER->findDImage("타일셋42");
	_mapTileImge[42] = IMAGEMANAGER->findDImage("타일셋43");
	_mapTileImge[43] = IMAGEMANAGER->findDImage("타일셋44");
	_mapTileImge[44] = IMAGEMANAGER->findDImage("타일셋45");
	_mapTileImge[45] = IMAGEMANAGER->findDImage("타일셋46");
	_mapTileImge[46] = IMAGEMANAGER->findDImage("타일셋47");
	_mapTileImge[47] = IMAGEMANAGER->findDImage("타일셋48");
	_mapTileImge[48] = IMAGEMANAGER->findDImage("타일셋49");

	_tileSetNum = 0;
	//렉트
	_mapTileRect[0] = RectMakeCenter(_GMx, _GMy, IMAGEMANAGER->findDImage("타일셋1")->getWidth(),
		IMAGEMANAGER->findDImage("타일셋1")->getHeight());

}

void tileClass::updateRect()
{
	_ground = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top, IMAGEMANAGER->findDImage("지형버튼")->getWidth(),
		IMAGEMANAGER->findDImage("지형버튼")->getHeight());
	_groundArrow = RectMake(CAMERAMANAGER->getScreen().right - 368, CAMERAMANAGER->getScreen().top, IMAGEMANAGER->findDImage("진행버튼")->getWidth(),
		IMAGEMANAGER->findDImage("진행버튼")->getHeight());

	_ground2 = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 85, IMAGEMANAGER->findDImage("언덕버튼")->getWidth(),
		IMAGEMANAGER->findDImage("언덕버튼")->getHeight());
	_groundArrow2 = RectMake(CAMERAMANAGER->getScreen().right - 368, CAMERAMANAGER->getScreen().top + 85, IMAGEMANAGER->findDImage("진행버튼")->getWidth(),
		IMAGEMANAGER->findDImage("진행버튼")->getHeight());


	_object = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 170, IMAGEMANAGER->findDImage("오브젝트버튼")->getWidth(),
		IMAGEMANAGER->findDImage("오브젝트버튼")->getHeight());
	_objectArrow = RectMake(CAMERAMANAGER->getScreen().right - 368, CAMERAMANAGER->getScreen().top + 170, IMAGEMANAGER->findDImage("진행버튼")->getWidth(),
		IMAGEMANAGER->findDImage("진행버튼")->getHeight());


	_water = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 255, IMAGEMANAGER->findDImage("바다버튼")->getWidth(),
		IMAGEMANAGER->findDImage("바다버튼")->getHeight());

	_build = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 340, IMAGEMANAGER->findDImage("건축물버튼")->getWidth(),
		IMAGEMANAGER->findDImage("건축물버튼")->getHeight());
	_buildArrow = RectMake(CAMERAMANAGER->getScreen().right - 368, CAMERAMANAGER->getScreen().top + 340, IMAGEMANAGER->findDImage("진행버튼")->getWidth(),
		IMAGEMANAGER->findDImage("진행버튼")->getHeight());

	_save = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 425, IMAGEMANAGER->findDImage("저장버튼")->getWidth(),
		IMAGEMANAGER->findDImage("저장버튼")->getHeight());
	_load = RectMake(CAMERAMANAGER->getScreen().right - 281, CAMERAMANAGER->getScreen().top + 510, IMAGEMANAGER->findDImage("불러오기버튼")->getWidth(),
		IMAGEMANAGER->findDImage("불러오기버튼")->getHeight());
	_mapTileRect[0] = RectMakeCenter(_GMx, _GMy, IMAGEMANAGER->findDImage("타일셋1")->getWidth(),
		IMAGEMANAGER->findDImage("타일셋1")->getHeight());
	_groundMenu = RectMake(CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, IMAGEMANAGER->findDImage("지형메뉴")->getWidth(),
		IMAGEMANAGER->findDImage("지형메뉴")->getHeight());
	test = RectMakeCenter(_ptMouse.x + CAMERAMANAGER->getScreen().left, _ptMouse.y + CAMERAMANAGER->getScreen().top, 10, 10);



}






