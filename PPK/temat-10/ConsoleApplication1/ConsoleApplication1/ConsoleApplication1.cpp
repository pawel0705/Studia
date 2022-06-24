// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "../../wycieki/nvwa/debug_new.h"
#include <iostream>

typedef int T;

struct element
{
	T wartosc;
	element* pnext;
};

void usunlisteodpoczatkurek(element* &pHead)
{
	if (pHead)
	{
		auto p = pHead->pnext;
		delete pHead;
		pHead = 0; //aby funkcja jak 2 razy uzyjemy sie nie wywalila
		usunlisteodpoczatkurek(p);
	}
}

void wypiszodkoncareurencyjnie(element *pHead)
{
	if (pHead)
	{
		wypiszodkoncareurencyjnie(pHead->pnext);
		std::cout << pHead->wartosc << " ";
	}
}

void wypiszodpoczatkurekurencyjnie(element* pHead)
{
	if (pHead)
	{
		std::cout << pHead->wartosc << " ";
		wypiszodpoczatkurekurencyjnie(pHead->pnext);
	}
}

void dodajnakoniec(element*& pHead, T wartosc)
{
	if (!pHead) ///lista pusta
	{
		pHead = new element{ wartosc, nullptr };
	}
	else //juz cos jest
	{
		auto p = pHead;
		while (p->pnext)
			p = p->pnext;
		p->pnext = new element{ wartosc, nullptr };
	}
}

void usunodpoczatku(element *& pHead)
{
	while (pHead) // listaniepusta
	{
		element *p = pHead;
		pHead = pHead->pnext; //wskaznik pomocniczy
		delete p;
	}
}

void wypiszodpoczatku(element* pHead)
{
	while (pHead) // lista niepusta
	{
		//element*p = pHead; // wskaznik pomocniczy (niepotrzebbny)
		std::cout << pHead->wartosc << " ";
		pHead = pHead->pnext;
	}
}

void dodajnapoczatek(element*& pHead, T wartosc) // pusta lista
{
	//element*pNowy = new element{ wartosc, pHead };
	//element * pNowy = new element{ wartosc, nullptr };
		/*
	if (!pHead)
	{
		//element *pNowy = new element{ wartosc, 0 };
		//pHead = pNowy;
	}
	else //lista nie pusta
	{
		//element * pNowy = new element{ wartosc, nullptr };
		pNowy->pnext = pHead;
		//pHead = pNowy;
	}
	*/
	//pHead = pNowy;
	pHead = new element{ wartosc, pHead };
}

int main()
{
	element *pGlowa = 0;
	//dodajnapoczatek(pGlowa, 2);
	//dodajnapoczatek(pGlowa, 8);
	dodajnapoczatek(pGlowa, 15);
	dodajnakoniec(pGlowa, 3);
	dodajnakoniec(pGlowa, 8);
	dodajnakoniec(pGlowa, 16);
	wypiszodpoczatkurekurencyjnie(pGlowa);
	usunlisteodpoczatkurek(pGlowa);
	

	//wypiszodkoncareurencyjnie(pGlowa);
	//wypiszodpoczatku(pGlowa);
	//usunodpoczatku(pGlowa);
	//wypiszodpoczatku(pGlowa);
    return 0;
}

