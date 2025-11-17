#pragma once
#include "GamesEngineeringBase.h"
#include "Camera.h"
#include <iostream>


class Player {
public:
    Player(float playerX, float playerY);

    void updatePos(float x, float y);
    void draw(GamesEngineeringBase::Window& canvas, float cameraLeftBound, float cameraTopBound);
    void takedamage(int damageAmount);

    //{GET PLAYER POS}
    float getPlayerX() const;
    float getPlayerY() const;

    //{SET PLAYER POS}
    void setPlayerX(float setX);
    void setPlayerY(float setY);


	float getPlayerHealth() const;

    void setPlayerHealth(float health);

private:
    GamesEngineeringBase::Window* canvas;
    GamesEngineeringBase::Image sprite;
    Camera* camera;

    float xPosition, yPosition;
    int width{}, height{};
    int moveSpeed{ 1 };
    int playerHealth{ 100 };
};
