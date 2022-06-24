// struktury zad 2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

struct wektory
{
	double x, y, z;
};

wektory odejmij(const wektory&a, const wektory&b)
{
	wektory wynik;
	wynik.x = a.x - b.x;
	wynik.y = a.y - b.y;
	wynik.z = a.z - b.z;
	return wynik;
}

int main()
{
	wektory a{ 1, 1, 1 }, b{ 1, 1, 1 };
	wektory xyz = odejmij(a, b);
	std::cout << xyz.x << xyz.y << xyz.z << std::endl;
	getchar();
    return 0;
}

