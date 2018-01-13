#include "ObjectLogic.h"



ObjectLogic::ObjectLogic()
{
}


ObjectLogic::~ObjectLogic()
{
}

//Getters
float ObjectLogic::getLength()
{
	return m_Length;
}

/*Main logic function*/
void ObjectLogic::processLogic(Time dt, std::vector<std::shared_ptr<Entity>> &entityVector, std::vector<std::shared_ptr<Resource>> &resourceVector)
{
	if (!entityVector.empty())
	{
		for (auto p : entityVector)
		{
			//Clear private objects vectors
			entitiesNoticed.clear();
			resourcesNoticed.clear();
			entitiesCreated.clear();

			//Check surrounding entities
			checkEntities(p, entityVector);

			//Check surrounding resources
			checkResources(p, resourceVector);

			//Interact with surrounding objects
			interact(dt, p, entitiesNoticed, resourcesNoticed);
		}
		//Create new object based on mating
		for (auto p : entitiesCreated)
		{
			entityVector.push_back(p);
		}
	}
}

void ObjectLogic::checkEntities(std::shared_ptr<Entity> entity, std::vector<std::shared_ptr<Entity>>& entityVector)
{
	std::shared_ptr<Entity> closestDanger = nullptr;
	std::shared_ptr<Entity> closestEntity = nullptr;
	std::shared_ptr<Entity> closestPrey = nullptr;

	float shortestDistanceEntity = 9999.f;
	float shortestDistanceDanger = 9999.f;
	float shortestDistancePrey = 9999.f;

	//Check collisions with another entities
	for (auto m : entityVector)
	{
		//Calculate lenght between two entites
		m_PositionVector.x = entity->getPosition().x - m->getPosition().x;
		m_PositionVector.y = entity->getPosition().y - m->getPosition().y;
		m_Length = sqrt(m_PositionVector.x * m_PositionVector.x + m_PositionVector.y * m_PositionVector.y);

		if (entity->getCircleShape().getRadius() >= m_Length && entity != m)
		{
			entitiesNoticed.push_back(m);

			//Checking closest entity
			if (m_Length < shortestDistanceEntity)
			{
				shortestDistanceEntity = m_Length;
				closestEntity = m;
			}

			//Checking closest danger
			if (m_Length < shortestDistanceDanger && m->getType() == "CARNIVORE" && entity->getType() == "HERBIVORE")
			{
				shortestDistanceDanger = m_Length;
				closestDanger = m;
			}

			//Checking closest prey
			if (m_Length < shortestDistancePrey && m->getType() == "HERBIVORE")
			{
				shortestDistancePrey = m_Length;
				closestPrey = m;
			}
		}
	}

	//Remembering closest entities
	if (closestEntity != nullptr)
	{
		entity->setClosestEntity(closestEntity);
	}
	else
	{
		entity->setClosestEntity(nullptr);
	}

	if (closestDanger != nullptr)
	{
		entity->setClosestDanger(closestDanger);
	}
	else
	{
		entity->setClosestDanger(nullptr);
	}

	if (closestPrey != nullptr)
	{
		entity->setClosestPrey(closestPrey);
	}
	else
	{
		entity->setClosestPrey(nullptr);
	}
}

