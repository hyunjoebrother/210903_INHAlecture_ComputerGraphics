#include <gl/glut.h> //OpenGL을 사용하기 위해 윈도우 시스템과 연결하는 함수들
#include <stdio.h>
#include <iostream>
using namespace std;
// Character 출력 - strlen 함수
#include <string.h>
#include <math.h>

// 점 찍기 좌표 전역변수
int pointX, pointY;

// 카메라 좌표 -> 구좌표계를 위한 전역변수 
double radius = 10;
double theta = 45, phi = 45;

double cam[3]; // 카메라 위치
double center[3] = { 0, 0, 0 }; // 바라보는 점
double up[3] = { 0, 1, 0 }; // 카메라의 Up vector

// 구좌표계 지정
int x, y, z;

/* 초기화 및 Display Callback 함수 */

// 사용자 초기화 함수 
void init(void)
{
	printf("Init function ON\n");
	/* 화면의 기본색으로 Black 설정 */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// (0,0) ~ (500,500) 2차원 viewport 생성
	gluOrtho2D(0.0f, 500.0f, 0.0f, 500.0f);

	// Alpha-Blendign OFF
	glDisable(GL_BLEND);
}


/* Callback 함수 정의 */

// key에 따른 phi, theta 값 변경 by 키보드 입력
void special_keyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		phi -= 5;
		if (phi < 0) phi = 355;
		printf("Got Left_KEY\n");
	}
	if (key == GLUT_KEY_RIGHT)
	{
		phi += 5;
		if (phi >= 360) phi = 0;
		printf("Got Right_KEY\n");
	}
	else if (key == GLUT_KEY_UP)
	{
		theta -= 5;
		if (theta <= 0) theta = 360;
		printf("Got Up_KEY\n");
	}
	else if (key == GLUT_KEY_DOWN)
	{
		theta += 5;
		if (theta > 360) theta = 5;
		printf("Got Down_KEY\n");
	}

	cout << "theta : " << theta << ", phi : " << phi << endl;

	// 화면 재생성 - 실시간 반영
	glutPostRedisplay();
}


/* WM_SIZE의 메시지 처리를 위한 callback 함수 */
// 윈도우 생성 및 크기 변화시 WM_SIZE 메시지 발생

// Viewport TF와 Projection TF 구현
// -> resize 함수 (WM_SIZE 처리)에서 (= glutReshapeFunc)
void resize(int width, int height)
{
	// Viewport TF
	glViewport(0, 0, width, height); // 윈도우 크기 변화시 viewport 재설정
	printf("Window Change! Resize function ON\n"); // 메시지 출력 확인용
	/* 화면 좌표 정보 설정 */
	glMatrixMode(GL_PROJECTION); // 투상 좌표계 선언 -> Projection TF 가능하도록
	glLoadIdentity(); // 좌표계 초기화

	// Projection TF
	gluPerspective(45, (float)width / (float)height, 1, 500);

	glMatrixMode(GL_MODELVIEW); // Projection 설정 후 환원
}

/* xyz 좌표계 그리기 함수 */
void draw_axis(void)
{
	// 좌표축 두께
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); // X축은 red
	glVertex3f(0, 0, 0);
	glVertex3f(4, 0, 0);

	glColor3f(0, 1, 0); // Y축은 green
	glVertex3f(0, 0, 0);
	glVertex3f(0, 4, 0);

	glColor3f(0, 0, 1); // Z축은 blue
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 4);
	glEnd();
	// 두께 다시 환원
	glLineWidth(1);
}

// Display Callback 함수
// draw 함수 호출 전에 resize() 호출됨 -> Viewport & Projection TF 끝난 상태
// -> Viewing TF ON
void draw(void)
{
	printf("Draw function ON\n");
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // 단위행렬로 

	// Viewing TF (World -> Camera Coordinate)
	// cam, center, up -> 키보드 입력을 받자
	// gluLookAt(5, 0, -10, 0, 0, 0, 0, 1, 0); 
	// -> (10,10,10)에서 (0,0,0) 바라보는 Viewing TF

	x = radius * sin(theta) * cos(phi);
	y = radius * sin(theta) * cos(theta);
	z = radius * cos(theta);

	gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);


	// Teapot 그리기
	glColor3f(1, 1, 0);
	glutWireTeapot(4);
	draw_axis(); // 좌표계


	/* 그리기 명령을 바로 그래픽 카드로 보냄*/
	glFlush(); // Buffer에 명령을 모아둔 후에 한번에 수행
	glutSwapBuffers(); // Double Buffering시 Buffer Swap
}


/* 한번에 clear하는 함수 -> 메뉴 따로 만들어줌 */
void clear(void)
{
	/* 화면 깨끗하게 지우기 */
	glClear(GL_COLOR_BUFFER_BIT);
}


/* GLUT - 키보드 입력 처리 */

// Callback 함수 keyboard
void keyboard(unsigned char key, int x, int y)
{
	printf("You pressed %c\n", key);

	// 화면 재생성 - 실시간 반영
	glutPostRedisplay();
}


// 마우스 휠 변화 Callback 함수


/* GLUT - 메뉴 추가 */

void main_menu_function(int option)
{
	printf("Main menu %d has been selected\n", option);

	switch (option)
	{
	case 831:
		printf("Lets Clear this window!\n");
		clear();
		break;

	case 999:
		exit(0);
		break;
	}

	// 화면 재생성 - 실시간 반영
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	int submenu1; // 메뉴 만들기

	/* Window 초기화 */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12181761_김현조_Lab06 GL");

	init(); // 사용자 초기화 함수


	/* Callback 함수 정의 */
	glutDisplayFunc(draw); // draw: 실제 그리기 함수
	glutKeyboardFunc(keyboard); // keyboard 함수 만들어주자

	glutReshapeFunc(resize); // WM_SIZE 처리하는 Callback 함수 resize 지정
	glutSpecialFunc(special_keyboard); // 키보드 입력으로 시점 조정

	glutCreateMenu(main_menu_function);

	glutAddMenuEntry("Clear", 831);
	glutAddMenuEntry("Quit", 999);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	/* Looping 시작 */
	glutMainLoop(); // 가장 마지막에 오도록...!

	return 0;
}