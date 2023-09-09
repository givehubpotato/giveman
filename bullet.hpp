#include "actor.h"
#pragma once
//#define bulletNum 5

enum MyEnum
{

};
class bullet :public actor
{
public:
	bullet();
	int attackValue; //������
	double direct[2]; //����
	int targetX; //Ŀ��X
	int targetY; //Ŀ��Y
	bool modify; //�Ƿ�����ı䵱ǰ�ӵ�����
	int collisionR = 15;
	void bulletMove();
	void setBulletDirect();
};

bullet::bullet()
{
	this->isLive = 0;
	this->modify = 0;
	this->speed = 20;
}

void bullet::bulletMove()
{

	if (this->isLive) {
		if (this->modify) {
			this->setBulletDirect();
			this->modify = 0;
		}

		this->posX += this->direct[0] * this->speed;
		this->posY += this->direct[1] * this->speed;
		
		//�����߽�����������������������
		if (this->posX < 30 || this->posX>1250 || this->posY < 30 || this->posY>750) {
			this->isLive = 0;
		}
	}
	else {
		return;
	}
	
}

void bullet::setBulletDirect()
{
	vector<double> temp = setDirect(this->posX, this->posY, this->targetX, this->targetY);
	this->direct[0] = temp[0];
	this->direct[1] = temp[1];
}