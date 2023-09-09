#pragma once
#include <iostream>
#include <graphics.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <mmsystem.h>
#include "funcSet.hpp"
#pragma comment(lib,"winmm.lib")
using namespace std;

class actor
{
public:
	int posX;
	int posY;
	int speed;
	bool isLive;
	int state;
	double alpha = 1.0; //用来修改难度
	int collisionR; //碰撞检测半径
};