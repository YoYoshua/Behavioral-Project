#pragma once
#include "Entity.h"
class Carnivore :
	public Entity
{
public:
	using Entity::Entity;

	Carnivore();
	~Carnivore();
};

