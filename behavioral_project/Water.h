#pragma once
#include "Resource.h"

class Water :
	public Resource
{
public:
	Water(Sprite sprite, Vector2f position, Vector2f resolution);
	~Water();
};

