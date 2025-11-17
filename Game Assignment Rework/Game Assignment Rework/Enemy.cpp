#include "Enemy.h"

Enemy::Enemy(const std::string& enemyType, int enemyHealth, float enemySpeed, const std::string& enemyFileLoc) :
	enemyType(enemyType), enemyHealth(enemyHealth), enemySpeed(enemySpeed), enemyFileLoc(enemyFileLoc), x(0.0f), y(0.0f) {
	enemyImg.load(enemyFileLoc);

}

Enemy* getRandomEnemy() {
	int randEnemy = std::rand() % 4;

	switch (randEnemy) {
	case 0:	//Slow large enemy (high health)
		return new Enemy("Minotaur", 200, 0.2f, "Resources/Enemies/Minotaur.png");
	case 1:		//Fast goblin (low health)
		return new Enemy("Goblin", 50, 0.7f, "Resources/Enemies/Goblin.png");
	case 2:		//Mediunm skeleton (medium health)
		return new Enemy("Skeleton", 100, 0.6f, "Resources/Enemies/Skeleton.png");
	case 3:		//Archer (Projectile enemy)
		return new Enemy("Archer", 150, 0.0f, "Resources/Enemies/Archer.png");
	}
}

//{GET CLOSEST}
Enemy* getClosestEnemy(float playerX, float playerY, Enemy** enemies) {
	//high dist to set current 
	float currentEnemyClosestDistance = 69696;

	Enemy* currentEnemyClosest = nullptr;
	//Loop through enemies

	for (int i = 0; i < 100; i++) {
		if (enemies[i] != nullptr) {
			//get xy for each
			float distanceFromPlayerX = enemies[i]->getEnemyX() - playerX;
			float distanceFromPlayerY = enemies[i]->getEnemyY() - playerY;

			//dis rt (swarm code from lecture)
			float root = distanceFromPlayerX * distanceFromPlayerX + distanceFromPlayerY * distanceFromPlayerY;

			//if closer to player take top pos
			if (root < currentEnemyClosestDistance) {
				currentEnemyClosestDistance = root;
				currentEnemyClosest = enemies[i];
			}
		}
	}
	//std::cout << "closest enemy      " << currentEnemyClosest;
	return currentEnemyClosest;
}

void Enemy::drawEnemy(float cameraX, float cameraY, float cameraLeft, float cameraTop, GamesEngineeringBase::Window& canvas) {
	int screenW = canvas.getWidth();
	int screenH = canvas.getHeight();

	for (int py = 0; py < enemyImg.height; py++) {
		for (int px = 0; px < enemyImg.width; px++) {
			int drawX = static_cast<int>(x + px - cameraLeft);
			int drawY = static_cast<int>(y + py - cameraTop);

			if (drawX < 0 || drawY < 0 || drawX >= screenW || drawY >= screenH) continue;

			if (enemyImg.alphaAt(px, py) > 0) {
				unsigned char* pixel = enemyImg.at(px, py);
				canvas.draw(drawX, drawY, pixel);
			}
		}
	}
}


void Enemy::moveToPlayerPos(float playerX, float playerY, float dt) {
	//Get center of img
	float enemyCenterX = x + enemyImg.width * 0.5f;
	float enemyCenterY = y + enemyImg.height * 0.5f;
	//Calc player direction from enemy
	float directionX = playerX - enemyCenterX;
	float directionY = playerY - enemyCenterY;
	//Calculate distance
	float length = sqrt(directionX * directionX + directionY * directionY);
	if (length != 0) {
		directionX /= length;
		directionY /= length;
	}
	//Move at default speed * enemy speed
	float speed = 80.0f;
	x += directionX * speed * dt * enemySpeed;
	y += directionY * speed * dt * enemySpeed;
}

void Enemy::spawnEnemyAt(float posX, float posY) {
	x = posX;
	y = posY;
}

//{DAMAGE}
void Enemy::takedamage(int damageAmount) {
	if (enemyHealth <= 0) {
		enemyHealth = 0;
	}
	else {
		enemyHealth -= damageAmount;
	}
}

//getting and set enemy health/get enemy type
float Enemy::getEnemyHealth() const { return enemyHealth; }

std::string Enemy::getEnemyType() const { return enemyType; }

void Enemy::setEnemyHealth(int newhealth) {
	enemyHealth = newhealth;
}