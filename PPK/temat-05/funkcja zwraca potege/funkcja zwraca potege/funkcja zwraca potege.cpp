// funkcja zwraca potege.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

double funkcja(double licz, double pot)
{
	double obliczenie = 1;
	if (pot>0)
	for (int i = 0; i < pot; i++)
		obliczenie *= licz;
	else
		for (int i=0; i< -pot; i++)
			obliczenie *= licz;
	obliczenie = (1 / obliczenie);
	return obliczenie;
}

int main()
{
	double liczba, potega;
	std::cin >> liczba >> potega;
	std::cout<< funkcja(liczba, potega);

    return 0;
}

