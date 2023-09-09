#include "actor.h"
#include "bullet.hpp"
#pragma once

class enemy :public actor
{
public:


	int HP;
	int type;
	double direct[2];
	int attackValue;
	int exp;


	void init(int x,int y,double al,int t); //�Ե��˵�λ�ý��г�ʼ��
	void setEnemyDirect(int x,int y); //���õ��˵��ƶ�����xyΪ��������
	void enemyMove(int x,int y); //�ı���˵��ƶ�λ��
	bool beHitted(bullet &target); //�ж��Ƿ��ܵ��������ı���״̬

};

void enemy::init(int x, int y, double al, int t)
{
	this->isLive = 1;
	this->posX = x;
	this->posY = y;
	this->alpha = al;
	this->collisionR = 20;
	this->type = t;
	if (t == 1) {
		this->HP = (int)100 * this->alpha;
		this->speed = (int)5 * this->alpha;
		this->exp = (int)10 * this->alpha;
		this->attackValue = (int)10 * this->alpha;
	}
	else if (t == 2) {
		this->HP = (int)140 * this->alpha;
		this->speed = (int)6 * this->alpha;
		this->exp = (int)15 * this->alpha;
		this->attackValue = (int)15 * this->alpha;
	}
	else if (t == 3) {
		this->HP = (int)160 * this->alpha;
		this->speed = (int)6 * this->alpha;
		this->exp = (int)18 * this->alpha;
		this->attackValue = (int)20 * this->alpha;
	}
}

void enemy::setEnemyDirect(int x,int y)
{
	vector<double> temp = setDirect(this->posX, this->posY, x, y);
	this->direct[0] = temp[0];
	this->direct[1] = temp[1];
	
}

void enemy::enemyMove(int x,int y)
{
	this->setEnemyDirect(x, y);
	this->posX += this->direct[0] * this->speed;
	this->posY += this->direct[1] * this->speed;
}

bool enemy::beHitted(bullet &target)
{

	if (this->type == 1) {
		if (collisionCheck(this->posX+80, this->posY+40, target.posX+8, target.posY+8, this->collisionR, target.collisionR)) {
			this->HP -= target.attackValue;
			if (this->HP <= 0) {
				this->isLive = 0;
			}
			return 1;
		}
	}
	if (type == 2) {
		if (collisionCheck(this->posX+80, this->posY+50, target.posX+8, target.posY+8, this->collisionR, target.collisionR)) {
			this->HP -= target.attackValue;
			if (this->HP <= 0) {
				this->isLive = 0;
			}
			return 1;
		}
	}
	if (type == 3) {
		if (collisionCheck(this->posX+70, this->posY+110, target.posX+8, target.posY+8, this->collisionR, target.collisionR)) {
			this->HP -= target.attackValue;
			if (this->HP <= 0) {
				this->isLive = 0;
			}
			return 1;
		}
	}

	return 0;
}