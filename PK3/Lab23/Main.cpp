// Lab 2-3.cpp : References as member variable
//

#include "stdafx.h"
#include "Dog.h"
using namespace std;

int main()
{
	// create breeds
	Breed alabai("Alabai", 10, 10, 65, 55);
	Breed anatolian("Anatilian/kangal", 10, 9, 75, 55);
	Breed tosa("Tosa Inu", 8, 9, 75, 55);
	Breed caucasian("Caucasian ovcharka", 9, 9, 65, 50);
	Breed fila("Fila bresileiro", 8, 9, 70, 50);
	Breed boerboel("Boerboel", 10, 7, 70, 60);
	Breed blackie("Black russian terrier", 9, 7, 60, 50);
	Breed watchdog("Moscow watchdog", 8, 9, 65, 55);
	Breed rottweiler("Rottweiler", 6, 8, 50, 40);
	Breed newfoundland("Newfoundland", 10, 2, 72, 60);
	cout << "Breeds created" << endl << endl;

	// create dogs
	Dog fafik("Fafik", 6, true, alabai);
	Dog reksio("Reksio", 8, true, anatolian);
	Dog puszek("Puszek", 2, true, tosa);
	Dog berni("Berni", 4, true, caucasian);
	Dog misiak("Misiak", 2, true, tosa);
	Dog borek("Borek", 4, true, boerboel);
	Dog hugo("Hugo", 5, true, blackie);
	Dog raflik("Raflik", 2, true, watchdog);
	Dog roti("Roti", 4, true, rottweiler);
	cout << "Dogs created" << endl << endl;

	// and what about mongrel
	Dog szarik("Szarik");
	szarik.PrintInfo();


	// look and number of copy constructor calls 
	Dog resultFafikVsRoti = fafik.SimulateFightWith(roti);
	fafik.PrintInfo();
	roti.PrintInfo();
	resultFafikVsRoti.PrintInfo();
	cout << "End of simulaton" << endl << endl;  
	
	// now the real fight
	// but we use references
	fafik.FightWith(roti);
	fafik.PrintInfo();
	roti.PrintInfo();
	cout << "End of real fight" << endl << endl;
	

	// adding some images
	fafik.SetImage("Fafik img");
	roti.SetImage("Roti img");

	return 0;
}
