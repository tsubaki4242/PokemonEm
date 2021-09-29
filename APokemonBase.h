#pragma once
#include "gameNode.h"
#include <vector>
#include "skillManger.h"
#include "skillBase.h"



struct PokemonState
{


	vector<skillBase*>				vSkill;
	vector<skillBase*>::iterator	viSkill;
	skillManger* skillManger;
	dImage* invenImg;

	dImage* icon;
	float iconX;
	float iconY;
	float iconFrameX;
	float iconFrameY;

	wstring name;
	
	TYPE type[2];
	PERSONA persona;
	dImage* ftont;
	int FrameX;
	int FrameY;
	float ftontX;
	float ftontY;
	dImage* back;
	int FrameXb;
	int FrameYb;
	float backX;
	float backY;

	bool shiney;
//	int abilities;
	int LV;
	int maxExp;
	int exp;
	int love;
	bool sex;
	int maxHp;
	int hp;
	int atk;
	int def;
	int matk;
	int mdef;
	int spd;

	int count;

	//오르는 능력치 값
	int LVPlus;
	int expPlus;
	int lovePlus;
	int sexPlus;
	int maxHpPlus;
	int hpPlus;
	int atkPlus;
	int defPlus;
	int matkPlus;
	int mdefPlus;
	int spdPlus;

	//종족값
	int maxHpZ;
	int atkZ;
	int defZ;
	int matkZ;
	int mdefZ;
	int spdZ;

	//개체치
	int maxHpV;
	int atkV;
	int defV;
	int matkV;
	int mdefV;
	int spdV;

	//노력차
	int maxHpS;
	int atkS;
	int defS;
	int matkS;
	int mdefS;
	int spdS;

	//성격보정
	float maxHpP;
	float atkP;
	float defP;
	float matkP;
	float mdefP;
	float spdP;

};



class APokemonBase : public gameNode
{
protected:



	PokemonState _pokemon;

	

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void frontRender(float x, float y);
	virtual void backRender(float x, float y);
	virtual void iconRender(float x, float y);

	virtual void personaPlus();
	virtual void CapabilityValue();

	dImage* getIconImg() { return _pokemon.icon; }
	dImage* getFront() { return _pokemon.ftont; }
	dImage* getBack() { return _pokemon.back; }
	dImage* getInvenImg() { return _pokemon.invenImg; }
	TYPE getType1() { return _pokemon.type[0]; }
	TYPE getType2() { return _pokemon.type[1]; }
	PERSONA getPersona() { return _pokemon.persona; }

	wstring getName() { return _pokemon.name; }

	void setIconX(float x) { _pokemon.iconX = x; }
	int getIconX() { return _pokemon.iconX; }
	void setIconY(float y) { _pokemon.iconY = y; }
	int getIconY() { return _pokemon.iconY; }

	void setFrameX(int x) { _pokemon.FrameX = x; }
	int getFrameX() { return _pokemon.FrameX; }
	void setFrameY(int y) { _pokemon.FrameY = y; }
	int getFrameY() { return _pokemon.FrameY; }

	void setFtontX(float x) { _pokemon.ftontX = x; }
	float getFtontX() { return _pokemon.ftontX; }
	void setFtontY(float y) { _pokemon.ftontY = y; }
	float getFtontY() { return _pokemon.ftontY; }

	void setFrameXb(int x) { _pokemon.FrameXb = x; }
	int getFrameXb() { return _pokemon.FrameXb; }
	void setFrameYb(int y) { _pokemon.FrameYb = y; }
	int getFrameYb() { return _pokemon.FrameYb; }

	void setBackX(float x) { _pokemon.backX = x; }
	float getBackX() { return _pokemon.backX; }
	void setBackY(float y) { _pokemon.backY = y; }
	float getBackY() { return _pokemon.backY; }

	void setShiney(bool shiney) { _pokemon.shiney = shiney; }
	bool getShiney() { return _pokemon.shiney; }


