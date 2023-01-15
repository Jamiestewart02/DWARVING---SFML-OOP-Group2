/*AUTHOR: ALAN MCSEVENEY*/
/*Animation remaining public as to allow access to the attritubes and methods throughout the game
And to manage circular dependancies*/
#pragma once
#include <string>
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

class Animation
{
public:
	//Image Targeting attributes
	std::string fileName = "";
	sf::IntRect coordinates;
	int coordinateWidth, coordinateHeight;
	
	//Spritesheet/animation speed management attributes
	int startPoint, startY, endPoint, incrementFrame, row;
	float time = 0.1f;
	float switchTime = 0.8f;
	float totalTime;

	//Condition Checks
	bool flipped = false;
	bool attack = false;;

	//Animation Action Methods
	void setFileName(std::string fileName);
	void setAnimation(int startX, int startY, int width, int height, int endPoint);
	void setStartEndPoints(int start, int end);
	void Animate(sf::RectangleShape &rect, float switchTime);
};

