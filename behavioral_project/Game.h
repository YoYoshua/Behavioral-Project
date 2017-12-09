#pragma once

#include <sstream>

#include "SFML\Graphics.hpp"
#include "ObjectFactory.h"

class Game
{
private:
	/*State related variables*/
	enum class State
	{
		PLAYING
	};
	
	State state;
	bool debugModeActive;

	/*Video related variables*/
	Vector2f videoResolution;

	//Object related variables
	//Herbivore
	Vector2f herbivorePosition;
	Texture herbivoreTexture;
	Sprite herbivoreSprite;
	std::vector<Herbivore> herbivoreVector;

	//Water
	Vector2f waterPosition;
	Texture waterTexture;
	Sprite waterSprite;
	std::vector<Water> waterVector;

	//Plant
	Vector2f plantPosition;
	Texture plantTexture;
	Sprite plantSprite;
	std::vector<Plant> plantVector;

	/*Text related variables*/
	Font debugFont;
	Text debugText;

	/*Event and clock related variables*/
	Event inputEvent;
	Clock clock;
	Time dt;

	/*Various objects*/
	ObjectFactory factory;

public:
	RenderWindow gameWindow;

	Game();
	~Game();

	void initialiseVariables();
	void handleInput();
	void updateScene();
	void drawScene();
};

