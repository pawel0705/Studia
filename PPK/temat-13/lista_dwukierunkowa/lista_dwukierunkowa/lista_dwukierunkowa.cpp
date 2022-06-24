// lista_dwukierunkowa.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


struct element
{
	int wartosc;
	element *pNext, *pPrev;
};

//Do domu!
//void dodajNaPoczatek(element *&pHead, element *& pTail, int w);
//void dodajNaKoniec(element *&pHead, element *& pTail, int w);
//element *znajdz(element *&pHead, element *&pHead, T w);
//void usunElement(element *& pHead, element *& pTail, element * p);
//void zammien pierwszy elemetn z ostatnim(element *& pHead, element *& pTail, element * p);
//void rozdziel(element*&pHead, element*&pTail, element*&pHeadParz, element*&pTailNieparzyste, element*&pHeadNP, element*&pTailNP); rozdzielic liste na parzyste i nieparzyste

void dodaj_w_porzadku(element *&pHead, element *&pTail, int w)
{
	if (pHead == nullptr)
	{
		pHead->wartosc = w;
		pHead->pNext = nullptr;
		pHead->pPrev = nullptr;
		pTail = pHead;
	}

	else
	{
		element* pomoc = new element;
		pomoc = nullptr;

		if (pomoc->wartosc > w) //dodajemy na pocz
		{
			pomoc = pHead;
			pomoc->wartosc = w;
		//	pHead->pPrev = nullptr;
		//	pomoc->pNext = nullptr;
			pomoc->pPrev = pHead;
			pHead->pNext = pomoc;
			pTail = pomoc;
		}
	}
}

void wypisz_liste(element *pHead)
{
	std::cout << pHead->wartosc << " " << std::endl;
	wypisz_liste(pHead->pNext);
}

int main()
{
	element* pHead = nullptr;
	element* pTail = nullptr;
	dodaj_w_porzadku(pHead, pTail, 5);
	wypisz_liste(pHead);
	system("pause");
    return 0;
}

