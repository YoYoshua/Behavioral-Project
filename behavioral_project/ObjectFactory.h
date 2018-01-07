#pragma once

#include <memory>

#include "SFML\Graphics.hpp"
#include "Entity.h"
#include "Herbivore.h"
#include "Carnivore.h"
#include "Water.h"
#include "Plant.h"


class ObjectFactory
{
private:
	unsigned int m_cVectorSize;
	unsigned int m_hVectorSize;
	unsigned int m_wVectorSize;
	unsigned int m_pVectorSize;

	Vector2f m_GameResolution;

public:
	ObjectFactory();
	~ObjectFactory();

	std::shared_ptr<Entity> createHerbivore(Sprite sprite, Vector2f position);
	std::shared_ptr<Entity> createCarnivore(Sprite sprite, Vector2f position);
	std::shared_ptr<Resource> createWater(Sprite sprite, Vector2f position);
	std::shared_ptr<Resource> createPlant(Sprite sprite, Vector2f position);

	void clean(std::vector<Herbivore> *h_vector, std::vector<Carnivore> *c_vector, 
		std::vector<Water> *w_vector, std::vector<Plant> *p_vector);
	void clean(std::vector<std::shared_ptr<Entity >> &entityVector, std::vector<std::shared_ptr<Resource >> &resourceVector);

	void setResolution(Vector2f resolution);
};

