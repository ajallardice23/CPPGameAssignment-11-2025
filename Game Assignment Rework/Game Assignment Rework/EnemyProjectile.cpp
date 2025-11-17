#include "GamesEngineeringBase.h"
#include "EnemyProjectile.h"

//Create proj const
EnemyProjectile::EnemyProjectile(const std::string& projFileLoc)
{
	projectileImg.load(projFileLoc);
}


void EnemyProjectile::drawProj(float cameraX, float cameraY, float cameraLeft, float cameraTop, GamesEngineeringBase::Window& canvas) {
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


void EnemyProjectile::moveToPlayerPos(float enemyPosX, float enemyPosY) {

	float projectileDX = enemyPosX - projectilePosX;
	float projectileDY = enemyPosY - projectilePosY;

	float root = sqrt(projectileDX * projectileDX + projectileDY * projectileDY);

	projectileDirX = projectileDX / root;
	projectileDirY = projectileDY / root;

}


void EnemyProjectile::setFromEnemyPos(float x, float y) {
	projectilePosX = x;
	projectilePosY = y;
}



bool EnemyProjectile::hitPlayer(float playerX, float playerY) const {
	float distanceX = playerX - projectilePosX;
	float distanceY = playerY - projectilePosY;
	float distanceRt = distanceX * distanceX + distanceY * distanceY;
	//If distance close to enemy then return saying (true it hit enemy)
	if (distanceRt < 900.0f) {
		return true;
	}
	else {
		return false;
	}
}

void EnemyProjectile::countdown(float dt) {
	projectileTime -= dt;
}

bool EnemyProjectile::checkTime() {
	if (projectileTime <= 0) {
		return true;
	}
	else {
		return false;
	}
}

void EnemyProjectile::update(float dt) {
	projectilePosX += projectileDirX * projectileSpeed * dt;
	projectilePosY += projectileDirY * projectileSpeed * dt;
}