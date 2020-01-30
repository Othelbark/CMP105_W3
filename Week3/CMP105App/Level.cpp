#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects

	circle.setFillColor(sf::Color::Magenta);
	circle.setRadius(10);
	circle.setOrigin(10, 10);
	circle.setPosition(200, 100);
	circleSpeed = 50;
	movingRight = true;

	player.setFillColor(sf::Color::Green);
	player.setRadius(15);
	player.setOrigin(15, 15);
	player.setPosition(300, 300);
	playerSpeed = 200;
	playerXSpeedScale = 0;
	playerYSpeedScale = 0;

}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	handlePlayerInput();

	//escape to quit
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		window->close();
	}
}

// Update game objects
void Level::update(float dt)
{
	//player movement
	player.move(playerSpeed * dt * playerXSpeedScale, playerSpeed * dt * playerYSpeedScale);

	//stop player at edge
	stopCircleAtEdge(player);
	

	//Circle
	if (movingRight) 
	{
		circle.move(circleSpeed * dt, 0);
	}
	else
	{
		circle.move(-circleSpeed * dt, 0);
	}
	
	// If circle had hit right side
	if (circle.getPosition().x >= window->getSize().x)
	{
		movingRight = false;
	}
	// If circle had hit left side
	if (circle.getPosition().x <= 0)
	{
		movingRight = true;
	}
}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(circle);
	window->draw(player);

	endDraw();
}

// clear back buffer
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}

void Level::handlePlayerInput()
{
	//Find player x and y speed scales
	playerXSpeedScale = 0;
	playerYSpeedScale = 0;

	//right
	if (input->isKeyDown(sf::Keyboard::Right) || input->isKeyDown(sf::Keyboard::D))
	{
		playerXSpeedScale += 1;
	}
	//left
	if (input->isKeyDown(sf::Keyboard::Left) || input->isKeyDown(sf::Keyboard::A))
	{
		playerXSpeedScale -= 1;
	}
	//down
	if (input->isKeyDown(sf::Keyboard::Down) || input->isKeyDown(sf::Keyboard::S))
	{
		playerYSpeedScale += 1;
	}
	//up
	if (input->isKeyDown(sf::Keyboard::Up) || input->isKeyDown(sf::Keyboard::W))
	{
		playerYSpeedScale -= 1;
	}

	//diagonal
	if (playerXSpeedScale != 0 && playerYSpeedScale != 0)
	{
		float root2 = 1.41421356;
		playerXSpeedScale /= root2;
		playerYSpeedScale /= root2;
	}
}

void Level::stopCircleAtEdge(sf::CircleShape &object)
{
	//find window size and player posistion
	float xSize = window->getSize().x;
	float ySize = window->getSize().y;
	float objectXPos = object.getPosition().x;
	float objectYPos = object.getPosition().y;

	// If player has passed the right side
	if (objectXPos > xSize)
	{
		//dont go off the side
		object.setPosition(xSize, objectYPos);
	}
	// If player has passed the left side
	else if (objectXPos < 0)
	{
		//dont go off the side
		object.setPosition(0, objectYPos);
	}

	//check if x value changed
	objectXPos = object.getPosition().x;

	// If player has passed the bottom side
	if (objectYPos > ySize)
	{
		//dont go off the side
		object.setPosition(objectXPos, ySize);
	}
	// If player has passed the left side
	else if (objectYPos < 0)
	{
		//dont go off the side
		object.setPosition(objectXPos, 0);
	}
}