#include "Manager.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Player.h"

#include <fstream>

//SCORING
int playerScore = 0;



//{ENEMIES}
void Manager::spawnInEnemy(int maxEnemies) {
	//check for how many enemies are allowed at a time
	if (i >= maxEnemies) return;
	float screenRand = rand() % 2;

	//Create new enemy select from rand
	Enemy* enemy = getRandomEnemy();

	//Spawn off screen, decide which side
	if (screenRand == 0) {
		enemy->spawnEnemyAt((rand() % 1024 + 1024), (rand() % 768 + 768));
	}
	else {
		enemy->spawnEnemyAt(-(rand() % 1024 + 1024), -(rand() % 768 + 768));
	}


	//add enemy array
	enemies[i++] = enemy;

	if (i > 100) {
		i = 100;
	}
}

void Manager::drawEnemies(GamesEngineeringBase::Window& canvas, float cameraLeft, float cameraTop) {
	for (int j = 0; j < 100; j++) {
		//Cycle through and draw
		if (enemies[j] != nullptr) {
			enemies[j]->drawEnemy(enemies[j]->getEnemyX(), enemies[j]->getEnemyY(), cameraLeft, cameraTop, canvas);
		}
	}
}

void Manager::updateEnemy(float playerX, float playerY, float dt) {
	//Loop through enemy array
	for (int j = 0; j < 100; j++) {
		if (enemies[j] != nullptr) {
			//Only make enemies move to player if not horse(archer) as this is the static enemy
			if (enemies[j]->getEnemyType() != "Archer") {
				enemies[j]->moveToPlayerPos(playerX, playerY, dt);
			}
		}
	}
}
//Note to self - Swarm
void Manager::checkEnemyHealth(){
	for (int j = 0; j < 100; j++) {
		if (enemies[j] != nullptr) {
			//cycle through each health
			if (enemies[j]->getEnemyHealth() <= 0) {
				//kill if health is 0
				delete enemies[j];
				enemies[j] = nullptr;
				playerScore += 1;
				//output score
				std::cout << "PLAYER SCORE: " << playerScore << std::endl;
			}
		}
	}
}

//{ENEMY PROJECTILES}
void Manager::spawnInEnemyProjectiles(float playerX, float playerY) {
	for (int j = 0; j < 100; j++) {
		if (enemies[j] != nullptr) {
			//too many enemies shoot same time so I made a chance to shoot
			int shootChance = rand() % 8;
			//If the enemy is an archer only
			if (enemies[j]->getEnemyType() == "Archer" && shootChance == 1) {
				enemyProjectiles[j] = new EnemyProjectile("Resources/Weapons/Arrow.png");
				enemyProjectiles[j]->setFromEnemyPos(enemies[j]->getEnemyX(), enemies[j]->getEnemyY());
				enemyProjectiles[j]->moveToPlayerPos(playerX, playerY);
			}
		}
	}
}

void Manager::drawEnemyProjectiles(GamesEngineeringBase::Window& canvas, float cameraLeft, float cameraTop) {
	for (int j = 0; j < 100; j++) {
		if (enemyProjectiles[j] != nullptr) {
			enemyProjectiles[j]->drawProj(enemyProjectiles[j]->getEnemyProjX(), enemyProjectiles[j]->getEnemyProjY(), cameraLeft, cameraTop, canvas);
		}
	}
}
void Manager::updateEnemyProjectiles(float dt) {
	for (int j = 0; j < 100; j++) {
		//Proj time alive count
		if (enemyProjectiles[j] != nullptr) {
			enemyProjectiles[j]->countdown(dt);
			enemyProjectiles[j]->update(dt);
			if (enemyProjectiles[j]->checkTime()) {
				delete enemyProjectiles[j];
				enemyProjectiles[j] = nullptr;
			}
		}
	}
}






//{AOE}
void Manager::areaOfEffect() {
	//Set low value to start the check
	int enemyHighestHealth = 1;
	Enemy* currentEnemyHighestHealth = nullptr;

	//loop check for highest health
	for (int i = 0; i < 100; i++) {
		if (enemies[i] != nullptr) {
			float enemyHealth = enemies[i]->getEnemyHealth();
			//If next health higher update
			if (enemyHealth >= enemyHighestHealth) {
				enemyHighestHealth = enemyHealth;
				currentEnemyHighestHealth = enemies[i];
			}
		}
	}
	//After loop kill enemy (damage is bigger than anyt enemies hp)
	currentEnemyHighestHealth->takedamage(500);
}


//{PLAYER PROJECTILES}
void Manager::spawnInProjectile(float playerX, float playerY) {
	Enemy* closestEnemy = getClosestEnemy(playerX, playerY, enemies);
	
	if (closestEnemy != nullptr) {		
		//Find empty slots in arr
		for (int j = 0; j < 10; j++) {
			if (projectiles[j] == nullptr) {
				//Add a new projectile to the array, set from player toward enemy
				projectiles[j] = new Projectile("Resources/Weapons/ThrowingAxe.png");
				projectiles[j]->setFromPlayerPos(playerX, playerY);
				projectiles[j]->moveToEnemyPos(closestEnemy->getEnemyX(), closestEnemy->getEnemyY());
				break;
			}
		}

	}
}

