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

void ObjectFactory::createCarnivore(Sprite sprite, Vector2f position, std::vector<Carnivore> *vector, Vector2f resolution)
{
	Carnivore carnivore(sprite, position, resolution);
	vector->push_back(carnivore);
}

void ObjectFactory::createWater(Sprite sprite, Vector2f position, std::vector<Water> *vector, Vector2f resolution)
{
	Water water(sprite, position, resolution);
	vector->push_back(water);
}

void ObjectFactory::createPlant(Sprite sprite, Vector2f position, std::vector<Plant> *vector, Vector2f resolution)
{
	Plant plant(sprite, position, resolution);
	vector->push_back(plant);
}

void ObjectFactory::clean(std::vector<Herbivore> *h_vector, std::vector<Carnivore> *c_vector, std::vector<Water> *w_vector, std::vector<Plant> *p_vector)
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

	//Cleaning carnivore vector
	if (!c_vector->empty() && c_vector->size() != 1)
	{
		for (int i = 0; i <= c_vector->size() - 1; i++)
		{
			if ((*c_vector)[i].isDead())
			{
				c_vector->erase(c_vector->begin() + i);
			}
		}
	}
	else if (!c_vector->empty() && c_vector->size() == 1)
	{
		if ((*c_vector)[0].isDead())
		{
			c_vector->pop_back();
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

	//Cleaning plant vector
	if (!p_vector->empty() && p_vector->size() != 1)
	{
		for (int i = 0; i <= p_vector->size() - 1; i++)
		{
			if ((*p_vector)[i].isEmpty())
			{
				p_vector->erase(p_vector->begin() + i);
			}
		}
	}
	else if (!p_vector->empty() && p_vector->size() == 1)
	{
		if ((*p_vector)[0].isEmpty())
		{
			p_vector->pop_back();
		}
	}
}
