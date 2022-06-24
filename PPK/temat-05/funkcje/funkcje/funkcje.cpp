// funkcje.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

/*
double funkcja(double liczba, int potega)
{
	double obliczenie = 1;

	if (potega > 0)
	{
		for (int i = 0; i < potega; i++)
			obliczenie *= liczba;
	}
	else
	{
		for (int i = 0; i < -potega; i++)
			obliczenie *= liczba;
		obliczenie = (1 / obliczenie);
	}
	return obliczenie;
}

int main()
{
	double liczba = 2;
	double potega = -10;
	std::cout << funkcja(liczba, potega);

	return 0;
}

*/


void wypeln(double tab[], int N)
{
	return;
}

int main()

{

	const int N = 10;

	double tab[N];



	std::default_random_engine silnik;

	std::uniform_real_distribution<double> rozklad(-1, 1);



	auto czas = std::chrono::system_clock::now();

	auto interwal = czas.time_since_epoch();

	silnik.seed(interwal.count());





	for (int i = 0; i < N; i++)

	{

		tab[i] = rozklad(silnik);

		std::cout << tab[i] << std::endl;

	}

	double pomoc;



	for (int i = 0; i < N; i++)

	{

		int minimum2 = i;

		for (int j = i + 1; j < N; j++) 

		{

			if (tab[j] < tab[minimum2])

				minimum2 = j;

		}

		

		pomoc = tab[minimum2];

		tab[minimum2] = tab[i];

		tab[i] = pomoc;

	}



	for (int i = 0; i < N; i++)

		std::cout << "tablica[" << i << "] = " << tab[i] << std::endl;

	return 0;

}