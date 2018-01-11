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

void ObjectFactory::clean(std::vector<std::shared_ptr<Entity>>& entityVector, std::vector<std::shared_ptr<Resource>>& resourceVector)
{
	unsigned int eVectorSize = entityVector.size();
	unsigned int rVectorSize = resourceVector.size();

	//Cleaning entities
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

	//Cleaning resources
	if (!resourceVector.empty() && rVectorSize != 1)
	{
		for (std::vector<std::shared_ptr<Resource >>::iterator it = resourceVector.begin(); it != resourceVector.end(); ++it)
		{
			if ((*it)->isEmpty())
			{
				it = resourceVector.erase(it);
			}
			if (it == resourceVector.end())
			{
				--it;
			}
		}
	}
	else if (!resourceVector.empty() && eVectorSize == 1)
	{
		if (resourceVector[0]->isEmpty())
		{
			resourceVector.pop_back();
		}
	}
	
}

void ObjectFactory::setResolution(Vector2f resolution)
{
	m_GameResolution = resolution;
}
