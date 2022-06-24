#include "stdafx.h"
#include "Rabbit.h"

using namespace std;

#pragma region Constructors
Rabbit::Rabbit() : Rabbit("Anonymous", 0, true, 0)
{}

Rabbit::Rabbit(string name) : Rabbit(name, 0, true, 0)
{}

Rabbit::Rabbit(std::string name, int age, bool isMale, WORD color) : Animal(name, age, isMale, color)
{}

Rabbit::Rabbit(const Rabbit &rabbit) : Animal(rabbit)
{}

Rabbit::Rabbit(Rabbit &&rabbit) : Animal(move(rabbit))
{}

Rabbit::~Rabbit()
{}
#pragma endregion

#pragma region Operators
Rabbit& Rabbit::operator= (const Rabbit& rabbit)
{
	Animal::operator= (rabbit);
	return *this;
}

Rabbit& Rabbit::operator= (Rabbit&& rabbit)
{
	Animal::operator= (std::move(rabbit));
	return *this;
}
#pragma endregion


#pragma region Virtual functions
Rabbit::Action Rabbit::ActionInfo(int index)
{
	return actionInfo[index];
}

string Rabbit::DoGetInfo()
{
	return "Dog " + Animal::DoGetInfo();
}
#pragma endregion


#pragma region Metods: actions

void Rabbit::DoAction(Console &console)
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

void Rabbit::ActionThinking(Console &console)
{
	dx = -1.5f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	dy = -1.5f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void Rabbit::ActionMoving(Console &console)
{

	if (x + dx < 0 || x + dx > console.GetWidth())
		dx = -dx;

	if (y + dy < 0 || y + dy > console.GetHeight())
		dy = -dy;

	if ((actionActualFrame > 95 && actionActualFrame < 100) || (actionActualFrame > 30 && actionActualFrame < 35)) //jump 2 times in one action
	{
		x += dx;
		y += dy;
	}
}

void Rabbit::ActionSpecial(Console &console)
{
	if (actionActualFrame == 80) console.DrawRectangleOnBackground((short)x, (short)y, 1, 0,  0x000000);
}

void Rabbit::ActionDontMove(Console &console)
{
	if (actionActualFrame % 50 == 0) actionText = actionText + "...";
}

#pragma endregion
