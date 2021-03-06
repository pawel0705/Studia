// funkcjia pseudolosowe wartosci tablica.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <random>
#include <chrono>
#include <iostream>

void posortuj(double tab[], int N)
{
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
}

void wypeln(double tab[], int N)
{
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

	posortuj(tab, N);
	}

int main()
{
	const int N = 10;
	double tab[N];
	wypeln(tab, N);
    return 0;
}

