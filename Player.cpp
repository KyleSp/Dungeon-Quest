//Kyle Spurlock

#include "Player.h"

Player::Player(Sprite sIn, int xIn, int yIn) :
	Entity(sIn, "Player", xIn, yIn, 100, 10, 0), level(1), direction(0), attackCooldown(0) {}

void Player::calcMove(int gains[2]) {
	int xGain = 0;
	int yGain = 0;
	
	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
		yGain = -1;
		direction = 1;
	} else if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
		yGain = 1;
		direction = 3;
	}

	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
		xGain = -1;
		direction = 2;
	} else if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
		xGain = 1;
		direction = 4;
	}
	
	gains[0] = xGain;
	gains[1] = yGain;
}

int Player::checkCollisions(vector<vector<Pixel> > tiles, int gains[2], int height) {
	if (tiles[getY() + gains[1]][getX() + gains[0]].getName() == "Wall") {
		if (tiles[getY() + gains[1]][getX()].getName() == "Background") {
			gains[0] = 0;
		} else if (tiles[getY()][getX() + gains[0]].getName() == "Background") {
			gains[1] = 0;
		} else {
			gains[0] = 0;
			gains[1] = 0;
		}
	} else if (tiles[getY() + gains[1]][getX() + gains[0]].getName() == "Door") {
		int doorNum;
		if (getY() + gains[1] == 0) {
			doorNum = 0;
		} else if (getX() + gains[0] == 0) {
			doorNum = 1;
		} else if (getY() + gains[1] == height - 1) {
			doorNum = 2;
		} else {
			doorNum = 3;
		}
		return doorNum;
	}
	return -1;
}

int Player::move(vector<vector<Pixel> > tiles, int height) {
	int gains[2];
	
	//calculate movement gains
	calcMove(gains);
	
	//check for collisions
	int doorNum = checkCollisions(tiles, gains, height);
	
	//update coordinates
	setX(getX() + gains[0]);
	setY(getY() + gains[1]);
	
	return doorNum;
}

void Player::levelUp() {
	for (int i = 0; i < NUM_LEVELS; ++i) {
		if (getXp() >= LEVELS[i] && level == i + 1) {
			++level;
		}
	}
}

int Player::getAttackCooldown() {
	return attackCooldown;
}

int Player::getDirection() {
	return direction;
}

int Player::getLevel() {
	return level;
}