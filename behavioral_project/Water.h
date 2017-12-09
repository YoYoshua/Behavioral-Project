#pragma once
#include "Resource.h"

class Water :
	public Resource
{
public:
	//Declaration of inheritance of constructor
	using Resource::Resource;

	Water();
	~Water();

	void update(Time dt);
};

