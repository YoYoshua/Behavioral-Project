#pragma once
#include "SFML\Graphics.hpp"

using namespace sf;

class Resource
{
private:
	/*Object variables*/
	//Object parameters
	float m_Amount;
	float m_Scale;
	bool m_IsEmpty;

	//Game enging variables
	Sprite m_Sprite;
	Vector2f m_Position;
	FloatRect m_Boundaries;
	Vector2f m_Resolution;

	//Resource type
	enum class ResourceType { UNDEFINED, WATER, PLANT, MEAT };
	ResourceType m_ResourceType;

	//Constant variables
	float DEFAULT_AMOUNT = 200;

	//Visibility circle
	CircleShape m_VisionCircle;

public:
	/*Constructors and Destructor*/
	Resource();
	Resource(Sprite sprite, Vector2f position, Vector2f resolution);
	~Resource();

	/*Getters and Setters*/
	//Sprite
	void setSprite(Sprite sprite);
	Sprite getSprite();

	//Vision Circle
	CircleShape getCircleShape();

	//Scale
	void setScale(float scale);
	float getScale();

	//Position
	void setPosition(Vector2f position);
	void setPosition(float x, float y);
	Vector2f getPosition();

	//Amount
	void setAmount(float amount);
	float getAmount();

	//Emptiness
	bool isEmpty();

	//Type
	std::string getType();

	/*Updating functions*/
	void updateParameters(Time dt);
	void update(Time dt);

	/*Friend classes declaration*/
	friend class Water;
	friend class Plant;
	friend class Meat;
};

