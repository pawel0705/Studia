// struktury zad 3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

struct wektory
{
	double x, y, z, iloczyn;
};

wektory iloczyn_skalarny(const wektory&a, const wektory&b)
{
	wektory wynik;
	wynik.x = a.x * b.x;
	wynik.y = a.y * b.y;
	wynik.z = a.z * b.z;
	wynik.iloczyn = wynik.x + wynik.y + wynik.z;

	
	return wynik;
}

int main()
{
	wektory a{ 2, 1, 1 }, b{ 1, 6, 3 };
	wektory xyz = iloczyn_skalarny(a, b);
	std::cout << xyz.iloczyn << std::endl;
	getchar();
	return 0;
}
