#pragma once
#include "singletonBase.h"

class batter : public singletonBase<batter>
{
private:
	dImage* _backGround;
	dImage* _butten[4];
	RECT  _buttenRc[4];
	int _buttenX[4];
	int _buttenCount;
	dImage* _playerPokemon;
	dImage* _playerunder;
	dImage* _enemyPokemon;

	dImage* _playerHpbar;
	dImage* _enemyHpbar;

	dImage* _playerBackHpbar;
	dImage* _enemyBackHpbar;

	int _count[10];
	float _fadeOut[10];
	int _frameX[10];

	dImage* _pokemonInvenBase[6];
	dImage* _pokemonInvenIcon[6];
	dImage* _pokemonInvenFront[6];
	dImage* _pokemonInvenBack[6];
	PERSONA _pokemonInvenPersona[6];
	wstring  _pokemonInvenName[6];
	TYPE _pokemonInvenType1[6];
	TYPE _pokemonInvenType2[6];
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

	dImage* _ball;
	int _ballX, _ballY;
	float _ballAngle;
	int _playerPokemonNum;
	int _playerfrontNum;

	int _playerX;

	dImage* _LvImg;
	dImage* _hpBox;
	dImage* _hpBar;
	float _hpBarCount;
	dImage* _hpBarBacck;

	dImage* _LvImgE;
	dImage* _hpBoxE;
	dImage* _hpBarE;
	float _hpBarCountE;
	dImage* _hpBarBacckE;

	dImage* _skillImg[4];

	dImage* _buttenPokemonImg[6];
	RECT _buttenPokemon[6];
	int _buttenPokemonNum;
	bool _pokemonMenuOn;
public:
	batter();
	~batter();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void imgAll();
	void fadeOut();
	void buttenUpdtae();
	void keyButten();
	void pokemonInven1all(int max, dImage* pokemon, dImage* inven, dImage* front, dImage* back, wstring name, TYPE type1, TYPE type2, PERSONA persona, int Lv, int exp, bool sex, int MaxHp, int hp, int atk, int def, int matk, int mdef, int spd);
	void pokemoSkill(int max,dImage* skill1, dImage* skill2);
	void enemyPkemon();
	
};

