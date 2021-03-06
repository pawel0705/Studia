// zad 5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>

struct wektory
{
	double x, y, z, dlugosc;
};

wektory dl_wektora(const wektory&a, const wektory&b)
{
	wektory wynik;
	wynik.dlugosc = sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y) + (b.z - a.z)*(b.z - a.z));
	return wynik;
}

int main()
{
	wektory a{ 0, 0, 0 }, b{ 2, 0, 0 };
	wektory xyz = dl_wektora(a, b);
	std::cout << xyz.dlugosc << std::endl;
	getchar();
	return 0;
}