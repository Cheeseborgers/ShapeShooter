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

#ifndef UNTITLED1_BULLET_H
#define UNTITLED1_BULLET_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <memory>
#include <sstream>
#include <ctime>

class Bullet {

private:
    sf::Sprite sprite;

    sf::Vector2f direction;
    float velocity{};

public:
    // Constructor
    Bullet();
    Bullet(sf::Texture* bulletTexture, float posX, float posY, float dir_x, float dir_y, float initial_velocity);
    virtual ~Bullet();

    // Accessor
    sf::FloatRect getBounds() const;

    // Methods
    void update();
    void render(sf::RenderTarget& target);
};


#endif //UNTITLED1_BULLET_H
