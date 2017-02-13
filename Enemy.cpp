//Kyle Spurlock

#include "Enemy.h"

Enemy::Enemy(Sprite sIn, int xIn, int yIn) :
	Entity(sIn, "Enemy", xIn, yIn, 100, 10, 10), movementCooldown(5), attackCooldown(5) {
	srand(time(NULL));
}

void Enemy::calcMove(int gains[2], Entity ent) {
	int xGain = 0;
	int yGain = 0;
	
	int r = rand() % 3 + 1;
	
	if (r == 1) {
		xGain = rand() % 3 - 1;
		yGain = rand() % 3 - 1;
	} else {
		int r2 = rand() % 2 + 1;
		if (r2 == 1) {
			if (ent.getX() > getX()) {
				xGain = 1;
			} else if (ent.getX() < getX()) {
				xGain = -1;
			}
		} else {
			if (ent.getY() > getY()) {
				yGain = 1;
			} else if (ent.getY() < getY()) {
				yGain = -1;
			}
		}
	}
	
	gains[0] = xGain;
	gains[1] = yGain;
}

void Enemy::checkCollisions(vector<vector<Pixel> > tiles, int gains[2]) {
	if (tiles[getY() + gains[1]][getX() + gains[0]].getName() == "Wall" ||
		tiles[getY() + gains[1]][getX() + gains[0]].getName() == "Door") {
		if (tiles[getY() + gains[1]][getX()].getName() == "Background") {
			gains[0] = 0;
		} else if (tiles[getY()][getX() + gains[0]].getName() == "Background") {
			gains[1] = 0;
		} else {
			gains[0] = 0;
			gains[1] = 0;
		}
	}
}

void Enemy::move(vector<vector<Pixel> > tiles, Entity ent) {
	int gains[2];
	
	//calculate movement gains
	calcMove(gains, ent);
	
	//check for collisions
	checkCollisions(tiles, gains);
	
	//update coordinates
	setX(getX() + gains[0]);
	setY(getY() + gains[1]);
}

bool Enemy::attack(Entity &ent) {
	if (ent.getX() == getX() && ent.getY() == getY() && isAlive() && ent.isAlive()) {
		ent.setHealth(ent.getHealth() - getAttack());
		return true;
	}
	return false;
}

int Enemy::getAttackCooldown() {
	return attackCooldown;
}

int Enemy::getMovementCooldown() {
	return movementCooldown;
}