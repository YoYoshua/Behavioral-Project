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

	m_IsFlipped = false;

	m_Resolution.x = 1980;
	m_Resolution.y = 1020;

	m_InternalClock = 0;
}

Entity::Entity(Sprite sprite, Vector2f position, Vector2f resolution)
{
	m_Position = position;
	m_NextPosition = m_Position;

	m_Type = EntityType::UNSPECIFIED;

	m_Sprite = sprite;
	m_Sprite.setOrigin(m_Sprite.getLocalBounds().width / 2, m_Sprite.getLocalBounds().height / 2);
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
	m_IdleCooldown = 0;

	m_VisionCircle.setRadius(150);
	m_VisionCircle.setOrigin(150, 150);
	m_VisionCircle.setPosition(m_Position);
	m_VisionCircle.setOutlineColor(Color::Black);
	m_VisionCircle.setOutlineThickness(1);
	m_VisionCircle.setFillColor(Color::Transparent);

	m_ClosestDanger = nullptr;
	m_ClosestEntity = nullptr;
	m_ClosestPrey = nullptr;
	m_ClosestFood = nullptr;
	m_ClosestWater = nullptr;
}


Entity::~Entity()
{
}

/*Getters and Setters*/

String Entity::getType()
{
	switch (m_Type)
	{
		case EntityType::UNSPECIFIED:
			return "UNSPECIFIED";

		case EntityType::CARNIVORE:
			return "CARNIVORE";
			
		case EntityType::HERBIVORE:
			return "HERBIVORE";

		default:
			return "UNSPECIFIED";
	}
}

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
	m_DangerSprite.setOrigin(m_Sprite.getLocalBounds().width / 2 - 30, m_Sprite.getLocalBounds().height / 2 + 30);
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

void Entity::setClosestEntity(std::shared_ptr<Entity> entity)
{
	m_ClosestEntity = entity;
}

std::shared_ptr<Entity> Entity::getClosestEntity()
{
	return m_ClosestEntity;
}

void Entity::setClosestDanger(std::shared_ptr<Entity> danger)
{
	m_ClosestDanger = danger;
}

std::shared_ptr<Entity> Entity::getClosestDanger()
{
	return m_ClosestDanger;
}

void Entity::setClosestPrey(std::shared_ptr<Entity> prey)
{
	m_ClosestPrey = prey;
}

std::shared_ptr<Entity> Entity::getClosestPrey()
{
	return m_ClosestPrey;
}

void Entity::setClosestWater(std::shared_ptr<Resource> water)
{
	m_ClosestWater = water;
}

std::shared_ptr<Resource> Entity::getClosestWater()
{
	return m_ClosestWater;
}

void Entity::setClosestFood(std::shared_ptr<Resource> food)
{
	m_ClosestFood = food;
}

std::shared_ptr<Resource> Entity::getClosestFood()
{
	return m_ClosestFood;
}


/*Events*/

void Entity::death()
{
	m_IsDead = true;
}

void Entity::stateChange()
{
	if (m_Hunger >= 50)
	{
		m_IsHungry = true;
	}
	else if (m_Hunger < 30)
	{
		m_IsHungry = false;
	}

	if (m_Thirst >= 50)
	{
		m_IsThirsty = true;
	}
	else if (m_Thirst < 30)
	{
		m_IsThirsty = false;
	}

	//Danger system
}

/*Behavioural functions*/
void Entity::behaviour(Time dt)
{
	if (isInDanger())
	{
		inDanger(dt);
	}
	else if(isThirsty() && !isInDanger())
	{
		thirsty(dt);
	}
	else if (isHungry() && !isThirsty() && !isInDanger())
	{
		hungry(dt);
	}
	else
	{
		idle(dt);
	}
}

void Entity::idle(Time dt)
{
	if ((int)m_InternalClock % 5 == 0 && m_IdleCooldown == 0.f)
	{
		srand(m_InternalClock * 1000 * dt.asMicroseconds());
		m_NextPosition.x = rand() % (int)m_Resolution.x;
		m_NextPosition.y = rand() % (int)m_Resolution.y;
	}
	m_IdleCooldown = m_IdleCooldown + dt.asSeconds();
	if (m_IdleCooldown >= 5.f)
	{
		m_IdleCooldown = 0.f;
	}
}

