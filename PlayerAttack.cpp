//Kyle Spurlock

#include "PlayerAttack.h"

PlayerAttack::PlayerAttack(Sprite sIn, int xIn, int yIn) :
	Pixel(sIn, "PlayerAttack", xIn, yIn), direction(1), active(false) {}

void PlayerAttack::setAttackSymbol() {
	if (direction == 1) {
		getSprite().setRotation(0);
		getSprite().setOrigin({0, 0});
		getSprite().setScale({1, 1});
	} else if (direction == 2) {
		getSprite().setRotation(270);
		getSprite().setOrigin({0, getSprite().getLocalBounds().width});
		getSprite().setScale({-1, 1});
		
	} else if (direction == 3) {
		getSprite().setRotation(0);
		getSprite().setOrigin({0, 0});
		getSprite().setScale({1, -1});
	} else {
		getSprite().setRotation(90);
		getSprite().setOrigin({getSprite().getLocalBounds().width, getSprite().getLocalBounds().width});
		getSprite().setScale({-1, 1});
	}
}

bool PlayerAttack::init(Player plr) {
	if (Keyboard::isKeyPressed(Keyboard::Space) && !active) {
		active = true;
		
		direction = plr.getDirection();
		
		setAttackSymbol();
		
		setX(plr.getX());
		setY(plr.getY());
		
		return true;
	}
	return false;
}

void PlayerAttack::calcMove(int gains[2]) {
	int xGain = 0;
	int yGain = 0;
	
	if (direction == 1) {
		yGain = -1;
	} else if (direction == 2) {
		xGain = -1;
	} else if (direction == 3) {
		yGain = 1;
	} else if (direction == 4) {
		xGain = 1;
	}
	
	gains[0] = xGain;
	gains[1] = yGain;
}

void PlayerAttack::checkCollisions(vector<vector<Pixel> > tiles, int gains[2]) {
	if (tiles[getY() + gains[1]][getX() + gains[0]].getName() == "Wall" ||
		tiles[getY() + gains[1]][getX() + gains[0]].getName() == "Door") {
		active = false;
	}
}

void PlayerAttack::move(vector<vector<Pixel> > tiles) {
	if (active) {
		int gains[2];
		
		//calculate movement gains
		calcMove(gains);
		
		//check for collisions (and attack)
		checkCollisions(tiles, gains);
		
		//update coordinates
		setX(getX() + gains[0]);
		setY(getY() + gains[1]);
	} else {
		setX(-10);
		setY(-10);
	}
}

bool PlayerAttack::attack(Player plr, Entity &ent) {
	if (ent.getX() == getX() && ent.getY() == getY() && ent.isAlive() && active) {
		ent.setHealth(ent.getHealth() - plr.getAttack());
		active = false;
		
		if (!ent.isAlive()) {
			return true;
		}
	}
	return false;
}

int PlayerAttack::getDirection() {
	return direction;
}