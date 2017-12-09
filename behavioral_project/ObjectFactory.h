#pragma once

#include <map>

#include "SFML\Graphics.hpp"
#include "Herbivore.h"
#include "Carnivore.h"
#include "Water.h"
#include "Plant.h"

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();

	void createHerbivore(Sprite sprite, Vector2f position, std::vector<Herbivore> *vector, Vector2f resolution);
	void createWater(Sprite sprite, Vector2f position, std::vector<Water> *vector, Vector2f resolution);
	void createPlant(Sprite sprite, Vector2f position, std::vector<Plant> *vector, Vector2f resolution);

	void clean(std::vector<Herbivore> *h_vector, std::vector<Water> *w_vector, std::vector<Plant> *p_vector);
};

