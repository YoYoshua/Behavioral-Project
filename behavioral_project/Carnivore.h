#pragma once
#include "Entity.h"
#include "Herbivore.h"

class Carnivore :
	public Entity
{
public:
	/*Constructors and Destructor*/
	Carnivore();
	Carnivore(Sprite sprite, Vector2f position, Vector2f resolution);
	~Carnivore();
};

