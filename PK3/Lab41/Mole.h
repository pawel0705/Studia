#pragma once
#include "Animal.h"
#include "Console.h"
#include <string>

class Mole : public Animal
{
private:
	const Action actionInfo[5] = {
		{ 01, "thinking",   1, &Animal::ActionThinking },
		{ 60, "digging_under_map",  200, &Animal::ActionSleeping},
		{ 20, "fixing",  100, &Animal::ActionSpecial },
		{ 19, "moving", 100, &Animal::ActionMoving },
	};
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
	void ActionSleeping(Console &console);

	void SeeOtherAimal(const Animal& dog, float width, float heigth);
};