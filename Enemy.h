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

#ifndef UNTITLED1_ENEMY_H
#define UNTITLED1_ENEMY_H

#include <SFML/Graphics.hpp>

#include <iostream>

class Enemy {

private:
    unsigned pointCount{};
    sf::CircleShape shape;
    int type{};
    float velocity{};
    int hp{};
    int hpMax{};
    int damageGain{};
    int pointGain{};

    void initVariables();
    void initShape();

public:
    // Constructor
    Enemy(float posX, float posY);

    // Accessors
    sf::FloatRect getBounds() const;
    const int& getPointsGain() const;
    const int& getDamageGain() const;

    // Methods
    void update();
    void render(sf::RenderTarget& target);
};


#endif //UNTITLED1_ENEMY_H
