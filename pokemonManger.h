#pragma once
#include "gameNode.h"
#include <vector>
#include "APokemonBase.h"
#include "Bulbasaur.h"
#include "Ivysaur.h"
#include "Venusaur.h"

class pokemonManger : public gameNode
{


private:

	vector<APokemonBase*>				vPokemon;
	vector<APokemonBase*>::iterator		viPokemon;
	int m;




public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();

	virtual void render();

	

	APokemonBase* GetPokemon(wstring name);



};

