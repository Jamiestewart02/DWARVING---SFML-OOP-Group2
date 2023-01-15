#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#define Max_Main_Menu 3
#define Min_Main_Menu 0
class MainMenu
{
public:
	MainMenu(float width, float height);

	void draw(sf::RenderWindow& window);
	void Down();
	void Up();
	void clear();
	int optionSelectedMenu;
	int pageNum = 0;
	bool inventory = false;
	bool cheatsEnabled = false;

	// Inventory Buttons
	sf::RectangleShape btnInvPick;
	sf::RectangleShape btnInvAxe;
	sf::RectangleShape btnInvBow;
	sf::RectangleShape btnChestOfCheats;
	sf::RectangleShape btnInvBlank;
	// Controls Buttons
	sf::RectangleShape btnControlsBack;

	//Game Over Screen Buttons
	sf::RectangleShape btnFinishMenu;
	sf::RectangleShape btnFinishExit;

	// Sprites
	// Screens
	sf::Sprite mainMenuScreen;
	sf::Sprite inventoryScreen;
	sf::Sprite controlsScreen;
	sf::Sprite gameOverScreen;

	// Items
	sf::Sprite pickaxe;
	sf::Sprite bow;
	sf::Sprite axe;
	sf::Sprite grappleHook;
	sf::Sprite victoryScreen;

	// Textures
	sf::Texture textureScreen;
	sf::Texture texturePickaxe;
	sf::Texture textureBow;
	sf::Texture textureAxe;
	sf::Texture textureChestOfCheats;
	sf::Texture textureControlMenu;
	sf::Texture textureMainMenu;
	sf::Texture textureGameOverScreen;
	sf::Texture textureVictoryScreen;

	int keyPressed() {
		return optionSelectedMenu;
	}

	void drawShape(sf::RenderWindow& window, sf::RectangleShape shape);

	void setInventoryMenu(sf::RenderWindow& window);

	void changeEquipment(Player& player, sf::Vector2f tracker);

	void mainMenuNavigation(sf::RenderWindow& window);

	void setControlsMenu(sf::RenderWindow& window);

	void setMainMenu(sf::RenderWindow& window);

	void mainMenuControls(sf::RenderWindow& window);

	void setGameOverScreen(sf::RenderWindow& window, Player &player, Level &level);

	void triggerGameOver(Player player, Level &level);

	void setVictoryScreen(sf::RenderWindow& window, Enemy& enemy, Player& player, Level& level);

	void triggerGameFinished(Level &level);

	MainMenu()
	{
		// Inventory Buttons
		btnInvPick.setSize({ 211, 118 });
		btnInvAxe.setSize({ 211, 118 });
		btnInvBow.setSize({ 211, 118 });
		btnChestOfCheats.setSize({ 211, 118 });
		btnInvBlank.setSize({ 211, 118 });

		// ControlsMenu Buttons
		btnControlsBack.setSize({ 160, 155 });

		//Game Over / Finish Buttons
		btnFinishMenu.setSize({ 546, 124 });
		btnFinishExit.setSize({ 546, 124 });
		btnFinishMenu.setPosition(279, 721);
		btnFinishExit.setPosition(958, 721);

		// Colour Declaration(sf::Color::Transparent)
		// Inventory
		btnInvPick.setFillColor(sf::Color::Transparent);
		btnInvAxe.setFillColor(sf::Color::Transparent);
		btnInvBow.setFillColor(sf::Color::Transparent);
		btnChestOfCheats.setFillColor(sf::Color::Transparent);
		btnInvBlank.setFillColor(sf::Color::Transparent);
		// Controls
		btnControlsBack.setFillColor(sf::Color::Transparent);
		//Game Over/ Finish
		btnFinishMenu.setFillColor(sf::Color::Transparent);
		btnFinishExit.setFillColor(sf::Color::Transparent);


		// Loading Image Assets
		font.loadFromFile("assets/blacknorthfont.otf");
		textureScreen.loadFromFile("assets/Inventory.png");
		texturePickaxe.loadFromFile("assets/PickAxe.png");
		textureBow.loadFromFile("assets/Bow.png");
		textureAxe.loadFromFile("assets/axe.png");
		textureChestOfCheats.loadFromFile("assets/chestOfCheats.png");
		textureControlMenu.loadFromFile("assets/Controlls.png");
		textureMainMenu.loadFromFile("assets/Menu.png");
		textureGameOverScreen.loadFromFile("assets/gameOver.png");
		textureVictoryScreen.loadFromFile("assets/victory.png");

		// Menu Code 
		// Play
		mainMenu[0].setFont(font);
		mainMenu[0].setFillColor(sf::Color::Red);
		mainMenu[0].setString("Start");
		mainMenu[0].setCharacterSize(50);
		mainMenu[0].setPosition(sf::Vector2f(1800 / 2 - 50, 1013 / (Max_Main_Menu + 1) + 150));
		// Controls 
		mainMenu[1].setFont(font);
		mainMenu[1].setFillColor(sf::Color::Black);
		mainMenu[1].setString("Controls");
		mainMenu[1].setCharacterSize(50);
		mainMenu[1].setPosition(sf::Vector2f(1800 / 2 - 50, 1013 / (Max_Main_Menu + 1) * 2));
		// Exit 
		mainMenu[2].setFont(font);
		mainMenu[2].setFillColor(sf::Color::Black);
		mainMenu[2].setString("Exit");
		mainMenu[2].setCharacterSize(50);
		mainMenu[2].setPosition(sf::Vector2f(1800 / 2 - 50, 1013 / (Max_Main_Menu + 1) * 2.5));
		optionSelectedMenu = 0;
	}

	//~MainMenu();
private:

	sf::Font font;
	sf::Text mainMenu[Max_Main_Menu];
};
