#include<graphics.h>
#include<stdio.h>
#include<conio.h>

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

enum movPosition { right, left, down, up };

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
		setlinecolor(WHITE);
		setfillcolor(GREEN);
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);
	}
	return 0;
}

int moveSnake()
{
	for(int i = snake.num - 1;i>0;i--)
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

void main()
{
	initgraph(800,600);
	initSnake();
	drawSnake();
	while (1)
	{
		cleardevice();
		drawSnake();
		moveSnake();
		Sleep(300);
		while (_kbhit())
		{
			keyDown();
		}
	}
	getchar();
	closegraph();
}