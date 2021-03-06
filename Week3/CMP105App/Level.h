#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string.h>
#include <iostream>


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;

	// Objects
	void stopCircleAtEdge(sf::CircleShape &object);

	sf::CircleShape circle;
	float circleSpeed;
	bool movingRight;

	sf::CircleShape player;
	float playerSpeed;
	float playerXSpeedScale;
	float playerYSpeedScale;
	void handlePlayerInput();

	sf::CircleShape bouncingCircle;
	float bouncingCircleXSpeed;
	float bouncingCircleYSpeed;
	float bouncingCircleSpeedScale;
};