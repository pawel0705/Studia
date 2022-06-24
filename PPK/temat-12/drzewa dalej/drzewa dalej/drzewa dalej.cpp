// drzewa dalej.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>

typedef int T;



/** Deklaracja wezla drzewa.

@author Ambrozy Kleks

@date   2018-02-31

*/

struct wezel

{

	T wartosc;

	wezel * pLewy, *pPrawy;

};
void dodajRek(wezel*& pRoot, T liczba)

{

	if (!pRoot) //drzewo puste

	{

		pRoot = new wezel{ liczba, nullptr, nullptr };

	}

	else

	{

		if (liczba < pRoot->wartosc)//w lewo

			dodajRek(pRoot->pLewy, liczba);

		else //w  prawo

			dodajRek(pRoot->pPrawy, liczba);

	}

}



//wypisz ze wcieciami

void wypisz(wezel * pRoot, int V)

{

	if (pRoot)

	{

		wypisz(pRoot->pLewy, V++);

		std::cout << std::setw(V) << pRoot->wartosc << std::endl;

		wypisz(pRoot->pPrawy, V++);

	}

}



/*

void wypisz(wezel * pRoot)

{

if (pRoot)

{

wypisz(pRoot->pLewy);

std::cout << pRoot->wartosc << ' ';

wypisz(pRoot->pPrawy);

}

}

*/



void usun(wezel *&pRoot)

{

	if (pRoot)

	{

		usun(pRoot->pLewy);

		usun(pRoot->pPrawy);

		delete pRoot;

		pRoot = nullptr;

	}

}

wezel* znajdzelement(wezel* pRoot, T w)
{
	if (pRoot == nullptr)
		return 0;
	else
	{
		if (pRoot->wartosc == w)
			return pRoot;
		else
		{
			if (pRoot->wartosc < w)
				return znajdzelement(pRoot->pPrawy, w);
			else
				return znajdzelement(pRoot->pLewy, w);
		}
	}
	return pRoot;

}
/*
wezel* znajdzRodzica(wezel* pRoot, wezel*pSyn)
{
	if (pSyn == nullptr || pRoot == nullptr)
		return nullptr;
	else
	{
		if (pSyn->wartosc == pRoot->wartosc)
			return pRoot;
		else if (pSyn->wartosc > pRoot->wartosc)
			return znajdzRodzica(pRoot, pSyn->pPrawy);
		else
			return znajdzRodzica(pRoot, pSyn->pLewy);
	}
	return pRoot;
}
*/
wezel* znajdzRodzica(wezel* pRoot, wezel*pSyn)
{
	if (pSyn == nullptr || pRoot == nullptr)
		return nullptr;
	else
	{
		if 
	}
}

/*
wezel* znajdzNastepnik(wezel*pRoot, wezel* p)
{
	if (pRoot == nullptr)
		return nullptr;
	else
	{

	}
}
*/
int main(int ile, char ** params)

{
	int V = 3;
	wezel * pKorzen = 0;

	dodajRek(pKorzen, 10);

	dodajRek(pKorzen, 2);

	dodajRek(pKorzen, 18);

	dodajRek(pKorzen, 12);
	wezel* pSyn = nullptr;
	wypisz(pKorzen, V);
	int T =10;

	if ((znajdzelement(pKorzen, T)) == nullptr)
		std::cout << "Nie znalazlem" << std::endl;
	else
	{
		std::cout << "Znalazlem!" << std::endl;
		pSyn = pKorzen;
	}
	pSyn = pKorzen;
	std::cout << std::endl;
	std::cout << std::endl;


	std::cout << std::endl;
	std::cout << std::endl;

	if ((znajdzRodzica(pKorzen, pSyn)) == nullptr)
		std::cout << "Nie znalazlem rodzica!" << std::endl;
	else
		std::cout << "Znalazlem rodzica!" << std::endl;
	usun(pKorzen);

	system("pause");


	return 0;

}
