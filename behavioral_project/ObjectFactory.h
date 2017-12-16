#pragma once

#include "SFML\Graphics.hpp"
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

public:
	ObjectFactory();
	~ObjectFactory();

	void createHerbivore(Sprite sprite, Vector2f position, std::vector<Herbivore> *vector, Vector2f resolution);
	void createCarnivore(Sprite sprite, Vector2f position, std::vector<Carnivore> *vector, Vector2f resolution);
	void createWater(Sprite sprite, Vector2f position, std::vector<Water> *vector, Vector2f resolution);
	void createPlant(Sprite sprite, Vector2f position, std::vector<Plant> *vector, Vector2f resolution);

	void clean(std::vector<Herbivore> *h_vector, std::vector<Carnivore> *c_vector, 
		std::vector<Water> *w_vector, std::vector<Plant> *p_vector);
};

