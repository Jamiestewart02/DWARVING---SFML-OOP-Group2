#include "MainMenu.h"

#include <iostream>



void MainMenu::draw(sf::RenderWindow& window)
{

	for (int i = 0; i < 3; i++)
	{
		window.draw(mainMenu[i]);
	}

}

// Allows the user to move up through the menu options using the DOWN arrow
void MainMenu::Down() {
	if (optionSelectedMenu + 1 <= Max_Main_Menu)
	{

		mainMenu[optionSelectedMenu].setFillColor(sf::Color::Black);
		optionSelectedMenu++;


		if (optionSelectedMenu == 3)
		{
			optionSelectedMenu = 0;

		}
		std::cout << optionSelectedMenu;
		mainMenu[optionSelectedMenu].setFillColor(sf::Color::Red);

	}
}

// Allows the user to move up through the menu options using the UP arrow
void MainMenu::Up() {
	if (optionSelectedMenu - 1 >= -1)
	{
		mainMenu[optionSelectedMenu].setFillColor(sf::Color::Black);
		optionSelectedMenu--;

		if (optionSelectedMenu == -1)
		{
			optionSelectedMenu = 2;
		}
		std::cout << optionSelectedMenu;
		mainMenu[optionSelectedMenu].setFillColor(sf::Color::Red);
	}
}

// Hides the Menu text when it’s no longer needed
void MainMenu::clear() {
	mainMenu[0].setFillColor(sf::Color::Transparent);
	mainMenu[1].setFillColor(sf::Color::Transparent);
	mainMenu[2].setFillColor(sf::Color::Transparent);

}

void MainMenu::drawShape(sf::RenderWindow& window, sf::RectangleShape shape) {
	window.draw(shape);
}

// Draws the Inventory Menu
void MainMenu::setInventoryMenu(sf::RenderWindow& window) {

	// Inventory Buttons
	btnInvPick.setPosition(142, 105);
	btnInvAxe.setPosition(468, 105);
	btnInvBow.setPosition(795, 105);
	btnChestOfCheats.setPosition(1123, 105);
	btnInvBlank.setPosition(1451, 105);

	// Loading Inventory Screen Assets
	inventoryScreen.setTexture(textureScreen);
	pickaxe.setTexture(texturePickaxe);
	bow.setTexture(textureBow);
	axe.setTexture(textureAxe);
	grappleHook.setTexture(textureChestOfCheats);

	// Inventory Asset locations
	pickaxe.setPosition(170, 115);
	pickaxe.setScale(0.3, 0.2);
	bow.setPosition(510, 106);
	bow.setScale(0.8, 0.75);
	axe.setPosition(810, 95);
	axe.setScale(1.2, 0.75);
	grappleHook.setPosition(1165, 95);
	grappleHook.setScale(0.35, 0.25);

	// Drawing the inventory Screen & assets
	window.draw(inventoryScreen);
	window.draw(btnInvPick);
	window.draw(btnInvAxe);
	window.draw(btnInvBow);
	window.draw(btnChestOfCheats);
	window.draw(btnInvBlank);
	window.draw(pickaxe);
	window.draw(bow);
	window.draw(axe);
	window.draw(grappleHook);
}

// This method contains IF statements that will check when the user interacts with the Inventory cells, changing the equipment the dwarf is using through their interactions.
void MainMenu::changeEquipment(Player& player, sf::Vector2f tracker) {

	// Change Equipment to a Pickaxe
	if (btnInvPick.getGlobalBounds().contains(tracker) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		player.isPick = true;
		player.isBow = false;
		player.isAxe = false;
		player.animation.coordinates.top = 0;
		inventory = false;
		std::cout << "PICK";
	}

	// Change Equipment to a Axe
	if (btnInvAxe.getGlobalBounds().contains(tracker) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		player.isPick = false;
		player.isBow = true;
		player.isAxe = false;
		player.animation.coordinates.top = 80;
		inventory = false;
		std::cout << "BOW";
	}

	// Change Equipment to a Bow
	if (btnInvBow.getGlobalBounds().contains(tracker) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		player.isPick = false;
		player.isBow = false;
		player.isAxe = true;
		player.animation.coordinates.top = 160;
		inventory = false;
		std::cout << "AXE";
	}

	// Enabled the cheat menu
	if (btnChestOfCheats.getGlobalBounds().contains(tracker) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		cheatsEnabled = true;
	}
}

void MainMenu::mainMenuNavigation(sf::RenderWindow& window) {
	if (keyPressed() == 0) {
		pageNum = 3;
	}
	if (keyPressed() == 1) {
		pageNum = 1;
	}
	if (keyPressed() == 2) {
		window.close();
		pageNum = 2;
	}
}

