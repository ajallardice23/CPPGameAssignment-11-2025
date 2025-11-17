#pragma once

class Projectile {
public:
	Projectile(const std::string& projFileLoc);

	//For spawn
	void setFromPlayerPos(float x, float y);
	void update(float dt);

	//Shoot towards enemy pos
	void moveToEnemyPos(float enemyPosX, float enemyPosY);
	bool checkTime();

	void drawProj(float cameraX, float cameraY, float cameraLeft, float cameraTop, GamesEngineeringBase::Window& canvas);
	

	//Countdown so I can make projectile despawn (if enemy miss)
	void countdown(float dt);

	//{GET PROJECTILE POS}
	float getProjX() { return projectilePosX; }
	float getProjY() { return projectilePosY; }


	bool hitEnemy(float enemyX, float enemyY) const;



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