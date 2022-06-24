#pragma once

class Breed
{
private:
	std::string name;
	int power = 0;
	int aggression = 0;
	int weightMale = 0;
	int weightFemale = 0;

public:
	// Constructors & destructors
	Breed();
	Breed(std::string name, int power, int aggresion, int weight_male, int weight_female);
	~Breed();

	// Accessors - getters
	std::string GetName() const;
	int GetPower() const;
	int GetAggression() const;
	int GetWeightMale() const;
	int GetWeightFemale() const;

	// Accessors - setters
	void SetName(std::string name);
	void SetPower(int power);
	void SetAggression(int aggresion);
	void SetWeightMale(int weightMale);
	void SetWeightFemale(int weightFemale);

	// Debug methods
	std::string GetInfo();
	void PrintInfo();

	// This is static object representing mongrel dog
	static Breed Mongrel;
};



