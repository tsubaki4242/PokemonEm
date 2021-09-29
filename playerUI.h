#pragma once
#include "singletonBase.h"

class playerUI : public singletonBase<playerUI>
{

private:

	dImage* _menu;
	RECT _menuRect;
	int _menuFrameCount;
	int _menuFrame;
	RECT _screanRect;

	int _leftHendle;
	int _rightHendle;
	int _menuHendle;
	int _menuSizeW, _menuSizeH;
	int _menuWich;;

	bool _menuOn;
	bool _menuOrgin;
	bool _invenStart;

	float _fadeOut[99];

	int count2;

	dImage* _buttenImg[6];
	RECT _butten[6];
	int _buttenNum;


	//포켓몬 메뉴
	RECT _frontRect;
	dImage* _buttenPokemonImg[6];
	RECT _buttenPokemon[6];
	int _buttenPokemonNum;
	bool _pokemonMenuOn;

	dImage* _pokemonInvenBase[6];
	dImage* _pokemonInvenIcon[6];
	dImage* _pokemonInvenFront[6];
	dImage* _pokemonInvenBack[6];
	PERSONA _pokemonInvenPersona[6];
	wstring  _pokemonInvenName[6];
	TYPE _pokemonInvenType1[6];
	TYPE _pokemonInvenType2[6];
	dImage* _pokemontype1;
	dImage* _pokemontype2;

	char _txtLV[64];
	char _txtLV1[64];
	char _txtLV2[64];
	char _txtLV3[64];
	char _txtLV4[64];
	char _txtLV5[64];
	bool _pokemonInvenSex[6];
	int _pokemonInvenNameLv[6];
	int _pokemonInvenNameExp[6];
	int _pokemonInvenNameMaxHp[6];
	int _pokemonInvenNameHp[6];
	int _pokemonInvenNamAtk[6];
	int _pokemonInvenNameDef[6];
	int _pokemonInvenNameMatk[6];
	int _pokemonInvenNameMdef[6];
	int _pokemonInvenNameSpd[6];

	dImage* _LvImg[6];
	dImage* _hpBox[6];
	dImage* _hpBar[6];
	float _hpBarCount[6];
	dImage* _hpBarBacck[6];




	//트레이너 카드
	RECT _bageGYM[8];
	dImage* _bageIMG[8];

	RECT _LeaderGYM[8];
	dImage* _LeaderIMG[8];
	bool _cardOn;

	float _alpa;
	dImage* _alpaScreen;
	bool _Go[10];




public:
	playerUI();
	~playerUI();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void IMGALL();
	void menuOn();
	void menuOff();
	void invenOn();
	void keyControl();
	void card();
	void menuPokemon();
	void pokemonInvenUpdate();

	void type1Img(TYPE type1);
	void type2Img(TYPE type2);
	void pokemonInven1all(int max,dImage* pokemon, dImage* inven, dImage* front, dImage* back, wstring name, TYPE type1, TYPE type2, PERSONA persona, int Lv, int exp, bool sex, int MaxHp, int hp, int atk, int def, int matk, int mdef, int spd);
	void fadeIn();
	void fadeOut();
};

