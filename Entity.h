//Kyle Spurlock

#ifndef ENTITY_H
#define ENTITY_H

#include "Pixel.h"

class Entity : public Pixel {
public:
	Entity(Sprite sIn, string nameIn, int xIn, int yIn, int healthIn, int attackIn, int xpIn);
	
	void setHealth(int health);
	void setMaxHealth(int maxHealth);
	void setAttack(int attack);
	void setXp(int xp);
	
	int getHealth();
	int getMaxHealth();
	int getAttack();
	int getXp();
	bool isAlive();
	
private:
	int health;
	int maxHealth;
	int attack;
	int xp;
};

#endif
