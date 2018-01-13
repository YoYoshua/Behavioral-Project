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
	Vector2i origin(0, 0);
	Vector2i size(76, 56);
	IntRect rectangle(origin, size);

	//Herbivore
	herbivorePosition.x = videoResolution.x / 2;
	herbivorePosition.y = videoResolution.y / 2;

	herbivoreTexture.loadFromFile("graphics/cow.png");

	herbivoreChildSprite.setTexture(herbivoreTexture);
	herbivoreChildSprite.setTextureRect(rectangle);

	rectangle.top = 56;

	herbivoreAdultSprite.setTexture(herbivoreTexture);
	herbivoreAdultSprite.setTextureRect(rectangle);

	//Carnivore
	rectangle.top = 0;
	rectangle.width = 78;

	carnivorePosition.x = videoResolution.x / 2;
	carnivorePosition.y = videoResolution.y / 2;

	carnivoreTexture.loadFromFile("graphics/lion.png");

	carnivoreChildSprite.setTexture(carnivoreTexture);
	carnivoreChildSprite.setTextureRect(rectangle);

	rectangle.top = 56;
	rectangle.height = 66;

	carnivoreAdultSprite.setTexture(carnivoreTexture);
	carnivoreAdultSprite.setTextureRect(rectangle);
	
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
	background.setPrimitiveType(Quads);

	int screenWidth = videoResolution.x / 80 + 1; 	//80 means tile size, + 1 because of int conversion causing black strips around edges
	int screenHeight = videoResolution.y / 80 + 1; 
	background.resize(screenWidth * screenHeight * 4);
	backgroundTexture.loadFromFile("graphics/backgroundTile.png");

	//Generating tile-based background
	int currentVertex = 0;

	for (int i = 0; i < screenWidth; i++)
	{
		for (int j = 0; j < screenHeight; j++)
		{
			//Set position
			background[currentVertex + 0].position = Vector2f(i * 80, j * 80);
			background[currentVertex + 1].position = Vector2f((i * 80) + 80, j * 80);
			background[currentVertex + 2].position = Vector2f((i * 80) + 80, (j * 80) + 80);
			background[currentVertex + 3].position = Vector2f(i * 80, (j * 80) + 80);

			//Set texture
			background[currentVertex + 0].texCoords = Vector2f(0, 0);
			background[currentVertex + 1].texCoords = Vector2f(80, 0);
			background[currentVertex + 2].texCoords = Vector2f(80, 80);
			background[currentVertex + 3].texCoords = Vector2f(0, 80);

			currentVertex = currentVertex + 4;
		}
	}

	//Needs sprite
	needsTexture.loadFromFile("graphics/needs.png");

	//Danger
	rectangle.left = 0;
	rectangle.top = 0;
	rectangle.width = 20;
	rectangle.height = 20;

	dangerSprite.setTexture(needsTexture);
	dangerSprite.setTextureRect(rectangle);

	//Mating
	rectangle.top = rectangle.top + 20;

	matingSprite.setTexture(needsTexture);
	matingSprite.setTextureRect(rectangle);

	//Hungry
	rectangle.top = rectangle.top + 20;

	hungrySprite.setTexture(needsTexture);
	hungrySprite.setTextureRect(rectangle);

	//Thirsty
	rectangle.top = rectangle.top + 20;

	thirstySprite.setTexture(needsTexture);
	thirstySprite.setTextureRect(rectangle);

	//Game speed
	gameSpeed = 1;

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
				entityVector.push_back(factory.createHerbivore(herbivoreChildSprite, herbivoreAdultSprite, herbivorePosition));

				//Setting icons
				(entityVector.back())->setDangerSprite(dangerSprite);
				(entityVector.back())->setHungerSprite(hungrySprite);
				(entityVector.back())->setThirstySprite(thirstySprite);
				(entityVector.back())->setMatingSprite(matingSprite);
			}

			//Creating new carnivore objects
			if (inputEvent.key.code == Keyboard::C)
			{
				srand((int)time(0) * dt.asMilliseconds() + 1 * 850 * entityVector.size() + 5);
				carnivorePosition.x = rand() % (int)videoResolution.x;
				carnivorePosition.y = rand() % (int)videoResolution.y;
				entityVector.push_back(factory.createCarnivore(carnivoreChildSprite, carnivoreAdultSprite, carnivorePosition));

				//Setting icons
				(entityVector.back())->setDangerSprite(dangerSprite);
				(entityVector.back())->setHungerSprite(hungrySprite);
				(entityVector.back())->setThirstySprite(thirstySprite);
				(entityVector.back())->setMatingSprite(matingSprite);
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

			//Changing game speed
			if (inputEvent.key.code == Keyboard::Num1)
			{
				gameSpeed = 1;
			}
			if (inputEvent.key.code == Keyboard::Num2)
			{
				gameSpeed = 2;
			}
			if (inputEvent.key.code == Keyboard::Num3)
			{
				gameSpeed = 3;
			}
			if (inputEvent.key.code == Keyboard::Num4)
			{
				gameSpeed = 4;
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
	dt = clock.restart() * gameSpeed;

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
			ssDebugMode << "Entity #: " << i << std::endl;
			ssDebugMode << "Type: " << p->getType() << std::endl;
			ssDebugMode << "Sex: " << p->getSex() << std::endl;
			ssDebugMode << "Age: " << (int)p->getAge() << std::endl;
			ssDebugMode << "HP: " << p->getHealth() << std::endl;
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
	gameWindow.draw(background, &backgroundTexture);

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

		//Drawing icon
		std::string priority;
		priority = p->getPriority();

		if (priority == "DANGER")
		{
			gameWindow.draw(p->getDangerSprite());
		}
		else if (priority == "THIRSTY")
		{
			gameWindow.draw(p->getThirstySprite());
		}
		else if (priority == "HUNGRY")
		{
			gameWindow.draw(p->getHungerSprite());
		}
		else if (priority == "MATING")
		{
			gameWindow.draw(p->getMatingSprite());
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
