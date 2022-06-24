#include "stdafx.h"
#include "Dog.h"
using namespace std;


//Konstruktory

Dog::Dog() //konstruktor bezparametrowy
{
	name = "Anonymous";
	breed = "Mongrel";

	age = 0;
	power = 0;
	aggresion = 0;

	isMale = true;
	isAlive = true;

	cout << "Constructor [parameterless]: Dog " << name << " of breed " << breed << " and age " << age << " and power " << power << " created" << endl;
}

Dog::Dog(string name) //konstruktor jednoparametrowy
{
	this->name = name;
	breed = "Mongrel";

	cout << "Constructor [one-parameter]: Dog " << name << " of breed " << breed << " and age " << age << " and power " << power << " created" << endl;
}

Dog::Dog(string name, int age, string breed, int power, int aggresion, bool isMale) //konstruktor wieloparametrowy
{
	this->name = name;
	this->age = age;
	this->breed = breed;
	this->power = power;
	this->aggresion = aggresion;
	this->isMale = isMale;

	cout << "Constructor [multi-parameter]: Dog " << name << " of breed " << breed << " and age " << age << " and power " << power << " created" << endl;
}

Dog::Dog(const Dog &dog) //konstruktor kopiujacy
{
	name = dog.name;
	age = dog.age;
	breed = dog.breed;
	power = dog.power;
	aggresion = dog.aggresion;
	isMale = dog.isMale;
	isAlive = dog.isAlive;

	cout << "Constructor [copy]: Dog " << name << " of breed " << breed << " and age " << age << " and power " << power << " created" << endl;
}

Dog::~Dog() //destruktor
{
	cout << "Destructor: Dog " << name << " of breed " << breed << " and age " << age << " and power " << power << " deleted" << endl;
}

//Akcesory

void Dog::SetName(string name)
{
	this->name = name;

	cout << name << " name modified to " << name << " by setter function" << endl;
}

void Dog::SetBreed(string breed)
{
	this->breed = breed;
	
	cout << name << " breed modified to " << breed << " by setter function" << endl;
}

void Dog::SetPower(int power)
{
	if (power < 0) //wartosc 'power' nie moze byc ujemna (z warunkow zadania)
	{
		power = 0;
	}

	this->power = power;
	
	cout << name << " power modified to " << power << " by setter function" << endl;
}

void Dog::SetAggresion(int aggresion)
{
	this->aggresion = aggresion;
}

void Dog::SetAge(int age)
{
	this->age = age;
}

std::string Dog::GetName() const
{
	return name;
}

std::string Dog::GetBreed() const
{
	return breed;
}

int Dog::GetPower() const
{
	return power;
}

int Dog::GetAggresion() const
{
	return aggresion;
}

int Dog::GetAge() const
{
	return age;
}

// Debug methods
string Dog::GetInfo()
{
	string liveDesc = isAlive ? "Dog " : "Dead dog";
	string infoString = liveDesc + GetName() + " of breed " + GetBreed() + " and age " + std::to_string(age) + " and power " + std::to_string(power);
	return infoString;
}

void Dog::PrintInfo()
{
	cout << GetInfo() << endl;
}
