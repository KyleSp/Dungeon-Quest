//Kyle Spurlock

#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

const int NUM_LEVELS = 6;
const int LEVELS[NUM_LEVELS] = {10, 20, 35, 50, 75, 100};

class Player : public Entity {
public:
	Player(Sprite sIn, int xIn, int yIn);
	
	int move(vector<vector<Pixel> > tiles, int height);
	
	void levelUp();
	
	int getAttackCooldown();
	int getDirection();
	int getLevel();
	
private:
	int level;
	int direction;
	int attackCooldown;
	
	void calcMove(int gains[2]);
	
	int checkCollisions(vector<vector<Pixel> > tiles, int gains[2], int height);
};

#endif