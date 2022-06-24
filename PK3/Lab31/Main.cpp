// Lab 3-1 solution.cpp : Simple game - no function pointers
//

#include "stdafx.h"
#include "Dog.h"
#include "Rabbit.h"
#include "Mole.h"
#include "Playground.h"
#include "Console.h"

using namespace std;
#define WIDTH 80
#define HEIGHT 25


int main()
{
	// initialize random generator
	srand((unsigned int) time(0));

	// create console 
	Console console(WIDTH, HEIGHT);

	// create playground for animals
	Playground playground(console);

	// create animals
	Dog fafik("Fafik", 10, true, 0, 10);
	Dog puszek("Puszek", 10, false, 0, 20);
	Dog borek("Borek", 10, true, 0 , 30);

	//create rabbit
	Rabbit kroliczek("Rabbit_1");
	Rabbit kroliczek2("Rabbit_2");

	//crate mole
	Mole kret1("Mole_1");
	Mole kret2("Mole_2");

	//add mole to playground
	playground.AddMole(kret1);
	playground.AddMole(kret2);

	// add animals to playground
	playground.AddDog(fafik);
	playground.AddDog(puszek);
	playground.AddDog(borek);

	//add rabbits to playground
	playground.AddRabbit(kroliczek);
	playground.AddRabbit(kroliczek2);

	// simulation mail loop
	playground.Simulate();

	return 0;
}

