// ImGuiwithSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "Platform.h"
#include "Player.h"
#include "Level.h"
#include "Enemy.h"
#include "Animation.h"
#include "MainMenu.h"
#include <array>
#include <iostream>

const float winWidth = 1800.f;
const float winHeight = 1013.f;

int main() {
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Game");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    MainMenu menu;
    Level level;
    level.setBackground("assets/lvl1.png");
    level.setMusic("assets/assets_intro.ogg");
    Player dwarf(355.f, 800.f, 100.f, 80.f, "assets/dwarves.png");
    Enemy enemy(2000, 2880, 48, 64, "assets/monster.png", 48, 92);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::I) {
                menu.inventory = !menu.inventory;
                dwarf.setSFX("assets/sfx_pageTurn.wav"); //Anthony
                menu.cheatsEnabled = false;
            }

            if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Enter) {
                level.levelSwitch = true;
            }

            menu.mainMenuControls(window);
            dwarf.setShot(event, window);
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        window.clear();

        if (!menu.inventory) {

            if (menu.pageNum == 0) {
                menu.setMainMenu(window);
            }

            else if (menu.pageNum == 3) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && menu.pageNum == 3)
                {
                    menu.pageNum = 0;
                }

                dwarf.checkDoor(level);

                if (!level.levelOneComplete && !level.levelTwoComplete && !level.levelThreeComplete) {
                    level.buildLevelOne();
                }
                else if (level.levelOneComplete && !level.levelTwoComplete) {
                    level.buildLevelTwo();
                }
                else if (level.levelOneComplete && level.levelTwoComplete) {
                    level.buildLevelThree(enemy);
                }

                
                window.draw(level.background);

                dwarf.setVelX();

                level.draw(window, dwarf);

                dwarf.initiateGrapple(level.grapplePoints, level.platforms, window);

                dwarf.checkBounds(level.platforms);
                dwarf.update(level.platforms, level.deathZone, window);
                window.draw(dwarf.bullet);
                window.draw(dwarf.healthBar);

                if (dwarf.cangrapple) {
                    dwarf.grapple();
                }

                if (dwarf.rect.getGlobalBounds().intersects(level.lever.getGlobalBounds())) {
                    level.leverPulled = true;
                }

                if (dwarf.grapplePoint != nullptr) {
                    dwarf.setRope();
                    if (dwarf.grappletopoint) {
                        dwarf.drawRope(window);
                    }
                }

                menu.triggerGameOver(dwarf, level);
                menu.triggerGameFinished(level);

                //sf::Vector2i position = sf::Mouse::getPosition(window);
                //sf::Vector2f tracker = window.mapPixelToCoords(position);

                window.display();
            }

            else if (menu.pageNum == 1) {
                menu.setControlsMenu(window);
            }

            else if (menu.pageNum == 4) {
                menu.setGameOverScreen(window, dwarf, level);
            }

            else if (menu.pageNum == 5) {
                menu.setVictoryScreen(window, enemy, dwarf, level);
            }
        }

        if (menu.inventory) {
            window.clear();

            sf::Vector2i position = sf::Mouse::getPosition(window);
            sf::Vector2f tracker = window.mapPixelToCoords(position);
            menu.setInventoryMenu(window);
            menu.changeEquipment(dwarf, tracker);

            if (menu.cheatsEnabled) {
                ImGui::SetNextWindowSize(ImVec2(200, 300));
                ImGui::Begin("CHEAT MENU", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

                if (ImGui::Button("Teleport to Level 1", ImVec2(150, 50))) {
                    level.levelOneComplete = false;
                    level.levelTwoComplete = false;
                    level.levelThreeComplete = false;

                    level.levelSwitch = true;

                    dwarf.setPosition(200, 800);
                }

                if (ImGui::Button("Teleport to Level 2", ImVec2(150, 50))) {
                    level.levelOneComplete = true;
                    level.levelTwoComplete = false;
                    level.levelThreeComplete = false;

                    level.levelSwitch = true;

                    dwarf.setPosition(100, 50);
                }

                if (ImGui::Button("Teleport to Level 3", ImVec2(150, 50))) {
                    level.levelOneComplete = true;
                    level.levelTwoComplete = true;
                    level.levelThreeComplete = false;

                    level.levelSwitch = true;

                    dwarf.setPosition(300, 250);
                }

                if (ImGui::Button("Infinite Health", ImVec2(150, 50))) {
                    dwarf.decreaseHealth = 0.f;
                }

                if (ImGui::Button("Drawf must Die", ImVec2(150, 50))) {
                    dwarf.dwarfMustDieMode();

                    for (int i = 0; i < level.enemies.size(); i++) {
                        level.enemies[i].dwarfMustDieMode = true;
                    }
                }

                ImGui::End;

                ImGui::SFML::Render(window);
            }

            window.display();
        }
    }
    ImGui::SFML::Shutdown();
}

