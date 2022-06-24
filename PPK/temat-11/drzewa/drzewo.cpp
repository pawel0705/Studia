

#include <iostream>
#include "drzewo.h"
#include <iomanip>

// definicje funkcji

void helloWorld ()
{
   std::cout << "Hello, world!" << std::endl;
}

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
		std::cout <<std::setw(V) << pRoot->wartosc << std::endl;
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