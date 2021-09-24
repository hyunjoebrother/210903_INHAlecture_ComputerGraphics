#include <gl/glut.h> //OpenGL을 사용하기 위해 윈도우 시스템과 연결하는 함수들
#include <stdio.h>

// Character 출력 - strlen 함수
#include <string.h>


// 점 찍기 좌표 전역변수
int pointX, pointY;

// 카메라 좌표를 위한 전역변수 
int radius, theta, phi;
int cam[3], center[3], up[3];


// 구좌표계 ON



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

/* WM_SIZE의 메시지 처리를 위한 callback 함수 */
// 윈도우 생성 및 크기 변화시 WM_SIZE 메시지 발생

void resize(int width, int height)
{
	// Viewport TF
	glViewport(0, 0, width, height); // 윈도우 크기 변화시 viewport 재설정
	printf("Window Change! Resize function ON\n"); // 메시지 출력 확인용
	/* 화면 좌표 정보 설정 */
	glMatrixMode(GL_PROJECTION); // 투상 좌표계 선언
	glLoadIdentity(); // 좌표계 초기화

	// Projection TF
	gluPerspective(45, (float)width / (float)height, 1, 500);

	glMatrixMode(GL_MODELVIEW);
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
void draw(void)
{
	printf("Draw function ON\n");
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Viewing TF
	// 카메라 위치, 카메라가 바라보는 점 위치, 카메라 위쪽의 방향 좌표 
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 0, 1); 
	// -> (10,10,10)에서 (0,0,0) 바라보는 Viewing TF

	glColor3f(1, 1, 0);
	glutWireTeapot(4);
	draw_axis();


	/* 그리기 명령을 바로 그래픽 카드로 보냄*/
	glFlush(); // Buffer에 명령을 모아둔 후에 한번에 수행
	glutSwapBuffers(); // Double Buffering시
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

// key에 따른 phi, theta 값 변경 by 키보드 입력
void special_keyboard(int key, int x, int y)
{
	if(key == GLUT_KEY_LEFT)
}

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

	glutReshapeFunc(resize); // WM_SIZE 처리하는 resize 함수

	glutCreateMenu(main_menu_function);

	glutAddMenuEntry("Clear", 831);
	glutAddMenuEntry("Quit", 999);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	/* Looping 시작 */
	glutMainLoop(); // 가장 마지막에 오도록...!

	return 0;
}