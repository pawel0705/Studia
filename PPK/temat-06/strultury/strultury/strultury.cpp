// strultury.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cmath>
#include <iostream>

/*
struct wspol
{
	double x, y, z;
};


wspol dodaj(const wspol&a, const wspol&b);

int main()
{
	wspol a{ 2, 1, 1 }, b{ 2, 1, 1 };
	wspol c = dodaj(a, b);
	std::cout << c.x << c.y << c.z << std::endl;
	system("pause");
}

wspol dodaj(const wspol&a, const wspol&b)
{
	wspol wynik;
	wynik.x = a.x + a.x;
	wynik.y = a.y + b.y;
	wynik.z = a.z + a.z;

	return wynik;
}
*/

struct wspol
{
	double x, y, z;
};

wspol odejmij(const wspol&a, const wspol&b);

int main()
{
	wspol a{ 1, 1, 1 }, b{ 1, 1, 1 };
	wspol c = odejmij(a, b);
	std::cout << c.x << c.y << c / z << std::endl;
}

wspol odejmij(const wspol&a, const wspol&b)
{
	wspol wynik;
	wynik.x
}
