//
//      Created by Goodecheeseburgers on 21/04/2020.
//      SomeRPG. A C++ console role playing game.
//      Copyright (C) 2020 - goodecheeseburgers@gmail.com
//
//      https://github.com/Cheeseborgers/SomeRPG
//
//      This program is free software: you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation, either version 3 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef UNTITLED1_GAME_H
#define UNTITLED1_GAME_H

#include "Player.h"
#include "Enemy.h"


class Game {

private:
    // Window
    sf::VideoMode videoMode;
    std::unique_ptr<sf::RenderWindow> window;

    // Resources
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;

    // Player
    std::unique_ptr<Player> player;

    // Player GUI
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack;
    sf::Font pointFont;
    sf::Text pointText;

    // Game over screen
    sf::Font gameOverFont;
    sf::Text gameOverText;

    // Enemies
    float spawnTimer{};
    float spawnTimerMax{};
    std::vector<Enemy*> enemies;

    // World
    sf::Texture worldBackgroundTexture;
    sf::Sprite worldBackground;

    // Private methods
    void initWindow();
    void initTextures();
    void initFonts();
    void initGUI();
    void initWorld();
    void initPlayer();
    void initEnemies();

public:
    // Constructor
    Game();
    ~Game();

    // Methods
    void run();

    // Update methods
    void updatePollEvents();
    void updateInput();
    void updateGUI();
    void updateBullets();
    void updateWorld();
    void updateCollision();
    void updateEnemies();
    void updateCombat();
    void update();

    // Render methods
    void renderGUI();
    void renderWorld();
    void render();
};

#endif //UNTITLED1_GAME_H
