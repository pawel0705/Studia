// struktury zad 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


struct wspol
{
	double x, y, z;
};

wspol dodaj(const wspol&a, const wspol&b)
{
	wspol wynik;
	wynik.x = a.x + b.x;
	wynik.y = a.y + b.y;
	wynik.z = a.z + b.z;
	return wynik;
}

int main()
{
	//wspol a{ 1, 2, 3 }, b{ 1, 2, 3 };
	wspol a;
	a.x = 1;
	a.z = 2;
	a.y = 3;

	wspol b;
	b.x = 1;
	b.y = 2;
	b.z = 3;

	wspol xyz = dodaj(a, b);
	std::cout << xyz.x << xyz.y << xyz.z << std::endl;
	getchar();
    return 0;
}

