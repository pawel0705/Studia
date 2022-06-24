// cwiczenia9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

/*
bool szachownica(const std::string& nazwa)
{
	const int N = 8;
	int tab[N][N];
	std::fstream plik;
	std::stringstream ss;
	std::string linia;
	if (plik.good())
	{
		getline(plik, linia);

	}
	plik.close();
}

int main()
{
	std::string nazwa = "szachownica.txt";
	if (szachownica(nazwa))
		std::cout << "Trasa poprawna";
	else
		std::cout << "Trasa niepoprawna";
		
    return 0;
}
*/


bool sudoku(const std::string& nazwa)
{
	const int N = 9;
	char tablica[N][N];
	std::stringstream s;
	std::ifstream plik(nazwa);
	if (plik.good())
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				plik >> tablica[i][j];
		}
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				if (tablica[i][j]==
		}
	}
	plik.close();
}

int main()
{
	std::string nazwa = "sudoku";
	sudoku(nazwa);
	if (sudoku(nazwa))
		std::cout << "Sudoku jest poprawne." << std::endl;
	else
		std::cout << "Trasa niepoprawna." << std::endl;

	return 0;
}

