//Kyle Spurlock

#ifndef PIXEL_H
#define PIXEL_H

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Pixel {
public:
	Pixel(Sprite sIn, string nameIn, int xIn, int yIn);
	
	void setName(string name);
	void setX(int x);
	void setY(int y);
	
	Sprite& getSprite();
	string getName();
	int getX();
	int getY();
private:
	Sprite s;
	string name;
	int x;
	int y;
};

#endif