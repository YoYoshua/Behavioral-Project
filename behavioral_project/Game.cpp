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
	debugText.setCharacterSize(10);
	debugText.setFont(debugFont);
	debugText.setPosition(40, 40);


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
				srand((int)time(0) * dt.asMilliseconds() + 1 * 800 * herbivoreVector.size() + 5);
				herbivorePosition.x = rand() % (int)videoResolution.x;
				herbivorePosition.y = rand() % (int)videoResolution.y;
				factory.createHerbivore(herbivoreSprite, herbivorePosition, &herbivoreVector, videoResolution);
				herbivoreVector.back().setDangerSprite(dangerSprite);
			}

			//Creating new carnivore objects
			if (inputEvent.key.code == Keyboard::C)
			{
				srand((int)time(0) * dt.asMilliseconds() + 1 * 850 * carnivoreVector.size() + 5);
				carnivorePosition.x = rand() % (int)videoResolution.x;
				carnivorePosition.y = rand() % (int)videoResolution.y;
				factory.createCarnivore(carnivoreSprite, carnivorePosition, &carnivoreVector, videoResolution);
			}

			//Creating new water objects
			if (inputEvent.key.code == Keyboard::W)
			{
				srand((int)time(0) * dt.asMilliseconds() + 1 * 900 * waterVector.size() + 5);
				waterPosition.x = rand() % (int)videoResolution.x;
				waterPosition.y = rand() % (int)videoResolution.y;
				factory.createWater(waterSprite, waterPosition, &waterVector, videoResolution);
			}

			//Creating new plant objects
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

	//Updating carnivore vector
	if (!carnivoreVector.empty())
	{
		for (int i = 0; i <= carnivoreVector.size() - 1; i++)
		{
			carnivoreVector[i].update(dt);
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
	factory.clean(&herbivoreVector, &carnivoreVector, &waterVector, &plantVector);

	//Processing object logic
	logic.processLogic(&herbivoreVector, &carnivoreVector, &waterVector, &plantVector, dt);

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
			ssDebugMode << "Is thirsty: " << herbivoreVector[i].isThirsty() << std::endl;
			ssDebugMode << "Found water: " << herbivoreVector[i].foundWater() << std::endl;
			ssDebugMode << "Circle radius: " << herbivoreVector[i].getCircleShape().getRadius() << std::endl;
			ssDebugMode << "Length: " << logic.getLength() << std::endl;
			ssDebugMode << std::endl << std::endl;
			debugText.setString(ssDebugMode.str());

		}
	}

	if (!carnivoreVector.empty())
	{

		for (int i = 0; i <= carnivoreVector.size() - 1; i++)
		{
			ssDebugMode << "Carnivore object #" << i << std::endl;
			ssDebugMode << "Test subject properties:" << std::endl;
			ssDebugMode << "Health: " << carnivoreVector[i].getHealth() << std::endl;
			ssDebugMode << "Hunger: " << (int)carnivoreVector[i].getHunger() << std::endl;
			ssDebugMode << "Thirst: " << (int)carnivoreVector[i].getThirst() << std::endl;
			ssDebugMode << "Position: " << carnivoreVector[i].getPosition().x << ", " << carnivoreVector[i].getPosition().y << std::endl;
			ssDebugMode << "Next position: " << carnivoreVector[i].getNextPosition().x << ", " << carnivoreVector[i].getNextPosition().y << std::endl;
			ssDebugMode << "Speed: " << carnivoreVector[i].getSpeed() << std::endl;
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
			ssDebugMode << "Circle radius: " << waterVector[i].getCircleShape().getRadius() << std::endl;
			ssDebugMode << std::endl << std::endl;
			debugText.setString(ssDebugMode.str());

		}
	}

	if (!plantVector.empty())
	{
		for (int i = 0; i <= plantVector.size() - 1; i++)
		{
			ssDebugMode << "Plant object #" << i << std::endl;
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

	//Drawing background
	gameWindow.draw(backgroundSprite);

	//Drawing game objects
	if (!waterVector.empty())
	{
		for (int i = 0; i <= waterVector.size() - 1; i++)
		{
			gameWindow.draw(waterVector[i].getSprite());
			//gameWindow.draw(waterVector[i].getCircleShape());
		}
	}

	if (!plantVector.empty())
	{
		for (int i = 0; i <= plantVector.size() - 1; i++)
		{
			gameWindow.draw(plantVector[i].getSprite());
			//gameWindow.draw(plantVector[i].getCircleShape());
		}
	}

	if (!herbivoreVector.empty())
	{
		for (int i = 0; i <= herbivoreVector.size() - 1; i++)
		{
			gameWindow.draw(herbivoreVector[i].getSprite());
			//gameWindow.draw(herbivoreVector[i].getCircleShape());

			if (herbivoreVector[i].isInDanger())
			{
				gameWindow.draw(herbivoreVector[i].getDangerSprite());
			}
		}
	}

	if (!carnivoreVector.empty())
	{
		for (int i = 0; i <= carnivoreVector.size() - 1; i++)
		{
			gameWindow.draw(carnivoreVector[i].getSprite());
			//gameWindow.draw(carnivoreVector[i].getCircleShape());
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
