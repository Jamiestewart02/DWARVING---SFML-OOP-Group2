/*AUTHOR: ALAN MCSEVENEY*/
/*Anything Animation related throughout the program was implemented by myself - Alan
Objects of animation class are passed through to the Player and Enemy Class which animates them*/
#include "Animation.h"
#include <string>

void Animation::setFileName(std::string fileName){
	this->fileName = fileName;
	}

//Constructor to manage control flow of spritesheets being passed to the animation class
void Animation::setAnimation(int startX, int startY, int width, int height, int endPoint) {
	coordinates.left = startX;
	coordinates.top = startY;
	coordinates.width = width;
	coordinates.height = height;
	this->endPoint = endPoint;
	this->startPoint = startX;
	incrementFrame = coordinates.width;
}

//setStartEndPoints is used to edit access to particular images within the spritesheet
void Animation::setStartEndPoints(int start, int end) {
	this->startPoint = start;
	this->endPoint = end;
}

//Rect Coordinates passed with switchTime to target specific images and control speed of animations
void Animation::Animate(sf::RectangleShape &rect, float switchTime) {

	this->switchTime = switchTime;

	totalTime += time;
	if (coordinates.left >= endPoint) {
		coordinates.left = startPoint;
	}

	if (coordinates.left <= startPoint) {
		coordinates.left = startPoint;
	}

	if (totalTime > switchTime) {
		coordinates.left += incrementFrame;
		totalTime -= switchTime;
	}

	rect.setTextureRect(coordinates);

	if (flipped) {
		rect.setScale(-1.f, 1.f);
	} else {
		rect.setScale(1.f, 1.f);
	}
}
