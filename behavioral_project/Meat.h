#pragma once
#include "Resource.h"

class Meat :
	public Resource
{
public:
	Meat(Sprite sprite, Vector2f position, Vector2f resolution);
	~Meat();
};

