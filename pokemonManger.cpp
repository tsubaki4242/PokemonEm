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
	if (name == L"�̻��ؾ�")
	{

		Bulbasaur* _Bulbasaur = new Bulbasaur;
		_Bulbasaur ->init();
		return _Bulbasaur;
	}
	if (name == L"�̻���Ǯ")
	{

		Ivysaur* _Ivysaur = new Ivysaur;
		_Ivysaur->init();
		return _Ivysaur;
	}
	if (name == L"�̻��ز�")
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
