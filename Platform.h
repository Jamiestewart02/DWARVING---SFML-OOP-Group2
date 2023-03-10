#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

/*Platform class made by Darren -- Used as building blocks for the level environment.Any use of the
platform class was implemented by me*/


class Platform
{
private:
	float posx;
	float posy;
	bool direction;
	float height;
	float width;
	float velx;
	float vely;
	sf::Color colour;
	sf::RectangleShape platform;

public:

	void setPosition (float x, float y);
	float getPositionX();
	float getPositionY();
	void setSize(float w, float h);
	void setShape();
	void setColour(sf::Color colour);
	void draw(sf::RenderWindow& window);
	sf::RectangleShape getShape();
	void setDirection(float pointA, float pointB);
	void setXVelocity();
	float getXVelocity();
	void movePlatformX(float pointA, float pointB);
	sf::FloatRect getBounds();
	bool getDirection();

	Platform(float posx, float posy, float height, float width) {
		setColour(sf::Color::Transparent);
		setSize(width, height);
		setPosition(posx, posy);
		setShape();
	}
};

