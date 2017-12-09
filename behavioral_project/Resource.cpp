#include "Resource.h"



Resource::Resource()
{
	m_Position.x = 0;
	m_Position.y = 0;

	m_Amount = DEFAULT_AMOUNT;

	m_Resolution.x = 1920;
	m_Resolution.y = 1080;

	m_Scale = m_Amount / DEFAULT_AMOUNT;

	m_IsEmpty = false;
}

Resource::Resource(Sprite sprite, Vector2f position, Vector2f resolution)
{
	m_Position = position;

	m_Sprite = sprite;
	m_Sprite.setOrigin(100, 100);
	m_Sprite.setPosition(m_Position);
	m_Boundaries = m_Sprite.getGlobalBounds();
	m_Amount = DEFAULT_AMOUNT;

	m_Resolution = resolution;

	m_Scale = m_Amount / DEFAULT_AMOUNT;

	m_IsEmpty = false;
}


Resource::~Resource()
{
}

/*Getters and Setters*/
//Sprite
void Resource::setSprite(Sprite sprite)
{
	m_Sprite = sprite;
}

Sprite Resource::getSprite()
{
	return m_Sprite;
}

//Scale
void Resource::setScale(float scale)
{
	m_Scale = scale;
}

float Resource::getScale()
{
	return m_Scale;
}

//Position
void Resource::setPosition(Vector2f position)
{
	m_Sprite.setPosition(position);
}

void Resource::setPosition(float x, float y)
{
	m_Sprite.setPosition(x, y);
}

Vector2f Resource::getPosition()
{
	return m_Sprite.getPosition();
}

//Emptiness
bool Resource::isEmpty()
{
	return m_IsEmpty;
}

/*Update functions*/
void Resource::updateParameters(Time dt)
{
	//Lowering parameters with passing time
	m_Amount = m_Amount - dt.asSeconds();
	m_Scale = m_Amount / DEFAULT_AMOUNT;

	//Handling passing the minimal parameters
	if (m_Amount <= 0)
	{
		m_IsEmpty = true;
		m_Amount = 0;
	}
}