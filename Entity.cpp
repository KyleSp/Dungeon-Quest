//Kyle Spurlock

#include "Entity.h"

Entity::Entity(Sprite sIn, string nameIn, int xIn, int yIn, int healthIn, int attackIn, int xpIn) :
	Pixel(sIn, nameIn, xIn, yIn), health(healthIn), maxHealth(healthIn), attack(attackIn), xp(xpIn) {}

void Entity::setHealth(int health) {
	this->health = health;
}

void Entity::setMaxHealth(int maxHealth) {
	this->maxHealth = maxHealth;
}

void Entity::setAttack(int attack) {
	this->attack = attack;
}

void Entity::setXp(int xp) {
	this->xp = xp;
}

int Entity::getHealth() {
	return health;
}

int Entity::getMaxHealth() {
	return maxHealth;
}

int Entity::getAttack() {
	return attack;
}

int Entity::getXp() {
	return xp;
}

bool Entity::isAlive() {
	return health > 0;
}
