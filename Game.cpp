//
//      Created by Goodecheeseburgers on 21/04/2020.
//      ShapeShooter. A C++ / SFML space, shape shooter game.
//      Copyright (C) 2020 - goodecheeseburgers@gmail.com
//
//      https://github.com/Cheeseborgers/ShapeShooter
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

#include "Game.h"

// Private Methods -------------------------------------------------------------------------------------
void Game::initWindow()
{
    this->videoMode = sf::VideoMode(800, 600); // Set video mode

    this->window = std::make_unique<sf::RenderWindow>( // Create window
            this->videoMode,
            "Window",
            sf::Style::Close | sf::Style::Titlebar
    );

    this->window->setFramerateLimit(60); // Set framerate

    this->window->setVerticalSyncEnabled(false); // Set Vsync to false;
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::initTextures()
{
    this->textures["BULLET"] = new sf::Texture();

    if (!this->textures["BULLET"]->loadFromFile("textures/bullet.png"))
    {
        std::cout << "ERROR::GAME::INITTEXTURES: Failed to load bullet.png\n";
    }
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::initFonts()
{
    /*
     * @return void
     * Loads the the game fonts from file
     * - Player Score points text font
     * - Game over text font
     */

    if (!this->pointFont.loadFromFile("fonts/hemi_head/hemi_head.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONTS: Failed to load: fonts/hemi_head/hemi_head.ttf\n";
    }

    if (!this->gameOverFont.loadFromFile("fonts/8bit_wonder/8bit_wonder.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONTS: Failed to load: fonts/8bit_wonder/8bit_wonder.ttf\n";
    }
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::initGUI()
{
    // Player health bar
    this->playerHpBar.setSize(sf::Vector2f(300.F, 25.F));
    this->playerHpBar.setFillColor(sf::Color(255, 0, 0, 50));
    this->playerHpBar.setPosition(20.F, 20.F);

    this->playerHpBarBack = this->playerHpBar;
    this->playerHpBarBack.setFillColor(sf::Color(20, 20, 20, 200));
    this->playerHpBarBack.setPosition(20.F, 20.F);

    // Player points text
    this->pointText.setPosition(
            20.F,
            this->playerHpBarBack.getGlobalBounds().top + (this->playerHpBarBack.getSize().y + 1.F)
            );
    this->pointText.setFont(this->pointFont);
    this->pointText.setCharacterSize(20);
    this->pointText.setFillColor(sf::Color(255, 255, 255, 150));
    this->pointText.setString("0");

    // Game over text
    this->gameOverText.setFont(this->gameOverFont);
    this->gameOverText.setCharacterSize(60);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setString("Game Over");
    this->gameOverText.setPosition(
            this->window->getSize().x / 2.F - this->gameOverText.getGlobalBounds().width / 2.F,
            this->window->getSize().y / 2.F - this->gameOverText.getGlobalBounds().height / 2.F);


}
// ----------------------------------------------------------------------------------------------------------------
void Game::initWorld()
{
    if (!this->worldBackgroundTexture.loadFromFile("textures/background1.jpg"))
    {
        std::cout << "ERROR::GAME::INITWORLD: Failed to load: texture/background1.jpg\n";
    }

    this->worldBackground.setTexture(this->worldBackgroundTexture);
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::initPlayer()
{
    this->player = std::make_unique<Player>();
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::initEnemies()
{
    this->spawnTimerMax = 50.F;
    this->spawnTimer = this->spawnTimerMax;
}
// Constructor ---------------------------------------------------------------------------------------------------------
Game::Game()
{
    this->initWindow();
    this->initTextures();
    this->initFonts();
    this->initGUI();
    this->initWorld();
    this->initPlayer();
    this->initEnemies();
}
// Destructor ----------------------------------------------------------------------------------------------------------
Game::~Game()
{
    // Delete textures
    for (auto &i : this->textures)
    {
        delete i.second;
    }

    // Delete bullets
    for (auto *i : this->bullets)
    {
        delete i;
    }

    // Delete enemies
    for (auto *i : this->enemies)
    {
        delete i;
    }
}
// Methods -------------------------------------------------------------------------------------------------------------
void Game::run()
{
    while (this->window->isOpen())
    {
        this->updatePollEvents();

        if (this->player->getHp() > 0)
        {
            this->update();
        }

        this->render();
    }
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::updatePollEvents()
{
    sf::Event e{};

    while (this->window->pollEvent(e))
    {
        // Close game events ==================================================================
        if (e.Event::type == sf::Event::Closed)
        {
            this->window->close();
        }

        if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
        {
            this->window->close();
        }
        // =====================================================================================
    }
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::updateInput()
{
    // Move player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->player->move(-1.F, 0.F);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->player->move(1.F, 0.F);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->player->move(0.F, -1.F);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->player->move(0.F, 1.F);
    }

    if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
         sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) &&
        this->player->canAttack())
    {
        this->bullets.push_back(new Bullet(
                this->textures["BULLET"],
                this->player->getPosition().x + this->player->getBounds().width / 2.F,
                this->player->getPosition().y, 0.f, -1.f, 5.f));
    }
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::updateGUI()
{
    // Player points
    std::stringstream ss;

    ss << "Points: " << this->player->getPoints();

    this->pointText.setString(ss.str());

    // Health bar
    float hpPercent = static_cast<float>(this->player->getHp()) /
                      static_cast<float>(this->player->getHpMax());
    this->playerHpBar.setSize(sf::Vector2f(300.F * hpPercent, this->playerHpBar.getSize().y));
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::updateBullets()
{
    unsigned counter{};

    for (auto *bullet : this->bullets)
    {
        bullet->update();

        // Bullet culling (top of screen)
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
        {
            // Delete bullet
            delete this->bullets.at(counter);
            this->bullets.erase(this->bullets.begin() + counter);
        }

        // DEBUG: std::cout << std::to_string(this->bullets.size()) << "\n";
        ++counter;
    }
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::updateEnemies()
{
    // Spawning
    this->spawnTimer += 0.5F; // Increase the spawn timer

    if (this->spawnTimer >= this->spawnTimerMax)
    {
        this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.F, -100.F));
        this->spawnTimer = 0.F;
    }

    // Update
    unsigned counter{};

    for (auto *enemy : this->enemies)
    {
        enemy->update();

        // Enemy culling (bottom of screen)
        if (enemy->getBounds().top > this->window->getSize().y)
        {
            // Delete enemy
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
        }
        // Enemy intersects with player
        else if  (enemy->getBounds().intersects(this->player->getBounds()))
        {
            // Player take damage
            this->player->loseHp(this->enemies.at(counter)->getDamageGain());

            // Delete enemy
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
        }

        // DEBUG: std::cout << std::to_string(this->enemies.size()) << "\n";
        ++counter;
    }
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::updateCombat()
{
    for (size_t i = 0; i < this->enemies.size(); ++i)
    {
        bool enemy_deleted = false;

        for (size_t k = 0; k < this->bullets.size() && !enemy_deleted; ++k)
        {
            if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
            {
                this->player->setPoints(this->enemies[i]->getPointsGain());

                delete this->enemies[i];
                this->enemies.erase(this->enemies.begin() + i);

                delete this->bullets[k];
                this->bullets.erase(this->bullets.begin() + k);

                enemy_deleted = true; // Leave the loop
            }
        }
    }
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::updateWorld()
{

}
// ---------------------------------------------------------------------------------------------------------------------
void Game::updateCollision()
{
    // Left world collision
    if (this->player->getBounds().left < 0.F)
    {
        this->player->setPosition(0.F, this->player->getBounds().top);
    }
        // Right world collision
    else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
    {
        this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
    }

    // Top world collision
    if (this->player->getBounds().top < 0.F)
    {
        this->player->setPosition(this->player->getBounds().left, 0.F);
    }
        // Bottom world collision
    else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
    {
        this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
    }

}
// ---------------------------------------------------------------------------------------------------------------------
void Game::update()
{
    this->updateInput();

    this->player->update();

    this->updateCollision();

    this->updateBullets();

    this->updateEnemies();

    this->updateCombat();

    this->updateGUI();

    this->updateWorld();
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::renderGUI()
{
    this->window->draw(this->pointText);
    this->window->draw(this->playerHpBarBack);
    this->window->draw(this->playerHpBar);
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::renderWorld()
{
    this->window->draw(this->worldBackground);
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::render()
{
    this->window->clear();

    // Draw game world
    this->renderWorld();

    // Draw all the stuff
    this->player->render(*this->window);

    for (auto *i : bullets)
    {
        i->render(*this->window);
    }

    for (auto *i : enemies)
    {
        i->render(*this->window);
    }

    this->renderGUI();

    // Game over screen
    if (this->player->getHp() <= 0)
    {
        this->window->draw(this->gameOverText);
    }

    this->window->display();
}
// ---------------------------------------------------------------------------------------------------------------------
