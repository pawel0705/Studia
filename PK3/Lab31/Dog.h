#pragma once
#include "Animal.h"
#include "Console.h"

class Dog : public Animal
{
private:
	typedef void(Dog::*ActionFunction)(Console&);
	struct Action
	{
		int probability;
		std::string actionText;
		int frameNumber;
		ActionFunction actionFunction;
	};
	const Action actionInfo[5] = {
		{ 01, "thinking",   1, &Dog::ActionThinking },
		{ 60, "running",  200, &Dog::ActionMoving },
		{ 20, "pissing",  100, &Dog::ActionSpecial },
		{ 19, "sleeping", 100, &Dog::ActionSleeping },
	};
	ActionFunction currentActionFunction = &Dog::ActionThinking;
	int actionActualFrame = 0;
	int actionLastFrame = 1;

	int power = 0;
	bool have_child = false;

public:
	// konstruktory
	Dog();
	Dog(const Dog &dog);
	Dog(Dog &&dog);
	Dog(std::string name);
	Dog(std::string name, int age, bool isMale, WORD color);
	Dog(std::string name, int age, bool isMale, WORD color, int power); //add dog with power
	~Dog();

	// Operatory
	Dog& operator= (const Dog &dog);
	Dog& operator= (Dog &&dog); 
	Dog operator+(const Dog & dog); //for creating new dog
		
	// Dog virtual actions
	virtual std::string DoGetInfo();

	// Action implementation
	Action ActionInfo(int);
	void DoAction(Console &console);
	void ActionThinking(Console &console);
	void ActionMoving(Console &console);
	void ActionSpecial(Console &console);
	void ActionSleeping(Console &console);

	void FightWith(Dog &dog); //fight with dog

	int GetPower();
	bool GetIsAlive();
	bool GetHaveChild();
	void SetIsAlive(bool);
	void SetHaveChild(bool);
	void SetPower(int);
};

