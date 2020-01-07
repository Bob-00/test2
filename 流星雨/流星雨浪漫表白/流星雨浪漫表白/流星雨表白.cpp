
#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define MAXSTAR 1000
#define MAXMETEOR 100
//���������Ǻ�����
//���ǵ�����
struct Star
{
	int x, y;	//����
	int step;	//�Լӿ����ƶ��ٶ�
	int color;	//��ɫ
}star[MAXSTAR];
//���ǵ�����
struct Meteor
{
	int x, y;	//����
	int step;	//�����ƶ��ٶ�
	int style;	//���ǵķ��
}meteor[MAXMETEOR];

//һ����������ͼƬ����
IMAGE img1, img2, img3;

//��������
void initStar(int i);
void moveStar(int i);
void initData(int i);
void initMeteor(int i);
void drawMeteor(int i);
void moveMeteor(int i);

//�������
void text()
{
	//char text[100] = "";
	//sprintf(text, "ĳĳĳ����ϲ���㣬����Ů���Ѱɣ�");
	settextcolor(RGB(rand()%255,rand()%255,rand()%255));
	settextstyle(30, 0, "");
	setbkmode(TRANSPARENT);
	outtextxy(700, 550, "������");
}
//��ֱ��ӡ����
void textAction()
{
	char *text[20] = { "��", "һ", "��", "��", "��", "c", "++", "��", "���", "", "", "", "" };
	settextcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
	settextstyle(30, 0, "");
	setbkmode(TRANSPARENT);
	int x = 450, y = 100;
	for (int i = 0; i < 13; i++)
	{
		if (i < 7)
		{

			outtextxy(x, y + i * 50, text[i]);
		}
		else
		{
			outtextxy(x + 50, y + (i - 7) * 50 +30, text[i]);
		}
		//Sleep(500);
	}
}
int main()
{
	initgraph(1000, 600); 
	mciSendString("open 2.mp3", 0, 0, 0);
	mciSendString("play 2.mp3 repeat", 0, 0, 0);

	int i = 0;
	initData(i);
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		for (i = 0; i < MAXSTAR; i++)
		{
			moveStar(i);
		}
		text();
		drawMeteor( i);
		moveMeteor(i);
		textAction();
		Sleep(100);
		EndBatchDraw();
	}

	_getch();
	closegraph();
	return 0;
}
//��ʼ������
void initData(int i)
{
	//��������������Դ
	loadimage(&img1, "1.jpg", 50, 50);
	loadimage(&img2, "2.jpg", 50, 50);
	loadimage(&img3, "3.jpg", 50, 50);

	//srand((unsigned int)time(NULL));
	for (i = 0; i < MAXSTAR; i++)
	{
		initStar(i);
	}
	for (i = 0; i < MAXMETEOR; i++)
	{
		initMeteor(i);
	}
}
//��ʼ������
void initStar(int i)
{
	star[i].x = rand() % 1000;
	star[i].y = rand() % 600;
	star[i].step = rand() % 6;	//[0,5]
	star[i].color = RGB(star[i].step * 51, star[i].step * 51, star[i].step * 51);
}
//�ƶ�����
void moveStar(int i)
{
	//�����ʾ����
	putpixel(star[i].x, star[i].y, star[i].color);
	//�ƶ�
	star[i].x += star[i].step;
	//��������ƶ����������»�
	if (star[i].x > 1000)
	{
		putpixel(star[i].x, star[i].y, star[i].color);
	}
}
//��ʼ������
void initMeteor(int i)
{
	//���ǳ�ʼλ���ڴ�������
	meteor[i].x = rand() % 2000 - 1000;	//[0,1999]-->[-1000,999]
	meteor[i].y = -400;
	meteor[i].step = rand() % 30 + 1;
	meteor[i].style = rand() % 3 + 1;	//[0,2]-->[1,3]
}
//�����ǣ���ͼ��:��ͼ����(������)
void drawMeteor(int i)
{
	for (i = 0; i < MAXMETEOR; i++)
	{
		switch (meteor[i].style)
		{
		case 1:
			putimage(meteor[i].x, meteor[i].y, &img1, SRCPAINT);
			break;
		case 2:
			putimage(meteor[i].x, meteor[i].y, &img2, SRCPAINT);
			break;
		case 3:
			putimage(meteor[i].x, meteor[i].y, &img3, SRCPAINT);
			break;
		}
	}
}
//�ƶ�����
void moveMeteor(int i)
{
	for (i = 0; i < MAXMETEOR; i++)
	{
		meteor[i].x += meteor[i].step;
		meteor[i].y += meteor[i].step*0.8;
	}
}