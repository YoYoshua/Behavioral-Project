#pragma once
#include "SFML\Graphics.hpp"
#include "Water.h"
#include "Plant.h"

using namespace sf;

class Entity
{
private:
	/*Object variables*/
	//Object parameters
	float m_Health;

	float m_Hunger;
	float m_Thirst;

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

	Vector2f m_Resolution;

	//Entity type
	enum class EntityType { UNSPECIFIED, HERBIVORE, CARNIVORE };
	EntityType m_Type;

	//States
	bool m_IsHungry;
	bool m_IsThirsty;

	bool m_IsInDanger;
	bool m_IsHunting;

	bool m_IsDead;

	bool m_IsDrinking;

	bool m_FoundWater;
	bool m_FoundFood;
	bool m_FoundDanger;

	//Entity clock
	float m_InternalClock;
	float m_Timer;

	//Visual sprites
	Sprite m_DangerSprite;

	//Vision circle
	CircleShape m_VisionCircle;

public:
	/*Constructors and Destructor*/
	 Entity();
	 Entity(Sprite sprite, Vector2f position, Vector2f resolution);
	~Entity();

	/*Getters and Setters*/
	//Type
	String getType();

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

	/*Events*/
	void death();
	void stateChange();

	/*Update function*/
	void updateParameters(Time dt);
	virtual void update(Time dt);

	/*Friend classes declaration*/
	friend class Herbivore;
	friend class Carnivore;
};

