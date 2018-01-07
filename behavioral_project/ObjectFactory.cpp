#include "ObjectFactory.h"
#include <iostream>
#include <memory>


ObjectFactory::ObjectFactory()
{
}

ObjectFactory::~ObjectFactory()
{
}

std::shared_ptr<Entity> ObjectFactory::createHerbivore(Sprite sprite, Vector2f position)
{
	std::shared_ptr<Entity> ptr(std::make_shared<Herbivore>(sprite, position, m_GameResolution));
	return ptr;
}

std::shared_ptr<Entity> ObjectFactory::createCarnivore(Sprite sprite, Vector2f position)
{
	std::shared_ptr<Entity> ptr(std::make_shared<Carnivore>(sprite, position, m_GameResolution));
	return ptr;
}

std::shared_ptr<Resource> ObjectFactory::createWater(Sprite sprite, Vector2f position)
{
	std::shared_ptr<Resource> ptr(std::make_shared<Water>(sprite, position, m_GameResolution));
	return ptr;
}

std::shared_ptr<Resource> ObjectFactory::createPlant(Sprite sprite, Vector2f position)
{
	std::shared_ptr<Resource> ptr(std::make_shared<Resource>(sprite, position, m_GameResolution));
	return ptr;
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

void ObjectFactory::clean(std::vector<std::shared_ptr<Entity>>& entityVector, std::vector<std::shared_ptr<Resource>>& resourceVector)
{
	unsigned int eVectorSize = entityVector.size();
	unsigned int rVectorSize = resourceVector.size();

	if (!entityVector.empty() && eVectorSize != 1)
	{
		for (std::vector<std::shared_ptr<Entity >>::iterator it = entityVector.begin(); it != entityVector.end(); ++it)
		{
			if ((*it)->isDead())
			{
				it = entityVector.erase(it);
			}
			if (it == entityVector.end())
			{
				--it;
			}
		}
	}
	else if (!entityVector.empty() && eVectorSize == 1)
	{
		if (entityVector[0]->isDead())
		{
			entityVector.pop_back();
		}
	}
	
}

void ObjectFactory::setResolution(Vector2f resolution)
{
	m_GameResolution = resolution;
}
