//Kyle Spurlock

#ifndef PLAYERATTACK_H
#define PLAYERATTACK_H

#include "Pixel.h"
#include "Player.h"
#include "Entity.h"

/*
	direction = 1 -> up
	direction = 2 -> left
	direction = 3 -> down
	direction = 4 -> right
*/

class PlayerAttack : public Pixel {
public:
	PlayerAttack(Sprite sIn, int xIn, int yIn);
	
	void setAttackSymbol();
	
	bool init(Player plr);
	
	void move(vector<vector<Pixel> > tiles);
	
	bool attack(Player plr, Entity &ent);
	
	int getDirection();
	
private:
	int direction;
	bool active;
	
	void calcMove(int gains[2]);
	
	void checkCollisions(vector<vector<Pixel> > tiles, int gains[2]);
};

#endif