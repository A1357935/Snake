#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<time.h>
#include<windef.h>

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
	food.flag = 1;
	for (int i = 0; i < snake.num; i++)
	{
		if (food.foodxy.x == snake.xy[i].x && food.foodxy.y == snake.xy[i].y || food.foodxy.y <= 29 || food.foodxy.y >= 591)
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
		food.eatGrade += 1;
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
		if (boom.Boomxy.x == snake.xy[i].x && boom.Boomxy.y == snake.xy[i].y || boom.Boomxy.y <= 29 || boom.Boomxy.y >= 591)
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
		if (grass.grassxy.x == snake.xy[i].x && grass.grassxy.y == snake.xy[i].y || grass.grassxy.y <= 29 || grass.grassxy.y >= 591)
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

int gameover()
{

	if (snake.xy[0].x <= 9 || snake.xy[0].y <= 29 || snake.xy[0].x >= 781 || snake.xy[0].y >= 581)
	{
		return 1;
	}
	if (snake.num <= 2)
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
	setbkcolor(WHITE);
	initSnake();
	drawSnake();
	while (1)
	{
		cleardevice();
		setlinecolor(BLACK);
		rectangle(9, 30, 791, 591);
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
		outtextxy(350, 10, "Score£º");
		outtextxy(410, 10, grade);
		if (boom.flag == 0)
		{
			myBoom();
		}
		if (food.flag == 0)
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
			closegraph();
			printf("GameOver!");
			system("Pause");                   //´æÔÚbug£¬Î´½â¾ö
			break;
		}
		drawSnake();
		moveSnake();
		Sleep(100);
		while (_kbhit())
		{
			keyDown();
		}
	}
	getchar();
	closegraph();
}