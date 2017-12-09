#pragma once
#include "SFML\Graphics.hpp"

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

	//State enumeration
	enum class EntityState
	{
		IDLE, HUNGER, THIRST, DANGER
	};

	EntityState m_EntityState;
	bool m_IsDead;

	//Entity clock
	float m_InternalClock;

public:
	/*Constructors and Destructor*/
	 Entity();
	 Entity(Sprite sprite, Vector2f position, Vector2f resolution);
	~Entity();

	/*Getters and Setters*/

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
	int getState();

	//Dead
	bool isDead();

	/*Events*/
	void death();
	void stateChange();

	/*Update function*/
	void updateParameters(Time dt);

	/*Friend classes declaration*/
	friend class Herbivore;
	friend class Carnivore;
};

