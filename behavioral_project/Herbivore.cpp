#include "Herbivore.h"

Herbivore::Herbivore()
{
	m_Position.x = 0;
	m_Position.y = 0;

	m_Health = 100.0f;
	m_Hunger = 50.0f;
	m_Thirst = 50.0f;
	m_Speed = 150;

	m_InternalClock = 0;
}

Herbivore::Herbivore(Sprite sprite, Vector2f position, Vector2f resolution)
{
	m_Position = position;
	m_NextPosition = m_Position;

	m_Type = EntityType::HERBIVORE;

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

Herbivore::~Herbivore()
{
}

/*Behavioral functions*/

void Herbivore::behaviour(Time dt)
{
	if (!isInDanger())
	{
		idleBehaviour(dt);
	}
}

void Herbivore::idleBehaviour(Time dt)
{
	if ((int)m_InternalClock % 5 == 0)
	{
		srand(m_InternalClock * 1000 * dt.asMicroseconds());
		m_NextPosition.x = rand() % (int)m_Resolution.x;
		m_NextPosition.y = rand() % (int)m_Resolution.y;
	}
}

void Herbivore::drinkWater(Water *water, Time dt)
{
	m_Thirst = m_Thirst - dt.asSeconds() * 4;
	water->setAmount(water->getAmount() - dt.asSeconds() * 4);
}

void Herbivore::eatFood(Plant *plant, Time dt)
{
	m_Hunger = m_Hunger - dt.asSeconds() * 4;
	plant->setAmount(plant->getAmount() - dt.asSeconds() * 4);
}

/*Update function*/
void Herbivore::update(Time dt)
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
		//Below happens normalisation of movement vector
		Vector2f movement = getPosition() - m_NextPosition;

		float length = sqrt(movement.x * movement.x + movement.y * movement.y);

		Vector2f direction;
		direction.x = movement.x / length;
		direction.y = movement.y / length;

		Vector2f movementStep;
		movementStep.x = direction.x * dt.asSeconds() * m_Speed;
		movementStep.y = direction.y * dt.asSeconds() * m_Speed;

		//Updating position of the sprite 
		m_Sprite.setPosition(getPosition() - movementStep);
		m_DangerSprite.setPosition(getPosition() - movementStep);
		m_VisionCircle.setPosition(getPosition() - movementStep);
	}
}
