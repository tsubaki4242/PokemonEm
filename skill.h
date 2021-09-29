#pragma once
#include "gameNode.h"
#include <vector>



class skill : public gameNode
{
private:
	//vector<tagskill>			_vSkill;
	//vector<tagskill>::iterator _viSkill;


public:
	skill() {};
	~skill() {};

	HRESULT init(int skillMax, float range);
	void release();
	void update();
	void render();




	//vector<tagskill> getVSkill() { return _vSkill; }
	//vector<tagskill>::iterator getViSkill() { return _viSkill; }

};

