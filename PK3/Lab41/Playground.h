#pragma once
#include "Animal.h"
#include "Console.h"


#define MAXANIMALS 15
class Playground
{
private:
	// Object containers
	int noOfAnimals = 0;
	// array of references are illegal
	Animal *animals[MAXANIMALS];
	// Technical object grouping console operations
	Console &console;

public:
	// Constructors
	Playground(Console &console);
	~Playground();

	void Collision();
	void AddAnimal(Animal &animal);
	void AnimalsDoDraw();
	void AnimalsDoAction();
	void Simulate();
};

