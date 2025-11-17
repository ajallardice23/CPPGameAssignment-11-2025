#pragma once
#include "GamesEngineeringBase.h"

class EnemyProjectile {
public:
	EnemyProjectile(const std::string& projFileLoc);

	//For spawn
	void setFromEnemyPos(float x, float y);
	void update(float dt);

	//Shoot towards player pos
	void moveToPlayerPos(float enemyPosX, float enemyPosY);
	bool checkTime();

	void drawProj(float cameraX, float cameraY, float cameraLeft, float cameraTop, GamesEngineeringBase::Window& canvas);


	//Countdown so I can make projectile despawn (if enemy miss)
	void countdown(float dt);

	//{GET PROJECTILE POS}
	float getEnemyProjX() { return projectilePosX; }
	float getEnemyProjY() { return projectilePosY; }


	bool hitPlayer(float enemyX, float enemyY) const;



private:
	GamesEngineeringBase::Image projectileImg;
	float projectilePosX;
	float projectilePosY;

	float projectileDirX;
	float projectileDirY;

	float enemyPosX;
	float enemyPosY;

	float projectileSpeed = 500.0f;
	float projectileTime = 1.0f;

};