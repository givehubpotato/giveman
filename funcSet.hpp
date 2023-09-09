#pragma once
#include <graphics.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include "button.hpp"


using namespace std;

//������
// 
// 
//͸������ͼ
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y);
//�����ť��Ч
void hitButton();
//������ϷBGM
void BGM();
//������Ч
void hurt();
//player attack
void playerAttack();
// enemyhitted
void enemyHitted();
// overSound
void gameOver();
// winSound
void gameWin();
//���㷽������
vector<double> setDirect(int P1X, int P1Y, int P2X, int P2Y);
//��ײ����߼�
bool collisionCheck(int selfX,int selfY,int targetX,int targetY,int selfR,int targetR);
//���ý���
void settingPage(bool *st,double *alpha);
//��Ϸ��ʼ����
void init(double* alpha);
//��Ϸ���ؽ���
void loading();
//��ʾUI
void showUI(unordered_map<int, IMAGE>& hashMap, vector<IMAGE*> imgVector,int HP,int maxHP,int MP,int maxMP,int exp,int maxExp,int getScore,int level);
//block
bool block(int x, int y);
//overPage
void overPage();
//winPage
void winPage();
//���������
int chooseType(int x, int y);
//
void shullfeFunc(vector<int> &suf);


//����ʵ��
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //xΪ����ͼƬ��X���꣬yΪY����
{

	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}

void hitButton()
{
	mciSendString(L"close ./sound/button.mp3", 0, 0, 0);
	mciSendString(L"open ./sound/button.mp3", 0, 0, 0);
	mciSendString(L"play ./sound/button.mp3", 0, 0, 0);
}

void BGM()
{
	mciSendString(L"open ./sound/PVZ.mp3", 0, 0, 0);
	mciSendString(L"play ./sound/PVZ.mp3 repeat", 0, 0, 0);
}

void hurt()
{
	mciSendString(L"close ./sound/hurt.mp3", 0, 0, 0);
	mciSendString(L"open ./sound/hurt.mp3", 0, 0, 0);
	mciSendString(L"play ./sound/hurt.mp3", 0, 0, 0);
}

void playerAttack()
{
	mciSendString(L"close ./sound/attack.mp3", 0, 0, 0);
	mciSendString(L"open ./sound/attack.mp3", 0, 0, 0);
	mciSendString(L"play ./sound/attack.mp3", 0, 0, 0);
}

void enemyHitted()
{
	mciSendString(L"close ./sound/enemyHitted.mp3", 0, 0, 0);
	mciSendString(L"open ./sound/enemyHitted.mp3", 0, 0, 0);
	mciSendString(L"play ./sound/enemyHitted.mp3", 0, 0, 0);
}

void gameOver()
{
	mciSendString(L"close ./sound/gameOver.mp3", 0, 0, 0);
	mciSendString(L"open ./sound/gameOver.mp3", 0, 0, 0);
	mciSendString(L"play ./sound/gameOver.mp3", 0, 0, 0);
}

void gameWin()
{
	mciSendString(L"close ./sound/gameWin.mp3", 0, 0, 0);
	mciSendString(L"open ./sound/gameWin.mp3", 0, 0, 0);
	mciSendString(L"play ./sound/gameWin.mp3", 0, 0, 0);
}

vector<double> setDirect(int P1X, int P1Y, int P2X, int P2Y)
{
	int dirX = P2X - P1X;
	int dirY = P2Y - P1Y;
	double temp;
	try {
		temp = sqrt(dirX * dirX + dirY * dirY);
		if (temp - 0.001 <= 0.0) {
			throw 0.0;
		}
	}
	catch(double dl){
		try {
			temp = (abs(dirX)+abs(dirY))/2;
			if (temp - 0.001 <= 0) {
				throw 1.0;
			}
		}
		catch(double dltemp){
			temp = 50.0;
		}		
	}
	
	double X = dirX / temp;
	double Y = dirY / temp;
	return { X,Y };
}

void init(double *alpha)
{
	IMAGE img[4];
	loadimage(&img[0], L"./picture/beginPage/beginPage.jpg");
	loadimage(&img[1], L"./picture/beginPage/start.png");
	loadimage(&img[2], L"./picture/beginPage/setting.png");
	loadimage(&img[3], L"./picture/beginPage/quit.png");


	vector<button> buttonVector(3);	
	button but1(&img[1], 568, 360);
	button but2(&img[2], 568, 430);
	button but3(&img[3], 568, 490);

	buttonVector[0] = but1;
	buttonVector[1] = but2;
	buttonVector[2] = but3;

	bool *state=new bool;
	*state = 1;
	MOUSEMSG* msg = new MOUSEMSG;
	short mouseX = 0, mouseY = 0;


	while (*state) {
		BeginBatchDraw();
		
		putimage(0, 0, &img[0]);

		for (int i = 0; i < buttonVector.size(); i++) {
			buttonVector[i].showButton();
		}

		FlushBatchDraw();

		if (PeekMouseMsg(msg)) {
			if (msg->uMsg == WM_LBUTTONDOWN) {
				mouseX = msg->x;
				mouseY = msg->y;
			}
		}

		
		if (buttonVector[0].buttonDown(mouseX, mouseY)) {
			hitButton();
			cleardevice();		
			break;
		}

		if (buttonVector[1].buttonDown(mouseX, mouseY)) {
			hitButton();
			cleardevice();
			settingPage(state,alpha);			
		}

		if (buttonVector[2].buttonDown(mouseX, mouseY)) {
			hitButton();
			HWND hWnd;
			hWnd = GetHWnd();
			int num = MessageBox(hWnd, L"�˳���Ϸ", L"��Ϣ֪ͨ", MB_OKCANCEL);
			if (num == IDOK)
			{
				exit(0);
			}
			if (num == IDCANCEL)
			{
				
			}
		}

		mouseX = 0;
		mouseY = 0;
	}
	
}

