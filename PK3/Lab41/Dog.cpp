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
#pragma endregion


#pragma region Virtual functions
Animal::Action Dog::ActionInfo(int index)
{
	return actionInfo[index];
}

string Dog::DoGetInfo()
{
	return "Dog " + Animal::DoGetInfo();
}
#pragma endregion


#pragma region Metods: actions
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

void Dog::SeeOtherAimal(const Animal& animal, float width, float height) // if see other animal run away
{

	if (x + dx < 0 || x + dx > width)
	{
		dx = -dx;
		x += dx;
		return;
	}
	else if (y + dy < 0 || y + dy > height)
	{
		dy = -dy;
		y += dy;
		return;
	}
	else
	{

		if (dx < 0)
			dx = abs(dx);

		if (dy < 0)
			dy = abs(dy);

		if (x > animal.x && y < animal.y)
		{
			x = x + dx;
			y = y - dy;
		}
		else if (x < animal.x && y < animal.y)
		{
			x = x - dx;
			y = y - dy;
		}
		else if (x > animal.x && y > animal.y)
		{
			y = y + dx;
			x = x + dx;
		}
		else
		{
			y = y + dy;
			x = x - dx;
		}
	}
}

#pragma endregion
