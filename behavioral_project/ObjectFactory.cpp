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
	//Getting sizes of every vector
	m_cVectorSize = c_vector->size();
	m_hVectorSize = h_vector->size();
	m_wVectorSize = w_vector->size();
	m_pVectorSize = p_vector->size();

	//Cleaning herbivore vector
	if (!h_vector->empty() && m_hVectorSize != 1)
	{
		for (std::vector<Herbivore>::iterator it = h_vector->begin(); it != h_vector->end(); ++it)
		{
			if ((*it).isDead())
			{
				it = h_vector->erase(it);
			}

			if (it == h_vector->end())
			{
				--it;
			}
		}
	}
	else if (!h_vector->empty() && m_hVectorSize == 1)
	{
		if ((*h_vector)[0].isDead())
		{
			h_vector->pop_back();
		}
	}

	//Cleaning carnivore vector
	if (!c_vector->empty() && m_cVectorSize != 1)
	{
		for (std::vector<Carnivore>::iterator it = c_vector->begin(); it != c_vector->end(); ++it)
		{
			if ((*it).isDead())
			{
				it = c_vector->erase(it);
			}

			if (it == c_vector->end())
			{
				--it;
			}
		}
	}
	else if (!c_vector->empty() && m_cVectorSize == 1)
	{
		if ((*c_vector)[0].isDead())
		{
			c_vector->pop_back();
		}
	}

	//Cleaning water vector
	if (!w_vector->empty() && m_wVectorSize != 1)
	{
		for (std::vector<Water>::iterator it = w_vector->begin(); it != w_vector->end(); ++it)
		{
			if ((*it).isEmpty())
			{
				it = w_vector->erase(it);
			}

			if (it == w_vector->end())
			{
				--it;
			}
		}
	}
	else if (!w_vector->empty() && m_wVectorSize == 1)
	{
		if ((*w_vector)[0].isEmpty())
		{
			w_vector->pop_back();
		}
	}

	//Cleaning plant vector
	if (!p_vector->empty() && m_pVectorSize != 1)
	{
		for (std::vector<Plant>::iterator it = p_vector->begin(); it != p_vector->end(); ++it)
		{
			if ((*it).isEmpty())
			{
				it = p_vector->erase(it);
			}

			if (it == p_vector->end())
			{
				--it;
			}
		}
	}
	else if (!p_vector->empty() && m_pVectorSize == 1)
	{
		if ((*p_vector)[0].isEmpty())
		{
			p_vector->pop_back();
		}
	}
}