void Entity::inDanger(Time dt)
{
	Vector2f relativePosition;

	if (m_ClosestDanger != nullptr)
	{
		relativePosition.x = this->getPosition().x - m_ClosestDanger->getPosition().x;
		relativePosition.y = this->getPosition().y - m_ClosestDanger->getPosition().y;
		m_NextPosition = this->getPosition() + relativePosition;
	}
	else
	{
		idle(dt);
	}
}

void Entity::thirsty(Time dt)
{
	if (m_ClosestWater != nullptr)
	{
		m_NextPosition = m_ClosestWater->getPosition();
	}
	else
	{
		idle(dt);
	}
}

void Entity::hungry(Time dt)
{
	//TODO: Finding food mechanics
}

void Entity::reproduce(Time dt)
{
	//TODO: Reproduction mechanics
}

void Entity::hunt(Time dt)
{
	m_NextPosition = m_ClosestPrey->getPosition();
}

void Entity::attack(Time dt, std::shared_ptr<Entity> prey)
{
	prey->setHealth(prey->getHealth() - dt.asSeconds() * 5);
}

void Entity::eat(Time dt, std::shared_ptr<Resource> food)
{
	m_Hunger = m_Hunger - dt.asSeconds() * 4;
	food->setAmount(food->getAmount() - dt.asSeconds() * 4);
}

void Entity::drink(Time dt, std::shared_ptr<Resource> water)
{
	m_Thirst = m_Thirst - dt.asSeconds() * 4;
	water->setAmount(water->getAmount() - dt.asSeconds() * 4);
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

void Entity::update(Time dt)
{
	//Updating internal clock
	m_InternalClock = m_InternalClock + dt.asSeconds();

	//Updating entity parameters
	updateParameters(dt);

	//Setting actual state
	stateChange();

	//Setting behaviour
	behaviour(dt);

	//Updating position according to the m_NextPosition parameter
	if (m_NextPosition.x >= m_Resolution.x || m_NextPosition.x < 0)
	{
		srand(m_InternalClock * 1000 * dt.asMicroseconds());
		m_NextPosition.x = rand() % (int)m_Resolution.x;
	}

	if (m_NextPosition.y >= m_Resolution.y || m_NextPosition.y < 0)
	{
		srand(m_InternalClock * 1000 * dt.asMicroseconds());
		m_NextPosition.y = rand() % (int)m_Resolution.y;
	}

	if (m_NextPosition != getPosition())
	{
		//Flipping the sprite depending on next position
		if (m_NextPosition.x >= getPosition().x && abs(m_NextPosition.x - getPosition().x) > 1.f)
		{
			m_Direction = EntityDirection::RIGHT;
		}
		else
		{
			m_Direction = EntityDirection::LEFT;
		}

		//Below happens normalisation of movement vector
		Vector2f movement = getPosition() - m_NextPosition;

		float length = sqrt(movement.x * movement.x + movement.y * movement.y);

		Vector2f direction;
		direction.x = movement.x / length;
		direction.y = movement.y / length;

		Vector2f movementStep;
		movementStep.x = direction.x * dt.asSeconds() * m_Speed;
		movementStep.y = direction.y * dt.asSeconds() * m_Speed;

		//Updating direction of the sprite
		if (m_Direction == EntityDirection::RIGHT && m_IsFlipped == false)
		{
			m_Sprite.setScale(-1.f, 1.f);
			m_IsFlipped = true;
		}
		else if (m_Direction == EntityDirection::LEFT && m_IsFlipped == true)
		{
			m_Sprite.setScale(1.f, 1.f);
			m_IsFlipped = false;
		}

		//Updating position of the sprite 
		m_Sprite.setPosition(getPosition() - movementStep);
		m_DangerSprite.setPosition(getPosition() - movementStep);
		m_VisionCircle.setPosition(getPosition() - movementStep);
	}
}
