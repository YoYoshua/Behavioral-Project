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
	m_Sprite.setOrigin(m_Sprite.getLocalBounds().width / 2, m_Sprite.getLocalBounds().height / 2);
	m_Sprite.setPosition(m_Position);
	m_Boundaries = m_Sprite.getGlobalBounds();

	m_Health = 100.0f;
	m_Hunger = 50.0f;
	m_Thirst = 50.0f;
	m_ReproductionValue = 0.f;
	m_Speed = 150;

	m_IsHungry = false;
	m_IsThirsty = false;
	m_IsMating = false;

	m_IsInDanger = false;
	m_IsHunting = false;
	m_IsDead = false;

	m_FoundFood = false;
	m_FoundWater = false;
	m_FoundDanger = false;

	m_Resolution = resolution;

	m_InternalClock = 0;
	m_IdleCooldown = 5.f;
	m_MateCooldown = 5.f;

	m_VisionCircle.setRadius(250);
	m_VisionCircle.setOrigin(250, 250);
	m_VisionCircle.setPosition(m_Position);
	m_VisionCircle.setOutlineColor(Color::Black);
	m_VisionCircle.setOutlineThickness(1);
	m_VisionCircle.setFillColor(Color::Transparent);

	m_ClosestDanger = nullptr;
	m_ClosestEntity = nullptr;
	m_ClosestFood = nullptr;
	m_ClosestWater = nullptr;
}

Herbivore::~Herbivore()
{
}
