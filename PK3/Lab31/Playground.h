#pragma once
#include "Dog.h"
#include "Rabbit.h"
#include "Mole.h"
#include "Console.h"


#define MAXDOGS 15
#define MAXRABBITS 15
#define MAXMOLES 15
class Playground
{
private:
	// Array of dogs 
	int noOfDogs = 0;
	Dog *dogs[MAXDOGS];
	// Add array of cats and rabbits

	// Array of Rabbits
	int noOfRabbits = 0;
	Rabbit *rabbits[MAXRABBITS];

	// Array of Moles
	int noOfMoles = 0;
	Mole *moles[MAXMOLES];

	// Technical object grouping console operations
	Console &console;

	float x1=0, x2=0, y1=0, y2=0;

public:
	// Constructors
	Playground(Console &console);
	~Playground();

	void AddDog(Dog &dog);

	void AddRabbit(Rabbit &rabbit); //add Rabbit
	void AddMole(Mole &mole); //add Mole

	void AnimalsCOllision(); //dogs collision

	void AnimalsDoDraw();
	void AnimalsDoAction();
	void Simulate();
};

