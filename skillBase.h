#pragma once
#include "gameNode.h"



struct  SKillSTAT
{
	dImage* skill[10];
	string name;
	float imgX[10];
	float imgY[10];
	int skillCount;
	int count;
	int FrameX;
	int FrameY;
	TYPE type;
	bool atteckType; // false이 물리 true가 특공	
	int damge;
	int speed;
	int aime;
	int index;
	int indey;

};


class skillBase : public gameNode
{
protected:


	SKillSTAT _skill;




public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	dImage* getskillImg() { return _skill.skill[0]; }

	void setFrameX(int x) { _skill.FrameX = x; }
	int getFrameX() { return _skill.FrameX; }
	void setFrameY(int y) { _skill.FrameY = y; }
	int getFrameY() { return _skill.FrameY; }
	void settAtteckType(bool type) { _skill.atteckType = type; }
	bool getAtteckType() { return _skill.atteckType; }
	void settDamge(int damge) { _skill.damge = damge; }
	int getDamge() { return _skill.damge; }
	void settAime(int aime) { _skill.aime = aime; }
	int getAime() { return _skill.aime; }
	void setSkillCount(int skillCount) { _skill.skillCount = skillCount; }
	int getSkillCount() { return _skill.skillCount; }
	void setSpeed(int speed) { _skill.speed = speed; }
	int getSpeed() { return _skill.speed; }

	string getName() { return _skill.name; }

	SKillSTAT getSkillStat() { return _skill; }


};

