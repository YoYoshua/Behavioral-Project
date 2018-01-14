#include "Game.h"

Game::Game()
{
}


Game::~Game()
{
}

void Game::initialiseVariables()
{
	//Rectangle for sprites
	IntRect rectangle(0, 0, 0, 0);

	/*Engine variables initialisation*/

	//Game states initialisation
	state = State::SPLASH;

	//Debug mode initialisation
	debugModeActive = 0;

	/*Video initialisation*/

	//Getting resolution parameters
	videoResolution.x = VideoMode::getDesktopMode().width;
	videoResolution.y = VideoMode::getDesktopMode().height;

	//Game window
	gameWindow.create(VideoMode(videoResolution.x, videoResolution.y), "BP", Style::Fullscreen);

	/*Splashscreen and menu*/
	//Splashscreen
	splashscreenTexture.loadFromFile("graphics/splashscreen.png");
	splashscreenSprite.setTexture(splashscreenTexture);

	splashscreenSprite.setScale(videoResolution.x / splashscreenSprite.getLocalBounds().width,
		videoResolution.x / splashscreenSprite.getLocalBounds().width);  //Scale according to resolution

	splashscreenSprite.setOrigin(splashscreenSprite.getLocalBounds().width / 2, splashscreenSprite.getLocalBounds().height / 2);
	splashscreenSprite.setPosition(videoResolution.x / 2, videoResolution.y / 2);
	splashscreenSprite.setColor(sf::Color(255, 255, 255, alpha));

	//Menu
	menuFont.loadFromFile("font/ARCADECLASSIC.ttf");


	//Title
	titleText.setFont(menuFont);
	titleText.setString("ECOSIM");
	titleText.setCharacterSize(150);

	titleText.setOutlineColor(Color::Black);
	titleText.setOutlineThickness(2);
	titleText.setFillColor(Color::White);

	titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
	titleText.setPosition(videoResolution.x / 2, videoResolution.y / 5);

	//Play buttons
	playText.setFont(menuFont);
	playText.setString("PLAY");
	playText.setCharacterSize(100);

	playText.setFillColor(Color::White);

	playText.setOrigin(playText.getLocalBounds().width / 2, playText.getLocalBounds().height / 2);
	playText.setPosition(videoResolution.x / 2, videoResolution.y / 2);

	//Help buttons
	helpText.setFont(menuFont);
	helpText.setString("HELP");
	helpText.setCharacterSize(100);

	helpText.setFillColor(Color::White);

	helpText.setOrigin(helpText.getLocalBounds().width / 2, helpText.getLocalBounds().height / 2);
	helpText.setPosition(videoResolution.x / 2, playText.getPosition().y + 100);

	//Exit buttons
	exitText.setFont(menuFont);
	exitText.setString("EXIT");
	exitText.setCharacterSize(100);

	exitText.setFillColor(Color::White);

	exitText.setOrigin(exitText.getLocalBounds().width / 2, exitText.getLocalBounds().height / 2);
	exitText.setPosition(videoResolution.x / 2, helpText.getPosition().y + 100);

	/*Help*/
	//Help sprite
	helpTexture.loadFromFile("graphics/help.png");
	helpSprite.setTexture(helpTexture);

	helpSprite.setScale(videoResolution.x / helpSprite.getLocalBounds().width,
		videoResolution.x /helpSprite.getLocalBounds().width);  //Scale according to resolution

	helpSprite.setOrigin(helpSprite.getLocalBounds().width / 2, helpSprite.getLocalBounds().height / 2);
	helpSprite.setPosition(videoResolution.x / 2, videoResolution.y / 2);

	//Thanks button
	thanksText.setFont(menuFont);
	thanksText.setString("THANKS!");
	thanksText.setCharacterSize(100);

	thanksText.setFillColor(Color::White);

	thanksText.setOrigin(thanksText.getLocalBounds().width / 2, thanksText.getLocalBounds().height / 2);
	thanksText.setPosition(videoResolution.x / 2, 4*(videoResolution.y/5));

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

	//Carnivore
	carnivorePosition.x = videoResolution.x / 2;
	carnivorePosition.y = videoResolution.y / 2;

	carnivoreTexture.loadFromFile("graphics/lion.png");
	
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
	rectangle.top = 0;
	rectangle.left = 0;
	rectangle.height = 20;
	rectangle.width = 20;

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

	/*Object factory*/
	//Set factory
	factory.setTextures(&herbivoreTexture, &carnivoreTexture);
	factory.setResolution(videoResolution);

	/*Object logic*/
	//Assign factory
	logic.setFactory(&factory);

	/*Creating objects for menu*/
	//Herbivores
	for (int i = 0; i <= 2; i++)
	{
		//Herbivores
		srand((int)time(0) * dt.asMilliseconds() + 1 * 800 * entityVector.size() + 5);
		herbivorePosition.x = rand() % (int)videoResolution.x;
		herbivorePosition.y = rand() % (int)videoResolution.y;
		entityVector.push_back(factory.createHerbivore(herbivorePosition));

		//Setting icons
		(entityVector.back())->setDangerSprite(dangerSprite);
		(entityVector.back())->setHungerSprite(hungrySprite);
		(entityVector.back())->setThirstySprite(thirstySprite);
		(entityVector.back())->setMatingSprite(matingSprite);

		//Carnivores
		srand((int)time(0) * dt.asMilliseconds() + 1 * 850 * entityVector.size() + 5);
		carnivorePosition.x = rand() % (int)videoResolution.x;
		carnivorePosition.y = rand() % (int)videoResolution.y;
		entityVector.push_back(factory.createCarnivore(carnivorePosition));

		//Setting icons
		(entityVector.back())->setDangerSprite(dangerSprite);
		(entityVector.back())->setHungerSprite(hungrySprite);
		(entityVector.back())->setThirstySprite(thirstySprite);
		(entityVector.back())->setMatingSprite(matingSprite);

		//Plants
		srand((int)time(0) * dt.asMilliseconds() + 1 * 1234 * resourceVector.size() + 5);
		plantPosition.x = rand() % (int)videoResolution.x;
		plantPosition.y = rand() % (int)videoResolution.y;
		resourceVector.push_back(factory.createPlant(plantSprite, plantPosition));

		//Water
		srand((int)time(0) * dt.asMilliseconds() + 1 * 900 * resourceVector.size() + 5);
		waterPosition.x = rand() % (int)videoResolution.x;
		waterPosition.y = rand() % (int)videoResolution.y;
		resourceVector.push_back(factory.createWater(waterSprite, waterPosition));

		//Meat
		srand((int)time(0) * dt.asMilliseconds() + 1 * 413 * resourceVector.size() + 5);
		meatPosition.x = rand() % (int)videoResolution.x;
		meatPosition.y = rand() % (int)videoResolution.y;
		resourceVector.push_back(factory.createMeat(meatSprite, meatPosition));

	}


}

