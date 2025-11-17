#include "GamesEngineeringBase.h"
#include "Projectile.h"

//Create proj const
Projectile::Projectile(const std::string& projFileLoc)
{
	projectileImg.load(projFileLoc);
}

//How proj is drawn
void Projectile::drawProj(float cameraX, float cameraY, float cameraLeft, float cameraTop, GamesEngineeringBase::Window& canvas) {
	int screenW = canvas.getWidth();
	int screenH = canvas.getHeight();

	for (int py = 0; py < projectileImg.height; py++) {
		for (int px = 0; px < projectileImg.width; px++) {
			int drawX = static_cast<int>(projectilePosX + px - cameraLeft);
			int drawY = static_cast<int>(projectilePosY + py - cameraTop);

			if (drawX < 0 || drawY < 0 || drawX >= screenW || drawY >= screenH) continue;

			if (projectileImg.alphaAt(px, py) > 0) {
				unsigned char* pixel = projectileImg.at(px, py);
				canvas.draw(drawX, drawY, pixel);
			}
		}
	}
}

//How projectile is updated
void Projectile::moveToEnemyPos(float enemyPosX, float enemyPosY) {

	float projectileDX = enemyPosX - projectilePosX;
	float projectileDY = enemyPosY - projectilePosY;
	
	float root = sqrt(projectileDX * projectileDX + projectileDY * projectileDY);

	projectileDirX = projectileDX/root;
	projectileDirY = projectileDY/root;

}

//How projectile is set from the players position
void Projectile::setFromPlayerPos(float x, float y) {
	projectilePosX = x;
	projectilePosY = y;
}


//Checking distance between the enemy and player
bool Projectile::hitEnemy(float enemyX, float enemyY) const {
	float distanceX = enemyX - projectilePosX;
	float distanceY = enemyY - projectilePosY;
	float distanceRt = distanceX * distanceX + distanceY * distanceY;
	//If distance close to enemy then return saying (true it hit enemy)
	if (distanceRt < 900.0f) {
		return true;
	}
	else {
		return false;
	}
}
//For time alive
void Projectile::countdown(float dt) {
	projectileTime -= dt;
}
//For checking if alive too long
bool Projectile::checkTime() {
	if (projectileTime <= 0) {
		return true;
	}
	else {
		return false;
	}
}
//Move projectile function
void Projectile::update(float dt) {
	projectilePosX += projectileDirX * projectileSpeed * dt;
	projectilePosY += projectileDirY * projectileSpeed * dt;
}