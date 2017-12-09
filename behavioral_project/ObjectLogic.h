#pragma once

#include "SFML\Graphics.hpp"
#include "Herbivore.h"
#include "Carnivore.h"
#include "Water.h"
#include "Plant.h"

class ObjectLogic
{
private:
	Vector2f m_PositionVector;
	float m_Length;

	Resource *m_ClosestResource;
	float m_ClosestResourceDistance;

	Entity *m_ClosestEntity;
	float m_ClosestEntityDistance;

public:
	ObjectLogic();
	~ObjectLogic();

	//Getters
	float getLength();

	/*Main logic function*/
	void processLogic(std::vector<Herbivore> *h_vector, std::vector<Carnivore> *c_vector,
		std::vector<Water> *w_vector, std::vector<Plant> *p_vector);

};

