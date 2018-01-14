#include "ObjectFactory.h"
#include <iostream>
#include <memory>

ObjectFactory::ObjectFactory()
{
}

ObjectFactory::~ObjectFactory()
{
}

std::shared_ptr<Entity> ObjectFactory::createHerbivore(Vector2f position)
{
	std::string sex;
	//Random sex
	float value = (float)rand() / RAND_MAX;

	if (value < 0.5)
	{
		sex = "MALE";
		std::shared_ptr<Entity> ptr(std::make_shared<Herbivore>(m_HerbivoreChildSprite, m_HerbivoreMaleSprite, sex, position, m_GameResolution));
		return ptr;
	}
	else
	{
		sex = "FEMALE";
		std::shared_ptr<Entity> ptr(std::make_shared<Herbivore>(m_HerbivoreChildSprite, m_HerbivoreFemaleSprite, sex, position, m_GameResolution));
		return ptr;
	}
}

std::shared_ptr<Entity> ObjectFactory::createCarnivore(Vector2f position)
{
	//Random sex
	float value = (float)rand() / RAND_MAX;

	if (value < 0.5)
	{
		std::shared_ptr<Entity> ptr(std::make_shared<Carnivore>(m_CarnivoreChildSprite, m_CarnivoreMaleSprite, "MALE", position, m_GameResolution));
		return ptr;
	}
	else
	{
		std::shared_ptr<Entity> ptr(std::make_shared<Carnivore>(m_CarnivoreChildSprite, m_CarnivoreFemaleSprite, "FEMALE", position, m_GameResolution));
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

void ObjectFactory::setTextures(Texture * herbivoreTexture, Texture * carnivoreTexture)
{
	/*Game objects initialisation*/
	Vector2i origin(0, 0);
	Vector2i size(76, 56);
	IntRect rectangle(origin, size);

	//Herbivore
	herbivoreTexture->loadFromFile("graphics/cow.png");

	m_HerbivoreChildSprite.setTexture(*herbivoreTexture);
	m_HerbivoreChildSprite.setTextureRect(rectangle);

	rectangle.top = 56;

	m_HerbivoreFemaleSprite.setTexture(*herbivoreTexture);
	m_HerbivoreFemaleSprite.setTextureRect(rectangle);

	rectangle.top = 112;
	rectangle.height = 63;

	m_HerbivoreMaleSprite.setTexture(*herbivoreTexture);
	m_HerbivoreMaleSprite.setTextureRect(rectangle);

	//Carnivore
	carnivoreTexture->loadFromFile("graphics/lion.png");

	rectangle.top = 0;
	rectangle.width = 78;
	rectangle.height = 56;

	m_CarnivoreChildSprite.setTexture(*carnivoreTexture);
	m_CarnivoreChildSprite.setTextureRect(rectangle);

	rectangle.top = 56;
	rectangle.height = 58;

	m_CarnivoreFemaleSprite.setTexture(*carnivoreTexture);
	m_CarnivoreFemaleSprite.setTextureRect(rectangle);

	rectangle.top = 115;
	rectangle.height = 66;

	m_CarnivoreMaleSprite.setTexture(*carnivoreTexture);
	m_CarnivoreMaleSprite.setTextureRect(rectangle);
}

void ObjectFactory::setResolution(Vector2f resolution)
{
	m_GameResolution = resolution;
}

void ObjectFactory::setMeatSprite(Sprite meatSprite)
{
	m_MeatSprite = meatSprite;
}
