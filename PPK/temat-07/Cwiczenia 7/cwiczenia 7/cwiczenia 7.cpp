// Cwiczenia 7.cpp : Defines the entry point for the console application.
//
// Cwiczeniia 7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include <random>
#include <chrono>
#include <vector>
#include <iostream>

/*
std::vector<double> pobierz(const std::string&nazwa)
{
std::vector<double> liczby;
{
std::ifstream plik(nazwa);
if (plik)
{
double l;
while (plik >> l)
{
liczby.push_back(l);
}
plik.close();
}
return liczby;
}
}

void zapisanie(int ilosc,const std::string&nazwa)
{
std::ofstream plik(nazwa);

std::default_random_engine silnik;
std::uniform_real_distribution<double> rozklad(-2, 2);

auto czas = std::chrono::system_clock::now();
auto interwal = czas.time_since_epoch();

silnik.seed(interwal.count());

if (plik)
{
//plik << rozklad(silnik) << std::endl;
for (int i = 0; i < ilosc; i++)
{
plik << rozklad(silnik) << std::endl;
}
plik.close();
}
}

int main()
{
const int ilosc = 10;
std::string nazwa = "losowanie.txt";
zapisanie(ilosc, nazwa);
std::vector<double> liczba = pobierz(nazwa);
for (int i = 0; i < liczba.size(); i++)
{
std::cout << liczba[i] << std::endl;
}
getchar();
return 0;
}
*/


int main()
{
	std::fstream(plik);
	plik.open("pan-tadeusz.txt", std::ios::in);

	if (plik.good() == false)
	{
		std::cout << "Plik nie istnieje!";
	}

	std::string linia;

	while (std::getline(plik, linia))
	{
		std::cout << linia << std::endl;
	}
	plik.close();
	getchar();
	return 0;
}

