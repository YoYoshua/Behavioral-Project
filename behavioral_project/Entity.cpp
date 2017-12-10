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

	m_IsHungry = false;
	m_IsThirsty = false;

	m_IsInDanger = false;
	m_IsHunting = false;
	m_IsDead = false;

	m_FoundFood = false;
	m_FoundWater = false;
	m_FoundDanger = false;

	m_IsDrinking = false;

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

	m_IsHungry = false;
	m_IsThirsty = false;

	m_IsInDanger = false;
	m_IsHunting = false;
	m_IsDead = false;

	m_FoundFood = false;
	m_FoundWater = false;
	m_FoundDanger = false;

	m_Resolution = resolution;

	m_InternalClock = 0;

	m_VisionCircle.setRadius(150);
	m_VisionCircle.setOrigin(150, 150);
	m_VisionCircle.setPosition(m_Position);
	m_VisionCircle.setOutlineColor(Color::Black);
	m_VisionCircle.setOutlineThickness(1);
	m_VisionCircle.setFillColor(Color::Transparent);
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

//Danger Sprite
void Entity::setDangerSprite(Sprite sprite)
{
	m_DangerSprite = sprite;
	m_DangerSprite.setOrigin(5, 30);
	m_DangerSprite.setPosition(m_Position);
}

Sprite Entity::getDangerSprite()
{
	return m_DangerSprite;
}

//Vision Circle
CircleShape Entity::getCircleShape()
{
	return m_VisionCircle;
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

/*State*/
//Hungry
bool Entity::isHungry()
{
	return m_IsHungry;
}

void Entity::setIsHungry(bool set)
{
	m_IsHungry = set;
}

//Thirsty
bool Entity::isThirsty()
{
	return m_IsThirsty;
}

void Entity::setIsThirsty(bool set)
{
	m_IsThirsty= set;
}

//In Danger
bool Entity::isInDanger()
{
	return m_IsInDanger;
}

void Entity::setIsInDanger(bool set)
{
	m_IsInDanger = set;
}

//Hunting
bool Entity::isHunting()
{
	return m_IsHunting;
}

void Entity::setIsHunting(bool set)
{
	m_IsHunting = set;
}

//Drinking
bool Entity::isDrinking()
{
	return m_IsDrinking;
}

void Entity::setIsDrinking(bool set)
{
	m_IsDrinking = set;
}

//Dead
bool Entity::isDead()
{
	return m_IsDead;
}

//Awareness
bool Entity::foundFood()
{
	return m_FoundFood;
}

bool Entity::foundWater()
{
	return m_FoundWater;
}

bool Entity::foundDanger()
{
	return m_FoundDanger;
}

void Entity::setFoundFood(bool set)
{
	m_FoundFood = set;
}

void Entity::setFoundWater(bool set)
{
	m_FoundWater = set;
}

void Entity::setFoundDanger(bool set)
{
	m_FoundDanger = set;
}


/*Events*/

void Entity::death()
{
	m_IsDead = true;
}

void Entity::stateChange()
{
	if (m_Hunger >= 30)
	{
		m_IsHungry = true;
	}

	if (m_Thirst >= 30)
	{
		m_IsThirsty = true;
	}

	//Danger system
}

/*Updating*/

void Entity::updateParameters(Time dt)
{
	//Lowering parameters with passing time
	m_Hunger = m_Hunger + dt.asSeconds();
	m_Thirst = m_Thirst + dt.asSeconds() / 2;

	//Updating speed parameter according to hunger and thirst
	m_Speed = DEFAULT_SPEED - ((int)m_Hunger - 50) - ((int)m_Thirst - 50);

	//Healing
	if ((m_Hunger <= 60 || m_Thirst <= 60) && m_Hunger + m_Thirst != 0)
	{
		m_Health = m_Health + dt.asSeconds() * (120 / (m_Hunger + m_Thirst));
	}
	else if (m_Hunger + m_Thirst == 0)
	{
		m_Health = m_Health + dt.asSeconds() * 4;
	}

	/*Handling passing max parameters*/

	//Passing hunger
	if (m_Hunger >= MAX_HUNGER)
	{
		//Reducing HP
		m_Health = m_Health - dt.asSeconds() * 2;
		m_Hunger = 100;
	}
	else if (m_Hunger >= MAX_HUNGER *(3 / 4))
	{
		//Reducing HP
		m_Health = m_Health - dt.asSeconds();
	}

	if (m_Hunger < 0)
	{
		m_Hunger = 0;
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

	if (m_Thirst < 0)
	{
		m_Thirst = 0;
	}

	//Passing HP points
	if (m_Health <= 0)
	{
		m_Health = 0;

		//Death event
		death();
	}
	else if (m_Health > 100)
	{
		m_Health = 100;
	}
}
