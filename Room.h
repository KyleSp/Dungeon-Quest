//Kyle Spurlock

#ifndef ROOM_H
#define ROOM_H

#include "main.h"

static int tickCount = 0;
static int enMovementCooldown = 0;
static int enAttackCooldown = 0;
static int plrAttackCooldown = 0;

class Room {
public:
	Room(int widthIn, int heightIn, bool hasDoorsIn[4],
		int locDoorsIn[4], Texture textures[3]);
	
	void makeWalls();
	
	void makeDoors();
	
	int update(Player &plr, Enemy &en, PlayerAttack &plrAttack);
	
	vector<vector<Pixel> > getRoom();
	
private:
	int width;
	int height;
	vector<vector<Pixel> > tiles;
	bool hasDoors[4];
	int locDoors[4];
	Texture tWall;
	Texture tDoor;
	Texture tBackground;
};

#endif