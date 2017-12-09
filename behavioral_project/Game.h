#pragma once

#include <sstream>
#include <map>

#include "SFML\Graphics.hpp"
#include "Carnivore.h"
#include "Herbivore.h"
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

	Vector2f herbivorePosition;
	Texture herbivoreTexture;
	Sprite herbivoreSprite;
	std::vector<Herbivore> herbivoreVector;

	int herbivoreTotal = 0;

	Vector2f waterPosition;
	Texture waterTexture;
	Sprite waterSprite;
	std::vector<Water> waterVector;

	int waterTotal = 0;

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

