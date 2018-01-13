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

Entity::Entity(Sprite childSprite, Sprite adultSprite, std::string sex, Vector2f position, Vector2f resolution)
{
	m_Position = position;
	m_NextPosition = m_Position;

	m_Type = EntityType::UNSPECIFIED;

	if (sex == "MALE")
	{
		m_EntitySex = EntitySex::MALE;
	}
	else
	{
		m_EntitySex = EntitySex::FEMALE;
	}

	m_Sprite = childSprite;
	m_ChildSprite = childSprite;
	m_AdultSprite = adultSprite;
	m_Sprite.setOrigin(m_Sprite.getLocalBounds().width / 2, m_Sprite.getLocalBounds().height / 2);
	m_Sprite.setPosition(m_Position);
	m_Boundaries = m_Sprite.getGlobalBounds();

	m_Health = 100.0f;
	m_Hunger = 50.0f;
	m_Thirst = 50.0f;
	m_ReproductionValue = 0.f;

	m_Age = 0;
	m_AgeTimer = 0.f;

	m_Speed = 150;

	m_IsHungry = false;
	m_IsThirsty = false;
	m_IsMating = false;

	m_IsInDanger = false;
	m_IsHunting = false;

	m_IsDead = false;
	m_IsAdult = false;

	m_FoundFood = false;
	m_FoundWater = false;
	m_FoundDanger = false;

	m_Resolution = resolution;

	m_InternalClock = 0;
	m_IdleCooldown = 5.f;
	m_MateCooldown = 5.f;

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

std::string Entity::getType()
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

std::string Entity::getPriority()
{
	switch (m_Priority)
	{
	case EntityPriority::NONE:
		return "NONE";

	case EntityPriority::DANGER:
		return "DANGER";

	case EntityPriority::HUNGRY:
		return "HUNGRY";

	case EntityPriority::THIRSTY:
		return "THIRSTY";

	case EntityPriority::MATING:
		return "MATING";

	default:
		return "NONE";
	}
}

std::string Entity::getSex()
{
	switch (m_EntitySex)
	{
	case EntitySex::MALE:
		return "MALE";

	case EntitySex::FEMALE:
		return "FEMALE";

	default:
		return "ERROR";
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

//Age
void Entity::setAge(float age)
{
	m_Age = age;
}

float Entity::getAge()
{
	return m_Age;
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

Sprite Entity::getAdultSprite()
{
	return m_AdultSprite;
}

Sprite Entity::getChildSprite()
{
	return m_AdultSprite;
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

void Entity::setHungerSprite(Sprite sprite)
{
	m_HungerSprite = sprite;
	m_HungerSprite.setOrigin(m_Sprite.getLocalBounds().width / 2 - 30, m_Sprite.getLocalBounds().height / 2 + 30);
	m_HungerSprite.setPosition(m_Position);
}

Sprite Entity::getHungerSprite()
{
	return m_HungerSprite;
}

void Entity::setThirstySprite(Sprite sprite)
{
	m_ThirstySprite = sprite;
	m_ThirstySprite.setOrigin(m_Sprite.getLocalBounds().width / 2 - 30, m_Sprite.getLocalBounds().height / 2 + 30);
	m_ThirstySprite.setPosition(m_Position);
}

Sprite Entity::getThirstySprite()
{
	return m_ThirstySprite;
}

void Entity::setMatingSprite(Sprite sprite)
{
	m_MatingSprite = sprite;
	m_MatingSprite.setOrigin(m_Sprite.getLocalBounds().width / 2 - 30, m_Sprite.getLocalBounds().height / 2 + 30);
	m_MatingSprite.setPosition(m_Position);
}

Sprite Entity::getMatingSprite()
{
	return m_MatingSprite;
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
	m_Sprite.setPosition((int)x, (int)y);
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
	m_IsThirsty = set;
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

//Mating
bool Entity::isMating()
{
	return m_IsMating;
}

void Entity::setIsMating(bool set)
{
	m_IsMating = set;
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

		if (this->getType() == "CARNIVORE")
		{
			setIsHunting(true);
		}
	}
	else if (m_Hunger < 30)
	{
		m_IsHungry = false;

		if (this->getType() == "CARNIVORE")
		{
			setIsHunting(false);
		}
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
	if (m_ClosestDanger != nullptr)
	{
		m_IsInDanger = true;
	}
	else
	{
		m_IsInDanger = false;
	}

	//Mating system
	if (m_ReproductionValue == 100.f)
	{
		m_IsMating = true;
	}
	else
	{
		m_IsMating = false;
	}
}

/*Behavioural functions*/
void Entity::behaviour(Time dt)
{
	if (m_IsInDanger)
	{
		inDanger(dt);
	}
	else if(m_IsThirsty)
	{
		if (m_ClosestWater != nullptr)
		{
			thirsty(dt);
		}
		else if (m_IsHungry)
		{
			if (m_ClosestFood != nullptr)
			{
				hungry(dt);
			}
			else if (this->getType() == "CARNIVORE")
			{
				hunt(dt);
			}
			else
			{
				idle(dt);
			}
		}
	}
	else if(m_IsHungry)
	{
		if (m_ClosestFood != nullptr)
		{
			hungry(dt);
		}
		else if (this->getType() == "CARNIVORE")
		{
			hunt(dt);
		}
		else
		{
			idle(dt);
		}
	}
	else if (m_IsMating)
	{
		matingCall(dt);
	}
	else
	{
		idle(dt);
	}
}

void Entity::idle(Time dt)
{
	//Every five seconds get new position 
	if (m_IdleCooldown >= 5.f)
	{
		srand(m_InternalClock * 1000 * dt.asMicroseconds());
		m_NextPosition.x = rand() % (int)m_Resolution.x;
		m_NextPosition.y = rand() % (int)m_Resolution.y;
		m_IdleCooldown = 0.f;
	}
	else if (m_IdleCooldown >= 0.f && m_IdleCooldown < 5.f)
	{
		m_IdleCooldown += dt.asSeconds();
	}
}

void Entity::inDanger(Time dt)
{
	Vector2f relativePosition;

	if (m_ClosestDanger != nullptr)
	{
		//Forget about food and water sources
		if (m_ClosestFood != nullptr)
		{
			m_ClosestFood = nullptr;
		}
		if (m_ClosestWater != nullptr)
		{
			m_ClosestWater = nullptr;
		}

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
	m_NextPosition = m_ClosestWater->getPosition();
}

void Entity::hungry(Time dt)
{
	m_NextPosition = m_ClosestFood->getPosition();
}

void Entity::hunt(Time dt)
{
	//Hunting only when adult
	if (m_ClosestPrey != nullptr && m_IsAdult)
	{
		m_NextPosition = m_ClosestPrey->getPosition();
	}
	else
	{
		idle(dt);
	}
}

void Entity::attack(Time dt, std::shared_ptr<Entity> prey)
{
	prey->setHealth(prey->getHealth() - dt.asSeconds() * 5);
}

void Entity::matingCall(Time dt)
{
	if (m_ClosestEntity != nullptr && m_ClosestEntity->getType() == this->getType() && m_ClosestEntity->getPriority() == "MATING" && this->getSex() != m_ClosestEntity->getSex())
	{
		m_NextPosition = m_ClosestEntity->getPosition();
	}
	else
	{
		idle(dt);
	}
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

bool Entity::mate(Time dt, std::shared_ptr<Entity> partner)
{
	//After five seconds finish mating
	if (m_MateCooldown <= 0.f)
	{
		//finish mating
		m_MateCooldown = 2.f;
		this->m_ReproductionValue = 0.f;
		partner->m_ReproductionValue = 0.f;
		return true;
	}
	else if (m_MateCooldown > 0.f && m_MateCooldown <= 5.f)
	{
		m_MateCooldown -= dt.asSeconds();
		return false;
	}
}

/*Updating*/

void Entity::updateParameters(Time dt)
{
	//Changing parameters with passing time
	m_Hunger = m_Hunger + dt.asSeconds();
	m_Thirst = m_Thirst + dt.asSeconds() / 2;

	//Raising reproduction value for adults
	if (m_IsAdult)
	{
		m_ReproductionValue = m_ReproductionValue + dt.asSeconds() * 4;
	}

	//Aging
	m_AgeTimer = m_AgeTimer + dt.asSeconds();

	//Updating age every 60 seconds
	if (m_AgeTimer >= 60.f)
	{
		m_Age = m_Age + 1;
		m_AgeTimer = 0.f;

		//Adulthood at age 5
		if (m_Age == 3 && !m_IsAdult)
		{
			m_IsAdult = true;

			m_AdultSprite.setPosition(m_Sprite.getPosition());
			m_AdultSprite.setOrigin(m_AdultSprite.getLocalBounds().width / 2, m_AdultSprite.getLocalBounds().height / 2);
			m_Sprite = m_AdultSprite;
		}

		//Random chance of dying of age
		float value = (float)rand() / RAND_MAX;

		if (m_Age < 5 && value < 0.01) //Chance of dying is 1% at age [0, 5]
		{
			death();
		}
		else if (m_Age >= 5 && m_Age < 10 && value < 0.05) //Chance of dying is 5% at age [5, 10]
		{
			death();
		}
		else if (m_Age >= 10 && m_Age < 20 && value < 0.25) //Chance of dying is 25% at age [10, 20]
		{
			death();
		}
		else if (m_Age >= 20 && m_Age < 30 && value < 0.5) //Chance of dying is 50% at age [20, 30]
		{
			death();
		}
		else if (m_Age > 30 && value < 0.95) //Chance of dying is 95% at age below 30
		{
			death();
		}
	}

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

	//Passing reproduction value
	if (m_ReproductionValue >= 100.f)
	{
		m_ReproductionValue = 100.f;
	}
}

void Entity::updatePriority()
{
	if (m_IsInDanger)
	{
		m_Priority = EntityPriority::DANGER;
	}
	else if (m_IsThirsty && !m_IsInDanger)
	{
		m_Priority = EntityPriority::THIRSTY;
	}
	else if (m_IsHungry && !m_IsThirsty && !m_IsInDanger)
	{
		m_Priority = EntityPriority::HUNGRY;
	}
	else if (m_IsMating && !m_IsHungry && !m_IsThirsty && !m_IsInDanger)
	{
		m_Priority = EntityPriority::MATING;
	}
	else
	{
		m_Priority = EntityPriority::NONE;
	}

}

void Entity::updatePosition(Time dt)
{
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
		if (m_NextPosition.x >= getPosition().x && abs(m_NextPosition.x - getPosition().x) > 5.f)
		{
			m_Direction = EntityDirection::RIGHT;
		}
		else if (m_NextPosition.x < getPosition().x && abs(m_NextPosition.x - getPosition().x) > 5.f)
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

		//Updating position of the sprite and icons
		m_Sprite.setPosition(getPosition() - movementStep);

		//Converting to int
		m_Sprite.setPosition(getPosition().x, getPosition().y);

		m_DangerSprite.setPosition(getPosition() - movementStep);
		m_HungerSprite.setPosition(getPosition() - movementStep);
		m_ThirstySprite.setPosition(getPosition() - movementStep);
		m_MatingSprite.setPosition(getPosition() - movementStep);

		m_VisionCircle.setPosition(getPosition() - movementStep);
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

	//Updating entity priority
	updatePriority();

	//Setting behaviour
	behaviour(dt);

	//Updating position
	updatePosition(dt);
}
