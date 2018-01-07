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

	/*Behavioral functions*/
	void behaviour(Time dt);
	void idleBehaviour(Time dt);
	void drinkWater(Water *water, Time dt);
	void eatFood(Herbivore *herbivore, Time dt);

	//Update function
	virtual void update(Time dt);
};

