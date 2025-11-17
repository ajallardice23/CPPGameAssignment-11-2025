#pragma once
#include "Enemy.h"
#include "Projectile.h"
#include "Player.h"
#include "EnemyProjectile.h"

class Manager {
private:
	float spawnTimer = 0.4f;
	int i = 0;
	Enemy* enemies[100] = { nullptr };
	Projectile* projectiles[10] = { nullptr };
	EnemyProjectile* enemyProjectiles[100] = { nullptr };
	int pI = 0;

public:

	//{ENEMIES}
	void spawnInEnemy(int maxEnemies);

	void drawEnemies(GamesEngineeringBase::Window& canvas, float cameraLeft, float cameraTop);

	void updateEnemy(float playerX, float playerY, float dt);

	void checkEnemyHealth();


	//{AOE}
	void areaOfEffect();

	//{PROJECTILES}
	void spawnInProjectile(float playerX, float playerY);

	void drawProjectiles(GamesEngineeringBase::Window& canvas, float cameraLeft, float cameraTop);
	void updateProjectiles(float dt);


	//{ENEMY PROJECTILES}
	void spawnInEnemyProjectiles(float playerX, float playerY);

	void drawEnemyProjectiles(GamesEngineeringBase::Window& canvas, float cameraLeft, float cameraTop);

	void updateEnemyProjectiles(float dt);


	//{COLLISIONS}
	void checkEnemyPlayerCollision(float playerPosX, float playerPosY, Player& player, float& playerCollisionCooldown);
	void checkPlayerProjectileCollisions();
	void checkEnemyProjectileCollisions(float playerX, float playerY, Player& player);





	//{SAVING AND LOADING}

	void saveGame(Player& player, int mapType, int fileNum);
	void loadGame(Player& player, int& mapType, int fileNum);
};