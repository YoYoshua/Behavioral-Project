#pragma once
#include "Resource.h"
class Plant :
	public Resource
{
public:
	//Declaration of inheritance of constructor
	using Resource::Resource;

	Plant();
	~Plant();

	void update(Time dt);
};

