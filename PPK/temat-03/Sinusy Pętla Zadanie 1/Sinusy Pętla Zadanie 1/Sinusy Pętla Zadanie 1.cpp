// Sinusy Pętla Zadanie 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
	for (int i = 0; i <= 360; i = i + 5)
	{
		if (i==180 || i==360)
		cout << setw(0) << "Kat " << i << "sinus " << setw(1) << "0" << endl;
		else
		cout << setw(0) << "Kat " << i << "sinus " << setw(1) << sin(i*(acos(-1)) / 180) << endl;
	}
    return 0;
}

