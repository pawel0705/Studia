#include "stdafx.h"
#include "Breed.h"
using namespace std;


Breed::Breed()
{
}

Breed::Breed(std::string name, int power, int aggresion, int weightMale, int weightfemale): name(name), power(power), aggression(aggresion), weightMale(weightMale), weightFemale(weightFemale)
{
	cout << "Constructor: Breed " << name << " created" << endl;
}

Breed::~Breed()
{

}

// accessors

std::string Breed::GetName() const
{
	return name;
}

int Breed::GetPower() const
{
	return power;
}

int Breed::GetAggression() const
{
	return aggression;
}

int Breed::GetWeightMale() const
{
	return weightMale;
}

int Breed::GetWeightFemale() const
{
	return weightFemale;
}

void Breed::SetName(std::string name)
{
	this->name = name;
}

void Breed::SetPower(int power)
{
	this->power = power;
}

void Breed::SetAggression(int aggresion)
{
	this->aggression = aggression;
}

void Breed::SetWeightMale(int weightMale)
{
	this->weightMale = weightMale;
}

void Breed::SetWeightFemale(int weightFemale)
{
	this->weightFemale = weightFemale;
}

// Debug methods
string Breed::GetInfo()
{
	return "breed " + name + " power " + std::to_string(power) + " aggression " + std::to_string(aggression);
}

void Breed::PrintInfo()
{
	cout << GetInfo() << endl;
}

// Mongrel definition
Breed Breed::Mongrel("Mongrel", 0, 0, 0, 0);