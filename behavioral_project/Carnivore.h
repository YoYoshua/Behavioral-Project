#pragma once
#include "Entity.h"
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

	//Update function
	void update(Time dt);
};

