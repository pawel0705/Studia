// liczby pseudolosowe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <random>
#include <iostream>
#include <chrono>
#include <functional>



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

	double minimum = tab[0];

	for (int i = 0; i < N; i++)
	{
		if (minimum > tab[i])
			minimum = tab[i];
	}
	std::cout << std::endl;
	std::cout << minimum << std::endl;
	std::cout << std::endl;
	//SZYBKIE SORTOWANIE
	//tablica posortowana od min do max
	std::sort(tab, tab + N);
	for (int i = 0; i < N; i++)
		std::cout << tab[i] << std::endl;

	std::cout << std::endl;

	//tablica posortowana od max do min
	std::sort(tab, tab + N, std::greater<double>());
	for (int i = 0; i < N; i++)
		std::cout << tab[i] << std::endl;

	std::cout << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << std::endl;
	//SORTOWANIE POPRZEZ WYBIERANIE
	double pomoc;

	for (int i = 0; i < N; i++) // zaczynamy od pierwszego elementu i konczymy na ostatnim
	{
		int minimum2 = i; // indeks najmniejszego znalezionego elementu
		for (int j = i + 1; j < N; j++) // poszukujemy najmniejszego elementu poczawszy od i
		{
			if (tab[j] < tab[minimum2]) // jezeli znalezlismy mniejszy element zapisujemy jego indeks w minimum2
				minimum2 = j;
		}
		// wstawiamy najmniejszy element na odpowiednie miejsce
		pomoc = tab[minimum2];
		tab[minimum2] = tab[i];
		tab[i] = pomoc;
	}

	for (int i = 0; i < N; i++) // wypisanie posortowanej tablicy
		std::cout << "tablica[" << i << "] = " << tab[i] << std::endl;
    return 0;
}

