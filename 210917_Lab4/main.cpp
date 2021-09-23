
#include <gl/glut.h> //OpenGL을 사용하기 위해 윈도우 시스템과 연결하는 함수들
#include <stdio.h>

// Character 출력 - strlen 함수
#include <string.h>


// 점 찍기 좌표 전역변수
int pointX, pointY;

// Alpha-Blending 할 때 Alpha값 전역변수
GLfloat Alpha = 0;

// AntiAliasing 하기 전에 기본 상태는 false로 지정
bool antiON = false;

// 점찍기 for문을 위한 전역변수
int i; 


/* 초기화 및 Display Callback 함수 */

// 사용자 초기화 함수 
void init(void)
{
	/* 화면의 기본색으로 Black 설정 */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	/* 화면 좌표 정보 설정 */
	glMatrixMode(GL_PROJECTION); // 투상 좌표계 선언
	glLoadIdentity(); // 좌표계 초기화

	// (0,0) ~ (500,500) 2차원 viewport 생성
	gluOrtho2D(0.0f, 500.0f, 0.0f, 500.0f);

	// Alpha-Blendign OFF
	glDisable(GL_BLEND);
}



/* Callback 함수 정의 */

// 점 그리기
void draw_point(void)
{
	/* 점 색상 붉은색 */
	glColor3f(1.0f, 0.0f, 0.0f);
	/* 점의 크기 (초기값은 1.0) */
	glPointSize(10.0f);

	glBegin(GL_POINTS);
	glVertex2i(pointX, 500 - pointY);
	printf("point X, Y : (%d, %d)\n", pointX, 500 - pointY);
	glEnd();
}

// 선 그리기
void draw_line(void)
{
	/* 선 색상 노란색 */
	glColor3f(1.0f, 1.0f, 0.0f);

	/* 선 속성 */
	glLineWidth(5.0f); // 선 두께
	glEnable(GL_LINE_STIPPLE); // 선 패턴 변경하기 위해 STATE ON 시킴
	glLineStipple(3, 0xAAAA); // 선 패턴 (fatctor 주기, pattern 패턴)

	glBegin(GL_LINES);
	/*
	for (i = 0; i < 2; i++)
	{
		glVertex2i(pointX, 500 - pointY);
		printf("Line point X, Y : (%d, %d)\n", pointX, 500 - pointY);	
	}
	*/
	glVertex2i(150, 470);
	glVertex2i(320, 30);
	glEnd();
}

// 면(Triangle) 그리기
void draw_triangle(void)
{
	/* 면 색상 노란색 */
	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	glVertex2i(50, 50);
	glVertex2i(250, 450);
	glVertex2i(400, 100);
	glEnd();
}

// Polygon 그리기
void draw_polygon(void)
{
	/* 색상 */
	glColor3f(0.3f, 0.2f, 1.0f);

	glBegin(GL_POLYGON);
	glVertex2i(10, 10);
	glVertex2i(40, 70);
	glVertex2i(120, 200);
	glVertex2i(250, 450);
	glVertex2i(450, 350);
	glEnd();
}


/* Alpha-Blending */
void blend_function(void)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Left Triangle - Alpha값 조절
	glColor4f(1.0, 1.0, 0.0, Alpha); // yellow
	glBegin(GL_TRIANGLES);
	glVertex2i(50, 50);
	glVertex2i(50, 450);
	glVertex2i(350, 250);
	glEnd();

	// Right Triangle
	glColor4f(0.0, 1.0, 1.0, 0.75); // cyan
	glBegin(GL_TRIANGLES);
	glVertex2i(450, 50);
	glVertex2i(450, 450);
	glVertex2i(150, 250);
	glEnd();
	
	glFlush();

	// 화면 재생성 - 실시간 반영
	glutPostRedisplay();
}

/* Antialiasing */
void antialiasing_function(bool antiON)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// HINT 조건 추가
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_LINE_SMOOTH_HINT,  GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);
	
	// ON/OFF
	if (antiON)
	{
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);

		//printf("Antialiasing ON\n");
	} 
	else {
		glDisable(GL_POINT_SMOOTH);
		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_POLYGON_SMOOTH);

		//printf("Antialiasing OFF\n");
	}

	glFlush();

	// 화면 재생성 - 실시간 반영
	glutPostRedisplay();
}