//Builds control screen and listens for when the user clicks back
void MainMenu::setControlsMenu(sf::RenderWindow& window) {

	window.clear();
	sf::Vector2i position = sf::Mouse::getPosition(window);
	sf::Vector2f tracker = window.mapPixelToCoords(position);

	controlsScreen.setTexture(textureControlMenu);

	btnControlsBack.setPosition(1605, 835);

	window.draw(controlsScreen);

	if (btnControlsBack.getGlobalBounds().contains(tracker) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		pageNum = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && pageNum == 1) {
		pageNum = 0;
	}

	drawShape(window, btnControlsBack);
	window.display();
}

void MainMenu::setMainMenu(sf::RenderWindow& window) {
	mainMenuScreen.setTexture(textureMainMenu);
	window.clear();
	window.draw(mainMenuScreen);
	draw(window);
	window.display();
}

//Calls the relevant methods to move through the menu
void MainMenu::mainMenuControls(sf::RenderWindow& window) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pageNum == 0) {
		Down();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pageNum == 0) {
		Up();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && pageNum == 0) {
		mainMenuNavigation(window);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && pageNum == 1) {
		pageNum = 0;
	}
}

//Sets the Game Over screen by passing window, player, and level by reference, checking the parameters
//and executing dependent on those parameters being true/false. Draws to the screen and changes the state of the levels to reset the game.
void MainMenu::setGameOverScreen(sf::RenderWindow& window, Player &player, Level &level) {
	window.clear();
	gameOverScreen.setTexture(textureGameOverScreen);

	sf::Vector2i position = sf::Mouse::getPosition(window);
	sf::Vector2f tracker = window.mapPixelToCoords(position);

	btnFinishMenu.setPosition(279, 721);
	btnFinishExit.setPosition(958, 721);

	// Draws the game over screen
	window.draw(gameOverScreen);
	window.draw(btnFinishMenu);
	window.draw(btnFinishExit);

	//Checks for user click in Game Over screen and resets level states if the user returns to the menu.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && btnFinishMenu.getGlobalBounds().contains(tracker)) {
		player.setHealthToMax();
		level.levelOneComplete = false;
		level.levelTwoComplete = false;
		level.levelThreeComplete = false;
		level.levelSwitch = true;
		level.setMusic("assets/assets_intro.ogg");
		player.setPosition(200, 860);
		pageNum = 0;
	}

	//Closes window dependent on user click in the Game Over screen on the Exit button
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && btnFinishExit.getGlobalBounds().contains(tracker)) {
		window.close();
	}

	window.display();
}

//Triggers the Game Over state dependent on the players current health. Done by passing the player as a parameter by reference
//Done by checking the players health is 0, then changing the page number and starting music.
void MainMenu::triggerGameOver(Player player, Level &level) {
	player.checkForSpikes(level.deathZone);
	if (player.animation.coordinates.left == 1600) {
		pageNum = 4;
		level.setMusic("assets/assets_death.ogg");
	}
}

//Sets the Victory screen by passing window, player and level by reference, checking the parameters
//and executing dependent on those parameters being true/false. Draws to the screen and changes the state of the levels to reset the game.
void MainMenu::setVictoryScreen(sf::RenderWindow& window, Enemy& enemy, Player& player, Level& level) {
	window.clear();
	victoryScreen.setTexture(textureVictoryScreen);
	sf::Vector2i position = sf::Mouse::getPosition(window);
	sf::Vector2f tracker = window.mapPixelToCoords(position);
	btnFinishMenu.setPosition(279, 721);
	btnFinishExit.setPosition(958, 721);
	btnFinishMenu.setFillColor(sf::Color::Transparent);
	btnFinishExit.setFillColor(sf::Color::Transparent);
	window.draw(victoryScreen);
	window.draw(btnFinishMenu);
	window.draw(btnFinishExit);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && btnFinishMenu.getGlobalBounds().contains(tracker)) {
		level.levelOneComplete = false;
		level.levelTwoComplete = false;
		level.levelThreeComplete = false;
		level.levelSwitch = true;
		level.setMusic("assets/assets_intro.ogg");
		player.setPosition(200, 860);
		pageNum = 0;
	}

	//Closes window dependent on user click in Victory screen.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && btnFinishExit.getGlobalBounds().contains(tracker)) {
		window.close();
	}

	window.display();
}

// The trigger that checks the parameters of the Victory status
void MainMenu::triggerGameFinished(Level &level) {

	for (int i = 0; i < level.enemies.size(); i++) {
		if (level.enemies[i].getEnemyHealth() <= 0.f && level.levelTwoComplete) {
			pageNum = 5;
			level.setMusic("assets/assets_victory.ogg");
		}
	}

}


