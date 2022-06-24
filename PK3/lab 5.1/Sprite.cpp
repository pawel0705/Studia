#include "stdafx.h"
#include "Sprite.h"

using namespace std;

#pragma region Constructors
Sprite::Sprite() : color(0)
{}

Sprite::Sprite(WORD color) : color(color)
{
	x = static_cast <float> (5 + rand() % 70);
	y = static_cast <float> (5 + rand() % 15);
}

Sprite::~Sprite()
{
	if (imageData)
		delete[] imageData;
}
#pragma endregion

#pragma region Accessors
void Sprite::SetImage(char *imageData)
{
	if (this->imageData) // != nullptr
		delete[] imageData;

	if (imageData)
	{
		imageData = new char[strlen(imageData) + 1];
		memcpy(this->imageData, imageData, strlen(imageData) + 1);
	}
}

WORD Sprite::GetColor() const
{
	return color;
}

char* Sprite::GetImage() const
{
	return imageData;
}
#pragma endregion