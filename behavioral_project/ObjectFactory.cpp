#include "ObjectFactory.h"
#include <iostream>



ObjectFactory::ObjectFactory()
{
}

ObjectFactory::~ObjectFactory()
{
}

void ObjectFactory::createHerbivore(Sprite sprite, Vector2f position, std::vector<Herbivore> *vector, Vector2f resolution)
{
	Herbivore herbivore(sprite, position, resolution);
	vector->push_back(herbivore);
}

void ObjectFactory::createWater(Sprite sprite, Vector2f position, std::vector<Water> *vector, Vector2f resolution)
{
	Water water(sprite, position, resolution);
	vector->push_back(water);
}

void ObjectFactory::clean(std::vector<Herbivore> *h_vector, std::vector<Water> *w_vector)
{
	//Cleaning herbivore vector
	if (!h_vector->empty() && h_vector->size() != 1)
	{
		for (int i = 0; i <= h_vector->size() - 1; i++)
		{
			if ((*h_vector)[i].isDead())
			{
				h_vector->erase(h_vector->begin() + i);
			}
		}
	}
	else if (!h_vector->empty() && h_vector->size() == 1)
	{
		if ((*h_vector)[0].isDead())
		{
			h_vector->pop_back();
		}
	}

	//Cleaning water vector
	if (!w_vector->empty() && w_vector->size() != 1)
	{
		for (int i = 0; i <= w_vector->size() - 1; i++)
		{
			if ((*w_vector)[i].isEmpty())
			{
				w_vector->erase(w_vector->begin() + i);
			}
		}
	}
	else if (!w_vector->empty() && w_vector->size() == 1)
	{
		if ((*w_vector)[0].isEmpty())
		{
			w_vector->pop_back();
		}
	}
}
