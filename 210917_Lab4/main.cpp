
#include <gl/glut.h> //OpenGL을 사용하기 위해 윈도우 시스템과 연결하는 함수들
#include <stdio.h>

// 점 찍기 좌표 전역변수
float pointX, pointY;


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
void draw_point()
{
	/* 점 색상 붉은색 */
	glColor3f(1.0f, 0.0f, 0.0f);
	/* 점의 크기 (초기값은 1.0) */
	glPointSize(5.0f);

	glBegin(GL_POINTS);
	glVertex2i(pointX, pointY);
	printf("point X, Y : (%d, %d)\n", pointX, pointY);
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
	glLineStipple(3, 0xAAAA); // 선 패턴 (fatctor 주기, pattern 패턴)

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
	// glClear(GL_COLOR_BUFFER_BIT); -> 이제 계속 유지됨

	/* 그리기 명령을 바로 그래픽 카드로 보냄*/
	glFlush(); // Buffer에 명령을 모아둔 후에 한번에 수행
}

/* Alpha-Blending */
void blend_function(void)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.0, 1.0, 1.0, 0.75);
}

/* Antialiasing */
void antialiasing_function(void)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
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
			printf("Mouse button is clicked! (%d, %d) \n", x, y);
			pointX = x;
			pointY = y;
		}
	}
}


/* GLUT - 키보드 입력 처리 */

// Callback 함수 keyboard
void keyboard(unsigned char key, int x, int y)
{
	printf("You pressed %c\n", key);

	if (key == 'b')
	{
		printf("You want Alpha-Blending\n");
		blend_function();
	}
	if (key == 'a')
	{
		printf("You want Antialiasing\n");
		antialiasing_function();
	}
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
}

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
	glutAddMenuEntry("Clear", 831);
	glutAddMenuEntry("Quit", 999);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	/* Looping 시작 */
	glutMainLoop(); // 가장 마지막에 오도록...!

	return 0;
}