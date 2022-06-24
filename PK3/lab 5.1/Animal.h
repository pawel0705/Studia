#pragma once
#include "Console.h"
#include <string>
#include "stdafx.h"

class Animal //C5 A class that stores information about an animal
{
public:
	int actionActualFrame = 0;
	int actionLastFrame = 1;

protected:
	typedef void (Animal::*ActionFunction)(Console&);
	struct Action
	{
		int probability;
		std::string actionText;
		int frameNumber;
		ActionFunction actionFunction;
	};
	ActionFunction currentActionFunction = &Animal::ActionThinking;

	std::string name;
	std::string actionText;
	int age = 0;
	bool isMale = true;
	bool isAlive = true;

public:
	Animal();
	Animal(std::string, int, bool);
	~Animal();

	void SetName(std::string name);
	void SetAge(int age);

	std::string GetName() const;
	int GetAge() const;

	virtual std::string DoGetInfo();

	virtual Action ActionInfo(int index) = 0;
	virtual void ActionThinking(Console &console) = 0;
	virtual void ActionMoving(Console &console) = 0;
	virtual void ActionSpecial(Console &console) = 0;
	virtual void ActionSleeping(Console &console) = 0;
};