void Game::handleInput()
{
	/********************INPUT HANDLE*************************/

	/*Handling input by event*/
	while (gameWindow.pollEvent(inputEvent))
	{
		/*Game input*/
		if (state == State::PLAYING)
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
					entityVector.push_back(factory.createHerbivore(herbivorePosition));

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
					entityVector.push_back(factory.createCarnivore(carnivorePosition));

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
				if (inputEvent.key.code == Keyboard::Num0)
				{
					gameSpeed = 0;
				}
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

		/*Splashscreen input*/
		if (state == State::SPLASH)
		{
			if (inputEvent.type == Event::KeyPressed)
			{
				if (inputEvent.key.code == Keyboard::Return && fadein)
				{
					fadein = false;
				}
				else if (inputEvent.key.code == Keyboard::Return && !fadein)
				{
					fadeout = true;
				}
			}
		}

		/*Menu input*/
		if (state == State::MENU)
		{
			//Hovering over buttons
			if (inputEvent.type == Event::MouseMoved)
			{
				//Play button
				if (isPointOverText(Vector2f(inputEvent.mouseMove.x, inputEvent.mouseMove.y), playText))
				{
					playText.setFillColor(Color::Yellow);
				}
				else
				{
					playText.setFillColor(Color::White);
				}

				//Help button
				if (isPointOverText(Vector2f(inputEvent.mouseMove.x, inputEvent.mouseMove.y), helpText))
				{
					helpText.setFillColor(Color::Yellow);
				}
				else
				{
					helpText.setFillColor(Color::White);
				}

				//Exit button
				if (isPointOverText(Vector2f(inputEvent.mouseMove.x, inputEvent.mouseMove.y), exitText))
				{
					exitText.setFillColor(Color::Yellow);
				}
				else
				{
					exitText.setFillColor(Color::White);
				}
			}

			//Clicking
			if (inputEvent.type == Event::MouseButtonPressed)
			{
				//Play button
				if (inputEvent.mouseButton.button == Mouse::Button::Left && isPointOverText(Vector2f(inputEvent.mouseButton.x, inputEvent.mouseButton.y), playText))
				{
					//Clear background objects if opening game for the first time
					if (!backgroundObjectsCleared)
					{
						entityVector.clear();
						resourceVector.clear();
						backgroundObjectsCleared = true;
					}

					//Change game state
					gameSpeed = 1;
					state = State::PLAYING;
				}

				//Help button
				if (inputEvent.mouseButton.button == Mouse::Button::Left && isPointOverText(Vector2f(inputEvent.mouseButton.x, inputEvent.mouseButton.y), helpText))
				{
					state = State::HELP;
				}

				//Exit button
				if (inputEvent.mouseButton.button == Mouse::Button::Left && isPointOverText(Vector2f(inputEvent.mouseButton.x, inputEvent.mouseButton.y), exitText))
				{
					gameWindow.close();
				}

			}
		}

		/*Help input*/
		if (state == State::HELP)
		{
			//Hovering over button
			if (inputEvent.type == Event::MouseMoved)
			{
				//Thanks button
				if (isPointOverText(Vector2f(inputEvent.mouseMove.x, inputEvent.mouseMove.y), thanksText))
				{
					thanksText.setFillColor(Color::Yellow);
				}
				else
				{
					thanksText.setFillColor(Color::White);
				}
			}

			//Clicking button
			if (inputEvent.type == Event::MouseButtonPressed)
			{
				//Thanks button
				if (inputEvent.mouseButton.button == Mouse::Button::Left && isPointOverText(Vector2f(inputEvent.mouseButton.x, inputEvent.mouseButton.y), thanksText))
				{
					//Go back to menu
					state = State::MENU;
				}
			}
		}
	}


	/*Handling input by polling*/
	//Getting back to the menu
	if (Keyboard::isKeyPressed(Keyboard::Escape) && state == State::PLAYING)
	{
		gameSpeed = 0;
		state = State::MENU;
	}
}

