//Kyle Spurlock

#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class Enemy : public Entity {
public:
	Enemy(Sprite sIn, int xIn, int yIn);
	
	void move(vector<vector<Pixel> > tiles, Entity ent);
	
	bool attack(Entity &ent);
	
	int getAttackCooldown();
	
	int getMovementCooldown();
	
private:
	int movementCooldown;
	int attackCooldown;
	
	void calcMove(int gains[2], Entity ent);
	
	void checkCollisions(vector<vector<Pixel> > tiles, int gains[2]);
};

#endif