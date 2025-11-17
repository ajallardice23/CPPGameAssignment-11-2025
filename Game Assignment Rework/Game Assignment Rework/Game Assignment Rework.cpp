#include <iostream>
#include <fstream>
#include "GamesEngineeringBase.h"

//WM908 Programming and Fundamental Algorithms
//(MY) H files
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
#include "Tiles.h"
#include "Manager.h"
#include "Projectile.h"


int main() {


	//SAVESYS
	int load;
	std::cout << "Would you like to load a game or start new game? " << std::endl;
	std::cout << "[0] NEW" << std::endl;
	std::cout << "[1] LOAD" << std::endl;
	std::cin >> load;


	int fileNum;
	std::cout << "What file would you like to choose to load/save to?" << std::endl;
	std::cin >> fileNum;

	int mapType;

	if (load != 1) {
		//{GAME QUESTIONS FOR USER}
		std::cout << "What type of map would you like " << std::endl;
		std::cout << "[1] FIXED MAP" << std::endl;
		std::cout << "[2] INFINITE MAP" << std::endl;
		std::cin >> mapType;
	}
	




	//Create window
	GamesEngineeringBase::Window canvas;
	canvas.create(1024, 768, "Minatours");

	//Create timer
	GamesEngineeringBase::Timer timer;
	
	//Create Manager
	Manager manager;

	//Set player mid screen (*.5 for half)
	float playerX = canvas.getWidth() * 0.5f;
	float playerY = canvas.getHeight() * 0.5f;
	Player player(playerX, playerY);

	//start camera with player in mid (center)
	float startX = playerX - canvas.getWidth() * 0.5f;
	float startY = playerY - canvas.getHeight() * 0.5f;
	Camera camera(startX, startY);

	//initialise tiles
	tileSet tileset("");
	Environment enviro;
	




	//load map
	
	enviro.loadFixedEnvironment("Resources/Tiles/landscape.png");

	

	//Cooldowns
	float projCooldown = 0.0f;
	float aoeCooldown = 0.0f;
	float playerCollisionCooldown = 0.0f;

	//Powerup bool
	bool powerup = true;
	float powerUpTimer = 30.0f;

	int maxEnemiesAllowed = 5;
	float increaseEnemyTimer = 0.0f;
	//LOAD GAME
	if (load == 1) {
		manager.loadGame(player, mapType, fileNum);
	}

	float fpstimer = 0;
	int FPS = 0;


	while (true) {
		canvas.checkInput();
		canvas.clear();
		if (canvas.keyPressed(VK_ESCAPE)) {
			manager.saveGame(player, mapType, fileNum);
			break;
		}
		if (player.getPlayerHealth() <= 0) {
			break;
		}

		//Timer
		float dt = timer.dt();

		//Fps calculation
		fpstimer += dt;
		FPS++;
		if (fpstimer >= 1.0f) {
			std::cout << "FPS = " << FPS << std::endl;
			FPS = 0;
			fpstimer = 0;
		}


		//camera follow player
		camera.followPlayer(player.getPlayerX(), player.getPlayerY(), canvas.getWidth(), canvas.getHeight());

		//{TILES/MAP FUNC}
		if (mapType == 2) {
			enviro.drawEnvironment(canvas, camera.getCamX(), camera.getCamY());
		}
		else {
			enviro.drawFixedEnvironment(canvas, -camera.getCamX(), -camera.getCamY());
		}

		//ENEMY TIMER (increase frequency over time)
		increaseEnemyTimer += dt;
		if (increaseEnemyTimer >= 10.0f) {
			maxEnemiesAllowed += 2;
			increaseEnemyTimer = 4.0f;
			if (maxEnemiesAllowed > 99) {
				maxEnemiesAllowed = 99;
			}
		}


		//Spawn enemy & check all health
		manager.spawnInEnemy(maxEnemiesAllowed);
		manager.checkEnemyHealth();

		//Spawn projectile and cooldown by 1s
		projCooldown -= dt;
		if (projCooldown <= 0) {
			manager.spawnInProjectile(player.getPlayerX(), player.getPlayerY());
			manager.spawnInEnemyProjectiles(player.getPlayerX(), player.getPlayerY());
			projCooldown = 1.0f;
			std::cout << player.getPlayerHealth() << std::endl;
		}

		//{AOE}
		powerUpTimer -= dt;
		aoeCooldown -= dt;

		//powerup every 30s
		if (powerUpTimer <= 0) {
			powerup = true;
			powerUpTimer = 30.0f;
		}

		if (canvas.keyPressed(VK_SPACE) && aoeCooldown <= 0) {
			//If has powerup run aoe 10x
			if (powerup == true) {
				for (int i = 0; i < 10; i++)
					manager.areaOfEffect();
			}
			else {
				manager.areaOfEffect();
			}

			//reset cooldown and powerup to false
			aoeCooldown = 10.0f;
			powerup = false;
		}
		


		//{PLAYER MOVEMENT}
		float moveX = 0;
		float moveY = 0;
		float speed = 100.0f;

		
		
		//Move the playre on keypress
		if (canvas.keyPressed('A')) {
			moveX -= speed * dt;
		}
		if (canvas.keyPressed('D')) {
			moveX += speed * dt;
		}
		if (canvas.keyPressed('S')) {
			moveY += speed * dt;
		}
		if (canvas.keyPressed('W')) {
			moveY -= speed * dt;
		}

		//Colours and movement
		float testMoveX = player.getPlayerX() + moveX;
		float testMoveY = player.getPlayerY() + moveY;
		
		//{UPDATES}
		//RGB Conditions (took a lot of trial and error)
		if (mapType == 1) {

			Colour testColour = enviro.getColour(static_cast<int>(testMoveX), static_cast<int>(testMoveY));

			if (testColour.r < 12 && testColour.g > 62 && testColour.g < 82 && testColour.b > 102 && testColour.b < 122) {

			}
			//Allow move if not water
			else {
				player.updatePos(player.getPlayerX() + moveX, player.getPlayerY() + moveY);
			}
		}
		else {
			player.updatePos(player.getPlayerX() + moveX, player.getPlayerY() + moveY);
		}
		//enemy
		manager.updateEnemy(player.getPlayerX(), player.getPlayerY(), dt);
		//proj
		manager.updateProjectiles(dt);
		//enemyproj
		manager.updateEnemyProjectiles(dt);



		//{COLLISIONS}
		//cooldown in manager for player enemy collsion
		manager.checkEnemyPlayerCollision(player.getPlayerX(), player.getPlayerY(), player, playerCollisionCooldown);
		
		if (playerCollisionCooldown > 0) {
			playerCollisionCooldown -= dt;
		}



		manager.checkPlayerProjectileCollisions();
		manager.checkEnemyProjectileCollisions(player.getPlayerX(), player.getPlayerY(), player);

		//{DRAW}
		//Drawplayer
		player.draw(canvas, camera.getCamX(), camera.getCamY());
	
		//drawEmemy
		manager.drawEnemies(canvas, camera.getCamX(), camera.getCamY());

		//drawProj
		manager.drawProjectiles(canvas, camera.getCamX(), camera.getCamY());

		//drawenemyproj
		manager.drawEnemyProjectiles(canvas, camera.getCamX(), camera.getCamY());
		canvas.present();
		
	}


	return 0;
}