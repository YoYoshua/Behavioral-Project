#pragma once
#include "Entity.h"
#include "Herbivore.h"

class Carnivore :
	public Entity
{
public:
	using Entity::Entity;

	Carnivore();
	~Carnivore();

	/*Behavioral functions*/
	void behaviour(Time dt);
	void idleBehaviour(Time dt);
	void drinkWater(Water *water, Time dt);
	void eatFood(Herbivore *herbivore, Time dt);

	//Update function
	void update(Time dt);
};

