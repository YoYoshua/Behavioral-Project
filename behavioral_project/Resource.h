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

	//Constant variables
	const float DEFAULT_AMOUNT = 200;

public:
	/*Constructors and Destructor*/
	Resource();
	Resource(Sprite sprite, Vector2f position, Vector2f resolution);
	~Resource();

	/*Getters and Setters*/
	//Sprite
	void setSprite(Sprite sprite);
	Sprite getSprite();

	//Scale
	void setScale(float scale);
	float getScale();

	//Position
	void setPosition(Vector2f position);
	void setPosition(float x, float y);
	Vector2f getPosition();

	//Emptiness
	bool isEmpty();

	/*Updating functions*/
	void updateParameters(Time dt);

	/*Friend classes declaration*/
	friend class Water;
};

