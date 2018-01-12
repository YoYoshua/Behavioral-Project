#pragma once
#include "SFML\Graphics.hpp"
#include "Water.h"
#include "Plant.h"
#include <memory>

using namespace sf;

class Entity
{
private:
	/*Object variables*/
	//Object parameters
	float m_Health;
	float m_Hunger;
	float m_Thirst;
	float m_ReproductionValue;
	int m_Speed;


	//Constant parameters
	float MAX_HEALTH = 100;

	float MAX_HUNGER = 100;
	float MAX_THIRST = 100;

	int DEFAULT_SPEED = 150;

	//Game engine variables
	Sprite m_Sprite;
	Vector2f m_Position;
	Vector2f m_NextPosition;

	FloatRect m_Boundaries;

	//Entity type
	enum class EntityType { UNSPECIFIED, HERBIVORE, CARNIVORE };
	EntityType m_Type;

	//Entity priority
	enum class EntityPriority { DANGER, HUNGRY, THIRSTY, MATING, NONE };
	EntityPriority m_Priority;

	//Entity direction
	enum class EntityDirection { LEFT, RIGHT };
	EntityDirection m_Direction;

	//Internal states
	bool m_IsHungry;
	bool m_IsThirsty;
	bool m_IsMating;

	bool m_FoundWater;
	bool m_FoundFood;
	bool m_FoundDanger;

	//External states
	bool m_IsInDanger;
	bool m_IsHunting;

	bool m_IsDead;

	bool m_IsDrinking;
	bool m_IsEating;

	//Abstract states
	bool m_IsFlipped;

	//Entity clock
	float m_InternalClock;
	float m_Timer;

	//Visual sprites
	Sprite m_DangerSprite;
	Sprite m_HungerSprite;
	Sprite m_ThirstySprite;
	Sprite m_MatingSprite;

	//Vision circle
	CircleShape m_VisionCircle;

	//Closest entities and resources
	std::shared_ptr<Resource> m_ClosestWater;
	std::shared_ptr<Resource> m_ClosestFood;

	std::shared_ptr<Entity> m_ClosestEntity;
	std::shared_ptr<Entity> m_ClosestDanger;
	std::shared_ptr<Entity> m_ClosestPrey;

public:
	float m_IdleCooldown;
	float m_MateCooldown;
	Vector2f m_Resolution;

public:
	/*Constructors and Destructor*/
	 Entity();
	 Entity(Sprite sprite, Vector2f position, Vector2f resolution);
	~Entity();

	/*Getters and Setters*/
	//Type
	std::string getType();

	//Priority
	std::string getPriority();

	//Health
	void setHealth(float health);
	float getHealth();

	//Hunger
	void setHunger(float hunger);
	float getHunger();

	//Thirst
	void setThirst(float thirst);
	float getThirst();

	//Speed
	void setSpeed(float speed);
	float getSpeed();

	//Sprite
	void setSprite(Sprite sprite);
	Sprite getSprite();

	//Danger Sprite
	void setDangerSprite(Sprite sprite);
	Sprite getDangerSprite();

	//Hunger Sprite
	void setHungerSprite(Sprite sprite);
	Sprite getHungerSprite();

	//Thirsty Sprite
	void setThirstySprite(Sprite sprite);
	Sprite getThirstySprite();

	//Mating Sprite
	void setMatingSprite(Sprite sprite);
	Sprite getMatingSprite();

	//Vision Circle
	CircleShape getCircleShape();

	//Position
	void setPosition(Vector2f position);
	void setPosition(float x, float y);
	Vector2f getPosition();

	//Next Position
	void setNextPosition(Vector2f position);
	void setNextPosition(float x, float y);
	Vector2f getNextPosition();

	//Boundaries
	FloatRect getBoundaries();

	//State
	bool isHungry();
	void setIsHungry(bool set);

	bool isThirsty();
	void setIsThirsty(bool set);

	bool isInDanger();
	void setIsInDanger(bool set);

	bool isMating();
	void setIsMating(bool set);

	bool isHunting();
	void setIsHunting(bool set);

	bool isDead();

	bool isDrinking();
	void setIsDrinking(bool set);

	//Awareness
	bool foundFood();
	bool foundWater();
	bool foundDanger();

	void setFoundFood(bool set);
	void setFoundWater(bool set);
	void setFoundDanger(bool set);

	void setClosestEntity(std::shared_ptr<Entity> entity);
	std::shared_ptr<Entity> getClosestEntity();

	void setClosestDanger(std::shared_ptr<Entity> danger);
	std::shared_ptr<Entity> getClosestDanger();

	void setClosestPrey(std::shared_ptr<Entity> prey);
	std::shared_ptr<Entity> getClosestPrey();

	void setClosestWater(std::shared_ptr<Resource> water);
	std::shared_ptr<Resource> getClosestWater();

	void setClosestFood(std::shared_ptr<Resource> food);
	std::shared_ptr<Resource> getClosestFood();

	/*Events*/
	void death();
	void stateChange();

	/*Behavioural functions*/
	void behaviour(Time dt);

	//Various behaviour
	void idle(Time dt);
	void inDanger(Time dt);
	void thirsty(Time dt);
	void hungry(Time dt);
	void hunt(Time dt);
	void attack(Time dt, std::shared_ptr<Entity> prey);
	void matingCall(Time dt);

	bool mate(Time dt, std::shared_ptr<Entity> partner);

	//Consumption methods
	void eat(Time dt, std::shared_ptr<Resource> food);
	void drink(Time dt, std::shared_ptr<Resource> water);

	/*Update function*/
	void updateParameters(Time dt);
	void updatePriority();
	void update(Time dt);

	/*Friend classes declaration*/
	friend class Herbivore;
	friend class Carnivore;
};

