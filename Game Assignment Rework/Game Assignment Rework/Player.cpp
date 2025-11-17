#include "GamesEngineeringBase.h"
#include "Player.h"
#include "Camera.h"


Player::Player(float playerX, float playerY)
{
    sprite.load("Resources/Player.png");
    //Get cam and canvas
}

//Making player stay middle of cam (w and h/2 to centre as player too far right)
void Player::updatePos(float x, float y) {
    xPosition = x - sprite.width * 0.5f;
    yPosition = y - sprite.height * 0.5f;
}

void Player::draw(GamesEngineeringBase::Window& canvas, float cameraLeft, float cameraTop) {
    //Minus camera position x and y from player to ensure that player always draw mid screen
    for (int y = 0; y < sprite.height; y++) {
        for (int x = 0; x < sprite.width; x++) {
            if (sprite.alphaAt(x, y) > 0) {
                unsigned char* pixel = sprite.at(x, y);
                canvas.draw(x + xPosition - cameraLeft, y + yPosition - cameraTop, pixel);
            }
        }
    }
}

//{DAMAGE}
void Player::takedamage(int damageAmount) {
    playerHealth -= damageAmount;
}

//{GET PLAYER POS}
float Player::getPlayerX() const { return xPosition + sprite.width * 0.5f; }
float Player::getPlayerY() const { return yPosition + sprite.height * 0.5f; }

//{SET PLAYER POS}
void Player::setPlayerX(float setX){
    xPosition = setX;
}

void Player::setPlayerY(float setY){
    yPosition = setY;
}

//{GET PLAYER HEALTH}
float Player::getPlayerHealth() const { return playerHealth; }

void Player::setPlayerHealth(float health){
    playerHealth = health;
}

