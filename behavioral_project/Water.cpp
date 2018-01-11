#include "Water.h"


Water::Water(Sprite sprite, Vector2f position, Vector2f resolution)
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

	m_ResourceType = ResourceType::WATER;

	m_VisionCircle.setRadius(50);
	m_VisionCircle.setOrigin(50, 50);
	m_VisionCircle.setPosition(m_Position);
	m_VisionCircle.setOutlineColor(Color::Black);
	m_VisionCircle.setOutlineThickness(1);
	m_VisionCircle.setFillColor(Color::Transparent);
}

Water::~Water()
{
}

void Water::update(Time dt)
{
	//Updating parameters
	updateParameters(dt);

	//Changing object according to parameters
	m_Sprite.setScale(m_Scale, m_Scale);
	m_VisionCircle.setScale(m_Scale, m_Scale);
}
