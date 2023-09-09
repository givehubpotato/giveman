#include "actor.h"
#include "enemy.hpp"
#pragma once
class player :public actor
{
public:
	int score = 0;
	int HP;
	int MP;
	int maxHP;
	int maxMP;
	int exp;
	int level=0;
	int time = 0;
	double levelArr[20] = {1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.05,2.1,2.15,2.2,2.25,
						2.3,2.35,2.4,2.45,2.5};

	int expArr[20] = { 100,120,140,160,180,200,210,220,230,240,250,260,270,280,290,300,320,340,
						360,400 };
	player();
	void playerMove(int alphaX,int alphaY); //设置玩家移动 参数为修正量 改变用来调整偏移量
	void levelUp(int enemyExp); //升级
	bool collision(enemy *en); //碰撞//受击-修改状态
	void healMP();
	void healHP();
	bool gameOver();
};

player::player()
{
	this->posX = 550;
	this->posY = 350;
	this->speed = 15;
	this->level = 1;
	this->HP = 100;
	this->MP = 100;
	this->maxHP=100*levelArr[this->level];
	this->maxMP=100*levelArr[this->level];
	this->exp = 0;
	this->collisionR = 10;
}

void player::playerMove(int alphaX,int alphaY)
{
	int x = this->posX+this->speed * alphaX;
	int y = this->posY+this->speed * alphaY;
	if (block(x, y)) {
		return;
	}
	else {
		this->posX = x;
		this->posY = y;
	}	
}

void player::levelUp(int enemyExp)
{
	this->exp += enemyExp;
	if (this->exp >= this->expArr[this->level]) {
		this->level++;
		this->exp = 0;
	}
}

bool player::collision(enemy *en)
{
	if (en->type == 1) {
		if (collisionCheck(this->posX+75, this->posY+60, en->posX+80, en->posY+40, this->collisionR, en->collisionR)) {
			this->HP -= en->attackValue;
			if (this->HP <= 0) {
				this->isLive = 0;
			}
			return 1;
		}
	}

	if (en->type == 2) {
		if (collisionCheck(this->posX + 75, this->posY + 60, en->posX + 80, en->posY + 50, this->collisionR, en->collisionR)) {
			this->HP -= en->attackValue;
			if (this->HP <= 0) {
				this->isLive = 0;
			}
			return 1;
		}
	}

	if (en->type == 3) {
		if (collisionCheck(this->posX + 75, this->posY + 60, en->posX + 70, en->posY + 80, this->collisionR, en->collisionR)) {
			this->HP -= en->attackValue;
			if (this->HP <= 0) {
				this->isLive = 0;
			}
			return 1;
		}
	}

	return 0;
}

bool player::gameOver()
{	
	return 1;
}

void player::healMP()
{
	this->time++;
	if (this->time == 20) {
		this->time = 0;
		if (this->MP + 1 > this->maxMP) {
			return;
		}
		else {
			this->MP++;
		}
	}
}

void player::healHP()
{
	if (this->time == 20) {
		if (this->HP + 2 >= this->maxHP) {
			this->HP = this->maxHP; 
			return;
		}
		else {
			this->HP += 2;
		}
	}
}