#pragma once
#include "Entity.h"

class Herbivore :
	public Entity
{
public:
	//Constructors and Destructor
	Herbivore();
	Herbivore(Sprite sprite, Vector2f position, Vector2f resolution);
	~Herbivore();
};

