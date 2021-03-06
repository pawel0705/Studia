// zajecia 8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <chrono>
#include <random>
#include <iostream>

void wypelnij(double *tablica, int N)
{
	std::default_random_engine silnik;
	std::uniform_real_distribution<double> rozklad(-2, 2);

	auto czas = std::chrono::system_clock::now();
	auto interwal = czas.time_since_epoch();

	silnik.seed(interwal.count());

	for (int i = 0; i < N; i++)
	{
		*(tablica + i) = rozklad(silnik);
		std::cout << *(tablica + i) << std::endl;
	}
}

double sumuj(double *tablica, int N)
{
	double pomocnicza = 0;
	for (int i = 0; i < N; i++)
	{
		pomocnicza += *(tablica + i);
	}
	return pomocnicza;
}

double zsumuj(double *tablica, int N)
{
	if (N == 1)
		return *tablica;
	return *tablica + zsumuj(tablica + 1, N - 1);
}

double f1(double x) { return -x*x - x + 10; }
double calkowanie()
{
	double xp, xk, h, calka;
	int N;
	xp = -2;
	xk = 1;
	N = 3;
	h = (xk - xp) / (double)N;
	calka = 0;
	for (int i = 0; i < N; i++)
	{
		calka += f1(xp + i*h)*h;
	}
	return calka;
}

int main()
{
	const int N = 1000;
	double tab[N];
	wypelnij(tab, N);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << sumuj(tab, N) << std::endl;
	std::cout << std::endl;
	//rekurencyjnie
	std::cout << zsumuj(tab, N) << std::endl;
	std::cout << std::endl;
	std::cout << calkowanie();

	getchar();
	return 0;
}


