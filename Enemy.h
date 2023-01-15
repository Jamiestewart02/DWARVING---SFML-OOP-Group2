/*AUTHOR: ALAN MCSEVENEY*/
#pragma once
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "Player.h"
#include <vector>

class Enemy{
private:
	//General Enemy Dimensions
	float positionX;
	float positionY;
	float width;
	float height;
	float velx;
	float scaleX;
	float scaleY;

	//Enemy Health Attributes
	float enemyHealth = 100.f;
	float decreaseHealth = 25.f;

	//Condition Checks
	bool direction;
	bool death = false;

	//Enemy Texture Dimensions
	sf::Texture texture;
	sf::Vector2f rectScale = sf::Vector2f(5.f, 5.f);

	

public:
	//Cheat Menu Method 
	bool dwarfMustDieMode = false;

	//Object of animation inherited
	Animation animation;

	sf::RectangleShape enemyRect;

	

	//Getters
	sf::Vector2f getRectScale();
	sf::Texture getTexture();
	float getPositionX();
	float getPositionY();
	float getWidth();
	float getHeight();
	float getDecreaseHealth();
	float getEnemyHealth();
	float getXVelocity();
	bool getDirection();
	

	//Setters
	void setPosition(float x, float y);
	void setRectSize(float w, float h);
	void setEnemyShape();
	void setTexture();
	void setDirection(float pointA, float pointB);
	void setXVelocity();
	void setEnemyHealth();
	void setScaleValues(float x, float y);

	//Action Methods
	void flippedRect();
	void moveEnemyX(float pointA, float pointB);
	void enemyCollision(Player &player);
	void update(sf::RenderWindow& window);

	Enemy(float positionX, float positionY, float width, float height, std::string fileName, int incrementFrame, int endPoint);
};

