#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "Dog.h"
using namespace std;
#include <iostream>
#include <thread>

// Zestaw konstruktorów i destruktor
Dog::Dog()
{
	cout << "Constructor [parameterless]: " << GetInfo() << " created" << endl;
}

Dog::Dog(string name) : name(name)
{
	cout << "Constructor [one-parameter]: " << GetInfo() << " created" << endl;
}

Dog::Dog(std::string name, int age, std::string breed, int power, int aggresion, bool isMale = true) : name(name), breed(breed), power(power), aggresion(aggresion), age(age), isMale(isMale)
{
	cout << "Constructor [multi-parameter]: " << GetInfo() << " created" << endl;
}

Dog::Dog(const Dog &dog) : name(dog.name), breed(dog.breed), age(dog.age), power(dog.power), aggresion (dog.aggresion)
{
	if (dog.imageData)		// != nullptr
	{
		cout << "Constructor [copy]: copying image " << dog.imageData << " it will last 5s" << endl;
		imageData = new char[strlen(dog.imageData) + 1];
		memcpy(imageData, dog.imageData, strlen(dog.imageData) + 1);
		this_thread::sleep_for(chrono::seconds(5));
	}

	cout << "Constructor [copy]: " << GetInfo() << " created" << endl;
}


Dog::~Dog()
{
	cout << "Destructor: "<< GetInfo() << " deleted" << endl;
	if (imageData)
	{
		cout << "Destructor: " << GetName() << " image deleted" << endl;
		delete[] imageData;
	}
}

// Zestaw akcesorów - setters
void Dog::SetName(std::string name)
{
	this->name = name;
	cout << GetName() << " name modified to " << this->name << " by setter function" << endl;
}

void Dog::SetBreed(std::string breed)
{
	this->breed = breed;
	cout << GetName() << " breed modified to " << this->breed << " by setter function" << endl;
}

void Dog::SetPower(int power)
{
	if (power > 0)
		this->power = power;
	else
		this->power = 0;
	cout << GetName() << " power modified to " << this->power << " by setter function" << endl;
}

void Dog::SetAggresion(int aggresion)
{
	this->aggresion = aggresion;
	cout << GetName() << " aggresion modified to " << this->aggresion << " by setter function" << endl;
}


void Dog::SetAge(int age)
{
	this->age = age;
	cout << GetName() << " age modified to " << this->age << " by setter function" << endl;
}

void Dog::SetImage(char *imageData)
{
	cout << GetName() << " image modified to " << imageData << " by setter function" << imageData << endl;
	if (this->imageData != nullptr)
		delete[] imageData;

	if (imageData !=nullptr )
	{
		this->imageData = new char[strlen(imageData) + 1];
		strcpy(this->imageData, imageData);
	}
}

// Zestaw akcesorów - getters
std::string Dog::GetName() const
{
	return name.empty() ? "Anonymous" : name;
}

std::string Dog::GetBreed() const
{
	return 	breed.empty() ? "Mongrel" : breed;
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

char* Dog::GetImage() const
{
	return imageData;
}

// operatory
/* to do */

Dog & Dog::operator= (const Dog& dog)
{
	delete imageData;
	imageData = new char[strlen(dog.imageData) + 1];
	strcpy(imageData, dog.imageData);

	name = dog.name;
	breed = dog.breed;
	power = dog.power;
	aggresion = dog.aggresion;
	age = dog.age;
	isMale = dog.isMale;
	isAlive = dog.isAlive;

	cout << "[OPERATOR PRZYPISANIA TUTAJ PRACUJE]" << endl;

	return *this;
}

Dog & Dog::operator++()
{
	age++;
	return *this;
}

Dog Dog::operator++(int)
{
	Dog older_dog(*this);
	++(*this);
	return older_dog;
}

Dog Dog::operator+(const Dog &dog)
{
	// jeœli samiec i samica i ta sama rasa (ale != null) to powstaje rasowy szczeniak o wieku 0; 
	// jeœli ró¿ne rasy lub ojciec albo matka  nierasowi, powstaje nierasowy
	Dog doggy;
	if (((this->isMale == true && dog.isMale == false) || (this->isMale == false && dog.isMale == true)) != NULL)
	{
		if (this->breed == "Mongrel" || dog.breed == "Mongrel" || (this->breed != dog.breed))
		{
			doggy.breed = "Mongrel";
		}
		else if (this->breed == dog.breed)
		{
			doggy.breed = dog.breed;
		}
		doggy.age = 0;
		return doggy;
	}
	else
		return doggy;
}

// Inne metody
string Dog::GetInfo()
{
	string imageDesc = imageData ? imageData : "no data";
	string liveDesc = isAlive ? "Dog " : "Dead dog";
	string infoString = liveDesc + GetName() + " of breed " + GetBreed() + " and age " + std::to_string(age) + " and power " + std::to_string(power) + " image " + imageDesc;
	return infoString;
}

void Dog::PrintInfo()
{
	cout << GetInfo() << endl;
}

Dog Dog::SimulateFightWith(Dog dog)
{
	Dog clonedDog = *this;
	
	clonedDog.SetPower (power - dog.GetPower());
	return clonedDog;
}

void Dog::FightWith(Dog& dog)
{
	int dogPower = power;
	SetPower (power - dog.GetPower());		
	dog.SetPower( dog.GetPower() - dogPower);
}

std::ostream& operator<< (std::ostream& os, const Dog& dog)
{
	os << dog.GetName();
	return os;
}



