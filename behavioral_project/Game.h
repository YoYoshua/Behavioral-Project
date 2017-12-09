#pragma once
#include <sstream>

#include "SFML\Graphics.hpp"
#include "ObjectFactory.h"
#include "ObjectLogic.h"

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

	//Background
	Vector2f backgroundPosition;
	Texture backgroundTexture;
	Sprite backgroundSprite;

	/*Object related variables*/
	//Herbivore
	Vector2f herbivorePosition;
	Texture herbivoreTexture;
	Sprite herbivoreSprite;
	std::vector<Herbivore> herbivoreVector;

	//Carnivore
	Vector2f carnivorePosition;
	Texture carnivoreTexture;
	Sprite carnivoreSprite;
	std::vector<Carnivore> carnivoreVector;

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

	//Various textures
	Texture dangerTexture;
	Sprite dangerSprite;

	/*Text related variables*/
	Font debugFont;
	Text debugText;

	/*Event and clock related variables*/
	Event inputEvent;
	Clock clock;
	Time dt;

	/*Various objects*/
	ObjectFactory factory;
	ObjectLogic logic;

public:
	RenderWindow gameWindow;

	Game();
	~Game();

	void initialiseVariables();
	void handleInput();
	void updateScene();
	void drawScene();
};

