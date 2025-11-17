#pragma once
#include "GamesEngineeringBase.h"
#include <iostream>



class Camera {
public:
    Camera(float startx, float starty);

    //Follow player function, pass in player positions
    void followPlayer(float playerTargetX, float playerTargetY, int canvasWidth, int canvasHeight);

    //{GET CAM POS}
    float getCamX() {
        return x;
    }
    float getCamY() {
        return y;
    }

private:
    GamesEngineeringBase::Window* canvas;
    //Cam Pos
    float x; //center
    float y;
    float cameraLeftBound; //left
    float cameraRightBound;
};
