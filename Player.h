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

#ifndef UNTITLED1_PLAYER_H
#define UNTITLED1_PLAYER_H


#include "Bullet.h"

class Player {

private:
    sf::Sprite sprite;
    sf::Texture texture;

    float velocity{};
    unsigned points{};
    int hp{};
    int hpMax{};

    float attackCoolDown{};
    float attackCoolDownMax{};

    // Private methods
    void initTexture();
    void initSprite();

public:
    // Constructor
    Player();

    //Accessors
    const sf::Vector2f& getPosition() const;
    sf::FloatRect getBounds() const;
    unsigned getPoints() const;
    const int& getHp() const;
    const int& getHpMax() const;

    // Modifiers
    void setPosition(sf::Vector2f pos);
    void setPosition(float x, float y);
    void setPoints(unsigned value);
    void setHp(int value);
    void loseHp(int value);

    // Methods
    void move(float dirX, float dirY);
    bool canAttack();

    void updateAttackCoolDown();
    void update();
    void render(sf::RenderTarget& target);

};


#endif //UNTITLED1_PLAYER_H
