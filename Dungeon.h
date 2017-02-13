//Kyle Spurlock

#ifndef DUNGEON_H
#define DUNGEON_H

#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

const int MAX_DUNGEON_WIDTH = 100;
const int MAX_DUNGEON_HEIGHT = 100;

class Dungeon {
public:
	Dungeon();
	
	void readFromFile(string fileName);
	
	void generateDoors();
	
	void setEnAlive(bool alive, int x, int y);
	
	int getWidth(int x, int y);
	int getHeight(int x, int y);
	int getEnHealth(int x, int y);
	int getEnAttack(int x, int y);
	int getEnXp(int x, int y);
	bool getEnAlive(int x, int y);
	void getHasDoors(int x, int y, bool doors[4]);
	void getLocDoors(int x, int y, int doors[4]);
	
private:
	int width[MAX_DUNGEON_HEIGHT][MAX_DUNGEON_WIDTH];
	int height[MAX_DUNGEON_HEIGHT][MAX_DUNGEON_WIDTH];
	
	int enHealth[MAX_DUNGEON_HEIGHT][MAX_DUNGEON_WIDTH];
	int enAttack[MAX_DUNGEON_HEIGHT][MAX_DUNGEON_WIDTH];
	int enXp[MAX_DUNGEON_HEIGHT][MAX_DUNGEON_WIDTH];
	bool enAlive[MAX_DUNGEON_HEIGHT][MAX_DUNGEON_WIDTH];
	
	bool hasDoors[MAX_DUNGEON_HEIGHT][MAX_DUNGEON_WIDTH][4];
	int locDoors[MAX_DUNGEON_HEIGHT][MAX_DUNGEON_WIDTH][4];
};

#endif