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

	herbivoreTexture.loadFromFile("graphics/herbivore.png");

	herbivoreSprite.setTexture(herbivoreTexture);

	//Carnivore
	carnivorePosition.x = videoResolution.x / 2;
	carnivorePosition.y = videoResolution.y / 2;

	carnivoreTexture.loadFromFile("graphics/carnivore.png");

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

	//Background
	backgroundPosition.x = videoResolution.x / 2;
	backgroundPosition.y = videoResolution.y / 2;

	backgroundTexture.loadFromFile("graphics/background.png");

	backgroundSprite.setTexture(backgroundTexture);

	//Danger sprite
	dangerTexture.loadFromFile("graphics/danger.png");
	dangerSprite.setTexture(dangerTexture);
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
	if (!entityVector.empty())
	{
		for (int i = 0; i <= eVectorSize - 1; i++)
		{
			entityVector[i]->update(dt);
		}
	}

	//Updating resource vector
	if (!resourceVector.empty())
	{
		for (int i = 0; i <= rVectorSize - 1; i++)
		{
			resourceVector[i]->update(dt);
		}
	}
	
	//Cleaning dead objects
	factory.clean(entityVector, resourceVector);

	//Processing object logic
	logic.processLogic(entityVector, resourceVector);

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
		ssDebugMode << "Entities size:" << eVectorSize << std::endl;
		ssDebugMode << "Resources size:" << rVectorSize << std::endl;

		if (eVectorSize)
		{
			for (int i = 0; i <= eVectorSize - 1; i++)
			{
				ssDebugMode << "Entity object #" << i << std::endl;
				ssDebugMode << "Test subject properties:" << std::endl;
				ssDebugMode << "Health: " << entityVector[i]->getHealth() << std::endl;
				ssDebugMode << "Hunger: " << (int)entityVector[i]->getHunger() << std::endl;
				ssDebugMode << "Thirst: " << (int)entityVector[i]->getThirst() << std::endl;
				ssDebugMode << "Position: " << entityVector[i]->getPosition().x << ", " << entityVector[i]->getPosition().y << std::endl;
				ssDebugMode << "Next position: " << entityVector[i]->getNextPosition().x << ", " << entityVector[i]->getNextPosition().y << std::endl;
				ssDebugMode << "Speed: " << entityVector[i]->getSpeed() << std::endl;
				ssDebugMode << "Circle radius: " << entityVector[i]->getCircleShape().getRadius() << std::endl;
				ssDebugMode << "Length: " << logic.getLength() << std::endl;
				ssDebugMode << std::endl << std::endl;
				debugText.setString(ssDebugMode.str());

			}
		}

		if (rVectorSize)
		{
			for (int i = 0; i <= rVectorSize - 1; i++)
			{
				ssDebugMode << "Resource object #" << i << std::endl;
				ssDebugMode << "Test subject properties:" << std::endl;
				ssDebugMode << "Position: " << resourceVector[i]->getPosition().x << ", " << resourceVector[i]->getPosition().y << std::endl;
				ssDebugMode << "Scale: " << resourceVector[i]->getScale() << std::endl;
				ssDebugMode << "Circle radius: " << resourceVector[i]->getCircleShape().getRadius() << std::endl;
				ssDebugMode << std::endl << std::endl;
				debugText.setString(ssDebugMode.str());

			}
		}
	}
}

void Game::drawScene()
{
	/*********************DRAW SCENE**************************/

	//Clearing scene
	gameWindow.clear();

	//Drawing background
	gameWindow.draw(backgroundSprite);

	//Drawing game objects
	if (!resourceVector.empty())
	{
		for (int i = 0; i <= rVectorSize - 1; i++)
		{
			gameWindow.draw(resourceVector[i]->getSprite());
			if (debugModeActive)
			{
				gameWindow.draw(resourceVector[i]->getCircleShape());
			}
		}
	}

	if (!entityVector.empty())
	{
		for (int i = 0; i <= eVectorSize - 1; i++)
		{
			gameWindow.draw(entityVector[i]->getSprite());
			if (debugModeActive)
			{
				gameWindow.draw(entityVector[i]->getCircleShape());
			}

			if (entityVector[i]->isInDanger())
			{
				gameWindow.draw(entityVector[i]->getDangerSprite());
			}
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
