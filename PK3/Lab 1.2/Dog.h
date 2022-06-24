#pragma once

class Dog
{
private:
	std::string name;
	std::string breed;
	int power = 0;
	int aggresion = 0;
	int age = 0;
	bool isMale = true;
	bool isAlive = true;
	char *imageData = nullptr;

public:
	// konstruktory
	Dog();
	Dog(const Dog &dog);
	Dog(std::string name);
	Dog(std::string name, int age, std::string breed, int power, int aggresion, bool isMale);
	~Dog();				// pokombinowaæ

	// Akcesory - setters
	void SetName(std::string);
	void SetBreed(std::string);
	void SetPower(int);
	void SetAggresion(int);
	void SetAge(int);
	void SetImage(char *imageData);	// dodaæ

	// Akcesory - getters
	std::string GetName() const;
	std::string GetBreed() const;
	int GetPower() const;
	int GetAggresion() const;
	int GetAge() const;
	char* GetImage() const;	// dodaæ

	// Pozosta³e metody
	std::string GetInfo();
	void PrintInfo();
};

