#include "stdafx.h"
#include "Animal.h"

using namespace std;

#pragma region Constructors
Animal::Animal() : Animal("Noname animal", 0, true)
{

}

Animal::Animal(std::string name, int age, bool isMale) :name(name), age(age), isMale(isMale)
{

}

Animal::~Animal()
{

}
#pragma endregion

#pragma region Accessors
string Animal::DoGetInfo()
{
	return GetName() + " [" + actionText + "]";
}

void Animal::SetAge(int age)
{
	this->age = age;
}

void Animal::SetName(std::string name)
{
	this->name = name;
}

std::string Animal::GetName() const
{
	return name.empty() ? "Anonymous" : name;
}

int Animal::GetAge() const
{
	return age;
}
#pragma endregion