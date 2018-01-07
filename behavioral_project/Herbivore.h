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

	/*Behavioral functions*/
	void behaviour(Time dt);
	void idleBehaviour(Time dt);
	void drinkWater(Water *water, Time dt);
	void eatFood(Plant *plant, Time dt);

	//Update function
	virtual void update(Time dt);
};

