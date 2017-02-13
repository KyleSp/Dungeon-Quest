//Kyle Spurlock

#include "Pixel.h"

Pixel::Pixel(Sprite sIn, string nameIn, int xIn, int yIn) :
	s(sIn), name(nameIn), x(xIn), y(yIn) {}

void Pixel::setName(string name) {
	this->name = name;
}

void Pixel::setX(int x) {
	this->x = x;
}

void Pixel::setY(int y) {
	this->y = y;
}

Sprite& Pixel::getSprite() {
	return s;
}

string Pixel::getName() {
	return name;
}

int Pixel::getX() {
	return x;
}

int Pixel::getY() {
	return y;
}