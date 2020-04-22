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

#include "Player.h"

// Private functions ---------------------------------------------------------------------------------------------------
void Player::initTexture()
{
    // Load texture from file
    if (!this->texture.loadFromFile("textures/ship.png"))
    {
        std::cout << "ERROR::PLAYER::INITTEXTURE: Failed to load texture: ship.png\n";
    }

    // Resize the sprite
    this->sprite.scale(sf::Vector2f(0.1F, 0.1F));
}
// ---------------------------------------------------------------------------------------------------------------------
void Player::initSprite()
{
    // Set the texture to the sprite
    this->sprite.setTexture(this->texture);
}
// Constructor ---------------------------------------------------------------------------------------------------------
Player::Player()
{
    this->velocity = 3.F;
    this->points = 0;
    this->hpMax = 100;
    this->hp = hpMax;

    this->attackCoolDownMax = 10.F;
    this->attackCoolDown = this->attackCoolDownMax;

    this->initTexture();
    this->initSprite();
}
// Methods -------------------------------------------------------------------------------------------------------------
void Player::move(const float dirX, const float dirY)
{
    /* @return void
     * Moves the players sprite in relation to its velocity
     *  and the given x and y params.
     */

    this->sprite.move(this->velocity * dirX, this->velocity * dirY);
}
// ---------------------------------------------------------------------------------------------------------------------
bool Player::canAttack()
{
    /* @return bool
     * Returns whether the player can attack based on
     *  the attack player cool down.
     *  - Resets Cool down and returns true if higher or equal to max.
     *  - Else returns false leaving the current cool down timer value.
     */

    if (this->attackCoolDown >= this->attackCoolDownMax)
    {
        this->attackCoolDown = 0.F;
        return true;
    }

    return false;
}
// ---------------------------------------------------------------------------------------------------------------------
void Player::updateAttackCoolDown()
{
    /* @return void
     * Increments the player attack cool down if lower
     *  than the max
     */

    if (this->attackCoolDown < this->attackCoolDownMax)
    {
        this->attackCoolDown += 0.5F;
    }
}
// ---------------------------------------------------------------------------------------------------------------------
void Player::update()
{
    /* @return void
     * Updates player
     * - Update attack cool down
     */

    this->updateAttackCoolDown();
}
// ---------------------------------------------------------------------------------------------------------------------
void Player::render(sf::RenderTarget& target)
{
    /* @return void
     * Draws the player sprite to the target window.
     */

    target.draw(this->sprite);
}
// Accessors------------------------------------------------------------------------------------------------------------
const sf::Vector2f &Player::getPosition() const
{
    /* @return const sf::Vector2f const
     * returns the position of the player
     */

    return this->sprite.getPosition();
}
// ---------------------------------------------------------------------------------------------------------------------
sf::FloatRect Player::getBounds() const
{
    /* @return sf::FloatRect
     * returns global bounds of the
     *   player.
     */

    return this->sprite.getGlobalBounds();
}
// -------------------------------------------------------------------------------------------------------
const int &Player::getHp() const
{
    /* @return const int& const
     * returns the players hp
     */

    return this->hp;
}
// ----------------------------------------------------------------------------------------------------------------
const int &Player::getHpMax() const
{
    /* @return const int& const
     * returns the players Max hp
     */

    return this->hpMax;
}
// ------------------------------------------------------------------------------------------------------------
unsigned Player::getPoints() const
{
    /* @return unsigned const
     * returns the players points
     */

    return this->points;
}
// Modifiers -----------------------------------------------------------------------------------------------------------
void Player::setPosition(sf::Vector2f pos)
{
    /* @return void
     * sets the position of the player
     */

    this->sprite.setPosition(pos);
}
// ---------------------------------------------------------------------------------------------------------------------
void Player::setPosition(const float x, const float y)
{
    /* @return void
     * sets the position of the player
     */

    this->sprite.setPosition(x, y);
}
// ---------------------------------------------------------------------------------------------------------------------
void Player::setPoints(unsigned int value)
{
    /* @return void
     * sets the players points by adding the value
     *   to the current total
     */

    this->points += value;
}
// ---------------------------------------------------------------------------------------------------------------------
void Player::setHp(const int value)
{
    /* @return void
     * sets the players hp to the value
     */

    this->hp = value;
}
// ---------------------------------------------------------------------------------------------------------------------
void Player::loseHp(const int value)
{
    /* @return void
     * Decrements the current hp by the given value and ensures it does
     *  not fall below for display purposes.
     * - Sets player hp minus param value
     * - Checks and resets hp to 0 if below
     */

    this->hp -= value;

    if (this->hp < 0)
    {
        this->hp = 0;
    }
}
// ---------------------------------------------------------------------------------------------------------------------

