#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#define WIN_HEIGHT 240
#define WIN_WIDTH 320
#define MAX_SNAKE 100//蛇的最大节数
int score=0;
//枚举
enum DIR	
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
//定义蛇的结构体
struct Snake_tlg
{
	int num;
	int dir;//方向
	int size;
	POINT coor[MAX_SNAKE];
}snake;
//定义食物的结构体
struct Food_tlg
{
	POINT fd;
	int flag;
	DWORD color;
}food;
//结构体初始化
void GameInit()
{
	srand(GetTickCount());
	//初始化蛇
	snake.num=3;
	snake.dir=RIGHT;
	snake.size=10;
	snake.coor[2].x =0;
	snake.coor[2].y =0;
	snake.coor[1].x =snake.size;
	snake.coor[1].y =0;
	snake.coor[0].x =2*snake.size;
	snake.coor[0].y =0;
	//初始化食物
	food.fd.x=rand()%(WIN_WIDTH/10)*10;
	food.fd.y=rand()%(WIN_HEIGHT/10)*10;
	food.flag=1;
	food.color=RGB(rand()%256,rand()%256,rand()%256);
}
void GameDraw()
{
	//设置背景颜色
	setbkcolor(RGB(105,160,141));
	cleardevice();
	setfillcolor(YELLOW);
	setlinecolor(BLACK);
	//画蛇
	for(int i=0;i<snake.num;i++)
	{

		fillrectangle(snake.coor[i].x,snake.coor[i].y,snake.coor[i].x+snake.size,snake.coor[i].y+snake.size);
	}
	//画食物
	if(food.flag==1)
	{
		setfillcolor(food.color);
		fillellipse(food.fd.x,food.fd.y,food.fd.x+10,food.fd.y+10);
	}
}
void GameMove()
{
	for(int i=snake.num-1;i>0;i--)//从最后一节蛇 开始每节移动到上一节位置
	{
		snake.coor[i].x = snake.coor[i - 1].x;
		snake.coor[i].y = snake.coor[i - 1].y;
	}
	switch(snake.dir)	//通过方向来移动位置
	{
	case UP:
		snake.coor[0].y-=10;
		if (snake.coor[0].y < 0) snake.coor[0].y = WIN_HEIGHT;	//穿墙
		break;
	case DOWN:
		snake.coor[0].y+=10;
		if (snake.coor[0].y > WIN_HEIGHT) snake.coor[0].y = 0;
		break;
	case LEFT:
		snake.coor[0].x-=10;
		if (snake.coor[0].x < 0) snake.coor[0].x = WIN_WIDTH;
		break;
	case RIGHT:
		snake.coor[0].x+=10;
		if (snake.coor[0].x > WIN_WIDTH) snake.coor[0].x = 0;
		break;
	default:
		break;
	}
}
void KeyControl()
{
	//使用win32api获取键盘方向
	if(GetAsyncKeyState(VK_UP)&&snake.dir!=DOWN)
	{
		snake.dir = UP;
	}
	if (GetAsyncKeyState(VK_DOWN)&&snake.dir!=UP)
	{
		snake.dir = DOWN;
	}
	if (GetAsyncKeyState(VK_RIGHT)&&snake.dir!=LEFT)
	{
		snake.dir = RIGHT;
	}
	if (GetAsyncKeyState(VK_LEFT)&&snake.dir!=RIGHT)
	{
		snake.dir = LEFT;
	}
}
void EatFood()
{
	if(snake.coor[0].x==food.fd.x&&snake.coor[0].y==food.fd.y&&food.flag==1)
	{
		score+=10;
		system("cls");
		snake.num++;
		food.flag=0;
		printf("\a");
		printf("分数 ：%d\n",score);
		printf("\n蛇长 ：%d\n", snake.num);
	}
	if(food.flag==0)
	{
		food.fd.x = rand() % (WIN_WIDTH / 10) * 10;
		food.fd.y = rand() % (WIN_HEIGHT / 10) * 10;
		food.flag = 1;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
}
void NoEatSelf()
{
	for(int i=4;i<snake.num;i++)
	{
		if(snake.coor[0].x==snake.coor[i].x&&snake.coor[0].y==snake.coor[i].y)
		{
			outtextxy(200,200,L"Game Over!");
			_getch();
			exit(666);
		}
	}
}
int main()
{
	initgraph(WIN_WIDTH,WIN_HEIGHT,SHOWCONSOLE);
	GameInit();
	while(1)
	{
		GameMove();
		GameDraw();
		EatFood();
		KeyControl();
		NoEatSelf();
		Sleep(50);
	}
	getchar();
	closegraph();
	return 0;
}