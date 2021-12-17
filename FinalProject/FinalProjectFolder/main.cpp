// �δ��� Ű��� ����
// ���ϴ��б� ������Ű��а� 12181761 ������

#pragma once //� �ڵ�, ��������� �ٸ� �ڵ峪 ������� include �ɶ�, �ߺ��������
#define _CRT_SECURE_NO_WARNINGS // sprintf error

#include "bmpfuncs.h"
#include <GL/freeglut.h>
#include <gl/glut.h> //OpenGL�� ����ϱ� ���� ������ �ý��۰� �����ϴ� �Լ���
#include <stdio.h>

#include <Windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <ctime>
#pragma comment(lib, "winmm.lib")

#include <iostream>
using namespace std;


#include <stdlib.h>
#include <string.h> // Character ��� - strlen �Լ�
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PI 3.14159265


#define MAGIC_KEY 224
#define SPACE 32
#define KEY_NUM 4

// �������� ����

volatile double theta = 45.0; // ĳ�̵� data�� ���� �ʰ� �׻� �޸𸮿� ����
volatile double phi = 45.0;
volatile int radius = 18;
volatile double upVector = cos(phi * PI / 180);

volatile double* angle = new double[7]();
volatile double rotateFactor = 1.0;
bool spinEnable = true;
bool display_axis = false;
bool set_materialProperty = true;
int current_width, current_height;

// ���� ���� ���
volatile unsigned char lightMode = 0;

// �þ� ����
volatile double eyex, eyey, eyez;

// Texture Mapping ����
GLuint tmp;

// Quadric Object ����
GLUquadricObj* qobj = gluNewQuadric();

// Object Selector
volatile unsigned char selector = 4;


enum MENU
{
	GAMESTART = 0,
	GAMEINFO,
	QUIT
};

enum KEYBOARD
{
	UP = 72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80
};


/* Function List */
void init(void);
void resize(int, int);

void draw(void);
void draw_string(void*, const char*, float, float, float, float, float);
void draw_text(void);

void mouse(int, int, int, int);
void mouseWheel(int but, int dir, int x, int y);
void keyboard(unsigned char, int, int);
void specialKeyboard(int, int, int);

void idle(void);

void light_default(void);
void setDefault(void);

void light_sel(void);

typedef unsigned char uchar;



//Cursor move
void gotoXY(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//title, console size
void SetConsoleView()
{
	system("mode con:cols=50 lines=20");
	system("title �δ��� Ű��� ����");
}

// DRAW SECTION

// GAME HOME
void DrawGameHome()
{
	system("cls"); // Clean Screen
	gotoXY(2, 2);
	cout << "�δ��� Ű��� ����";
	gotoXY(15, 2);
	cout << "�δ��� ���� ON";
	gotoXY(15, 4);
	cout << "���� ���۹�";
	gotoXY(15, 10);
	cout << "�ȳ�";
}

// ���� ���۹�
void DrawGameInfo()
{
	cout << "----------���� ���۹�----------";
	cout << "'x' : zoom in";
	cout << "'z' : zoom out";
	cout << "����Ű : Object �̵�";
	cout << "'+' : Object rotate Left";
	cout << "'-' : Object rotate Right";
	cout << "F5 : ���ΰ�ħ";
}

// ������ �Ұ�
void DrawDeveloperInfo()
{
	cout << "----------������ �Ұ�----------";
	cout << "���ϴ��б� ������Ű��а� 12181761 ������";
	cout << "Mei";
}

// Ŀ�� ������
void DrawUserCursor(int& y)
{
	if (y <= 0)
	{
		y = 0;
	}
	else if (y >= 2)
	{
		y = 2;
	}

	gotoXY(9, 8 + y);
	cout << ">";
}


// FUNCTION SECTION

void GameInfo()
{
	DrawGameInfo();
	system("pause>null");
}

MENU ReadyGame()
{
	int y = 0;
	int input = 0;
	while (true)
	{
		DrawGameHome(); // ù ȭ��
		DrawUserCursor(y);
		input = _getch();
		// �����
		if (input == MAGIC_KEY)
		{
			switch (_getch())
			{
			case UP:
				--y;
				break;
			case DOWN:
				++y;
				break;
			}
		}
		else if (input == SPACE)
		{
			switch (y)
			{
			case 0:
				return GAMESTART;
			case 1:
				return GAMEINFO;
			case 2:
				return QUIT;
			}
		}
	}
}

// STAGE 1 ����
void GameStart1()
{
	cout << "STAGE 1";
	cout << "�δ��� �� ã��";
}

int main(void)
{
	SetConsoleView();
	while (true)
	{
		switch (ReadyGame())
		{
		case GAMESTART:
			GameStart1();
			break;
		case GAMEINFO:
			GameInfo();
			break;
		case QUIT:
			return 0;
		}
	}
	return 0;
}