// funkcja rozw ukl 2 row.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

double rozwiaz(double a11, double a12, double a21, double a22, double b1, double b2, double &x1, double &x2)
{
	if (a22*a11 - a12*a21 == 0 || a22*a11 - a12*a21 == 0)
		return 1;
	if (((b2 - a21*b1) / (-a12*a21 + a22*a11)) == ((b1 - a11*b2) / (-a22*a11 + a12*a21)))
		return -1;
	else
	{
		x1 = ((b2 - a21*b1) / (-a12*a21 + a22*a11));
		x2 = ((b1 - a11*b2) / (-a22*a11 + a12*a21));
		return 1;
	}
}

int main()
{
	double  a11, a12, a21, a22, b1, b2, x1, x2;
	std::cout << "Funkcja rozwiaze uklad rownan. Podaj kolejno parametry a11, a12, a21, a22, b1, b2" << std::endl;
	std::cin >> a11>>a12>>a21>> a22>> b1 >>b2;
	std::cout << "Wynik: " << rozwiaz(a11, a12, a21, a22, b1, b2, x1, x2) << std::endl;
	if (rozwiaz(a11, a12, a21, a22, b1, b2, x1, x2) == 1)
		std::cout << x1 << std::endl << x2;
    return 0;
}