void settingPage(bool *st,double *alpha)
{
	IMAGE img;
	loadimage(&img, L"./picture/beginPage/settingPicture.jpg");

	button back1(50, 50, 108, 108);
	button back2(1130, 175, 1190, 230);
	button gameStart(1180, 50, 1235, 108);
	button selectEasy(235, 530, 400, 590);
	button selectNormal(530, 525, 700, 590);
	button selectHard(800, 540, 1020, 630);

	MOUSEMSG* msg = new MOUSEMSG;
	short mouseX = 0, mouseY = 0;
	HWND hwnd;
	while (*st) {
		if (PeekMouseMsg(msg)) {
			if (msg->uMsg == WM_LBUTTONDOWN) {
				mouseX = msg->x;
				mouseY = msg->y;
			}
		}

		BeginBatchDraw();
		putimage(0, 0, &img);
		FlushBatchDraw();

		if (selectEasy.buttonDown(mouseX,mouseY)) {
			hitButton();
			hwnd = GetHWnd();
			int num1 = MessageBox(hwnd, L"ȷ���Ƿ�ѡ���ģʽ", L"��Ϣ֪ͨ", MB_OKCANCEL);
			if (num1 == IDOK)
			{
				*alpha = 1;
				//��ģʽ��ʼ��
			}
			else {
				
			}
		}
		if (selectNormal.buttonDown(mouseX, mouseY)) {
			hitButton();
			hwnd = GetHWnd();
			int num1 = MessageBox(hwnd, L"ȷ���Ƿ�ѡ��һ��ģʽ", L"��Ϣ֪ͨ", MB_OKCANCEL);
			if (num1 == IDOK)
			{
				*alpha = 1.4;
				//һ��ģʽ��ʼ��
			}
			else {
				
			}
		}
		if (selectHard.buttonDown(mouseX, mouseY)) {
			hitButton();
			hwnd = GetHWnd();
			int num1 = MessageBox(hwnd, L"ȷ���Ƿ�ѡ������ģʽ", L"��Ϣ֪ͨ", MB_OKCANCEL);
			if (num1 == IDOK)
			{
				*alpha = 1.7;
				//����ģʽ��ʼ��
			}
			else {
				
			}

		}
		if (back1.buttonDown(mouseX, mouseY) || back2.buttonDown(mouseX,mouseY)) {
			hitButton();
			return;
		}
		
		if (gameStart.buttonDown(mouseX, mouseY)) {
			hitButton();
			*st = 0;
			return;
		}

		mouseX = 0;
		mouseY = 0;
	}
}

void loading()
{
	IMAGE loading;
	loadimage(&loading, L"./picture/backGround/loading.png");
	cleardevice();
	BeginBatchDraw();
	putimage(0, 0, &loading);
	FlushBatchDraw();
	Sleep(2000);
}

bool collisionCheck(int selfX, int selfY, int targetX, int targetY,int selfR,int targetR)
{
	
	int disX = targetX - selfX;
	int disY = targetY - selfY;
			

	if (sqrt((disX * disX + disY * disY)) > (selfR + targetR)) {
		return 0;
	}
	else {
		return 1;
	}
	
}

