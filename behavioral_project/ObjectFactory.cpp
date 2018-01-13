#include "ObjectFactory.h"
#include <iostream>
#include <memory>


ObjectFactory::ObjectFactory()
{
}

ObjectFactory::~ObjectFactory()
{
}

std::shared_ptr<Entity> ObjectFactory::createHerbivore(Sprite childSprite, Sprite adultSprite, Vector2f position)
{
	std::string sex;
	//Random sex
	float value = (float)rand() / RAND_MAX;

	if (value < 0.5)
	{
		sex = "MALE";
		std::shared_ptr<Entity> ptr(std::make_shared<Herbivore>(childSprite, adultSprite, sex, position, m_GameResolution));
		return ptr;
	}
	else
	{
		sex = "FEMALE";
		std::shared_ptr<Entity> ptr(std::make_shared<Herbivore>(childSprite, adultSprite, sex, position, m_GameResolution));
		return ptr;
	}
}

std::shared_ptr<Entity> ObjectFactory::createCarnivore(Sprite childSprite, Sprite adultSprite, Vector2f position)
{
	//Random sex
	float value = (float)rand() / RAND_MAX;

	if (value < 0.5)
	{
		std::shared_ptr<Entity> ptr(std::make_shared<Carnivore>(childSprite, adultSprite, "MALE", position, m_GameResolution));
		return ptr;
	}
	else
	{
		std::shared_ptr<Entity> ptr(std::make_shared<Carnivore>(childSprite, adultSprite, "FEMALE", position, m_GameResolution));
		return ptr;
	}
}

std::shared_ptr<Resource> ObjectFactory::createWater(Sprite sprite, Vector2f position)
{
	std::shared_ptr<Resource> ptr(std::make_shared<Water>(sprite, position, m_GameResolution));
	return ptr;
}

std::shared_ptr<Resource> ObjectFactory::createPlant(Sprite sprite, Vector2f position)
{
	std::shared_ptr<Resource> ptr(std::make_shared<Plant>(sprite, position, m_GameResolution));
	return ptr;
}

std::shared_ptr<Resource> ObjectFactory::createMeat(Sprite sprite, Vector2f position)
{
	std::shared_ptr<Resource> ptr(std::make_shared<Meat>(sprite, position, m_GameResolution));
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
				if ((*it)->getType() == "HERBIVORE")
				{
					resourceVector.push_back(createMeat(m_MeatSprite, (*it)->getPosition()));
				}
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
			if (entityVector[0]->getType() == "HERBIVORE")
			{
				resourceVector.push_back(createMeat(m_MeatSprite, entityVector[0]->getPosition()));
			}
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

void ObjectFactory::setMeatSprite(Sprite meatSprite)
{
	m_MeatSprite = meatSprite;
}
