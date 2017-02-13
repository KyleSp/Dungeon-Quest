//Kyle Spurlock

#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "Pixel.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayerAttack.h"
#include "Room.h"
#include "Dungeon.h"

using namespace std;
using namespace sf;

//GAME CONSTANTS
const string GAME_TITLE = "Dungeon Quest";
const string FONT_TYPE = "Everson Mono.ttf";
const string DUNGEON_FILE_NAME = "DungeonLayout.txt";
const int WINDOW_WIDTH = 1580;
const int WINDOW_HEIGHT = 810;
const int FRAMERATE_LIMIT = 10;

//ROOM CONSTANTS
const int MAX_WIDTH = 25;
const int MIN_WIDTH = 6;
const int MAX_HEIGHT = 20;
const int MIN_HEIGHT = 6;

//TEXTURE CONSTANTS
const int T_TILE_X = 40;
const int T_TILE_Y = 40;
const string T_WALL = "Wall.png";
const string T_DOOR = "Door.png";
const string T_BACKGROUND = "Background.png";
const string T_PLAYER = "Player.png";
const string T_ENEMY = "Enemy.png";
const string T_PLAYER_ATTACK = "Arrow.png";

//SOUND CONSTANTS
const string S_ARROW = ".wav";


#endif