void showUI(unordered_map<int, IMAGE>& hashMap,vector<IMAGE*> imgVector, int HP, int maxHP, int MP, int maxMP, int exp,int maxExp,int getScore,int level)
{
	ofstream outLog("./uilog.txt", ios::app);
	putimage(0, 0, imgVector[0]);
	drawAlpha(imgVector[1], 1100, 5);
	outLog << "score OK" << endl;
	putimage(152, 2, imgVector[2]);
	//putimage(152, 33, imgVector[3]);
	//putimage(152, 66, imgVector[4]);
	//putimage(152, 97, imgVector[5]);
	drawAlpha(imgVector[3], 152, 33);
	outLog << "MP OK" << endl;
	drawAlpha(imgVector[4], 150, 60);
	outLog << "EXP OK" << endl;
	drawAlpha(imgVector[5], 150, 90);
	outLog << "level OK" << endl;
	// Ѫ��
	int Width = 150;   // Ѫ������,δ�����𻵵�Ѫ������
	int const Height = 20;   // Ѫ���߶�
	int Left = imgVector[0]->getwidth() +imgVector[2]->getwidth() + 4;

	int HP_Right = Left + Width * ((double)HP / maxHP);
	int HP_Top = 2;
	int HP_Bottom = HP_Top + Height;
	setfillcolor(RED);    // Ѫ����ɫ
	fillroundrect(Left+3, HP_Top+3, HP_Right+3, HP_Bottom+3, 10, 10);

	// ����
	int MG_Right = Left + Width * ((double)MP / maxMP);
	int MG_Top = HP_Top + 26;
	int MG_Bottom = MG_Top + Height;
	setfillcolor(BLUE);    // ������ɫ
	fillroundrect(Left+3, MG_Top+10, MG_Right+3, MG_Bottom+10, 10, 10);

	// ������
	int EXP_Right = Left +Width * ((double)exp / maxExp);
	int EXP_Top = HP_Top + 52;
	int EXP_Bottom = EXP_Top + Height-2;
	setfillcolor(YELLOW);    // ��������ɫ
	fillroundrect(Left+3, EXP_Top+15, EXP_Right+3, EXP_Bottom+15, 10, 10);

	if (getScore == 0) {
		drawAlpha(&hashMap[0], 1190, 10);
	}

	vector<int> vec;
	int temp;
	while (getScore) {
		temp = getScore % 10;
		vec.push_back(temp);
		getScore /= 10;
	}

	int count = 0;
	for (int i = vec.size(); i > 0; i--) {
		drawAlpha(&hashMap[vec[i - 1]], 1190 + 21 * count, 10);
		count++;
	}

	vec.clear();
	while (level) {
		temp = level % 10;
		vec.push_back(temp);
		level /= 10;
	}

	count = 0;
	for (int i = vec.size(); i > 0; i--) {
		drawAlpha(&hashMap[vec[i - 1]], 270 + 21 * count, 90);
		count++;
	}
}

bool block(int x, int y)
{
	if (x <= 10 || x >= 1120) {
		return 1;
	}
	if (y <= 10 || y >= 658) {
		return 1;
	}

	return 0;
}

int chooseType(int x,int y)
{
	if (x > 1 && x < 51 && y>152 && y < 202) {
		return 1;
	}
	else if (x > 52 && x < 102 && y>152 && y < 202) {
		return 2;
	}
	return 0;
}

void overPage()
{
	IMAGE overImg;
	IMAGE BK;
	IMAGE *yesButton=new IMAGE;
	loadimage(&overImg, L"./picture/backGround/lost.png");
	loadimage(&BK, L"./picture/backGround/BK.png");
	loadimage(yesButton, L"./picture/backGround/yesButton.png");

	button bnt(yesButton, 250, 420);

	MOUSEMSG* overMsg=new MOUSEMSG;

	initgraph(640, 640);
	while (1) {
		BeginBatchDraw();
		putimage(0, 0, &BK);
		drawAlpha(&overImg, 60, 100);
		bnt.showButton();
		FlushBatchDraw();

		if (PeekMouseMsg(overMsg)) {
			if (overMsg->uMsg == WM_LBUTTONDOWN) {
				if (bnt.buttonDown(overMsg->x, overMsg->y)) {
					hitButton();
					break;
				}
			}
		}
	}

	cleardevice();
	delete overMsg;
	overMsg = nullptr;
	delete yesButton;
	yesButton = nullptr;
	closegraph();
}

void winPage()
{
	IMAGE winImg;
	IMAGE BK;
	IMAGE *yesButton=new IMAGE;
	loadimage(&winImg, L"./picture/backGround/victory.png");
	loadimage(&BK, L"./picture/backGround/BK.png");
	loadimage(yesButton, L"./picture/backGround/yesButton.png");

	button bnt(yesButton,250,420);

	initgraph(640, 640,SHOWCONSOLE);

	MOUSEMSG *winMsg=new MOUSEMSG;
	short mouseX = 0, mouseY = 0;

	while (1) {
		BeginBatchDraw();
		putimage(0, 0, &BK);
		drawAlpha(&winImg, 0, 150);

		bnt.showButton();
		FlushBatchDraw();

		if (PeekMouseMsg(winMsg)) {
			if (winMsg->uMsg == WM_LBUTTONDOWN) {
				mouseX = winMsg->x;
				mouseY = winMsg->y;
			}
		}

		if (bnt.buttonDown(mouseX, mouseY)) {
			hitButton();
			break;
		}
	}

	cleardevice();
	delete winMsg;
	winMsg = nullptr;
	delete yesButton;
	yesButton = nullptr;
	closegraph();
}

void shullfeFunc(vector<int> &suf)
{
	random_shuffle(suf.begin(), suf.end());
}