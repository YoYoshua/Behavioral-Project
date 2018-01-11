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
	m_Sprite.setOrigin(m_Sprite.getLocalBounds().width / 2, m_Sprite.getLocalBounds().height / 2);
	m_Sprite.setPosition(m_Position);
	m_Boundaries = m_Sprite.getGlobalBounds();
	m_Amount = DEFAULT_AMOUNT;

	m_Resolution = resolution;

	m_Scale = m_Amount / DEFAULT_AMOUNT;

	m_IsEmpty = false;

	m_ResourceType = ResourceType::UNDEFINED;

	m_VisionCircle.setRadius(50);
	m_VisionCircle.setOrigin(50, 50);
	m_VisionCircle.setPosition(m_Position);
	m_VisionCircle.setOutlineColor(Color::Black);
	m_VisionCircle.setOutlineThickness(1);
	m_VisionCircle.setFillColor(Color::Transparent);
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

//Vision Circle
CircleShape Resource::getCircleShape()
{
	return m_VisionCircle;
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

//Amount
void Resource::setAmount(float amount)
{
	m_Amount = amount;
}

float Resource::getAmount()
{
	return m_Amount;
}

//Emptiness
bool Resource::isEmpty()
{
	return m_IsEmpty;
}

std::string Resource::getType()
{
	switch (m_ResourceType)
	{
		case ResourceType::MEAT:
			return "MEAT";

		case ResourceType::PLANT:
			return "PLANT";

		case ResourceType::WATER:
			return "WATER";

		default:
			return "UNDEFINED";
	}
}

/*Update functions*/
void Resource::updateParameters(Time dt)
{
	//Lowering parameters with passing time
	m_Scale = m_Amount / DEFAULT_AMOUNT;

	//Handling passing the minimal parameters
	if (m_Amount <= 0)
	{
		m_IsEmpty = true;
		m_Amount = 0;
	}
}

void Resource::update(Time dt)
{
}
