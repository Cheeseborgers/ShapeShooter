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

#include "Bullet.h"


// Constructors --------------------------------------------------------------------------------------------------------
Bullet::Bullet() = default;
// ---------------------------------------------------------------------------------------------------------------------
Bullet::Bullet(sf::Texture* bulletTexture, float posX, float posY, float dir_x, float dir_y, float initial_velocity)
    :  direction(sf::Vector2f(dir_x, dir_y)), velocity(initial_velocity)
{
    this->sprite.setTexture(*bulletTexture);
    this->sprite.setPosition(posX, posY);
}
// Deconstructor--------------------------------------------------------------------------------------------------------
Bullet::~Bullet() = default;
// Methods -------------------------------------------------------------------------------------------------------------
void Bullet::update()
{
    // Movement
    this->sprite.move(this->velocity * this->direction);
}
// ---------------------------------------------------------------------------------------------------------------------
void Bullet::render(sf::RenderTarget &target)
{
    /* @return void
     * Draws the bullet sprite to the target window.
     */

    target.draw(this->sprite);
}
// ---------------------------------------------------------------------------------------------------------------------
sf::FloatRect Bullet::getBounds() const
{
    /* @return sf::FloatRect
     * returns global bounds of the
     *   bullet.
     */

    return this->sprite.getGlobalBounds();
}
//----------------------------------------------------------------------------------------------------------------------
