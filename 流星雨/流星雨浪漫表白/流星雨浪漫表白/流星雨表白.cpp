
#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define MAXSTAR 1000
#define MAXMETEOR 100
//分析：星星和流星
//星星的属性
struct Star
{
	int x, y;	//坐标
	int step;	//自加控制移动速度
	int color;	//颜色
}star[MAXSTAR];
//流星的属性
struct Meteor
{
	int x, y;	//坐标
	int step;	//控制移动速度
	int style;	//流星的风格
}meteor[MAXMETEOR];

//一部曲：定义图片变量
IMAGE img1, img2, img3;

//声明函数
void initStar(int i);
void moveStar(int i);
void initData(int i);
void initMeteor(int i);
void drawMeteor(int i);
void moveMeteor(int i);

//文字输出
void text()
{
	//char text[100] = "";
	//sprintf(text, "某某某，我喜欢你，做我女朋友吧！");
	settextcolor(RGB(rand()%255,rand()%255,rand()%255));
	settextstyle(30, 0, "");
	setbkmode(TRANSPARENT);
	outtextxy(700, 550, "啦啦啦");
}
//垂直打印文字
void textAction()
{
	char *text[20] = { "有", "一", "个", "叫", "作", "c", "++", "的", "软件", "", "", "", "" };
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
//初始化数据
void initData(int i)
{
	//二部曲：加载资源
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
//初始化星星
void initStar(int i)
{
	star[i].x = rand() % 1000;
	star[i].y = rand() % 600;
	star[i].step = rand() % 6;	//[0,5]
	star[i].color = RGB(star[i].step * 51, star[i].step * 51, star[i].step * 51);
}
//移动星星
void moveStar(int i)
{
	//画点表示星星
	putpixel(star[i].x, star[i].y, star[i].color);
	//移动
	star[i].x += star[i].step;
	//如果星星移动到外面重新画
	if (star[i].x > 1000)
	{
		putpixel(star[i].x, star[i].y, star[i].color);
	}
}
//初始化流星
void initMeteor(int i)
{
	//流星初始位置在窗口上面
	meteor[i].x = rand() % 2000 - 1000;	//[0,1999]-->[-1000,999]
	meteor[i].y = -400;
	meteor[i].step = rand() % 30 + 1;
	meteor[i].style = rand() % 3 + 1;	//[0,2]-->[1,3]
}
//画流星（贴图）:贴图技术(三部曲)
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
//移动流星
void moveMeteor(int i)
{
	for (i = 0; i < MAXMETEOR; i++)
	{
		meteor[i].x += meteor[i].step;
		meteor[i].y += meteor[i].step*0.8;
	}
}