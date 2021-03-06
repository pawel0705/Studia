// zad 6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

struct wspol
{
	double x, y, z;
};

void wypisz_punkty(const std::vector<wspol>&punkt)
{
	for (wspol w : punkt)
	{
		std::cout << w.x << std::setw(20) << w.y << std::setw(20) << w.z << std::endl;
	}
}

std::vector<wspol> punkty(int N)
{
	std::default_random_engine silnik;
	std::uniform_real_distribution<double> rozklad(-2, 2);

	auto czas = std::chrono::system_clock::now();
	auto interwal = czas.time_since_epoch();
	silnik.seed(interwal.count());


	std::vector<wspol> punkty;
	for (int i = 0; i < N; i++)
	{
		wspol punkt;
		punkt.x = rozklad(silnik);
		punkt.y = rozklad(silnik);
		punkt.z = rozklad(silnik);

		punkty.push_back(punkt);
	}
	return punkty;
}


int main()
{
	const int N = 10;
	punkty(N);
	wypisz_punkty(punkty(N));
	getchar();
		return 0;
}