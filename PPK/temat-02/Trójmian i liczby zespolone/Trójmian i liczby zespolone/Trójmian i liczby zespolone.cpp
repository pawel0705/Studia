// Trójmian i liczby zespolone.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>


using namespace std;

int main()
{
	double a, b, c, delta, x1, x2, z1, z2;

	cout << "Program obliczy trojmian kwadratowy ax^2+bx+c=0" << endl;
	cout << "Wprowadz kolejno parametry a, b i c." << endl;
	cin >> a >> b >> c;

	if (a != 0)
	{
		delta = b * b - 4 * a * c;
		if (delta < 0)
		{
			z1 = delta - delta - delta;
			z2 = sqrt(z1);
			cout << "x1=" << -b / (2 * a) << "+" << z2 / (2 * a) << "i" << endl;
			cout << "x2=" << -b / (2 * a) << "-" << z2 / (2 * a) << "i" << endl;
		}
		if (delta == 0)
		{
		    x1 = -b / (2 * a);
		    cout << "x=" << x1 << endl;
	    }
		if (delta > 0)
		{
			x1 = (-b - sqrt(delta)) / (2 * a);
			x2 = (-b - sqrt(delta)) / (2 * a);
			cout << "x1=" << x1 << endl;
			cout << "x2=" << x2 << endl;
		}
	}
	else
		cout << "Zly parametr a." << endl;
    return 0;
}

