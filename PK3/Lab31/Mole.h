#pragma once
#include "Animal.h"
#include "Console.h"
#include <string>

class Mole : public Animal
{
private:
	typedef void(Mole::*ActionFunction)(Console&);
	struct Action
	{
		int probability;
		std::string actionText;
		int frameNumber;
		ActionFunction actionFunction;
	};
	const Action actionInfo[5] = {
		{ 01, "thinking",   1, &Mole::ActionThinking },
		{ 60, "digging_under_map",  200, &Mole::ActionDiggingUnderMap },
		{ 20, "fixing",  100, &Mole::ActionSpecial },
		{ 19, "moving", 100, &Mole::ActionMoving },
	};
	ActionFunction currentActionFunction = &Mole::ActionThinking;
	int actionActualFrame = 0;
	int actionLastFrame = 1;

public:
	// konstruktory
	Mole();
	Mole(const Mole &Mole);
	Mole(Mole &&Mole);
	Mole(std::string name);
	Mole(std::string name, int age, bool isMale, WORD color);
	~Mole();

	// Operatory
	Mole& operator= (const Mole &mole);
	Mole& operator= (Mole &&mole);

	// Mole virtual actions
	virtual std::string DoGetInfo();

	// Action implementation
	Action ActionInfo(int);
	void DoAction(Console &console);
	void ActionThinking(Console &console);
	void ActionMoving(Console &console);
	void ActionSpecial(Console &console);
	void ActionDiggingUnderMap(Console &console);
};

