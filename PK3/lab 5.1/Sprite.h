#pragma once
#include "Console.h"

class Sprite //C5 A class that stores sprite information
{
public:
	float x, y;
	float dx = 0.0f, dy = 0.0f;
	WORD color = 0;

protected:
	char *imageData = nullptr;

public:
	Sprite();
	Sprite(WORD);
	~Sprite();

	void SetImage(char *imageData);

	WORD GetColor() const;
	char* GetImage() const;
};