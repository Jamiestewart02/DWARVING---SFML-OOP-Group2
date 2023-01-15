/*AUTHOR: ALAN MCSEVENEY*/

/*Anything Enemy related throughout the program was implemented by myself - Alan*/
#include "Enemy.h"

/*===============================================
			GETTERS
===============================================*/

float Enemy::getPositionX() {
	return positionX;
}

float Enemy::getPositionY() {
	return positionY;
}

float Enemy::getXVelocity() {
	return velx;
}

float Enemy::getWidth() {
	return width;
}

float Enemy::getHeight() {
	return height;
}

float Enemy::getEnemyHealth() {
	return enemyHealth;
}

float Enemy::getDecreaseHealth() {
	return decreaseHealth;
}

bool Enemy::getDirection() {
	return direction;
}

sf::Texture Enemy::getTexture() {
	return this->texture;
}

sf::Vector2f Enemy::getRectScale() {
	return this->rectScale;
}

/*===============================================
			SETTERS
===============================================*/

void Enemy::setPosition(float x, float y) {
	this->positionX = x;
	this->positionY = y;
}

void Enemy::setRectSize(float w, float h) {
	this->width = w;
	this->height = h;
}

void Enemy::setEnemyShape() {
	enemyRect.setSize({ width, height });
	enemyRect.setPosition({ positionX, positionY });
}

void Enemy::setTexture() {
	texture.loadFromFile(animation.fileName);
}

void Enemy::setEnemyHealth() {
	enemyHealth -= decreaseHealth;
}

//Flips sprite according to collison with specified points
void Enemy::setDirection(float pointA, float pointB) {
	setScaleValues(3.f, 3.f);
	if (enemyRect.getPosition().x <= pointA) {
		direction = true;
		animation.flipped = false;
		setScaleValues(3.f, 3.f);
	}

	if (enemyRect.getPosition().x >= pointB) {
		direction = false;
		animation.flipped = true;
		setScaleValues(-3.f, 3.f);
	}

	if (animation.flipped) {
		setScaleValues(-3.f, 3.f);
	}
	else {
		setScaleValues(3.f, 3.f);
	}
}

void Enemy::setXVelocity() {
	if (direction) {
		velx = 2.f;
		if (dwarfMustDieMode) { //Method incoporated within the cheat menu to enable a greater difficulty
			velx = 50.f;
		}
	}
	else {
		velx = -2.f;
		if (dwarfMustDieMode) {
			velx = -50.f;
		}
	}
}

void Enemy::setScaleValues(float x, float y) {
	scaleX = x;
	scaleY = y;
}

//sets the direction the enemy faces
void Enemy::flippedRect() {
	if (animation.flipped) {
		rectScale.x = -5.f;
	}
	else {
		rectScale.x = 5.f;
	}
}

/*===============================================
			MOVEMENT/COLLISION MECHANICS
===============================================*/

void Enemy::moveEnemyX(float pointA, float pointB) {
	setDirection(pointA, pointB);
	setXVelocity();
	positionX += velx;
	enemyRect.setPosition(positionX, positionY);
}

/*Makes call to player class to check for collision intersection with enemy
Player damaging the enemy is dependant on the position of the spritesheet
Eunans initial health bar implemented using OOP principles by Alan, Collision detection created by Alan and Darren
incoporating related classes built by ourselves*/

void Enemy::enemyCollision(Player &player) {
	if (enemyRect.getGlobalBounds().intersects(player.hurtBox.getGlobalBounds())) {
		if (player.animation.coordinates.left == 1300) {
			setEnemyHealth();
			setScaleValues(0.f, 0.f);
		}
		player.setPlayerHealth();
	}

	if (enemyRect.getGlobalBounds().intersects(player.bullet.getGlobalBounds())) {
		setEnemyHealth();
		setScaleValues(0.f, 0.f);
		if (enemyRect.getGlobalBounds().intersects(player.bullet.getGlobalBounds())) {
			player.bullet.setPosition(player.getPositionX(), player.getPositionY());
			player.bullet.setScale(0.f, 0.f);
		}
	}

	if (enemyHealth == 0) {
		setPosition(2000, 1000);
	}
}

//updates the enemy condition every frame
void Enemy::update(sf::RenderWindow& window) {
	enemyRect.setScale(scaleX, scaleY);
	window.draw(enemyRect);
}

Enemy::Enemy(float positionX, float positionY, float width, float height, std::string fileName, int incrementFrame, int endPoint) {
	setPosition(positionX, positionY);
	setRectSize(width, height);
	animation.setFileName(fileName);

	animation.setAnimation(0, 0, width, height, endPoint);

	setTexture();
	enemyRect.setTexture(&texture);
	enemyRect.setOrigin(24, 32);

	setEnemyShape();
}