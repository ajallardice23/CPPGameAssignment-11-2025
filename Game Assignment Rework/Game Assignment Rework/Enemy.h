#pragma once
#include "GamesEngineeringBase.h"

class Enemy {
private:
	GamesEngineeringBase::Image enemyImg;
	//Enemy attributes
	std::string enemyType;
	int enemyHealth;
	float enemySpeed;
	std::string enemyFileLoc;
	float x, y;



public:
	Enemy(const std::string& enemyType, int enemyHealth, float enemySpeed, const std::string& enemyFileLoc);

	float getEnemyX() {
		return x + (enemyImg.width / 2.0f);
	}
	float getEnemyY() {
		return y + (enemyImg.height / 2.0f);
	}

	void drawEnemy(float locationX, float locationY, float cameraLeft, float cameraTop, GamesEngineeringBase::Window& canvas);

	void spawnEnemyAt(float x, float y);

	void moveToPlayerPos(float playerX, float playerY, float dt);

	void setEnemyHealth(int newhealth);
	void takedamage(int damageAmount);

	//{GET ENEMY HEALTH}
	float getEnemyHealth() const;

	//{GET ENEMY TYPE}
	//used for the skeleton (proj)
	std::string getEnemyType() const;
};

Enemy* getRandomEnemy();
Enemy* getClosestEnemy(float playerX, float playerY, Enemy** enemies);
