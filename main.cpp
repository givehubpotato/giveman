#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <mutex>
#include "bullet.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include "spawn.hpp"
#include "bulletManager.hpp"

using namespace std;

mutex mt;
//程序入口
void entrance();

//鼠标事件
void mouseEvent(short& mouseX, short& mouseY, bool& click,bool &isOver);

int main()
{
	while (1) {
		entrance();
	}
	system("pause");
	return 0;
}

void entrance()
{

	initgraph(1280, 800);
	setbkcolor(WHITE);
	cleardevice();

	BGM();

	double* alpha=new double;
	*alpha = 1;
	
	init(alpha);

	double al = *alpha;

	delete alpha;
	alpha = nullptr;

	//将鼠标事件添加到子线程中
	short mouseX, mouseY;
	bool isClick = 0;
	bool isOver = 0;

	thread t1(mouseEvent, ref(mouseX), ref(mouseY), ref(isClick),ref(isOver));
	t1.detach();
	//完成添加

	//声明变量开始测试
	//玩家变量声明
	player* mainPlayer = new player;
	int countPlayer = 0;
	IMAGE playerL[6];
	IMAGE playerR[6];
	bool left = 1;

	{
		loadimage(&playerL[0], L"./picture/player/playerL_1.png");
		loadimage(&playerL[1], L"./picture/player/playerL_2.png");
		loadimage(&playerL[2], L"./picture/player/playerL_3.png");
		loadimage(&playerL[3], L"./picture/player/playerL_4.png");
		loadimage(&playerL[4], L"./picture/player/playerL_5.png");
		loadimage(&playerL[5], L"./picture/player/playerL_6.png");

		loadimage(&playerR[0], L"./picture/player/playerR_1.png");
		loadimage(&playerR[1], L"./picture/player/playerR_2.png");
		loadimage(&playerR[2], L"./picture/player/playerR_3.png");
		loadimage(&playerR[3], L"./picture/player/playerR_4.png");
		loadimage(&playerR[4], L"./picture/player/playerR_5.png");
		loadimage(&playerR[5], L"./picture/player/playerR_6.png");
	}
	
	//背景声明
	IMAGE bk;
	IMAGE bk2;
	loadimage(&bk2, L"./picture/backGround/glass2.jpg");
	loadimage(&bk, L"./picture/backGround/glass.png");

;
	//子弹声明

	bulletManager bulManager;


	IMAGE *bul=new IMAGE;
	loadimage(bul, L"./picture/bullet/bullet.png");


	//敌人管理
	vector<spawn> spawnVector(3);

	//声明三个管理器，代表三种类型敌人
	spawn admit1(200, 200,1,al); //->tyep1
	spawn admit2(200, 400,2,al); //->type2
	spawn admit3(200, 600,3,al); //->type3


	bool allDie = 1; //默认是全部生成 如果有敌人存活则值改为0
	spawnVector[0] = admit1;
	spawnVector[1] = admit2;
	spawnVector[2] = admit3;

	for (int i = 0; i < 3; i++) {
		spawnVector[i].toSpawn();
	}

	IMAGE enemyImageType1[5];
	IMAGE enemyImageType1L[5];
	int countType1 = 0;

	IMAGE enemyImageType2[6];
	IMAGE enemyImageType2L[6];
	int countType2 = 0;

	IMAGE enemyImageType3[6];
	IMAGE enemyImageType3L[6];
	int countType3 = 0;

	{
		loadimage(&enemyImageType1L[0], L"./picture/enemy/enemy1_1L.png");
		loadimage(&enemyImageType1L[1], L"./picture/enemy/enemy1_2L.png");
		loadimage(&enemyImageType1L[2], L"./picture/enemy/enemy1_3L.png");
		loadimage(&enemyImageType1L[3], L"./picture/enemy/enemy1_4L.png");
		loadimage(&enemyImageType1L[4], L"./picture/enemy/enemy1_5L.png");

		loadimage(&enemyImageType1[0], L"./picture/enemy/enemy1_1.png");
		loadimage(&enemyImageType1[1], L"./picture/enemy/enemy1_2.png");
		loadimage(&enemyImageType1[2], L"./picture/enemy/enemy1_3.png");
		loadimage(&enemyImageType1[3], L"./picture/enemy/enemy1_4.png");
		loadimage(&enemyImageType1[4], L"./picture/enemy/enemy1_5.png");
	}
	
	{
		loadimage(&enemyImageType2[0], L"./picture/enemy/enemy2_01.png");
		loadimage(&enemyImageType2[1], L"./picture/enemy/enemy2_02.png");
		loadimage(&enemyImageType2[2], L"./picture/enemy/enemy2_03.png");
		loadimage(&enemyImageType2[3], L"./picture/enemy/enemy2_04.png");
		loadimage(&enemyImageType2[4], L"./picture/enemy/enemy2_05.png");
		loadimage(&enemyImageType2[5], L"./picture/enemy/enemy2_06.png");

		loadimage(&enemyImageType2L[0], L"./picture/enemy/enemy2_01L.png");
		loadimage(&enemyImageType2L[1], L"./picture/enemy/enemy2_02L.png");
		loadimage(&enemyImageType2L[2], L"./picture/enemy/enemy2_03L.png");
		loadimage(&enemyImageType2L[3], L"./picture/enemy/enemy2_04L.png");
		loadimage(&enemyImageType2L[4], L"./picture/enemy/enemy2_05L.png");
		loadimage(&enemyImageType2L[5], L"./picture/enemy/enemy2_06L.png");
	}

	{
		loadimage(&enemyImageType3[0], L"./picture/enemy/enemy3_1.png");
		loadimage(&enemyImageType3[1], L"./picture/enemy/enemy3_2.png");
		loadimage(&enemyImageType3[2], L"./picture/enemy/enemy3_3.png");
		loadimage(&enemyImageType3[3], L"./picture/enemy/enemy3_4.png");
		loadimage(&enemyImageType3[4], L"./picture/enemy/enemy3_3.png");
		loadimage(&enemyImageType3[5], L"./picture/enemy/enemy3_2.png");

		loadimage(&enemyImageType3L[0], L"./picture/enemy/enemy3_1L.png");
		loadimage(&enemyImageType3L[1], L"./picture/enemy/enemy3_2L.png");
		loadimage(&enemyImageType3L[2], L"./picture/enemy/enemy3_3L.png");
		loadimage(&enemyImageType3L[3], L"./picture/enemy/enemy3_4L.png");
		loadimage(&enemyImageType3L[4], L"./picture/enemy/enemy3_3L.png");
		loadimage(&enemyImageType3L[5], L"./picture/enemy/enemy3_2L.png");
	}
	


	IMAGE* personHead=new IMAGE;
	IMAGE* score=new IMAGE;
	IMAGE* hpUI = new IMAGE;
	IMAGE* mpUI = new IMAGE;
	IMAGE* expUI = new IMAGE;
	IMAGE* levelUI = new IMAGE;

	vector<IMAGE*> uiImage(6);
	
	uiImage[0] = personHead;
	uiImage[1] = score;
	uiImage[2] = hpUI;
	uiImage[3] = mpUI;
	uiImage[4] = expUI;
	uiImage[5] = levelUI;

	{
		loadimage(personHead, L"./picture/UI/player_UI.jpg");
		loadimage(score, L"./picture/UI/score.png");
		loadimage(hpUI, L"./picture/UI/HP_UI.png");
		loadimage(mpUI, L"./picture/UI/MP_UI.png");
		loadimage(expUI, L"./picture/UI/gettedExp.png");
		loadimage(levelUI, L"./picture/UI/level_UI.png");
	}
	

	//声明一个哈希表展示得分
	unordered_map<int, IMAGE> hashMap;
	IMAGE scoreImage[10];

	{
		loadimage(&scoreImage[0], L"./picture/UI/zero.png");
		loadimage(&scoreImage[1], L"./picture/UI/one.png");
		loadimage(&scoreImage[2], L"./picture/UI/two.png");
		loadimage(&scoreImage[3], L"./picture/UI/three.png");
		loadimage(&scoreImage[4], L"./picture/UI/four.png");
		loadimage(&scoreImage[5], L"./picture/UI/five.png");
		loadimage(&scoreImage[6], L"./picture/UI/six.png");
		loadimage(&scoreImage[7], L"./picture/UI/seven.png");
		loadimage(&scoreImage[8], L"./picture/UI/eight.png");
		loadimage(&scoreImage[9], L"./picture/UI/nine.png");
	}

	for (int i = 0; i < 10; i++) {
		hashMap[i] = scoreImage[i];
	}

	IMAGE pauseButton;
	IMAGE continueButton;
	IMAGE quitButton;
	loadimage(&quitButton, L"./picture/UI/quit.png");
	loadimage(&pauseButton, L"./picture/UI/pause.png");
	loadimage(&continueButton, L"./picture/UI/continue.png");

	int clickType = 0;
	int pauseOrcontinue = 0; //1表示暂停 0表示继续 
	bool isQuit = 0;

	int overType = 0; //0 nothing 1 win 2 over
	loading();

	while (1) {


		//动画播放计数
		if (countPlayer == 6) {
			countPlayer = 0;
		}

		if (countType1 == 5) {
			countType1 = 0;
		}

		if (countType2 == 6) {
			countType2 = 0;
		}

		if (countType3 == 6) {
			countType3 = 0;
		}
		

		//鼠标事件和子弹生成
		if (isClick) {	

			mt.lock();
			short tempX = mouseX;
			short tempY = mouseY;
			isClick = 0;
			mt.unlock();

			clickType = chooseType(tempX, tempY);
			if (clickType==1) {
				hitButton();
				pauseOrcontinue = 1;
			}
			else if (clickType==2) {
				hitButton();
				isQuit = 1;
			}
			else if(clickType==0){
				pauseOrcontinue = 0;
				bulManager.createBullet(mainPlayer->posX + 40, mainPlayer->posY + 10);
				playerAttack();
				for (int i = 0; i < bulManager.bulletVector.size(); i++) {
					if (bulManager.bulletVector[i].modify) {
						bulManager.bulletVector[i].targetX = tempX;
						bulManager.bulletVector[i].targetY = tempY;
						break;
					}
				}
			}
			
		}

		//子弹移动
		for (int i = 0; i < bulManager.bulletVector.size(); i++) {
			if (bulManager.bulletVector[i].isLive) {
				bulManager.bulletVector[i].bulletMove();
			}
		}

		//检查敌人状态
		for (int i = 0; i < spawnVector.size(); i++) {
			for (int j = 0; j < bulManager.bulletVector.size(); j++) {
				if (bulManager.bulletVector[j].isLive) {
					for (int k = 0; k < spawnVector[i].enemyVec.size(); k++) {
						if (spawnVector[i].enemyVec[k]->beHitted(bulManager.bulletVector[j])) {
							enemyHitted();
							bulManager.bulletVector[j].isLive = 0;
							if (!bulManager.bulletVector[j].isLive) {
								mainPlayer->levelUp(spawnVector[i].enemyVec[k]->exp);
								mainPlayer->score++;
							}
						}
					}
				}
			}
			spawnVector[i].changeStatue(); //在改变存在状态			
		}

		//主角碰撞
		for (int i = 0; i < spawnVector.size(); i++) {
			for (int j = 0; j < spawnVector[i].enemyVec.size(); j++) {
				if (spawnVector[i].enemyVec[j]!=nullptr && spawnVector[i].enemyVec[j]->isLive==1) {
					if (mainPlayer->collision(spawnVector[i].enemyVec[j])) {
						hurt();
					}
				}			
			}
		}

		//检查是否要重新生成
		for (int i = 0; i < spawnVector.size(); i++) {
			//确定是否要生成
			if (spawnVector[i].emptyVector()) {
				spawnVector[i].spawnAgain();
			}
			
		}
		
		//敌人的移动
		for (int i = 0; i < spawnVector.size(); i++) {
			for (int j = 0; j < spawnVector[i].enemyVec.size(); j++) {
				if (spawnVector[i].enemyVec[j] != nullptr && spawnVector[i].enemyVec[j]->isLive==1 ) {
					spawnVector[i].enemyVec[j]->enemyMove(mainPlayer->posX + 30, mainPlayer->posY + 30);
				}
			}
		}

		if (mainPlayer->isLive == 0) {
			delete bul;
			bul = nullptr;
			delete personHead;
			personHead = nullptr;
			delete score;
			score = nullptr;
			delete mainPlayer;
			mainPlayer = nullptr;

			for (int i = 0; i < spawnVector.size(); i++) {
				for (int j = 0; j < spawnVector[i].enemyVec.size(); j++) {
					if (spawnVector[i].enemyVec[j] != nullptr) {
						delete spawnVector[i].enemyVec[j];
						spawnVector[i].enemyVec[j] = nullptr;
					}
				}
			}

			overType = 2;
			cleardevice();
			closegraph();
			break;
		}

		if (mainPlayer->score >= 60) {
			overType = 1;
			cleardevice();
			closegraph();
			break;
		}

		if (isQuit) {
			delete bul;
			bul = nullptr;
			delete personHead;
			personHead = nullptr;
			delete score;
			score = nullptr;
			delete mainPlayer;
			mainPlayer = nullptr;

			for (int i = 0; i < spawnVector.size(); i++) {
				for (int j = 0; j < spawnVector[i].enemyVec.size(); j++) {
					if (spawnVector[i].enemyVec[j] != nullptr) {
						delete spawnVector[i].enemyVec[j];
						spawnVector[i].enemyVec[j] = nullptr;
					}
				}
			}
			cleardevice();
			closegraph();
			break;
		}

		mainPlayer->healHP();
		mainPlayer->healMP();


		BeginBatchDraw();
		/*for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				putimage(640 * j, 640 * i, &bk);
			}
		}*/

		putimage(0, 0, &bk2);

		showUI(hashMap,uiImage, mainPlayer->HP, mainPlayer->maxHP, mainPlayer->MP, mainPlayer->maxMP, mainPlayer->exp,mainPlayer->expArr[mainPlayer->level], mainPlayer->score,mainPlayer->level);

		if (pauseOrcontinue == 2) {
			while (1) {
				if (isClick) {
					hitButton();
					mt.lock();
					short tempX = mouseX;
					short tempY = mouseY;
					isClick = 0;
					mt.unlock();
					if (chooseType(tempX, tempY)) {
						pauseOrcontinue = 0;
						break;
					}
				}
			}
		}
		else if (pauseOrcontinue == 1) {
			drawAlpha(&continueButton, 1, 152);
			pauseOrcontinue++;
		}
		else {
			drawAlpha(&pauseButton, 1, 152);
		}

		drawAlpha(&quitButton, 51, 152);

		//绘制子弹
		for (int i = 0; i < bulManager.bulletVector.size(); i++) {
			if (bulManager.bulletVector[i].isLive) {
				drawAlpha(bul, bulManager.bulletVector[i].posX, bulManager.bulletVector[i].posY);
			}
		}

		//绘制敌人
		for (int i = 0; i < spawnVector.size(); i++) {
			//第一类敌人
			if (i == 0) {
				for (int j = 0; j < spawnVector[i].enemyVec.size(); j++) {
					if (spawnVector[i].enemyVec[j] != nullptr && spawnVector[i].enemyVec[j]->isLive == 1) {
						//如果活着就绘制 否则不绘制
						if (spawnVector[i].enemyVec[j]->direct[0] >= 0.0) {
							drawAlpha(&enemyImageType1[countType1], spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY);
							//putimage(spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY, &enemyImageType1[countType1]);
						}
						else {
							drawAlpha(&enemyImageType1L[countType1], spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY);
							//putimage(spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY, &enemyImageType1[countType1]);
						}

					}

				}
			}
			//第二类敌人
			if (i == 1) {
				for (int j = 0; j < spawnVector[i].enemyVec.size(); j++) {
					if (spawnVector[i].enemyVec[j] != nullptr && spawnVector[i].enemyVec[j]->isLive == 1) {
						//如果活着就绘制 否则不绘制
						
						if (spawnVector[i].enemyVec[j]->direct[0] >= 0.0) {
							drawAlpha(&enemyImageType2[countType2], spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY);
							//putimage(spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY, &enemyImageType2[countType2]);
						
						}
						else {
							drawAlpha(&enemyImageType2L[countType2], spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY);
							//putimage(spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY, &enemyImageType2[countType2]);
						;
						}
					}
				}
			}
			//第三类敌人
			if (i == 2) {
				for (int j = 0; j < spawnVector[i].enemyVec.size(); j++) {
					if (spawnVector[i].enemyVec[j] != nullptr && spawnVector[i].enemyVec[j]->isLive == 1) {
						//如果活着就绘制 否则不绘制
						
						if (spawnVector[i].enemyVec[j]->direct[0] >= 0.0) {
							drawAlpha(&enemyImageType3[countType3], spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY);
							//putimage(spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY, &enemyImageType3[countType3]);
							
						}
						else {
							drawAlpha(&enemyImageType3L[countType3], spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY);
							//putimage(spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY, &enemyImageType3[countType3]);
							
						}
					}
				}
			}
		}

		//绘制主角
		if (left) {
			drawAlpha(&playerL[countPlayer], mainPlayer->posX, mainPlayer->posY);
		
		}
		else {
			drawAlpha(&playerR[countPlayer], mainPlayer->posX, mainPlayer->posY);
		
		}
		
		FlushBatchDraw();

		/*
		
		if (left) {
			BeginBatchDraw();
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					putimage(640 * j, 640 * i, &bk);
				}
			}
			
			//showUI(hashMap,uiImage, mainPlayer->HP, mainPlayer->maxHP, mainPlayer->MP, mainPlayer->maxMP, mainPlayer->exp,mainPlayer->expArr[mainPlayer->level], mainPlayer->score);

			if (pauseOrcontinue == 2) {
				while (1) {
					if (isClick) {
						mt.lock();
						short tempX = mouseX;
						short tempY = mouseY;
						isClick = 0;
						mt.unlock();
						if (chooseType(tempX, tempY)) {
							pauseOrcontinue = 0;
							break;
						}
					}
				}
			}
			else if (pauseOrcontinue == 1) {
				drawAlpha(&continueButton, 38, 152);
				pauseOrcontinue++;
			}
			else {
				drawAlpha(&pauseButton, 38, 152);
			}
					
			//绘制子弹
			for (int i = 0; i < bulManager.bulletVector.size(); i++) {
				if (bulManager.bulletVector[i].isLive) {
					drawAlpha(bul, bulManager.bulletVector[i].posX, bulManager.bulletVector[i].posY);
				}
			}
		
			//绘制敌人
			for (int i = 0; i < spawnVector.size(); i++) {
				//第一类敌人
				if (i == 0) { 
					for (int j = 0; j < spawnVector[i].enemyVec.size(); j++) {
						if (spawnVector[i].enemyVec[j] != nullptr && spawnVector[i].enemyVec[j]->isLive==1) {
							//如果活着就绘制 否则不绘制
							if (spawnVector[i].enemyVec[j]->direct[0] >= 0.0) {
								drawAlpha(&enemyImageType1[countType1], spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY);
								//putimage(spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY, &enemyImageType1[countType1]);
							}
							else {
								drawAlpha(&enemyImageType1L[countType1], spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY);
								//putimage(spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY, &enemyImageType1[countType1]);
							}
							
						}
						
					}
				}
				//第二类敌人
				if (i == 1) {
					for (int j = 0; j < spawnVector[i].enemyVec.size(); j++) {
						if (spawnVector[i].enemyVec[j] != nullptr && spawnVector[i].enemyVec[j]->isLive == 1) {
							//如果活着就绘制 否则不绘制
							if (spawnVector[i].enemyVec[j]->direct[0] >= 0.0) {
								drawAlpha(&enemyImageType2[countType2], spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY);
								//putimage(spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY, &enemyImageType2[countType2]);
							}
							else {
								drawAlpha(&enemyImageType2L[countType2], spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY);
								//putimage(spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY, &enemyImageType2[countType2]);
							}
						}
					}
				}
				//第三类敌人
				if (i == 2) {
					for (int j = 0; j < spawnVector[i].enemyVec.size(); j++) {
						if (spawnVector[i].enemyVec[j] != nullptr && spawnVector[i].enemyVec[j]->isLive == 1) {
							//如果活着就绘制 否则不绘制
							if (spawnVector[i].enemyVec[j]->direct[0] >= 0.0) {
								drawAlpha(&enemyImageType3[countType3], spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY);
								//putimage(spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY, &enemyImageType3[countType3]);
							}
							else {
								drawAlpha(&enemyImageType3L[countType3], spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY);
								//putimage(spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY, &enemyImageType3[countType3]);
							}							
						}					
					}
				}
			}

			//绘制主角
			drawAlpha(&playerL[countPlayer], mainPlayer->posX, mainPlayer->posY);

			FlushBatchDraw();
		}
		else {
			BeginBatchDraw();
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					putimage(640 * j, 640 * i, &bk);
				}
			}
			
			//showUI(hashMap, uiImage, mainPlayer->HP, mainPlayer->maxHP, mainPlayer->MP, mainPlayer->maxMP, mainPlayer->exp,mainPlayer->expArr[mainPlayer->level], mainPlayer->score);

			if (pauseOrcontinue == 2) {
				while (1) {
					if (isClick) {
						mt.lock();
						short tempX = mouseX;
						short tempY = mouseY;
						isClick = 0;
						mt.unlock();
						if (chooseType(tempX, tempY)) {
							pauseOrcontinue = 0;
							break;
						}
					}
				}
			}
			else if (pauseOrcontinue == 1) {
				drawAlpha(&continueButton, 38, 152);
				pauseOrcontinue++;
			}
			else {
				drawAlpha(&pauseButton, 38, 152);
			}
			
			
			//绘制子弹
			for (int i = 0; i < bulManager.bulletVector.size(); i++) {
				if (bulManager.bulletVector[i].isLive) {
					drawAlpha(bul, bulManager.bulletVector[i].posX, bulManager.bulletVector[i].posY);
				}
			}

			//绘制敌人
			for (int i = 0; i < spawnVector.size(); i++) {
				//第一类敌人
				if (i == 0) {
					for (int j = 0; j < spawnVector[i].enemyVec.size(); j++) {
						if (spawnVector[i].enemyVec[j] != nullptr && spawnVector[i].enemyVec[j]->isLive == 1) {
							//如果活着就绘制 否则不绘制
							if (spawnVector[i].enemyVec[j]->direct[0] >= 0.0) {
								drawAlpha(&enemyImageType1[countType1], spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY);
								//putimage(spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY, &enemyImageType1[countType1]);
							}
							else {
								drawAlpha(&enemyImageType1L[countType1], spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY);
								//putimage(spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY, &enemyImageType1[countType1]);
							}
						}						
					}
				}
				//第二类敌人
				if (i == 1) {
					for (int j = 0; j < spawnVector[i].enemyVec.size(); j++) {
						if (spawnVector[i].enemyVec[j] != nullptr && spawnVector[i].enemyVec[j]->isLive == 1) {
							//如果活着就绘制 否则不绘制						
							if (spawnVector[i].enemyVec[j]->direct[0] >= 0.0) {
								drawAlpha(&enemyImageType2[countType2], spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY);
								//putimage(spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY, &enemyImageType2[countType2]);
							}
							else {
								drawAlpha(&enemyImageType2L[countType2], spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY);
								//putimage(spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY, &enemyImageType2[countType2]);
							}
						}
					}
				}
				//第三类敌人
				if (i == 2) {
					for (int j = 0; j < spawnVector[i].enemyVec.size(); j++) {
						if (spawnVector[i].enemyVec[j] != nullptr && spawnVector[i].enemyVec[j]->isLive == 1) {
							//如果活着就绘制 否则不绘制
							if (spawnVector[i].enemyVec[j]->direct[0] >= 0.0) {
								drawAlpha(&enemyImageType3[countType3], spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY);
								//putimage(spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY, &enemyImageType3[countType3]);
							}
							else {
								drawAlpha(&enemyImageType3L[countType3], spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY);
								//putimage(spawnVector[i].enemyVec[j]->posX, spawnVector[i].enemyVec[j]->posY, &enemyImageType3[countType3]);
							}
						}
					}
				}
			}

			//绘制主角
			drawAlpha(&playerR[countPlayer], mainPlayer->posX, mainPlayer->posY);

			FlushBatchDraw();
		}
		*/
	
		
		//向上移动
		if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('w') ||GetAsyncKeyState('W')) {
			mainPlayer->playerMove(0, -1);
		}
		//向下移动
		if (GetAsyncKeyState(VK_DOWN)|| GetAsyncKeyState('S') || GetAsyncKeyState('s')) {
			mainPlayer->playerMove(0, 1);
		}
		//向右移动
		if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D') || GetAsyncKeyState('d')) {
			mainPlayer->playerMove(1, 0);
			left = 0;
		}
		//向左移动
		if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A') || GetAsyncKeyState('a')) {
			mainPlayer->playerMove(-1, 0);
			left = 1;
		}

		countPlayer++;
		countType1++;
		countType2++;
		countType3++;

		Sleep(100);
		cleardevice();
	}

	mt.lock();
	isOver = 1;
	mt.unlock();

	if (overType == 1) {
		gameWin();
		winPage();
		Sleep(200);
	}
	else if(overType==2){
		gameOver();
		overPage();
		Sleep(200);
	}

}

//鼠标事件
void mouseEvent(short& mouseX, short& mouseY, bool& click,bool &isOver)
{
	MOUSEMSG* ms = new MOUSEMSG;
	while (1) {
		if (PeekMouseMsg(ms)) {
			if (ms->uMsg == WM_LBUTTONDOWN) {
				mt.lock();
				mouseX = ms->x;
				mouseY = ms->y;
				click = 1;
				mt.unlock();
			}
		}

		if (isOver) {
			break;
		}
	}
	delete ms;
	ms = nullptr;
}
