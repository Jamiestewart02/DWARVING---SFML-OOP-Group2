#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include "Animation.h"
#include "Level.h"
#include <vector>
#include <iostream>

//Author -- Darren Gallagher

class Player
{
private:

	const float SCREENWIDTH = 1800.f;
	const float SCREENHEIGHT = 1013.f;

	//PLAYER DIMENSIONS
	float distance;
	float playerHeight;
	float playerWidth;
	sf::Vector2f playerPosition;
	sf::Vector2f playerVelocity;
	float indirVelX = 0.f;
	sf::Texture texture;
	sf::Texture bulletTexture;
	sf::Color borderColor;
	sf::Color colour;
	sf::RectangleShape topBound;
	sf::RectangleShape leftBound;
	sf::RectangleShape rightBound;
	sf::RectangleShape bottomBound;
	
	//PLAYER/ENVIRONMENT INTERACTION VALUES
	sf::Vector2f distanceBetween;
	sf::Vector2f bulletDistanceBetween;
	sf::Vector2f bulletVelocity;
	float gravity = 0.7f;
	float groundHeight = 930.f;
	float inverseDistance;
	float bulletInverseDistance;
	bool lift = false;
	bool onLedge = false;
	bool anchored;
	float direction;

	//PLAYER/COMBAT INTERACTION VALUES
	int immuneTime = 30;
	int damageTime = 0;
	float healthBarX = 20.f;
	float healthBarY = 20.f;
	sf::Vector2f playerHealth = sf::Vector2f(100.f, 20.f);

public:
	float decreaseHealth = 10.f;

	//DRAWABLES
	sf::RectangleShape healthBar;
	sf::RectangleShape backBar;
	sf::Sprite bullet;
	sf::RectangleShape hurtBox;
	Animation animation;
	sf::RectangleShape rect;
	sf::Vertex rope[5];
	sf::Sprite *grapplePoint;

	//CONDITION CHECKS
	bool cangrapple = false;
	bool grappletopoint = false;
	bool shot = false;
	bool ropeGrow = false;
	bool isPick = true;
	bool isBow = false;
	bool isAxe = false;

	//ANTHONY SFX
	sf::SoundBuffer sfxBuffer;
	sf::Sound sound;
	std::string sfxFileName;
	void setSFX(std::string fileName);

	//SETTERS
	void setPosition(float x, float y);
	void setSize(float w, float h);
	void setAnchor(bool anchor);
	void setColour(sf::Color colour);
	void setShapeColour(sf::Color colour);
	void setShape();
	void setTexture();
	void setGroundHeight(float height);
	void setVelX();
	void setVelY(float vely);
	void setGrappleVelocity(float velx, float vely);
	void setDistanceBetween(sf::Vector2f targetPosition);
	void setBulletDistanceBetween(sf::Vector2i targetPosition);
	void setBulletVelocity();
	void setIndirVelX(float vel);
	void setOnLedge(bool onLedge);
	void setRope();
	void setShot(sf::Event event, sf::RenderWindow& window);
	void setHealthBarShape();
	void setHealthBarPosition(float x, float y);
	void setPlayerHealth();
	void setHealthToMax();

	//GETTERS
	float getPositionX();
	float getPositionY();
	sf::Vector2f getPosition();
	float getPlayerWidth();
	float getPlayerHeight();
	float getGroundHeight();
	float getAngle(float sideX, float sideY);
	bool getAnchor();
	float getVelX();
	float getVelY();
	sf::Vector2f getDistanceBetween();
	float getInversedDistance();
	bool getOnLedge();
	float getHealthBarPositionX();
	float getHealthBarPositionY();
	float getDecreaseHealth();
	sf::Vector2f getPlayerHealth();
	sf::FloatRect getBounds();
	sf::RectangleShape getShape();
	
	//PLAYER ACTION METHODS
	bool isLeftOf(float currentPositionX,float targetPositionX);
	void checkForSpikes(std::vector<Platform> deathZones);
	void jump();
	void update(std::vector<Platform> platforms, std::vector<Platform> deathZones, sf::RenderWindow& window);
	void movePlayer();
	void grapple();
	void anchor(Platform platform);
	void shoot(std::vector<Platform> ledges, sf::RenderWindow& window);
	void checkBulletCondition(std::vector<Platform> ledges);
	void checkBounds(std::vector<Platform> platforms);
	void drawRope(sf::RenderWindow& window);
	void initiateGrapple(std::vector<sf::Sprite> grapplePoints, std::vector<Platform> platforms, sf::RenderWindow &window);
	bool checkGrapplePath(std::vector<Platform> ledges);
	void checkDoor(Level& level);
	void attack(std::vector<Platform> ledges, sf::RenderWindow &window);
	void dwarfMustDieMode();

	Player(float posx, float posy, float width, float height, std::string fileName) {
		setPosition(posx, posy);
		setSize(width, height);
		animation.setFileName(fileName);
		animation.setAnimation(0, 0, width, height, 300);
		setTexture();
		rect.setTexture(&texture);
		setShape();
		rect.setOrigin({ rect.getGlobalBounds().width / 2, rect.getGlobalBounds().height / 2 });
		topBound.setSize({ rect.getGlobalBounds().width / 2 - 2.f, 5.f });
		bottomBound.setSize({ rect.getGlobalBounds().width / 2 - 10.f, 5.f });
		leftBound.setSize({ 10.f, rect.getGlobalBounds().height / 2 });
		rightBound.setSize({ 10.f, rect.getGlobalBounds().height / 2 });
		hurtBox.setSize({ 5.f, 15.f });
		hurtBox.setOrigin({ 25.f, 20.f });
		hurtBox.setFillColor(sf::Color::White);
		topBound.setFillColor(sf::Color::Transparent);
		leftBound.setFillColor(sf::Color::Transparent);
		rightBound.setFillColor(sf::Color::White);
		bottomBound.setFillColor(sf::Color::White);
		bulletTexture.loadFromFile("assets/arrow.png");
		bullet.setTexture(bulletTexture);
	}
};

