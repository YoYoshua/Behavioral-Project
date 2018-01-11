#pragma once
#include "Resource.h"
class Plant :
	public Resource
{
public:
	Plant(Sprite sprite, Vector2f position, Vector2f resolution);
	~Plant();

	void update(Time dt);
};

