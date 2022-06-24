#include "stdafx.h"
#include "Animal.h"
#include <cmath>

using namespace std;

#pragma region Constructors
Animal::Animal(): Animal("Noname animal", 0, true, 0)
{}

Animal::Animal(std::string name, int age, bool isMale, WORD color): name(name), age(age), isMale(isMale), color(color)
{
	x = static_cast <float> (5 + rand() % 70);
	y = static_cast <float> (5 + rand() % 15);
}

Animal::Animal(const Animal &animal) 
{
	color = animal.color;
	x = animal.x;
	y = animal.y;

	if (animal.imageData)		
	{
		imageData = new char[strlen(animal.imageData) + 1];
		memcpy(imageData, animal.imageData, strlen(animal.imageData) + 1);
	}
}

Animal::Animal(Animal &&animal): name(animal.name), age(animal.age), isMale(animal.isMale), imageData(animal.imageData)
{
	color = animal.color;
	x = animal.x;
	y = animal.y;

	animal.imageData = nullptr;
}

Animal::~Animal()
{
	if (imageData)
		delete[] imageData;
}
#pragma endregion

#pragma region Accessors
// Akcesory - setters
void Animal::SetName(std::string name)
{
	this->name = name;
}

void Animal::SetAge(int age)
{
	this->age = age;
}

void Animal::SetImage(char *imageData)
{
	if (this->imageData) // != nullptr
		delete[] imageData;

	if (imageData)
	{
		imageData = new char[strlen(imageData) + 1];
		memcpy(this->imageData, imageData, strlen(imageData) + 1);
	}
}

// Akcesory - getters
std::string Animal::GetName() const
{
	return name.empty() ? "Anonymous" : name;
}

int Animal::GetAge() const
{
	return age;
}

char* Animal::GetImage() const
{
	return imageData;
}

WORD Animal::GetColor() const
{
	return color;
}

#pragma endregion

#pragma region Operators
Animal& Animal::operator= (const Animal& animal)
{
	x = animal.x;
	y = animal.y;
	name = animal.name;
	age = animal.age;
	isMale = animal.isMale;

	if (imageData)
	{
		delete[] imageData;
		imageData = nullptr;
	}

	if (animal.imageData)
	{
		imageData = new char[strlen(animal.imageData) + 1];
		memcpy(imageData, animal.imageData, strlen(animal.imageData) + 1);
	}


	return *this;
}

Animal& Animal::operator= (Animal&& animal)
{
	x = animal.x;
	y = animal.y;
	name = animal.name;
	age = animal.age;
	isMale = animal.isMale;

	if (imageData)
		delete[] imageData;

	imageData = animal.imageData;
	animal.imageData = nullptr;


	return *this;
}
#pragma endregion

#pragma region  Class methods
string Animal::DoGetInfo()
{
	return GetName() + " [" + actionText + "]";
}

void Animal::DoDraw(Console &console)
{
	console.DrawTextOnPlayground((short) x, (short) y, DoGetInfo(), GetColor());
}

void Animal::DoAction(Console &console)
{
	if (actionActualFrame == actionLastFrame)
	{
		Action action = ActionInfo(0);
		int random_number = rand() % 100;
		int newFunctionIndex = 0;
		int sum = action.probability;

		while (random_number > sum)
		{
			action = ActionInfo(++newFunctionIndex);
			sum += action.probability;
		}

		currentActionFunction = action.actionFunction;
		actionLastFrame = action.frameNumber;
		actionText = action.actionText;
		actionActualFrame = 0;
	}

	(this->*currentActionFunction)(console);
	actionActualFrame++;
}

#pragma endregion  