void Game::updateScene()
{
	/*********************UPDATE SCENE************************/

	//Updating delta time
	dt = clock.restart() * gameSpeed;

	/*Updating game objects*/
	if (state != State::SPLASH)
	{
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
}

void Game::drawScene()
{
	/*********************DRAW SCENE**************************/

	//Clearing scene
	gameWindow.clear();

	//Draw splashscreen
	if (state == State::SPLASH)
	{
		filterTimer += dt.asSeconds();
		//Fade in
		if (!fadeout && (alpha < 255) && filterTimer >= filterDelay)
		{
			alpha += 1;
			splashscreenSprite.setColor(sf::Color(255, 255, 255, alpha));
			filterTimer = 0.f;
		}
		//Finishing fade in
		if (fadein && alpha == 255)
		{
			fadein = false;
		}
		//Skipping fade in
		if (!fadein && !fadeout)
		{
			alpha = 255;
			splashscreenSprite.setColor(sf::Color(255, 255, 255, alpha));
			filterTimer = 0.f;
		}
		//Fade out
		else if (fadeout && alpha > 0 && filterTimer >= filterDelay)
		{
			alpha -= 1;
			splashscreenSprite.setColor(sf::Color(255, 255, 255, alpha));
			filterTimer = 0.f;
		}
		else if (fadeout && alpha == 0)
		{
			state = State::MENU;
		}

		gameWindow.draw(splashscreenSprite);
	}

	//Draw game
	else if (state != State::SPLASH)
	{
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
	}

	//Draw menu on top of rendered scene
	if (state == State::MENU)
	{
		gameWindow.draw(titleText);
		gameWindow.draw(playText);
		gameWindow.draw(helpText);
		gameWindow.draw(exitText);
	}

	if (state == State::HELP)
	{
		gameWindow.draw(helpSprite);
		gameWindow.draw(thanksText);
	}
	
	//Displaying scene
	gameWindow.display();

}

bool Game::isPointOverText(const sf::Vector2f Position, const Text &Text)
{
	return	(Position.x < (Text.getGlobalBounds().width / 2) + Text.getPosition().x)
		&& (Position.x > (Text.getPosition().x - (Text.getGlobalBounds().width / 2)))
		&& (Position.y < (Text.getGlobalBounds().height / 2) + Text.getPosition().y + Text.getGlobalBounds().height)
		&& (Position.y > (Text.getPosition().y - (Text.getGlobalBounds().height / 2) + Text.getGlobalBounds().height));
}
