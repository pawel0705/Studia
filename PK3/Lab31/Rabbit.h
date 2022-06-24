#pragma once
#include "Animal.h"
#include "Console.h"
#include <string>

class Rabbit : public Animal
{
private:
	typedef void(Rabbit::*ActionFunction)(Console&);
	struct Action
	{
		int probability;
		std::string actionText;
		int frameNumber;
		ActionFunction actionFunction;
	};
	const Action actionInfo[5] = {
		{ 01, "thinking",   1, &Rabbit::ActionThinking },
		{ 60, "jumping",  200, &Rabbit::ActionMoving },
		{ 20, "eating",  100, &Rabbit::ActionSpecial },
		{ 20, "sitting",  100, &Rabbit::ActionDontMove },
	};
	ActionFunction currentActionFunction = &Rabbit::ActionThinking;
	int actionActualFrame = 0;
	int actionLastFrame = 1;

public:
	// konstruktory
	Rabbit();
	Rabbit(const Rabbit &rabbit);
	Rabbit(Rabbit &&rabbit);
	Rabbit(std::string name);
	Rabbit(std::string name, int age, bool isMale, WORD color);
	~Rabbit();

	// Operatory
	Rabbit& operator= (const Rabbit &rabbit);
	Rabbit& operator= (Rabbit &&rabbit);

	// Rabbit virtual actions
	virtual std::string DoGetInfo();

	// Action implementation
	Action ActionInfo(int);
	void DoAction(Console &console);
	void ActionThinking(Console &console);
	void ActionMoving(Console &console);
	void ActionSpecial(Console &console);
	void ActionDontMove(Console &console);
};

