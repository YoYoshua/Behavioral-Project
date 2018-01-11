#include "Game.h"

Game::Game()
{
}


Game::~Game()
{
}

void Game::initialiseVariables()
{
	/*Engine variables initialisation*/

	//Game states initialisation
	state = State::PLAYING;

	//Debug mode initialisation
	debugModeActive = 0;

	//Clock initialisation

	/*Video initialisation*/

	//Getting resolution parameters
	videoResolution.x = VideoMode::getDesktopMode().width;
	videoResolution.y = VideoMode::getDesktopMode().height;

	//Passing resolution to the ObjectFactory
	factory.setResolution(videoResolution);

	//Game window
	gameWindow.create(VideoMode(videoResolution.x, videoResolution.y), "BP", Style::Fullscreen);

	/*Text initialsation*/
	//Constructing and setting Font objects
	debugFont.loadFromFile("font/lucon.ttf");

	//Constructing and setting Text objects
	debugText.setCharacterSize(10);
	debugText.setFont(debugFont);
	debugText.setPosition(40, 40);

	fpsText.setCharacterSize(10);
	fpsText.setFont(debugFont);
	fpsText.setPosition(videoResolution.x - 80, 40);

	/*Game objects initialisation*/
	//Herbivore
	herbivorePosition.x = videoResolution.x / 2;
	herbivorePosition.y = videoResolution.y / 2;

	herbivoreTexture.loadFromFile("graphics/cow.png");

	herbivoreSprite.setTexture(herbivoreTexture);

	//Carnivore
	carnivorePosition.x = videoResolution.x / 2;
	carnivorePosition.y = videoResolution.y / 2;

	carnivoreTexture.loadFromFile("graphics/lion.png");

	carnivoreSprite.setTexture(carnivoreTexture);

	//Water
	waterPosition.x = videoResolution.x / 2;
	waterPosition.y = videoResolution.y / 2;

	waterTexture.loadFromFile("graphics/water.png");

	waterSprite.setTexture(waterTexture);

	//Plant
	plantPosition.x = videoResolution.x / 2;
	plantPosition.y = videoResolution.y / 2;

	plantTexture.loadFromFile("graphics/plant.png");

	plantSprite.setTexture(plantTexture);

	//Meat
	meatPosition.x = videoResolution.x / 2;
	meatPosition.y = videoResolution.y / 2;

	meatTexture.loadFromFile("graphics/meat.png");

	meatSprite.setTexture(meatTexture);
	factory.setMeatSprite(meatSprite);

	//Background
	backgroundPosition.x = videoResolution.x / 2;
	backgroundPosition.y = videoResolution.y / 2;

	backgroundTexture.loadFromFile("graphics/background.png");

	backgroundSprite.setTexture(backgroundTexture);

	//Needs sprite
	needsTexture.loadFromFile("graphics/needs.png");
	IntRect rectangle;
	Vector2i origin;
	Vector2i size(20, 20);

	//Danger
	origin.x = 0;
	origin.y = 0;
	rectangle = new IntRect(origin, size);
	dangerSprite.setTexture(needsTexture);
	dangerSprite.setTextureRect();
}

void Game::handleInput()
{
	/********************INPUT HANDLE*************************/

	/*Handling input by event*/
	while (gameWindow.pollEvent(inputEvent))
	{
		if (inputEvent.type == Event::KeyPressed)
		{
			//Toggling Debug Mode
			if (inputEvent.key.code == Keyboard::F1 && debugModeActive == 1)
			{
				debugModeActive = 0;
			}
			else if (inputEvent.key.code == Keyboard::F1 && debugModeActive == 0)
			{
				debugModeActive = 1;
			}

			//Creating new herbivore objects
			if (inputEvent.key.code == Keyboard::H)
			{
				srand((int)time(0) * dt.asMilliseconds() + 1 * 800 * entityVector.size() + 5);
				herbivorePosition.x = rand() % (int)videoResolution.x;
				herbivorePosition.y = rand() % (int)videoResolution.y;
				entityVector.push_back(factory.createHerbivore(herbivoreSprite, herbivorePosition));
				(entityVector.back())->setDangerSprite(dangerSprite);
			}

			//Creating new carnivore objects
			if (inputEvent.key.code == Keyboard::C)
			{
				srand((int)time(0) * dt.asMilliseconds() + 1 * 850 * entityVector.size() + 5);
				carnivorePosition.x = rand() % (int)videoResolution.x;
				carnivorePosition.y = rand() % (int)videoResolution.y;
				entityVector.push_back(factory.createCarnivore(carnivoreSprite, carnivorePosition));
				(entityVector.back())->setDangerSprite(dangerSprite);
			}

			//Creating new water objects
			if (inputEvent.key.code == Keyboard::W)
			{
				srand((int)time(0) * dt.asMilliseconds() + 1 * 900 * resourceVector.size() + 5);
				waterPosition.x = rand() % (int)videoResolution.x;
				waterPosition.y = rand() % (int)videoResolution.y;
				resourceVector.push_back(factory.createWater(waterSprite, waterPosition));
			}

			//Creating new plant objects
			if (inputEvent.key.code == Keyboard::P)
			{
				srand((int)time(0) * dt.asMilliseconds() + 1 * 1234 * resourceVector.size() + 5);
				plantPosition.x = rand() % (int)videoResolution.x;
				plantPosition.y = rand() % (int)videoResolution.y;
				resourceVector.push_back(factory.createPlant(plantSprite, plantPosition));
			}

			//Creating new meat objects
			if (inputEvent.key.code == Keyboard::M)
			{
				srand((int)time(0) * dt.asMilliseconds() + 1 * 413 * resourceVector.size() + 5);
				meatPosition.x = rand() % (int)videoResolution.x;
				meatPosition.y = rand() % (int)videoResolution.y;
				resourceVector.push_back(factory.createMeat(meatSprite, meatPosition));
			}
		}
	}


	/*Handling input by polling*/
	//Closing game
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		gameWindow.close();
	}
}

