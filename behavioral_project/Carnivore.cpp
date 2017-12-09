#include "Carnivore.h"



Carnivore::Carnivore()
{
	m_Position.x = 0;
	m_Position.y = 0;

	m_Health = 100.0f;
	m_Hunger = 50.0f;
	m_Thirst = 50.0f;
	m_Speed = 150;

	m_InternalClock = 0;
}


Carnivore::~Carnivore()
{
}

/*Behavioral functions*/

void Carnivore::behaviour(Time dt)
{
	if (m_EntityState == EntityState::IDLE)
	{
		idleBehaviour(dt);
	}
	else if (m_EntityState == EntityState::HUNGER)
	{
		//TO DO
		idleBehaviour(dt);
	}
	else if (m_EntityState == EntityState::THIRST)
	{
		//TO DO
		idleBehaviour(dt);
	}
}

void Carnivore::idleBehaviour(Time dt)
{
	if ((int)m_InternalClock % 5 == 0)
	{
		srand(m_InternalClock * 1000 * dt.asMicroseconds());
		m_NextPosition.x = rand() % (int)m_Resolution.x;
		m_NextPosition.y = rand() % (int)m_Resolution.y;
	}
}

/*Update function*/
void Carnivore::update(Time dt)
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
	}
}