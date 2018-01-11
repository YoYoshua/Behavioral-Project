#include "Plant.h"


Plant::Plant(Sprite sprite, Vector2f position, Vector2f resolution)
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

	m_ResourceType = ResourceType::PLANT;

	m_VisionCircle.setRadius(50);
	m_VisionCircle.setOrigin(50, 50);
	m_VisionCircle.setPosition(m_Position);
	m_VisionCircle.setOutlineColor(Color::Black);
	m_VisionCircle.setOutlineThickness(1);
	m_VisionCircle.setFillColor(Color::Transparent);
}


Plant::~Plant()
{
}
