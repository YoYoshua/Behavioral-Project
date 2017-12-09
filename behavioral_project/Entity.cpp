#include "Entity.h"

/*Constructors and Destructor*/

Entity::Entity()
{
	m_Position.x = 0;
	m_Position.y = 0;

	m_NextPosition = m_Position;

	m_Health = 100.0f;
	m_Hunger = 50.0f;
	m_Thirst = 50.0f;
	m_Speed = 150;

	m_EntityState = EntityState::IDLE;
	m_IsDead = false;

	m_Resolution.x = 1980;
	m_Resolution.y = 1020;

	m_InternalClock = 0;
}

Entity::Entity(Sprite sprite, Vector2f position, Vector2f resolution)
{
	m_Position = position;
	m_NextPosition = m_Position;

	m_Sprite = sprite;
	m_Sprite.setOrigin(10, 10);
	m_Sprite.setPosition(m_Position);
	m_Boundaries = m_Sprite.getGlobalBounds();

	m_Health = 100.0f;
	m_Hunger = 50.0f;
	m_Thirst = 50.0f;
	m_Speed = 150;

	m_EntityState = EntityState::IDLE;
	m_IsDead = false;

	m_Resolution = resolution;

	m_InternalClock = 0;
}


Entity::~Entity()
{
}

/*Getters and Setters*/

//Health
void Entity::setHealth(float health)
{
	m_Health = health;
}

float Entity::getHealth()
{
	return m_Health;
}

//Hunger
void Entity::setHunger(float hunger)
{
	m_Hunger = hunger;
}

float Entity::getHunger()
{
	return m_Hunger;
}

//Thirst
void Entity::setThirst(float thirst)
{
	m_Thirst = thirst;
}

float Entity::getThirst()
{
	return m_Thirst;
}

//Speed
void Entity::setSpeed(float speed)
{
	m_Speed = speed;
}

float Entity::getSpeed()
{
	return m_Speed;
}

//Sprite
void Entity::setSprite(Sprite sprite)
{
	m_Sprite = sprite;
}

Sprite Entity::getSprite()
{
	return m_Sprite;
}

//Position
void Entity::setPosition(Vector2f position)
{
	m_Sprite.setPosition(position);
}

void Entity::setPosition(float x, float y)
{
	m_Sprite.setPosition(x, y);
}

Vector2f Entity::getPosition()
{
	return m_Sprite.getPosition();
}

//Next Position
void Entity::setNextPosition(Vector2f position)
{
	m_NextPosition = position;
}

void Entity::setNextPosition(float x, float y)
{
	m_NextPosition.x = x;
	m_NextPosition.y = y;
}

Vector2f Entity::getNextPosition()
{
	return m_NextPosition;
}

//Boundaries
FloatRect Entity::getBoundaries()
{
	return m_Boundaries;
}

//State
int Entity::getState()
{
	if (m_EntityState == EntityState::IDLE)
	{
		return 1;
	}
	else if (m_EntityState == EntityState::HUNGER)
	{
		return 2;
	}
	else if (m_EntityState == EntityState::THIRST)
	{
		return 3;
	}
	else
	{
		return 0;
	}
}

//Dead
bool Entity::isDead()
{
	return m_IsDead;
}

/*Events*/

void Entity::death()
{
	m_IsDead = true;
}

void Entity::stateChange()
{
	if (m_Hunger >= 75 && m_EntityState == EntityState::IDLE)
	{
		m_EntityState = EntityState::HUNGER;
	}
	else if (m_Thirst >= 75 && m_EntityState != EntityState::THIRST)
	{
		m_EntityState = EntityState::THIRST;
	}
	else if (m_Hunger < 75 && m_Thirst < 75 && m_EntityState != EntityState::IDLE)
	{
		m_EntityState = EntityState::IDLE;
	}
}

/*Updating*/

void Entity::updateParameters(Time dt)
{
	//Lowering parameters with passing time
	m_Hunger = m_Hunger + dt.asSeconds();
	m_Thirst = m_Thirst + dt.asSeconds() / 2;

	//Updating speed parameter according to hunger and thirst
	m_Speed = DEFAULT_SPEED - ((int)m_Hunger - 50) - ((int)m_Thirst - 50);

	/*Handling passing max parameters*/

	//Passing hunger
	if (m_Hunger >= MAX_HUNGER)
	{
		//Reducing HP
		m_Health = m_Health - dt.asSeconds();
		m_Hunger = 100;
	}

	//Passing thirst
	if (m_Thirst >= (MAX_THIRST * 3) / 4)
	{
		if (m_Thirst >= MAX_THIRST)
		{
			//Reducing HP
			m_Health = m_Health - dt.asSeconds() * 5;
			m_Thirst = 100;
		}
		else
		{
			//Reducing HP
			m_Health = m_Health - dt.asSeconds();
		}
	}

	//Passing HP points
	if (m_Health <= 0)
	{
		m_Health = 0;

		//Death event
		death();
	}
}
