#pragma once
#include "actor.h"

class button
{
public:
	button();
	button(IMAGE* img, int x, int y);
	button(int x, int y, int w, int h);
	int posX;
	int posY;
	int width;
	int height;
	IMAGE *imgButton;

	bool buttonDown(int x,int y);
	void showButton();
};

button::button()
{

}

button::button(IMAGE* img, int x, int y)
{
	this->width = img->getwidth();
	this->height = img->getheight();
	this->posX = x;
	this->posY = y;
	this->imgButton = img;
}

button::button(int x,int y,int w,int h):posX(x),posY(y),width(w-x),height(h-y)
{
	
	
}

bool button::buttonDown(int x,int y)
{
	if (this->posX < x && this->posY < y && x < (this->posX + this->width) && y < (this->posY + this->height)) {
		return 1;
	}
	return 0;
}

void button::showButton()
{
	putimage(this->posX, this->posY, this->imgButton);
}
