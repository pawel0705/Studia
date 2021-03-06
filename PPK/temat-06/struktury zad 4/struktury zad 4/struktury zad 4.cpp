// struktury zad 4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

struct wektory
{
	double x, y, z, wektorowe1, wektorowe2, wektorowe3;
};

wektory iloczyn_skalarny(const wektory&a, const wektory&b)
{
	wektory wynik;
	wynik.x = a.x * b.x;
	wynik.y = a.y * b.y;
	wynik.z = a.z * b.z;
	wynik.wektorowe1 = a.y * b.z - a.z * b.y;
	wynik.wektorowe2 = a.z * b.x - a.x * b.z;
	wynik.wektorowe3 = a.x * b.y - a.y * b.x;


	return wynik;
}

int main()
{
	wektory a{ 2, 1, 1 }, b{ 1, 6, 3 };
	wektory xyz = iloczyn_skalarny(a, b);
	std::cout << xyz.wektorowe1 << " " << xyz.wektorowe2 << " " << xyz.wektorowe3 << std::endl;
	getchar();
	return 0;
}