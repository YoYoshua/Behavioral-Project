#pragma once
#include "Entity.h"

class Herbivore :
	public Entity
{
public:
	//Declaration of inheritance of constructor
	using Entity::Entity;

	//Constructors and Destructor
	Herbivore();
	~Herbivore();

	/*Behavioral functions*/
	void behaviour(Time dt);
	void idleBehaviour(Time dt);

	//Update function
	void update(Time dt);
};

