//Kyle Spurlock

#include "Room.h"

Room::Room(int widthIn, int heightIn, bool hasDoorsIn[4], int locDoorsIn[4],
	Texture textures[3]) : width(widthIn), height(heightIn), tWall(textures[0]),
	tDoor(textures[1]), tBackground(textures[2]) {
	//INITIALIZE DOORS
	for (int i = 0; i < 4; ++i) {
		hasDoors[i] = hasDoorsIn[i];
		locDoors[i] = locDoorsIn[i];
	}
	
	//INITIALIZE TILES
	for (int y = 0; y < MAX_HEIGHT; ++y) {
		vector<Pixel> row;
		for (int x = 0; x < MAX_WIDTH; ++x) {
			Sprite s;
			s.setTexture(tBackground);
			
			//hide tiles not in room
			if (x >= width || y >= height) {
				s.setPosition(-10 * T_TILE_X, -10 * T_TILE_Y);
			} else {
				s.setPosition(x * T_TILE_X, y * T_TILE_Y);
			}
			
			Pixel p(s, "Background", x, y);
			row.push_back(p);
		}
		tiles.push_back(row);
	}
	
	makeWalls();
	makeDoors();
}

void Room::makeWalls() {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if (y == 0 || y == height - 1 || x == 0 || x == width - 1) {
				tiles[y][x].setName("Wall");
				tiles[y][x].getSprite().setTexture(tWall);
			}
		}
	}
}

void Room::makeDoors() {
	//top door
	if (hasDoors[0]) {
		tiles[0][locDoors[0]].setName("Door");
		tiles[0][locDoors[0]].getSprite().setTexture(tDoor);
	}
	
	//left door
	if (hasDoors[1]) {
		tiles[locDoors[1]][0].setName("Door");
		tiles[locDoors[1]][0].getSprite().setTexture(tDoor);
	}
	
	//bottom door
	if (hasDoors[2]) {
		tiles[height - 1][locDoors[2]].setName("Door");
		tiles[height - 1][locDoors[2]].getSprite().setTexture(tDoor);
	}
	
	//right door
	if (hasDoors[3]) {
		tiles[locDoors[3]][width - 1].setName("Door");
		tiles[locDoors[3]][width - 1].getSprite().setTexture(tDoor);
	}
}

int Room::update(Player &plr, Enemy &en, PlayerAttack &plrAttack) {
	++tickCount;
	
	//movement
	if (tickCount >= enMovementCooldown) {
		en.move(tiles, plr);
		enMovementCooldown = tickCount + en.getMovementCooldown();
	}
	
	int doorNum = plr.move(tiles, height);
	plrAttack.move(tiles);
	
	//update location
	plr.getSprite().setPosition(plr.getX() * T_TILE_X, plr.getY() * T_TILE_Y);
	
	if (en.isAlive()) {
		en.getSprite().setPosition(en.getX() * T_TILE_X, en.getY() * T_TILE_Y);
	} else {
		en.getSprite().setPosition(1000 * T_TILE_X, 1000 * T_TILE_Y);
	}
	
	if (plrAttack.getDirection() == 2) {
		plrAttack.getSprite().setPosition((plrAttack.getX() + 1) * T_TILE_X, plrAttack.getY() * T_TILE_Y);
	} else if (plrAttack.getDirection() == 3) {
		plrAttack.getSprite().setPosition(plrAttack.getX() * T_TILE_X, (plrAttack.getY() + 1) * T_TILE_Y);
	} else {
		plrAttack.getSprite().setPosition(plrAttack.getX() * T_TILE_X, plrAttack.getY() * T_TILE_Y);
	}
	
	//enemy attack
	if (tickCount >= enAttackCooldown) {
		if (en.attack(plr)) {
			enAttackCooldown = tickCount + en.getAttackCooldown();
		}
	}
	
	//player attack
	if (tickCount >= plrAttackCooldown) {
		if (plrAttack.init(plr)) {
			plrAttackCooldown = tickCount + plr.getAttackCooldown();
		}
	}
	
	if (plrAttack.attack(plr, en)) {
		plr.setXp(plr.getXp() + en.getXp());
	}
	
	return doorNum;
}

vector<vector<Pixel> > Room::getRoom() {
	return tiles;
}
