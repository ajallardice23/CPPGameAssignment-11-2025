#include "Camera.h"

//Player and canvas passed as parameters from game loop
void Camera::followPlayer(float playerTargetX, float playerTargetY, int canvasWidth, int canvasHeight) {
	//Center camera on player
	x = playerTargetX - (canvasWidth / 2);
	y = playerTargetY - (canvasHeight / 2);
}

//Start position for camera
Camera::Camera(float startx, float starty) {
	x = startx;
	y = starty;
}