void ObjectLogic::checkResources(std::shared_ptr<Entity> entity, std::vector<std::shared_ptr<Resource>>& resourceVector)
{
	std::shared_ptr<Resource> closestWater = nullptr;
	std::shared_ptr<Resource> closestFood = nullptr;

	float shortestDistanceWater = 9999.f;
	float shortestDistanceFood = 9999.f;

	//Check collisions with another resources
	for (auto m : resourceVector)
	{
		//Calculate lenght between two entites
		m_PositionVector.x = entity->getPosition().x - m->getPosition().x;
		m_PositionVector.y = entity->getPosition().y - m->getPosition().y;
		m_Length = sqrt(m_PositionVector.x * m_PositionVector.x + m_PositionVector.y * m_PositionVector.y);

		if (entity->getCircleShape().getRadius() + m->getCircleShape().getRadius() >= m_Length)
		{
			resourcesNoticed.push_back(m);

			if (m->getType() == "WATER" && m_Length < shortestDistanceWater)
			{
				shortestDistanceWater = m_Length;
				closestWater = m;
			}
			else if (m->getType() == "MEAT" && m_Length < shortestDistanceFood && entity->getType() == "CARNIVORE")
			{
				shortestDistanceFood = m_Length;
				closestFood = m;
			}
			else if (m->getType() == "PLANT" && m_Length < shortestDistanceFood && entity->getType() == "HERBIVORE")
			{
				shortestDistanceFood = m_Length;
				closestFood = m;
			}
		}
	}

	//Remembering closest entities
	if (closestFood != nullptr)
	{
		entity->setClosestFood(closestFood);
	}
	
	if (closestWater != nullptr)
	{
		entity->setClosestWater(closestWater);
	}
}

void ObjectLogic::interact(Time dt, std::shared_ptr<Entity> entity, std::vector<std::shared_ptr<Entity>> &entitiesNoticed, 
	std::vector<std::shared_ptr<Resource>> &resourcesNoticed)
{
	bool dangerNoticed = false;
	Vector2f distanceVector;
	float distance;

	//Interactions with noticed enitities
	if (!entitiesNoticed.empty())
	{
		for (auto p : entitiesNoticed)
		{
			//Calculating distance
			distanceVector.x = entity->getPosition().x - p->getPosition().x;
			distanceVector.y = entity->getPosition().y - p->getPosition().y;
			distance = sqrt(distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y);

			//Attacking
			if (entity->isHunting() && distance < 20 && p->getType() == "HERBIVORE")
			{
				entity->attack(dt, p);
			}

			//Reproducing
			if (entity->isMating() && p->isMating() && distance < 20 && p->getType() == entity->getType() && entity->getSex() != p->getSex())
			{
				if (entity->mate(dt, p))
				{
					if (entity->getType() == "HERBIVORE")
					{
						ObjectFactory objectFactory;
						objectFactory.setResolution(p->m_Resolution);

						entitiesCreated.push_back(objectFactory.createHerbivore(entity->getChildSprite(), entity->getAdultSprite(), entity->getPosition()));

						//Setting icons
						(entitiesCreated.back())->setDangerSprite(p->getDangerSprite());
						(entitiesCreated.back())->setHungerSprite(p->getHungerSprite());
						(entitiesCreated.back())->setThirstySprite(p->getThirstySprite());
						(entitiesCreated.back())->setMatingSprite(p->getMatingSprite());
					}
					else if (entity->getType() == "CARNIVORE")
					{
						ObjectFactory objectFactory;
						objectFactory.setResolution(p->m_Resolution);
						entitiesCreated.push_back(objectFactory.createCarnivore(entity->getChildSprite(), entity->getAdultSprite(), entity->getPosition()));
					}
				}

			}
		}
	}
	
	if (!resourcesNoticed.empty())
	{
		for (auto p : resourcesNoticed)
		{
			//Calculating distance
			distanceVector.x = entity->getPosition().x - p->getPosition().x;
			distanceVector.y = entity->getPosition().y - p->getPosition().y;
			distance = sqrt(distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y);

			//Drinking
			if (entity->isThirsty() && distance < 20 && p->getType() == "WATER")
			{
				entity->drink(dt, p);
			}

			//Eating
			if (entity->isHungry() && entity->getType() == "HERBIVORE" && distance < 20 && p->getType() == "PLANT")
			{
				entity->eat(dt, p);
			}
			else if (entity->isHungry() && entity->getType() == "CARNIVORE" && distance < 20 && p->getType() == "MEAT")
			{
				entity->eat(dt, p);
			}

		}
	}
}
