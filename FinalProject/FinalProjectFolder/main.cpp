// 인덕이 키우기 게임
// 인하대학교 정보통신공학과 12181761 김현조

#pragma once //어떤 코드, 헤더파일이 다른 코드나 헤더에서 include 될때, 중복복사방지
#define _CRT_SECURE_NO_WARNINGS // sprintf error

#include "bmpfuncs.h"
#include <GL/freeglut.h>
#include <gl/glut.h> //OpenGL을 사용하기 위해 윈도우 시스템과 연결하는 함수들
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
#include <string.h> // Character 출력 - strlen 함수
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PI 3.14159265


#define MAGIC_KEY 224
#define SPACE 32
#define KEY_NUM 4

// 전역변수 선언

volatile double theta = 45.0; // 캐싱된 data를 읽지 않고 항상 메모리에 접근
volatile double phi = 45.0;
volatile int radius = 18;
volatile double upVector = cos(phi * PI / 180);

volatile double* angle = new double[7]();
volatile double rotateFactor = 1.0;
bool spinEnable = true;
bool display_axis = false;
bool set_materialProperty = true;
int current_width, current_height;

// 광원 설정 모드
volatile unsigned char lightMode = 0;

// 시야 설정
volatile double eyex, eyey, eyez;

// Texture Mapping 설정
GLuint tmp;

// Quadric Object 생성
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
	system("title 인덕이 키우기 게임");
}

// DRAW SECTION

// GAME HOME
void DrawGameHome()
{
	system("cls"); // Clean Screen
	gotoXY(2, 2);
	cout << "인덕이 키우기 게임";
	gotoXY(15, 2);
	cout << "인덕이 게임 ON";
	gotoXY(15, 4);
	cout << "게임 조작법";
	gotoXY(15, 10);
	cout << "안녕";
}

// 게임 조작법
void DrawGameInfo()
{
	cout << "----------게임 조작법----------";
	cout << "'x' : zoom in";
	cout << "'z' : zoom out";
	cout << "방향키 : Object 이동";
	cout << "'+' : Object rotate Left";
	cout << "'-' : Object rotate Right";
	cout << "F5 : 새로고침";
}

// 개발자 소개
void DrawDeveloperInfo()
{
	cout << "----------개발자 소개----------";
	cout << "인하대학교 정보통신공학과 12181761 김현조";
	cout << "Mei";
}

// 커서 움직임
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
		DrawGameHome(); // 첫 화면
		DrawUserCursor(y);
		input = _getch();
		// →←↑↓
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

// STAGE 1 시작
void GameStart1()
{
	cout << "STAGE 1";
	cout << "인덕이 알 찾기";
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