#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<time.h>
#include<windef.h>
#include<mmsystem.h>

typedef struct pointxy
{
	int x;
	int y;
} MYPOINT;

struct mySnake
{
	int num;
	MYPOINT xy[100];
	char position;
} snake;

struct myfood
{
	MYPOINT foodxy;
	int flag = 0;
	int eatGrade = 0;
} food;

struct myBoom
{
	MYPOINT Boomxy;
	int flag = 0;
}boom;

struct myGrass
{
	MYPOINT grassxy;
	int flag = 0;
}grass;

struct myLevel
{
	MYPOINT levelxy;
	int flag = 0;
	int thelevel = 1;
}level;

enum movPosition { right, left, down, up };

void start()
{
	settextcolor(GREEN);
	outtextxy(200, 200, "使用wasd、方向键操控小蛇。");
	outtextxy(200, 220, "绿色为食物，食用后小蛇长度增加一格，分数+1。");
	outtextxy(200, 240, "红色为毒草，食用后小蛇长度减少两格，分数-1。");
	outtextxy(200, 260, "黑色为地雷，踩到后小蛇长度减半，分数-2。");
	outtextxy(200, 280, "长度至10和20时，得分翻倍。");
	outtextxy(200, 300, "尽量得到更多的分数！");
	outtextxy(200, 320, "按下回车开始游戏");
	int userkey = 0;
	while (userkey != 13)
	{
		if (_kbhit())
			userkey = _getch();
	}
}

int initSnake()
{
	snake.xy[2].x = 300;
	snake.xy[2].y = 400;

	snake.xy[1].x = 310;
	snake.xy[1].y = 400;

	snake.xy[0].x = 320;
	snake.xy[0].y = 400;

	snake.num = 3;
	snake.position = right;

	food.flag = 0;

	return 0;
}

int drawSnake()
{
	for (int i = 0; i < snake.num; i++)
	{
		setlinecolor(BLACK);
		setfillcolor(GREEN);
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);
	}
	return 0;
}

int moveSnake()
{
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	switch (snake.position)
	{
	case right:
		snake.xy[0].x += 10;
		break;
	case left:
		snake.xy[0].x -= 10;
		break;
	case down:
		snake.xy[0].y += 10;
		break;
	case up:
		snake.xy[0].y -= 10;
		break;
	}
	return 0;
}

void keyDown()
{
	char userkey = '/0';
	userkey = _getch();
	switch (userkey)
	{
	case 'W':
	case 'w':
	case 72:
	case 38:
		if (snake.position != down)
		{
			snake.position = up;
		}
		break;
	case 's':
	case 'S':
	case 80:
	case 40:
		if (snake.position != up)
		{
			snake.position = down;
		}
		break;
	case'a':
	case 'A':
	case 75:
	case 37:
		if (snake.position != right)
		{
			snake.position = left;
		}
		break;
	case'd':
	case'D':
	case 77:
	case 39:
		if (snake.position != left)
		{
			snake.position = right;
		}
		break;
	}
}

void myFood()
{
	food.foodxy.x = rand() % 80 * 10;
	food.foodxy.y = rand() % 60 * 10;
	food.flag += 1;
	for (int i = 0; i < snake.num; i++)
	{
		if (food.foodxy.x == snake.xy[i].x && food.foodxy.y == snake.xy[i].y || food.foodxy.y <= 39 || food.foodxy.y >= 561 || food.foodxy.x <= 39 || food.foodxy.x >= 761)
		{
			food.foodxy.x = rand() % 80 * 10;
			food.foodxy.y = rand() % 60 * 10;
		}
	}

}

void drawFood()
{
	fillrectangle(food.foodxy.x, food.foodxy.y, food.foodxy.x + 10, food.foodxy.y + 10);
}

void eatFood()
{
	if (snake.xy[0].x == food.foodxy.x && snake.xy[0].y == food.foodxy.y)
	{
		snake.num++;
		if (snake.num < 10)
		{
			food.eatGrade += 1;
		}
		if (snake.num >= 10)
		{
			food.eatGrade += 2;
		}
		if (snake.num >= 20)
		{
			food.eatGrade += 2;
		}
		food.flag = 0;
	}
}

void myBoom()
{
	boom.Boomxy.x = rand() % 80 * 10;
	boom.Boomxy.y = rand() % 60 * 10;
	boom.flag = 1;
	for (int i = 0; i < snake.num; i++)
	{
		if (boom.Boomxy.x == snake.xy[i].x && boom.Boomxy.y == snake.xy[i].y || boom.Boomxy.y <= 39 || boom.Boomxy.y >= 561 || boom.Boomxy.x <= 39 || boom.Boomxy.x >= 761)
		{
			boom.Boomxy.x = rand() % 80 * 10;
			boom.Boomxy.y = rand() % 60 * 10;
		}
	}
}