	void setLV(int LV) { _pokemon.LV = LV; }
	int getLV() { return _pokemon.LV; }
	void setExp(int exp) { _pokemon.exp = exp; }
	int getExp() { return _pokemon.exp; }
	void setLove(int love) { _pokemon.love = love; }
	int getLove() { return _pokemon.love; }
	void setSex(bool sex) { _pokemon.sex = sex; }
	bool getSex() { return _pokemon.sex; }
	void setMaxHp(int MaxHp) { _pokemon.maxHp = MaxHp; }
	int getMaxHp() { return _pokemon.maxHp; }
	void damgeHP(int damge) { _pokemon.hp -= damge; }
	void setHP(int HP) { _pokemon.hp = HP; }
	int getHP() { return _pokemon.hp; }
	void setAtk(int atk) { _pokemon.atk = atk; }
	int getAtk() { return _pokemon.atk; }
	void setDef(int def) { _pokemon.def = def; }
	int getDef() { return _pokemon.def; }
	void setMatk(bool matk) { _pokemon.matk = matk; }
	bool getMatk() { return _pokemon.matk; }
	void setMdef(int mdef) { _pokemon.mdef = mdef; }
	int getMdef() { return _pokemon.mdef; }
	void setSpd(int spd) { _pokemon.spd = spd; }
	int getSpd() { return _pokemon.spd; }

	void setMaxHpV(int MaxHp) { _pokemon.maxHpV = MaxHp; }
	int getMaxHpV() { return _pokemon.maxHpV; }
	void setAtkV(int atk) { _pokemon.atkV = atk; }
	int getEAtkV() { return _pokemon.atkV; }
	void setDefV(int def) { _pokemon.defV = def; }
	int getDefV() { return _pokemon.defV; }
	void setMatkV(bool matk) { _pokemon.matkV = matk; }
	bool getMatkV() { return _pokemon.matkV; }
	void setMdefV(int mdef) { _pokemon.mdefV = mdef; }
	int getMdefV() { return _pokemon.mdefV; }
	void setSpdV(int spd) { _pokemon.spdV = spd; }
	int getSpdV() { return _pokemon.spdV; }

	void setMaxHpS(int MaxHp) { _pokemon.maxHpS = MaxHp; }
	int getMaxHpS() { return _pokemon.maxHpS; }
	void setAtkS(int atk) { _pokemon.atkS = atk; }
	int getEAtkS() { return _pokemon.atkS; }
	void setDefS(int def) { _pokemon.defS = def; }
	int getDefS() { return _pokemon.defS; }
	void setMatkS(bool matk) { _pokemon.matkS = matk; }
	bool getMatkS() { return _pokemon.matkS; }
	void setMdefS(int mdef) { _pokemon.mdefS = mdef; }
	int getMdefS() { return _pokemon.mdefS; }
	void setSpdS(int spd) { _pokemon.spdS = spd; }
	int getSpdS() { return _pokemon.spdS; }

	void setMaxHpP(int MaxHp) { _pokemon.maxHpP = MaxHp; }
	int getMaxHpP() { return _pokemon.maxHpP; }
	void setAtkP(int atk) { _pokemon.atkP = atk; }
	int getEAtkP() { return _pokemon.atkP; }
	void setDefP(int def) { _pokemon.defP = def; }
	int getDefP() { return _pokemon.defP; }
	void setMatkP(bool matk) { _pokemon.matkP = matk; }
	bool getMatkP() { return _pokemon.matkP; }
	void setMdefP(int mdef) { _pokemon.mdefP = mdef; }
	int getMdefP() { return _pokemon.mdefP; }
	void setSpdP(int spd) { _pokemon.spdP = spd; }
	int getSpdP() { return _pokemon.spdP; }

	PokemonState returnPokemonState() { return _pokemon; }

	vector<skillBase*> getVSkill() { return _pokemon.vSkill; }
	vector<skillBase*>::iterator getViSkill() { return _pokemon.viSkill; }
};

