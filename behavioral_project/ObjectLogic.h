#pragma once

#include<memory>

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
	Vector2f m_RelativePosition;

	Resource *m_ClosestResource;
	float m_ClosestResourceDistance;

	Entity *m_ClosestEntity;
	float m_ClosestEntityDistance;

	std::vector<std::shared_ptr<Entity>> entitiesNoticed;
	std::vector<std::shared_ptr<Resource>> resourcesNoticed;

public:
	ObjectLogic();
	~ObjectLogic();

	//Getters
	float getLength();

	/*Main logic method*/
	void processLogic(Time dt, std::vector<std::shared_ptr<Entity>> &entityVector, std::vector<std::shared_ptr<Resource>> &resourceVector);

	//Various logic methods
	void checkEntities(std::shared_ptr<Entity> entity, std::vector<std::shared_ptr<Entity>> &entityVector);
	void checkResources(std::shared_ptr<Entity> entity, std::vector<std::shared_ptr<Resource>> &resourceVector);
	void interact(Time dt, std::shared_ptr<Entity> entityOne, std::vector<std::shared_ptr<Entity>> &entitiesNoticed, std::vector<std::shared_ptr<Resource>> &resourcesNoticed);
};

