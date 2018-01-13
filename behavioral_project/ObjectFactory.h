#pragma once

#include <memory>

#include "SFML\Graphics.hpp"
#include "Entity.h"
#include "Herbivore.h"
#include "Carnivore.h"
#include "Water.h"
#include "Plant.h"
#include "Meat.h"


class ObjectFactory
{
private:
	Vector2f m_GameResolution;
	Sprite m_MeatSprite;

public:
	ObjectFactory();
	~ObjectFactory();

	std::shared_ptr<Entity> createHerbivore(Sprite childSprite, Sprite adultSprite, Vector2f position);
	std::shared_ptr<Entity> createCarnivore(Sprite childSprite, Sprite adultSprite, Vector2f position);
	std::shared_ptr<Resource> createWater(Sprite sprite, Vector2f position);
	std::shared_ptr<Resource> createPlant(Sprite sprite, Vector2f position);
	std::shared_ptr<Resource> createMeat(Sprite sprite, Vector2f position);

	void clean(std::vector<std::shared_ptr<Entity >> &entityVector, std::vector<std::shared_ptr<Resource >> &resourceVector);

	void setResolution(Vector2f resolution);
	void setMeatSprite(Sprite meatSprite);
};