// Character 출력 함수
void draw_string(void* font, const char* str, int x, int y)
{
	unsigned int i;
	glRasterPos2i(x, y);
	for (i = 0; i < strlen(str); i++) // 상단에 string.h 헤더파일 선언
	{
		glutBitmapCharacter(font, str[i]);
	}
}


// Display Callback 함수
void draw(void)
{
	// glClear(GL_COLOR_BUFFER_BIT); -> 이제 계속 유지됨

	// antialiasing ON/OFF
	antialiasing_function(antiON);

	// Character 출력
	glColor3f(1.0f, 0.7f, 0.5f);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "Graphics are cool!", 10, 10);
	glColor3f(1.0f, 1.0f, 1.5f);
	draw_string(GLUT_BITMAP_HELVETICA_18, "12181761 Kim Hyunjoe - Lab04", 230, 470);


	/* 그리기 명령을 바로 그래픽 카드로 보냄*/
	glFlush(); // Buffer에 명령을 모아둔 후에 한번에 수행
}


/* 한번에 clear하는 함수 -> 메뉴 따로 만들어줌 */
void clear(void)
{
	/* 화면 깨끗하게 지우기 */
	glClear(GL_COLOR_BUFFER_BIT);
}


/* GLUT - 마우스 입력 처리 */

// Callback 함수 mouse
// 
// 인자 정보
// button : Left = 0, Middle = 1, Right = 2
// state : Up = 0, Down = 1 (0 -> 1 출력)
// x, y : 마우스 클릭된 좌표

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN) // 누른 상태
		{
			pointX = x;
			pointY = y;
			printf("Mouse button is clicked! (%d, %d) \n", x, y);
		}

		// 화면 재생성 - 실시간 반영
		glutPostRedisplay();
	}
}

/* 마우스 입력으로 점 찍는 횟수 조건 */
//void click_point(int option) { }


/* GLUT - 키보드 입력 처리 */

// Callback 함수 keyboard
void keyboard(unsigned char key, int x, int y)
{
	printf("You pressed %c\n", key);
	// Left Triangle Alpha 값 조절
	switch (key)
	{
	// Alpha-Blending
	case 'w':
		Alpha += 5.0;
		printf("Alpha : %f\n", Alpha);
		break;

	case 's':
		Alpha -= 5.0;
		printf("Alpha : %f\n", Alpha);
		break;


	// Antialiasing ON/OFF
	case 'a':
		antiON = true;
		printf("Anti-Aliasing ON\n");
		antialiasing_function(antiON);
		break;

	case 'x':
		antiON = false;
		printf("Anti-Aliasing OFF\n");
		antialiasing_function(antiON);
		break;
	}

	// 화면 재생성 - 실시간 반영
	glutPostRedisplay();
}


/* GLUT - 메뉴 추가 */
// 메뉴 처리 함수
void sub_menu_function(int option)
{
	printf("Submenu %d has been selected\n", option);

	switch (option)
	{
	case 1 :
		draw_point();
		break;

	case 2:
		draw_line();
		break;

	case 3:
		draw_triangle();
		break;
		
	case 4:
		draw_polygon();
		break;
	}

	// 화면 재생성 - 실시간 반영
	glutPostRedisplay();
}


void main_menu_function(int option)
{
	printf("Main menu %d has been selected\n", option);

	switch (option)
	{
	case 123 :
		printf("Lets Alpha-Blending!\n");
		blend_function();
		break;

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
	glutCreateWindow("12181761_김현조_Lab04 GL");

	init(); // 사용자 초기화 함수


	/* Callback 함수 정의 */
	glutDisplayFunc(draw); // draw: 실제 그리기 함수
	glutMouseFunc(mouse); // mouse 함수 만들어주자
	glutKeyboardFunc(keyboard); // keyboard 함수 만들어주자


	/* Popup menu 생성 및 추가 */
	submenu1 = glutCreateMenu(sub_menu_function);
	glutAddMenuEntry("Point", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Triangle", 3);
	glutAddMenuEntry("Polygon", 4);

	glutCreateMenu(main_menu_function);

	glutAddSubMenu("Wanna Draw? Choose Mode", submenu1);
	glutAddMenuEntry("Wanna Alpha-Blending?", 123);
	glutAddMenuEntry("Clear", 831);
	glutAddMenuEntry("Quit", 999);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	/* Looping 시작 */
	glutMainLoop(); // 가장 마지막에 오도록...!

	return 0;
}