#include "stdafx.h"
#include "Dog.h"

using namespace std;

#pragma region Constructors
Dog::Dog(): Dog( "Anonymous", 0, true, 0)
{}

Dog::Dog(string name) : Dog( name, 0, true, 0)
{}

Dog::Dog(std::string name, int age, bool isMale, WORD color): Animal(name, age, isMale, color)
{}

Dog::Dog(const Dog &dog) : Animal(dog)
{}

Dog::Dog(Dog &&dog) : Animal(move(dog))
{}

Dog::Dog(std::string name, int age, bool isMale, WORD color, int power) : power(power), Animal(name, age, isMale, color)
{}

/*
Dog::Dog(const Dog &dog) : power(dog.power), Animal(dog.name, dog.age, dog.isMale, dog.color) 
{
}
*/

Dog::~Dog()
{}
#pragma endregion

#pragma region Operators
Dog& Dog::operator= (const Dog& dog)
{
	Animal::operator= (dog);
	return *this;
}

Dog& Dog::operator= (Dog&& dog)
{
	Animal::operator= (std::move(dog));
	return *this; 
}

Dog Dog::operator+(const Dog &dog)
{
	Animal::operator+ (dog);
	return *this;
}
#pragma endregion


#pragma region Virtual functions
Dog::Action Dog::ActionInfo(int index)
{
	return actionInfo[index];
}

string Dog::DoGetInfo()
{
	return "Dog " + Animal::DoGetInfo();
}
#pragma endregion


#pragma region Metods: actions

void Dog::DoAction(Console &console)
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
	/* this is conceptually the same as
	...
	switch (action_number) {
	    case 1:  ActionThinking(console); break;
		case 2:  ActionMoving(console); break;
		case 3:  ActionSpecial(console); break;
	}
	*/

	actionActualFrame++;
}

void Dog::ActionThinking(Console &console)
{
	dx = -0.5f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	dy = -0.5f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void Dog::ActionMoving(Console &console)
{


	if (x + dx < 0 || x + dx > console.GetWidth())
		dx = -dx;

	if (y + dy < 0 || y + dy > console.GetHeight())
		dy = -dy;

	x += dx;
	y += dy;

}

void Dog::ActionSpecial(Console &console)
{
	if (actionActualFrame == 20) console.DrawRectangleOnBackground((short) x, (short) y, 1, 1, BACKGROUND_RED | BACKGROUND_GREEN);
	if (actionActualFrame == 80) console.DrawRectangleOnBackground((short) x - 1, (short) y - 1, 3, 3, BACKGROUND_RED | BACKGROUND_GREEN);
}

void Dog::ActionSleeping(Console &console)
{
	if (actionActualFrame % 20 == 0 ) actionText = actionText + "..hrr";
}

bool Dog::GetIsAlive()
{
	return this->isAlive;
}

void Dog::SetIsAlive(bool isAlive)
{
	this->isAlive = isAlive;
}

int Dog::GetPower()
{
	return power;
}

bool Dog::GetHaveChild()
{
	return this->have_child;
}

void Dog::SetPower(int power)
{
	if (power > 0)
		this->power = power;
	else
		this->power = 0;
}

void Dog::SetHaveChild(bool have_child)
{
	this->have_child = have_child;
}

void Dog::FightWith(Dog & dog)
{
	int dogPower = power;
	SetPower(power - dog.GetPower());
	dog.SetPower(dog.GetPower() - dogPower);
}


#pragma endregion
