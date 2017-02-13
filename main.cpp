//Kyle Spurlock

#include "main.h"

int main()
{
	//SET WINDOW
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_TITLE);
	window.setFramerateLimit(FRAMERATE_LIMIT);
	
	//LOAD TEXTURES
	Texture tWall, tDoor, tBackground, tPlayer, tEnemy, tPlrAttack;
	tWall.loadFromFile(T_WALL);
	tDoor.loadFromFile(T_DOOR);
	tBackground.loadFromFile(T_BACKGROUND);
	tPlayer.loadFromFile(T_PLAYER);
	tEnemy.loadFromFile(T_ENEMY);
	tPlrAttack.loadFromFile(T_PLAYER_ATTACK);
	Texture textures[] = {tWall, tDoor, tBackground};
	
	//LOAD SOUNDS
	
	//SETUP TEXT
	Font font;
	font.loadFromFile(FONT_TYPE);
	Text menuText;
	menuText.setFont(font);
	menuText.setColor(Color::White);
	menuText.setCharacterSize(40);
	menuText.setPosition(MAX_WIDTH * T_TILE_X, 0);
	
	//MAKE TILES
	vector<vector<Pixel> > tiles;
	
	//MAKE PLAYER, ENEMY, and PLAYER ATTACK
	Sprite plrS;
	plrS.setTexture(tPlayer);
	plrS.setPosition(5 * T_TILE_X, 5 * T_TILE_Y);
	Player plr(plrS, 5, 5);
	
	Sprite enS;
	enS.setTexture(tEnemy);
	enS.setPosition(6 * T_TILE_X, 6 * T_TILE_Y);
	Enemy *en = new Enemy(enS, 6, 6);
	
	Sprite plrAttackS;
	plrAttackS.setTexture(tPlrAttack);
	plrAttackS.setPosition(-10 * T_TILE_X, -10 * T_TILE_Y);
	PlayerAttack plrAttack(plrAttackS, -10, -10);
	
	//MAKE DUNGEON
	Dungeon d;
	d.readFromFile(DUNGEON_FILE_NAME);
	int x = 2;
	int y = 2;
	bool hasDoors[4];
	int locDoors[4];
	d.getHasDoors(x, y, hasDoors);
	d.getLocDoors(x, y, locDoors);
	Room *room = new Room(d.getWidth(x, y), d.getHeight(x, y), hasDoors, locDoors, textures);
	tiles = room->getRoom();
	
	en->setHealth(d.getEnHealth(x, y));
	en->setMaxHealth(d.getEnHealth(x, y));
	en->setAttack(d.getEnAttack(x, y));
	en->setXp(d.getEnXp(x, y));
	
	//PLAY GAME
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed || event.key.code == Keyboard::Escape || !plr.isAlive()) {
				window.close();
			}
		}
		
		//update room and movement
		int nextRoom = room->update(plr, *en, plrAttack);
		
		d.setEnAlive(en->isAlive(), x, y);
		
		//check for level up
		plr.levelUp();
		
		//transition to next room
		if (nextRoom != -1) {
			delete room;
			delete en;
			
			if (nextRoom == 0) {
				//top door
				--y;
			} else if (nextRoom == 1) {
				//left door
				--x;
			} else if (nextRoom == 2) {
				//bottom door
				++y;
			} else {
				//right door
				++x;
			}
			
			d.getHasDoors(x, y, hasDoors);
			d.getLocDoors(x, y, locDoors);
			room = new Room(d.getWidth(x, y), d.getHeight(x, y), hasDoors, locDoors, textures);
			
			en = new Enemy(enS, 6, 6);
			en->setX(rand() % (d.getWidth(x, y) - 4) + 2);
			en->setY(rand() % (d.getHeight(x, y) - 4) + 2);
			en->setHealth(d.getEnHealth(x, y));
			en->setMaxHealth(d.getEnHealth(x, y));
			en->setAttack(d.getEnAttack(x, y));
			en->setXp(d.getEnXp(x, y));
			
			if (!d.getEnAlive(x, y)) {
				en->setHealth(0);
			}
			
			tiles = room->getRoom();
			
			//reposition player
			if (nextRoom == 0) {
				//to bottom door(2)
				plr.setX(locDoors[2]);
				plr.setY(d.getHeight(x, y) - 2);
			} else if (nextRoom == 1) {
				//to right door(3)
				plr.setX(d.getWidth(x, y) - 2);
				plr.setY(locDoors[3]);
			} else if (nextRoom == 2) {
				//to top door(0)
				plr.setX(locDoors[0]);
				plr.setY(1);
			} else {
				//to left door(1)
				plr.setX(1);
				plr.setY(locDoors[1]);
			}
		}
		
		//MENU TEXT
		ostringstream ss;
		ss << GAME_TITLE << endl;
		ss << "Player Health: " << plr.getHealth() << " / " << plr.getMaxHealth() << endl;
		ss << "Enemy Health:  " << en->getHealth() << " / " << en->getMaxHealth() << endl;
		ss << "Experience:    " << plr.getXp() << endl;
		ss << "Level:         " << plr.getLevel() << endl;
		menuText.setString(ss.str());
		
		//UPDATE WINDOW
		window.clear();
		//room
		for (int y = 0; y < MAX_HEIGHT; ++y) {
			for (int x = 0; x < MAX_WIDTH; ++x) {
				window.draw(tiles[y][x].getSprite());
			}
		}
		//player, enemy, and player attack
		window.draw(plr.getSprite());
		window.draw(en->getSprite());
		window.draw(plrAttack.getSprite());
		
		//text
		window.draw(menuText);
		
		window.display();
	}
	
	return 0;
}
