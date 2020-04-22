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

#include "Enemy.h"


// Private methods -----------------------------------------------------------------------------------------------------
void Enemy::initVariables()
{
    this->pointCount = rand() % 8 + 3; //min = 3 max = 10
    this->type = 0;
    this->velocity	= static_cast<float>(this->pointCount / 3);
    this->hpMax	= static_cast<int>(this->pointCount);
    this->hp = this->hpMax;
    this->damageGain = this->pointCount;
    this->pointGain	= this->pointCount;
}
// ---------------------------------------------------------------------------------------------------------------------
void Enemy::initShape()
{
    this->shape.setRadius(this->pointCount * 5);
    this->shape.setPointCount(this->pointCount);
    this->shape.setFillColor(
        sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}
// Constructor ---------------------------------------------------------------------------------------------------------
Enemy::Enemy(float posX, float posY)
{
    this->initVariables();

    this->initShape();

    this->shape.setPosition(posX, posY);
}
// Accessors -----------------------------------------------------------------------------------------------------------
sf::FloatRect Enemy::getBounds() const
{
    /* @return sf::FloatRect
     * returns global bounds of the
     *   enemy.
     */

    return this->shape.getGlobalBounds();
}
// ---------------------------------------------------------------------------------------------------------------------
const int &Enemy::getPointsGain() const
{
    return this->pointGain;
}
// ---------------------------------------------------------------------------------------------------------------------
const int &Enemy::getDamageGain() const
{
    return this->damageGain;
}
// Methods -------------------------------------------------------------------------------------------------------------
void Enemy::update()
{
    /* @return void
     * Update and moves the enemy's position
     *   down the screen using its velocity
     */

    this->shape.move(0.F, this->velocity);
}
// ---------------------------------------------------------------------------------------------------------------------
void Enemy::render(sf::RenderTarget &target)
{
    /* @return void
     * Draws the enemy shape to the target window.
     */

    target.draw(this->shape);
}
// ---------------------------------------------------------------------------------------------------------------------