void eatBoom()
{
	if (snake.xy[0].x == boom.Boomxy.x && snake.xy[0].y == boom.Boomxy.y)
	{
		boom.flag = 0;
		food.eatGrade -= 5;
		snake.num = snake.num / 2;
	}
}

void drawBoom()
{
	fillrectangle(boom.Boomxy.x, boom.Boomxy.y, boom.Boomxy.x + 10, boom.Boomxy.y + 10);
}

void myGrass()
{
	grass.grassxy.x = rand() % 80 * 10;
	grass.grassxy.y = rand() % 60 * 10;
	grass.flag = 1;
	for (int i = 0; i < snake.num; i++)
	{
		if (grass.grassxy.x == snake.xy[i].x && grass.grassxy.y == snake.xy[i].y || grass.grassxy.y <= 39 || grass.grassxy.y >= 561|| grass.grassxy.x<=39||grass.grassxy.x>=761)
		{
			grass.grassxy.x = rand() % 80 * 10;
			grass.grassxy.y = rand() % 60 * 10;
		}
	}
}

void drawGrass()
{
	fillrectangle(grass.grassxy.x, grass.grassxy.y, grass.grassxy.x + 10, grass.grassxy.y + 10);

}

void eatGrass()
{
	if (snake.xy[0].x == grass.grassxy.x && snake.xy[0].y == grass.grassxy.y)
	{
		grass.flag = 0;
		food.eatGrade -= 2;
		snake.num = snake.num - 2;
	}
}

void nextlevel()
{
	if (snake.num >=10)
	{
		level.levelxy.x = rand() % 80 * 10;
		level.levelxy.y = rand() % 60 * 10;
		level.flag = 1;
		for (int i = 0; i < snake.num; i++)
		{
			if (level.levelxy.x == snake.xy[i].x && level.levelxy.y == snake.xy[i].y || level.levelxy.y <= 29 || level.levelxy.y >= 591)
			{
				level.levelxy.x = rand() % 80 * 10;
				level.levelxy.y = rand() % 60 * 10;
			}
		}
	}
}

void gotonextlevel()
{
	if (snake.xy[0].x == level.levelxy.x && snake.xy[0].y == level.levelxy.y)
	{
		level.flag = 0;
		level.thelevel++;
	}
}

void drawnextlevel()
{
	fillrectangle(level.levelxy.x, level.levelxy.y, level.levelxy.x + 10, level.levelxy.y + 10);
}

int gameover()
{

	if (snake.xy[0].x <= 19 || snake.xy[0].y <= 39 || snake.xy[0].x >= 771 || snake.xy[0].y >= 571)
	{
		return 1;
	}
	if (snake.num <= 1)
	{
		return 1;
	}
	for (int i = 1; i < snake.num; i++)
	{
		if (snake.xy[0].x == snake.xy[i].x && snake.xy[0].y == snake.xy[i].y)
		{
			return 1;
		}
	}

	return 0;
}

void main()
{

	srand((unsigned int)time(NULL));
	initgraph(800, 600);
	start();
	setbkcolor(WHITE);

	initSnake();
	drawSnake();
	while (1)
	{
		cleardevice();
		setlinecolor(BLACK);
		rectangle(19, 39, 781, 581);
		setfillcolor(GREEN);
		drawFood();
		setfillcolor(BLACK);
		drawBoom();
		setfillcolor(RED);
		drawGrass();
		char grade[100] = { 0 };
		sprintf_s(grade, "%d", food.eatGrade);
		setbkmode(TRANSPARENT);
		settextcolor(BLACK);
		outtextxy(350, 10, "Score：");
		outtextxy(410, 10, grade);
		if (boom.flag == 0)
		{
			myBoom();
		}
		if (food.flag ==0)
		{
			myFood();
		}
		if (grass.flag == 0)
		{
			myGrass();
		}
		eatFood();
		eatBoom();
		eatGrass();
		if (gameover())
		{
			cleardevice();
			settextcolor(LIGHTGREEN);
			settextstyle(80, 0, "宋体");
			outtextxy(200, 200, "Game Over");
			Sleep(2000);
			exit(0);
		}
		drawSnake();
		moveSnake();
		Sleep(75);
		while (_kbhit())
		{
			keyDown();
		}
	}
	getchar();
	closegraph();
}