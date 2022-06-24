// Temat 4 cwiczenia.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <random>
#include <chrono>



int main()
{

	auto czas = std::chrono::system_clock::now();
	auto interwal = czas.time_since_epoch();
	std::default_random_engine silnik;
	std::uniform_real_distribution<double> rozklad(-1, 1);
	silnik.seed(interwal.count());

	const int N = 10;
	double tab[N];

	for (int i = 0; i <= N; i++)
		tab[i] = rozklad(silnik);
	for (int i = 0; i <= N; i++)
		std::cout << tab[i] << std::endl;

	double minimum = tab[0];
	for (int i = 1; i < N; i++)
	{
		if (minimum > tab[i])
			minimum = tab[i];
	}
	    std::cout << std::endl;
		std::cout << minimum;

		
return 0;
}

