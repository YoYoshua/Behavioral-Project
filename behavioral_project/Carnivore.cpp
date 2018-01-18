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

Carnivore::Carnivore(Sprite childSprite, Sprite adultSprite, std::string sex, Vector2f position, Vector2f resolution)
{
	m_Position = position;
	m_NextPosition = m_Position;

	m_Type = EntityType::CARNIVORE;

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
	m_MateCooldown = 2.f;

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

Carnivore::~Carnivore()
{
}