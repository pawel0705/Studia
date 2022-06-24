#include "stdafx.h"
#include "Cat.h"

using namespace std;

#pragma region Constructors
Cat::Cat() : Cat("Anonymous", 0, true, 0)
{}

Cat::Cat(string name) : Cat(name, 0, true, 0)
{}

Cat::Cat(std::string name, int age, bool isMale, WORD color) : Animal(name, age, isMale, color)
{}

Cat::Cat(const Cat &cat) : Animal(cat)
{}

Cat::Cat(Cat &&cat) : Animal(move(cat))
{}

Cat::~Cat()
{}
#pragma endregion

#pragma region Operators
Cat& Cat::operator= (const Cat& cat)
{
	Animal::operator= (cat);
	return *this;
}

Cat& Cat::operator= (Cat&& cat)
{
	Animal::operator= (std::move(cat));
	return *this;
}
#pragma endregion


#pragma region Virtual functions
Animal::Action Cat::ActionInfo(int index)
{
	return actionInfo[index];
}

string Cat::DoGetInfo()
{
	return "Cat " + Animal::DoGetInfo();
}
#pragma endregion


#pragma region Metods: actions
void Cat::ActionThinking(Console &console)
{
	dx = -0.5f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	dy = -0.5f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void Cat::ActionMoving(Console &console)
{
	if (x + dx < 0 || x + dx > console.GetWidth())
		dx = -dx;

	if (y + dy < 0 || y + dy > console.GetHeight())
		dy = -dy;

	x += dx;
	y += dy;
}

void Cat::ActionSpecial(Console &console)
{
	if (actionActualFrame == 20) console.DrawRectangleOnBackground((short)x, (short)y, 1, 1, BACKGROUND_RED | BACKGROUND_GREEN);
	if (actionActualFrame == 80) console.DrawRectangleOnBackground((short)x - 1, (short)y - 1, 3, 3, BACKGROUND_RED | BACKGROUND_GREEN);
}

void Cat::ActionSleeping(Console &console)
{
	if (actionActualFrame % 20 == 0) actionText = actionText + "..hrr";

}

void Cat::SeeOtherAimal(const Animal& animal, float width, float height) //if see other animal run away
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
