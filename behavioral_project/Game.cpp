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

	//Game window
	gameWindow.create(VideoMode(videoResolution.x, videoResolution.y), "BP", Style::Fullscreen);

	/*Text initialsation*/
	//Constructing and setting Font objects
	debugFont.loadFromFile("font/lucon.ttf");

	//Constructing and setting Text objects
	debugText.setCharacterSize(14);
	debugText.setFont(debugFont);
	debugText.setPosition(40, 40);


	/*Game objects initialisation*/
	//Herbivore
	herbivorePosition.x = videoResolution.x / 2;
	herbivorePosition.y = videoResolution.y / 2;

	herbivoreTexture.loadFromFile("graphics/herbivore.png");

	herbivoreSprite.setTexture(herbivoreTexture);

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
				srand((int)time(0) * dt.asMilliseconds() + 1 * 800 * herbivoreVector.size() + 5);
				herbivorePosition.x = rand() % (int)videoResolution.x;
				herbivorePosition.y = rand() % (int)videoResolution.y;
				factory.createHerbivore(herbivoreSprite, herbivorePosition, &herbivoreVector, videoResolution);
			}

			if (inputEvent.key.code == Keyboard::W)
			{
				srand((int)time(0) * dt.asMilliseconds() + 1 * 900 * waterVector.size() + 5);
				waterPosition.x = rand() % (int)videoResolution.x;
				waterPosition.y = rand() % (int)videoResolution.y;
				factory.createWater(waterSprite, waterPosition, &waterVector, videoResolution);
			}

			if (inputEvent.key.code == Keyboard::P)
			{
				srand((int)time(0) * dt.asMilliseconds() + 1 * 1000 * plantVector.size() + 5);
				plantPosition.x = rand() % (int)videoResolution.x;
				plantPosition.y = rand() % (int)videoResolution.y;
				factory.createPlant(plantSprite, plantPosition, &plantVector, videoResolution);
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
	//Updating herbivore vector
	if (!herbivoreVector.empty())
	{
		for (int i = 0; i <= herbivoreVector.size() - 1; i++)
		{
			herbivoreVector[i].update(dt);
		}
	}

	//Updating water vector
	if (!waterVector.empty())
	{
		for (int i = 0; i <= waterVector.size() - 1; i++)
		{
			waterVector[i].update(dt);
		}
	}

	//Updating plant vector
	if (!plantVector.empty())
	{
		for (int i = 0; i <= plantVector.size() - 1; i++)
		{
			plantVector[i].update(dt);
		}
	}
	
	//Cleaning dead objects
	factory.clean(&herbivoreVector, &waterVector, &plantVector);

	/*DEBUG MODE*/

	//Constructing and setting stringstreams for Debug Mode text display
	std::stringstream ssDebugMode;

	ssDebugMode << "Herbivore vector size: " << herbivoreVector.size() << std::endl;

	if (!herbivoreVector.empty())
	{

		for (int i = 0; i <= herbivoreVector.size() - 1; i++)
		{
			ssDebugMode << "Herbivore object #" << i << std::endl;
			ssDebugMode << "Test subject properties:" << std::endl;
			ssDebugMode << "Health: " << herbivoreVector[i].getHealth() << std::endl;
			ssDebugMode << "Hunger: " << (int)herbivoreVector[i].getHunger() << std::endl;
			ssDebugMode << "Thirst: " << (int)herbivoreVector[i].getThirst() << std::endl;
			ssDebugMode << "Position: " << herbivoreVector[i].getPosition().x << ", " << herbivoreVector[i].getPosition().y << std::endl;
			ssDebugMode << "Next position: " << herbivoreVector[i].getNextPosition().x << ", " << herbivoreVector[i].getNextPosition().y << std::endl;
			ssDebugMode << "Speed: " << herbivoreVector[i].getSpeed() << std::endl;
			ssDebugMode << "State: " << herbivoreVector[i].getState() << std::endl;
			ssDebugMode << std::endl << std::endl;
			debugText.setString(ssDebugMode.str());

		}
	}

	if (!waterVector.empty())
	{
		for (int i = 0; i <= waterVector.size() - 1; i++)
		{
			ssDebugMode << "Water object #" << i << std::endl;
			ssDebugMode << "Test subject properties:" << std::endl;
			ssDebugMode << "Position: " << waterVector[i].getPosition().x << ", " << waterVector[i].getPosition().y << std::endl;
			ssDebugMode << "Scale: " << waterVector[i].getScale() << std::endl;
			ssDebugMode << std::endl << std::endl;
			debugText.setString(ssDebugMode.str());

		}
	}

	if (!plantVector.empty())
	{
		for (int i = 0; i <= plantVector.size() - 1; i++)
		{
			ssDebugMode << "Water object #" << i << std::endl;
			ssDebugMode << "Test subject properties:" << std::endl;
			ssDebugMode << "Position: " << plantVector[i].getPosition().x << ", " << plantVector[i].getPosition().y << std::endl;
			ssDebugMode << "Scale: " << plantVector[i].getScale() << std::endl;
			ssDebugMode << std::endl << std::endl;
			debugText.setString(ssDebugMode.str());

		}
	}

}

void Game::drawScene()
{
	/*********************DRAW SCENE**************************/

	//Clearing scene
	gameWindow.clear();

	//Drawing game objects
	if (!waterVector.empty())
	{
		for (int i = 0; i <= waterVector.size() - 1; i++)
		{
			gameWindow.draw(waterVector[i].getSprite());
		}
	}

	if (!plantVector.empty())
	{
		for (int i = 0; i <= plantVector.size() - 1; i++)
		{
			gameWindow.draw(plantVector[i].getSprite());
		}
	}

	if (!herbivoreVector.empty())
	{
		for (int i = 0; i <= herbivoreVector.size() - 1; i++)
		{
			gameWindow.draw(herbivoreVector[i].getSprite());
		}
	}

	//Drawing text on scene
	if (debugModeActive)
	{
		gameWindow.draw(debugText);
	}
	
	//Displaying scene
	gameWindow.display();

}
