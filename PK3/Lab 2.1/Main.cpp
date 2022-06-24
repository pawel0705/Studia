// Lab 2-1.cpp : Konstruktor kopiujacy, referencje, operatory itp.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "Dog.h"
using namespace std;


int main()
{
	// create dogs
	Dog fafik("Fafik", 6, "Alabai", 10, 10, false);
	Dog reksio("Reksio", 8, "Anatilian/kangal", 10, 9, true);
	Dog puszek("Puszek", 2, "Tosa Inu", 8, 9, true);
	Dog berni("Berni", 4, "Caucasian ovcharka", 9, 9, true);
	Dog misiak("Misiak", 2, "Fila bresileiro", 8, 9, true);
	Dog borek("Borek", 4, "Boerboel", 8, 9, true);
	Dog hugo("Hugo", 5, "Black russian terrier", 9, 7, true);
	Dog raflik("Raflik", 2, "Moscow watchdog", 8, 9, true);
	Dog roti("Roti", 4, "Rottweiler", 6, 8, true);
	cout << "Dogs created" << endl << endl;

	// look and number of copy constructor calls
	//fafik = fafik.SimulateFightWith(roti); //zle
	Dog resultFafikVsRoti = fafik.SimulateFightWith(roti); //dobrze
	fafik.PrintInfo();
	roti.PrintInfo();
	resultFafikVsRoti.PrintInfo();
	cout << "End of simulaton 1" << endl << endl;

	// adding some images
	fafik.SetImage("Fafik img");
	roti.SetImage("Roti img");

	// look and number of copy constructor calls 
	// when copy requires more time
	resultFafikVsRoti = fafik.SimulateFightWith(roti);
	fafik.PrintInfo();
	roti.PrintInfo();
	resultFafikVsRoti.PrintInfo();
	cout << "End of simulaton 2" << endl << endl;

	// now the real fight 
	// but we use references
	fafik.FightWith(roti);
	fafik.PrintInfo();
	roti.PrintInfo();
	cout << "End of real fight" << endl << endl;

	// operatory ++
	//	++hugo;		// same as hugo.operator++()
	//	hugo++;		// same as hugo.operator++(1)
	// sprawdŸmy !!!
	cout << "Hugo age on ++hugo is " << (++hugo).GetAge() << endl;
	cout << "Huho age on hugo++ is " << (hugo++).GetAge() << endl;

	Dog bobik = hugo + fafik;
	bobik.SetName("Bobik");

	return 0;
}