//References - Anthony

/*controls background screen :
https://www.freepik.com/free-vector/entrance-cave-mountain-with-empty-space_21427495.htm#page=5&query=game%20background%20cave&position=29&from_view=search&track=ais
Artist: upklyak

font:
https://www.fontspace.com/black-north-font-f87052
Creator: Letterhend Studio

zipline texture :
https://www.gamedeveloperstudio.com/graphics/viewgraphic.php?page-name=Zip-line&item=1r6c678v716c991o77
Artist: Robert Brooks

arrow:
https://www.gamedeveloperstudio.com/graphics/viewgraphic.php?page-name=Prehistoric-weapon-icon-collection&item=165b2x9r1l43351678
Artist: Robert Brooks

music:
https://pixabay.com/music/search/medieval/

    assets/assets_intro.ogg
    Song Title: The Sorrow II - Dark Theme 02
    Artist: Zen Man

    assets/assets_level1.ogg
    Song Title: langhús burning - Viking Background Music
    Artist: OB-LIX

    assets/assets_level2.ogg
    Song Title: Heilir æsir | Norse - Viking Background Music
    Artist: OB-LIX

    assets/assets_level3.ogg
    Song Title: Warriors Across the Unknown - Epic Viking and Medieval Music
    Artist: GioeleFazzeri

    assets/assets_victory.ogg
    Song Title: Almost There
    Artist: GavinNellist

    assets/assets_death.ogg
    Song Title: ancient rhythm
    Artist: SamuelFrancisJohnson
*/

//References - Jamie

/*
assets/sfx_inventory.wav
Inventory: https://opengameart.org/content/inventory-sound-effects
Artist: opengameart

assets/sfx_pageTurn.wav
Page flip sounds: https://www.youtube.com/watch?v=ugKjl3vk7TA&ab_channel=SoundEffectsFactory
Artist: Sound Effect Factory

assets/sfx_bowAttack.wav
bow: https://www.youtube.com/watch?v=kiKOo6HQFRw&ab_channel=GFXSounds
Artist: GFXSounds

assets/sfx_axeAttack
Axe: https://www.youtube.com/watch?v=o7nAIbtMoxQ&ab_channel=2MirrorsDialogue
Artist: audiojungle, 2MD

assets/sfx_pickaxeAttack
Pick: https://www.youtube.com/watch?v=vHbNnHPQnII&t=8s&ab_channel=TheRustAdmin
Artist: The Rust Admin
Game: Rust

assets/bow
https://minecraft.fandom.com/wiki

assets/axe
https://minecraft.fandom.com/wiki

assets/pickaxe
https://minecraft.fandom.com/wiki


References - Alan

dwarve animations
https://opengameart.org/content/delve-deeper-dwarves "Lunar Giant!

Minatour animations
https://opengameart.org/content/minotaur-2 credited: "Jordan Irwin (AntumDeluge)"

Spider Animations
https://opengameart.org/content/arachne credited: "Svetlana Kushnariova"

Werewolf Animations
https://opengameart.org/content/werewolf-lpc credited: "Stephen Challener (Redshrike), William Thompson (William.Thompsonj), & Jordan Irwin (AntumDeluge)"
*/