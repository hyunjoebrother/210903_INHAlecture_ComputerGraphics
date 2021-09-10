/* 개인 메모용 주석 */
// OpenGL (Graphics Library)
//	: 그래픽 및 이미지를 조작하는데 사용할 수 있는 많은 기능들 제공
//	: API 비슷한데 Khronos 가 개발한 유지 관리하는 설명서
//	: 컴퓨터 그래픽을 하드웨어 가속으로 처리rendering함과 동시에 여러 분야에 사용되도록
//	: State Machine : 각 상태가 정의되고 조건에 따라 상태간의 변이가 정의
//					: 모든 설정이 상태 변수로 저장, 유지됨

#include <gl/glut.h> //OpenGL을 사용하기 위해 윈도우 시스템과 연결하는 함수들
#include <stdio.h>

/* 초기화 및 Display Callback 함수 */

// 사용자 초기화 함수 
void init(void)
{
	/* 화면의 기본색으로 Blue 설정 */
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

	/* 화면 좌표 정보 설정 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// (0,0) ~ (500,500) 2차원 viewport 생성
	gluOrtho2D(0.0f, 500.0f, 0.0f, 500.0f);
}



/* Callback 함수 정의 */

// 점 그리기
void draw_point(void)
{
	/* 점 색상 붉은색 */
	glColor3f(1.0f, 0.0f, 0.0f);
	/* 점의 크기 (초기값은 1.0) */
	glPointSize(4.0f);

	glBegin(GL_POINTS);
	glVertex2i(5, 5);
	glVertex2i(200, 200);
	glVertex2i(450, 300);
	glEnd();
}

// 선 그리기
void draw_line(void)
{
	/* 선 색상 노란색 */
	glColor3f(1.0f, 1.0f, 0.0f);

	/* 선 속성 */
	glLineWidth(2.0f); // 선 두께
	glEnable(GL_LINE_STIPPLE); // 선 패턴 변경하기 위해 STATE ON 시킴
	glLineStipple(3, 0xAAAA); // 선 패턴

	glBegin(GL_LINES);
	glVertex2i(50, 50);
	glVertex2i(250, 450);
	glVertex2i(300, 450);
	glVertex2i(400, 100);
	glEnd();
}

// 면(Triangle) 그리기
void draw_triangle(void)
{
	/* 면 색상 노란색 */
	glColor3f(1.0f, 1.0f, 0.0f);


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
	glVertex2i(40, 10);
	glVertex2i(120, 70);
	glVertex2i(200, 150);
	glVertex2i(300, 150);
	glEnd();
}

// Display Callback 함수
void draw(void)
{
	/* 화면 깨끗하게 지우기 */
	glClear(GL_COLOR_BUFFER_BIT);


	glFlush();
}


/* GLUT - 메뉴 추가 */
// 메뉴 처리 함수
void sub_menu_function(int option)
{
	printf("Submenu %d has been selected\n", option);
	
	if (option == 1)
	{
		draw_point();
	}
	if (option == 2)
	{
		draw_line();
	}
	if (option == 3)
	{
		draw_triangle();
	}
	if (option == 4)
	{
		draw_polygon();
	}
	
}

void main_menu_function(int option)
{
	printf("Main menu %d has been selected\n", option);
	if (option == 999) {
		exit(0);
	}
}



int main(int argc, char** argv)
{
	int submenu1; // 메뉴 만들기

	/* Window 초기화 */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12181761_김현조_Lab03 GL");

	init(); // 사용자 초기화 함수

	/* Callback 함수 정의 */
	glutDisplayFunc(draw); // draw: 실제 그리기 함수
	//glutIdleFunc(idle); // idle 함수 만들어주자


	/* Popup menu 생성 및 추가 */
	submenu1 = glutCreateMenu(sub_menu_function);
	glutAddMenuEntry("Point", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Triangle", 3);
	glutAddMenuEntry("Polygon", 4);

	glutCreateMenu(main_menu_function);

	glutAddSubMenu("Wanna Draw?", submenu1);
	glutAddMenuEntry("Quit", 999);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	/* Looping 시작 */
	glutMainLoop(); // 가장 마지막에 오도록...!

	return 0;
}