void Game::updateScene()
{
	/*********************UPDATE SCENE************************/

	//Updating delta time
	dt = clock.restart();

	/*Updating game objects*/
	//Getting vector sizes
	eVectorSize = entityVector.size();
	rVectorSize = resourceVector.size();

	//Updating entity vector
	for (auto p : entityVector)
	{
		p->update(dt);
	}

	//Updating resource vector
	for (auto p : resourceVector)
	{
		p->update(dt);
	}
	//Cleaning dead objects
	factory.clean(entityVector, resourceVector);

	//Processing object logic
	logic.processLogic(dt, entityVector, resourceVector);

	/*DEBUG MODE*/

	//Refreshing vector size
	eVectorSize = entityVector.size();
	rVectorSize = resourceVector.size();

	//Constructing and setting stringstream for FPS text display
	std::stringstream ssFPS;

	ssFPS << "FPS: " << 1.f / dt.asSeconds() << std::endl;
	fpsText.setString(ssFPS.str());

	//Constructing and setting stringstream for Debug Mode text display
	std::stringstream ssDebugMode;

	if (debugModeActive)
	{
		int i = 0;
		ssDebugMode << "Entities: " << entityVector.size() << std::endl;
		ssDebugMode << "Resources: " << resourceVector.size() << std::endl << std::endl;
		for (auto p : entityVector)
		{
			ssDebugMode << "Entity #:" << i << std::endl;
			ssDebugMode << "Type:" << p->getType() << std::endl;
			ssDebugMode << "Current position: " << p->getPosition().x << ", " << p->getPosition().y << std::endl;
			ssDebugMode << "Next position: " << p->getNextPosition().x << ", " << p->getNextPosition().y << std::endl;
			ssDebugMode << "Idle cooldown timer: " << p->m_IdleCooldown << std::endl;
			ssDebugMode << "HP: " << p->getHealth() << std::endl;
			ssDebugMode << "Hunger: " << p->getHunger() << std::endl;
			ssDebugMode << "Thirst: " << p->getThirst() << std::endl;
			ssDebugMode << "Is thirsty:" << p->isThirsty() << std::endl;
			ssDebugMode << "Is hungry:" << p->isHungry() << std::endl;
			ssDebugMode << "Is in danger:" << p->isInDanger() << std::endl;
			ssDebugMode << "Is hunting:" << p->isHunting() << std::endl << std::endl;
			i++;
		}

		i = 0;
		for (auto p : resourceVector)
		{
			ssDebugMode << "Resource #:" << i << std::endl;
			ssDebugMode << "Type:" << p->getType() << std::endl;
			ssDebugMode << "Current position: " << p->getPosition().x << ", " << p->getPosition().y << std::endl << std::endl;
			i++;
		}

		debugText.setString(ssDebugMode.str());
	}
}

void Game::drawScene()
{
	/*********************DRAW SCENE**************************/

	//Clearing scene
	gameWindow.clear();

	//Drawing background
	gameWindow.draw(backgroundSprite);

	/*Drawing game objects*/
	//Drawing resources
	for (auto p : resourceVector)
	{
		gameWindow.draw(p->getSprite());
		if (debugModeActive)
		{
			gameWindow.draw(p->getCircleShape());
		}
	}

	//Drawing entities
	for (auto p : entityVector)
	{
		gameWindow.draw(p->getSprite());
		if (debugModeActive)
		{
			gameWindow.draw(p->getCircleShape());
		}

		if (p->isInDanger())
		{
			gameWindow.draw(p->getDangerSprite());
		}
	}
	//Drawing text on scene
	if (debugModeActive)
	{
		gameWindow.draw(debugText);
	}

	gameWindow.draw(fpsText);
	
	//Displaying scene
	gameWindow.display();

}
