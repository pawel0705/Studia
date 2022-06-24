#include "stdafx.h"
#include "AnimalSprite.h"
#include <cmath>

using namespace std;

#pragma region Constructors
AnimalSprite::AnimalSprite() : Animal("Noname animal", 0, true), Sprite(0)
{}

AnimalSprite::AnimalSprite(std::string name, int age, bool isMale, WORD color) : Animal(name, age, isMale), Sprite(color)//color(color)
{}

AnimalSprite::AnimalSprite(const AnimalSprite &animal)
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

AnimalSprite::AnimalSprite(AnimalSprite &&animal) : Animal(animal.name,animal.age, animal.isMale)
{
	this->imageData = animal.imageData;

	color = animal.color;
	x = animal.x;
	y = animal.y;

	animal.imageData = nullptr;
}

AnimalSprite::~AnimalSprite()
{}
#pragma endregion

#pragma region Operators
AnimalSprite& AnimalSprite::operator= (const AnimalSprite& animal)
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

AnimalSprite& AnimalSprite::operator= (AnimalSprite&& animal)
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
void AnimalSprite::DoDraw(Console &console)
{
	console.DrawTextOnPlayground((short)x, (short)y, DoGetInfo(), GetColor());
}

void AnimalSprite::DoAction(Console &console)
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