void Manager::drawProjectiles(GamesEngineeringBase::Window& canvas, float cameraLeft, float cameraTop) {
	for (int j = 0; j < 10; j++) {
		if (projectiles[j] != nullptr) {
			projectiles[j]->drawProj(projectiles[j]->getProjX(), projectiles[j]->getProjY(), cameraLeft, cameraTop, canvas);
		}
	}
}

void Manager::updateProjectiles(float dt) {
	for (int j = 0; j < 10; j++) {
		//Proj time alive count loop through
		if (projectiles[j] != nullptr) {
			projectiles[j]->countdown(dt);
			projectiles[j]->update(dt);
			if (projectiles[j]->checkTime()) {
				delete projectiles[j];
				projectiles[j] = nullptr;
			}
		}
	}
}



//{COLLISIONS}
//Note to self - refer to swarm code from lectures
void Manager::checkEnemyPlayerCollision(float playerPosX, float playerPosY, Player& player, float& playerCollisionCooldown) {
	//(+ a bitr extra for close)
	float offset = 10.0f;


	for (int j = 0; j < 100; j++) {
		if (enemies[j] != nullptr) {
			float enemyPosX = enemies[j]->getEnemyX();
			float enemyPosY = enemies[j]->getEnemyY();

			float disX = enemyPosX - playerPosX;
			float disY = enemyPosY - playerPosY;
			//dis rt
			float root = sqrt(disX * disX + disY * disY);
			//if within range collide with player
			if (root < offset) {
				if (playerCollisionCooldown <= 0) {
					player.takedamage(10);
					std::cout << "COLLISION TEST" << std::endl;
					playerCollisionCooldown = 1.0f;
				}
			}
		}
	}
}


void Manager::checkPlayerProjectileCollisions() {
	for (int i = 0; i < 10; i++) {
		//loop through all proj and all enemies to detect any collision
		if (projectiles[i] != nullptr) {
			for (int j = 0; j < 100; j++) {
				if (enemies[j] != nullptr) {
					if (projectiles[i]->hitEnemy(enemies[j]->getEnemyX(), enemies[j]->getEnemyY())) {
						enemies[j]->takedamage(50);
						delete projectiles[i];
						projectiles[i] = nullptr;
						//note to self - DONT DELETE THIS BREAK THIS IS THE CAUSE OF THE NULLPTR ERROR/
						//it is breaking out on hit so it knows projectilehit
						break;
					}
				}
			}
		}
	}
}


void Manager::checkEnemyProjectileCollisions(float playerX, float playerY, Player& player) {
	for (int i = 0; i < 10; i++) {
		if (enemyProjectiles[i] != nullptr) {
			if (enemyProjectiles[i]->hitPlayer(playerX, playerY)) {
				player.takedamage(10);
				delete enemyProjectiles[i];
				enemyProjectiles[i] = nullptr;
				//note to self - DONT DELETE THIS BREAK THIS IS THE CAUSE OF THE NULLPTR ERROR/
				//it is breaking out on hit so it knows projectilehit
				break;
			}
		}
	}
}







//{SAVING AND LOADING}

void Manager::saveGame(Player& player, int mapType, int fileNum) {
	//Open file name and what the name to save chosen in main loopp
	std::string filePath = ("Resources/Saves/" + std::to_string(fileNum) + ".txt");
	std::ofstream playerSaveGame(filePath);
	//save all player info
	playerSaveGame << player.getPlayerHealth() << "\n";
	playerSaveGame << mapType << "\n";
	playerSaveGame << player.getPlayerX() << "\n";
	playerSaveGame << player.getPlayerY() << "\n";
	playerSaveGame << playerScore << "\n";


	playerSaveGame << i << "\n";
	//Save all enemy info and loop through all enemies
	for (int j = 0; j < i; j++) {
		if (enemies[j] != nullptr) {
			playerSaveGame << enemies[j]->getEnemyType() << " " << enemies[j]->getEnemyHealth()
				<< " " << enemies[j]->getEnemyX() << " " << enemies[j]->getEnemyY() << "\n";
		}
	}
	playerSaveGame.close();
}

//Function to load game
void Manager::loadGame(Player& player, int& mapType, int fileNum) {
	std::string filePath = ("Resources/Saves/" + std::to_string(fileNum) + ".txt");
	std::ifstream playerLoadGame(filePath);
	
	//Load health
	int health;
	playerLoadGame >> health;
	player.setPlayerHealth(health);

	//load maptype
	playerLoadGame >> mapType;

	//Load position
	float playerX;
	float playerY;
	playerLoadGame >> playerX;
	player.setPlayerX(playerX);
	playerLoadGame >> playerY;
	player.setPlayerY(playerY);
	playerLoadGame >> playerScore;


	playerLoadGame >> i;


	//Enemy load loop (for each enemy saved)
	for (int j = 0; j < i; j++) {
		std::string enemyType;
		float enemyHealth;
		float enemyX;
		float enemyY;

		playerLoadGame >> enemyType >> enemyHealth >> enemyX >> enemyY;

		Enemy* enemy = getRandomEnemy();
		//Spawn enemy and set correct health
		enemy->setEnemyHealth(enemyHealth);
		enemy->spawnEnemyAt(enemyX, enemyY);

		enemies[j] = enemy;
	}

	playerLoadGame.close();

}


