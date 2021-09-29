#pragma once
#include "gameNode.h"
#include <cmath>


#define TILESIZE 32

#define TILEX 50	//���� Ÿ�� ����
#define TILEY 50	//���� Ÿ�� ����
#define TILEIMGNUM 49 //Ÿ�� ��Ʈ


#define TILESIZEX TILESIZE * TILEX	//640 32 * 20
#define TILESIZEY TILESIZE * TILEY	//640 32 * 20

//Ÿ�ϼ� ����
#define SAMPLETILEX 24
#define SAMPLETILEY 24


#define SAMPLETILESIZE 32

#define TLEVEL 2

//����
enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_MOSTER, TR_WATER, TR_NONE,
	TR_MOVE, TR_UNMOVE,TR_LEFT,TR_RIGHT,TR_TOP,TR_BOTTOM,
	TR_LR,TR_LT,TR_LB, TR_RT, TR_RB, TR_TB,TR_LTR,TR_LBR,TR_BTR,TR_BTL, TR_LIGHT
};
enum TERRAIN2
{
	TR2_CEMENT, TR2_DESERT, TR2_MOSTER, TR2_WATER, TR2_NONE,
	TR2_MOVE, TR2_UNMOVE, TR2_LEFT, TR2_RIGHT, TR2_TOP, TR2_BOTTOM,
	TR2_LR, TR2_LT, TR2_LB, TR2_RT, TR2_RB, TR2_TB, TR2_LTR2, TR2_LBR, TR2_BTR2, TR2_BTL, TR2_LIGHT
};

enum BUILD
{
	BU_CEMENT, BU_DESERT, BU_GRASS, BU_WATER, BU_NONE,
	BU_MOVE, BU_UNMOVE, BU_LEFT, BU_RIGHT, BU_TOP, BU_BOTTOM,
	BU_LR, BU_LT, BU_LB, BU_RT, BU_RB, BU_TB, BU_LTR, BU_LBR, BU_BTR, BU_BTL

};

//������Ʈ
enum OBJECT
{
	OBJ_CEMENT, OBJ_DESERT, OBJ_MOSTER, OBJ_WATER, OBJ_NONE,
	OBJ_MOVE, OBJ_UNMOVE, OBJ_LEFT, OBJ_RIGHT, OBJ_TOP, OBJ_BOTTOM,
	OBJ_LR, OBJ_LT, OBJ_LB, OBJ_RT, OBJ_RB, OBJ_TB, OBJ_LTR, OBJ_LBR, OBJ_BTR, OBJ_BTL
};

//������
enum POS
{
	POS_FLAG1, POS_FLAG2, POS_TANK1, POS_TANK2
};

//Ÿ�� ���� ���� ����ü
struct tagTile
{
	dImage*		objImage;
	dImage*		buildImage;
	TERRAIN		terrain;
	TERRAIN2	terrain2;
	BUILD		build;
	OBJECT		obj;
	RECT		rc;
	int			terrainImgIndex;
	int			terrainImgIndex2;
	int			buildImgIndex;
	int			objImgIndex;
	int			terrainFrameX;
	int			terrainFrameY;
	int			terrainStartFrameX;
	int			terrainStartFrameY;
	int			terrainStart2FrameX;
	int			terrainStart2FrameY;
	int			terrain2FrameX;
	int			terrain2FrameY;
	int			buildFrameX;
	int			buildFrameY;
	int			objFrameX;
	int			objFrameY;
	int			tileObjZOrder;
	int			tileObjZOrderBild;
	int			tileTerrainZOrder;

	int			count;




};

//Ÿ�ϼ� ���� ���� ����ü
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//���� Ÿ�� �޾ƿ� ����ü
struct tagCurrentTile
{
	int startX;
	int startY;
	int endX;
	int endY;
	int sizeX;
	int sizeY;

};

struct OLLMOUSE
{
	int x, y;
	POINT Origin;

};

class tileClass : public gameNode
{
private:
	RECT test;
	bool _UION;

	int Wcount;

	//Ÿ��
	dImage* _mapTileImge[TILEIMGNUM];
	RECT _mapTileRect[TILEIMGNUM];
	int _tileSetNum;
	RECT _tileChoice;
	int _mouseX, _mouseY;
	bool _groundLevel;


	OLLMOUSE _Mouse;
	//��ŸƮ��Ʈ
	RECT _startRECT;

	tagCurrentTile _currentTile;
	tagSampleTile _sampleTile[SAMPLETILEX * SAMPLETILEY];
	tagTile _tiles[TILEX * TILEY];

	//��������
	RECT _ground;
	dImage* _groundImg;
	RECT _groundArrow;
	dImage* _groundArrowImg;
	int _groundNum;
	bool _groendOn;

	//Ÿ�ϼ� �޴�
	dImage* _groundMenuImg;
	RECT _groundMenu;
	int _GMx, _GMy;
	bool _groundMenuOn;

	RECT _ground2;
	dImage* _groundImg2;
	RECT _groundArrow2;
	dImage* _groundArrowImg2;
	int _groundNum2;
	bool _groendOn2;



	//�ǹ�����
	RECT _build;
	dImage* _buildImg;
	RECT _buildArrow;
	dImage* _buildArrowImg;
	int _buildNum;
	bool _buildOn;


	//������Ʈ ����
	RECT _object;
	dImage* _objectImg;
	RECT _objectArrow;
	dImage* _objectArrowImg;
	int _objectNum;
	bool _objectOn;

	RECT _water;
	dImage* _waterImg;

	RECT _save;
	dImage* _saveImg;
	RECT _load;
	dImage* _loadImg;
	const char* _fileName;
	float x, y;
	int _pos[2];
	dImage* tile;
	int _selectIndexX[2];
	int _selectIndexY[2];
	float playerY;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void maprender(RECT playerRC);

	virtual void setup();
	virtual void setMap();

	virtual void save();
	virtual void load();
	virtual void mapLoad(const char* _fileName);

	virtual void keyControl();

	virtual void Button();
	virtual void ButtonRenewal();
	virtual void RectCollisn();

	virtual void ToggleKeyIMG();
	virtual void imgGO();
	virtual void menuIMG();
	virtual void tileIMG();
	virtual void updateRect();

	tagTile* getTileAll() { return _tiles; }

};

