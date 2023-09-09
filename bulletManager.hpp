#pragma once
#include "bullet.hpp"

class bulletManager
{
public:
    vector<bullet> bulletVector;

    bulletManager();

    void createBullet(int x, int y);
};

bulletManager::bulletManager()
{
    this->bulletVector.resize(30);
    for (int i = 0; i < this->bulletVector.size(); i++) {
        bullet bullet;
        this->bulletVector[i] = bullet;
    }
}

void bulletManager::createBullet(int x, int y)
{
    for (int i = 0; i < this->bulletVector.size(); i++)
    {
        if (!this->bulletVector[i].isLive)
        {
            cout << "¼¤»î×Óµ¯±àºÅ" << i << endl;
            this->bulletVector[i].posX = x;
            this->bulletVector[i].posY = y;
            this->bulletVector[i].isLive = 1;
            this->bulletVector[i].modify = 1;
            break;
        }
    }
}
