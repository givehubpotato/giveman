#include "enemy.hpp"
#include "bullet.hpp"
#pragma once
 //�����������������
class spawn
{
public:
    
    spawn();
    spawn(int x,int y,int t,double al);
	int posX; //��������λ��
	int posY; //��������λ��
	int times=0; //��¼arr�±�
	int count = 0; //���ڸı��������
    int arr[3] = {1,2,3}; //��¼ÿ�����ɶ��ٴε���
    int type;
    double alpha;
	vector<vector<enemy*>> enemyVector; //
    vector<int> suf{ 0,1,2,3 };
    vector<enemy*> enemyVec;
    
	void toSpawn(); //��һ������
	bool emptyVector(); //�ж��������ɵĵ����Ƿ����� ���ȫ��������Ϊ1
	void spawnAgain(); //������е���������������һ������
	void changeStatue(); //�鿴���ı���˵Ĵ���״̬ ���ڻ�����
	void isHit(bullet &bul); //�鿴ÿ�������Ƿ��ܵ�����
};

spawn::spawn()
{

}

spawn::spawn(int x,int y, int t, double al):posX(x),posY(y)
{
    this->enemyVec.resize(2);
    this->alpha = al;
    this->type = t;

    /*this->enemyVector.resize(3);
    for (int i = 0; i < 3; i++) {
        this->enemyVector[i].resize(3);
    }*/
}

void spawn::toSpawn()
{

    //for (int i = 0; i  < this->arr[this->times]; i++) {
    //    for (int j = 0; j < 3; j++) {
    //        enemy* en = new enemy;
    //        en->init(this->posX + (rand() % 10) * 150, this->posY + (rand() % 10) * 150);
    //        this->enemyVector[i][j] = en;           
    //    }
    //    if (this[i].count == 5) {
    //        continue;
    //    }
    //    else {
    //        this[i].count++;
    //    }
    //
    //    if (this[i].count == 3) {
    //        this[i].times = 2;
    //        this[i].count = 0;
    //    }
    //    if (this[i].count == 5) {
    //        this[i].times = 3;
    //        this[i].count = 0;
    //    }
    //}

    shullfeFunc(suf);

    for (int i = 0; i < this->enemyVec.size(); i++) {
        enemy* en = new enemy;
        if (i == 0) {
            en->init(this->posX + 200*suf[i], this->posY, this->alpha, this->type);
            this->enemyVec[i] = en;
        }
        else {
            en->init(this->posX+200*suf[i], this->posY, this->alpha, this->type);
            this->enemyVec[i] = en;
        }
    }
    
}

bool spawn::emptyVector()
{
    //for (int i = 0; i < this->arr[this->times]; i++) {
    //    for (int j = 0; j < 3; j++) {
    //        if (this->enemyVector[i][j] != nullptr) {
    //            return 0;
    //        }
    //    }
    //}
    //return 1;

    for (int i = 0; i < this->enemyVec.size(); i++) {
        if (this->enemyVec[i] != nullptr && this->enemyVec[i]->isLive==1) {
            return 0;
        }
    }
    return 1;
}

void spawn::spawnAgain()
{
    this->toSpawn();
}

void spawn::changeStatue()
{
    //for (int i = 0; i < this->arr[this->times];i++) {
    //    for (int j = 0; j < 3; j++) {
    //        if (this->enemyVector[i][j]->isLive) {
    //            continue;
    //        }
    //        else {
    //            delete this->enemyVector[i][j];
    //            this->enemyVector[i][j] = nullptr;
    //        }
    //    }
    //}

    for (int i = 0; i < this->enemyVec.size(); i++) {
        if (this->enemyVec[i]!=nullptr ) {
            continue;
        }
        else {
            delete this->enemyVec[i];
            this->enemyVec[i] = nullptr;
        }
    }
}

void spawn::isHit(bullet &bul)
{
    //for (int i = 0; i < this->arr[this->times]; i++) {
    //    for (int j = 0; j < 3; j++) {
    //        this->enemyVector[i][j]->beHitted();
    //    }
    //}

    for (int i = 0; i < this->enemyVec.size(); i++) {
        this->enemyVec[i]->beHitted(bul);
    }
}

