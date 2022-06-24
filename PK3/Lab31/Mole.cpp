#include "stdafx.h"
#include "Mole.h"

using namespace std;

#pragma region Constructors
Mole::Mole() : Mole("Anonymous", 0, true, 0)
{}

Mole::Mole(string name) : Mole(name, 0, true, 0)
{}

Mole::Mole(std::string name, int age, bool isMale, WORD color) : Animal(name, age, isMale, color)
{}

Mole::Mole(const Mole &mole) : Animal(mole)
{}

Mole::Mole(Mole &&mole) : Animal(move(mole))
{}

Mole::~Mole()
{}
#pragma endregion

#pragma region Operators
Mole& Mole::operator= (const Mole& mole)
{
	Animal::operator= (mole);
	return *this;
}

Mole& Mole::operator= (Mole&& mole)
{
	Animal::operator= (std::move(mole));
	return *this;
}
#pragma endregion


#pragma region Virtual functions
Mole::Action Mole::ActionInfo(int index)
{
	return actionInfo[index];
}

string Mole::DoGetInfo()
{
	return "Mole " + Animal::DoGetInfo();
}
#pragma endregion


#pragma region Metods: actions

void Mole::DoAction(Console &console)
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

void Mole::ActionThinking(Console &console)
{
	dx = -0.3f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	dy = -0.3f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void Mole::ActionDiggingUnderMap(Console &console)
{
	if (x + dx < 0 || x + dx > console.GetWidth())
		dx = -dx;

	if (y + dy < 0 || y + dy > console.GetHeight())
		dy = -dy;

	if (actionActualFrame < 5)
	{
		color = 0x0000;
		x += dx;
		y += dy;
	}
	else if (actionActualFrame > 5 && actionActualFrame < 95) //digging underground
	{
		color = FOREGROUND_GREEN;
		x += dx;
		y += dy;
	}
	else
	{
		color = 0x0000;
		x += dx;
		y += dy;
	}
	
}

void Mole::ActionSpecial(Console &console)
{
	if (actionActualFrame == 20) console.DrawRectangleOnBackground((short)x, (short)y, 1, 1, BACKGROUND_GREEN | BACKGROUND_GREEN);
	if (actionActualFrame == 50) console.DrawRectangleOnBackground((short)x - 1, (short)y, 3, 3, BACKGROUND_GREEN | BACKGROUND_GREEN);
}

void Mole::ActionMoving(Console &console)
{
	if (x + dx < 0 || x + dx > console.GetWidth())
		dx = -dx;

	if (y + dy < 0 || y + dy > console.GetHeight())
		dy = -dy;

	x += dx;
	y += dy;
}

#pragma endregion
