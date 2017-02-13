//Kyle Spurlock

#include "Dungeon.h"

Dungeon::Dungeon() {
	for (int y = 0; y < MAX_DUNGEON_HEIGHT; ++y) {
		for (int x = 0; x < MAX_DUNGEON_WIDTH; ++x) {
			width[y][x] = 0;
			height[y][x] = 0;
			enHealth[y][x] = 0;
			enAttack[y][x] = 0;
			enXp[y][x] = 0;
			enAlive[y][x] = true;
			
			for (int i = 0; i < 4; ++i) {
				hasDoors[y][x][i] = false;
			}
		}
	}
}

void Dungeon::readFromFile(string fileName) {
	ifstream file(fileName);
	
	int xIn, yIn;
	int widthIn, heightIn;
	int enHealthIn, enAttackIn, enXpIn;
	
	while (file >> xIn >> yIn >> widthIn >> heightIn >> enHealthIn >> enAttackIn >> enXpIn) {
		width[yIn][xIn] = widthIn;
		height[yIn][xIn] = heightIn;
		enHealth[yIn][xIn] = enHealthIn;
		enAttack[yIn][xIn] = enAttackIn;
		enXp[yIn][xIn] = enXpIn;
	}
	
	generateDoors();
	
	file.close();
}

void Dungeon::generateDoors() {
	for (int y = 0; y < MAX_DUNGEON_HEIGHT; ++y) {
		for (int x = 0; x < MAX_DUNGEON_WIDTH; ++x) {
			//top door
			if (y - 1 >= 0) {
				if (width[y - 1][x] != 0) {
					hasDoors[y][x][0] = true;
				}
			}
			
			//left door
			if (x - 1 >= 0) {
				if (width[y][x - 1] != 0) {
					hasDoors[y][x][1] = true;
				}
			}
			
			//bottom door
			if (y + 1 <= MAX_DUNGEON_HEIGHT) {
				if (width[y + 1][x] != 0) {
					hasDoors[y][x][2] = true;
				}
			}
			
			//right door
			if (x + 1 <= MAX_DUNGEON_WIDTH) {
				if (width[y][x + 1] != 0) {
					hasDoors[y][x][3] = true;
				}
			}
			
			for (int i = 0; i < 4; ++i) {
				if (hasDoors[y][x][i]) {
					srand(time(NULL));
					int maxVal;
					if (i == 0 || i == 2) {
						maxVal = width[y][x] - 2;
					} else {
						maxVal = height[y][x] - 2;
					}
					locDoors[y][x][i] = rand() % maxVal + 1;
				}
			}
		}
	}
}

void Dungeon::setEnAlive(bool alive, int x, int y) {
	enAlive[y][x] = alive;
}

int Dungeon::getWidth(int x, int y) {
	return width[y][x];
}

int Dungeon::getHeight(int x, int y) {
	return height[y][x];
}

int Dungeon::getEnHealth(int x, int y) {
	return enHealth[y][x];
}

int Dungeon::getEnAttack(int x, int y) {
	return enAttack[y][x];
}

int Dungeon::getEnXp(int x, int y) {
	return enXp[y][x];
}

bool Dungeon::getEnAlive(int x, int y) {
	return enAlive[y][x];
}

void Dungeon::getHasDoors(int x, int y, bool doors[4]) {
	for (int i = 0; i < 4; ++i) {
		doors[i] = hasDoors[y][x][i];
	}
}

void Dungeon::getLocDoors(int x, int y, int doors[4]) {
	for (int i = 0; i < 4; ++i) {
		doors[i] = locDoors[y][x][i];
	}
}
