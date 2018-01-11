#pragma once
#include "Resource.h"

class Water :
	public Resource
{
public:
	//Declaration of inheritance of constructor
	using Resource::Resource;

	Water(Sprite sprite, Vector2f position, Vector2f resolution);
	~Water();

	void update(Time dt);
};

