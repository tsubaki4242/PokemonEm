#include "stdafx.h"
#include "pokemonManger.h"

HRESULT pokemonManger::init()
{



	return S_OK;
}

void pokemonManger::release()
{
}

void pokemonManger::update()
{

}

void pokemonManger::render()
{
}

APokemonBase* pokemonManger::GetPokemon(wstring name)
{
	if (name == L"이상해씨")
	{

		Bulbasaur* _Bulbasaur = new Bulbasaur;
		_Bulbasaur ->init();
		return _Bulbasaur;
	}
	if (name == L"이상해풀")
	{

		Ivysaur* _Ivysaur = new Ivysaur;
		_Ivysaur->init();
		return _Ivysaur;
	}
	if (name == L"이상해꽃")
	{

		Venusaur* _Venusaur = new Venusaur;
		_Venusaur->init();
		return _Venusaur;
	}




	//for (int i = 0; i < vPokemon.size(); i++)
	//{
	//	if (vPokemon[i]->getName() == name)
	//	{
	//		APokemonBase* temp = vPokemon[i];
	//		vPokemon.erase(vPokemon.begin() + i);
	//		return temp;
	//	}
	//	
	//}
	return nullptr;
}
