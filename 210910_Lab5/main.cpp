#include <gl/glut.h> //OpenGL을 사용하기 위해 윈도우 시스템과 연결하는 함수들
#include <stdio.h>


double spin; // 회전 각도 선언 및 초기화
int type; // draw 함수에 올릴 새로운 전역변수


/* 초기화 및 Display Callback 함수 */

// 사용자 초기화 함수 
void init(void)
{
	/* 화면의 기본색 설정 */
	glClearColor(0.4f, 0.0f, 0.5f, 0.0f);

	/* 화면 좌표 정보 설정 */
	glMatrixMode(GL_PROJECTION); // 투상 좌표계 선언
	glLoadIdentity(); // 좌표계 초기화

	// (0,0) ~ (500,500) 2차원 viewport 생성
	gluOrtho2D(0.0f, 500.0f, 0.0f, 500.0f);
}


/* Callback 함수 정의 */

void idle(void) // 애니메이션 구현 - 컴퓨터의 유휴시간에 할 일
{
	spin = spin + 0.1; // 회전 각도 + 0.1
	if (spin > 360) {
		spin -= 360;
	}

	glutPostRedisplay();
}

// Triangle 그리기
void draw_triangle(void)
{
	/* 면 색상 노란색 */
	glColor3f(1.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	glVertex2i(50, 50);
	glVertex2i(150, 400);
	glVertex2i(350, 100);
	glEnd();
}

// Quad 그리기
void draw_quad(void)
{
	/* 색상 */
	glColor3f(0, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glVertex2i(10, 100);
	glVertex2i(70, 170);
	glVertex2i(170, 200);
	glVertex2i(230, 170);
	glEnd();
}

// Polygon 그리기
void draw_polygon(void)
{
	/* 색상 */
	glColor3f(1.0f, 0, 1.0f);

	glBegin(GL_POLYGON);
	glVertex2i(10, 10);
	glVertex2i(40, 10);
	glVertex2i(120, 120);
	glVertex2i(200, 150);
	glVertex2i(300, 150);
	glEnd();
}

// Display Callback 함수
void draw(void)
{
	/* 화면 깨끗하게 지우기 */
	glClear(GL_COLOR_BUFFER_BIT);


	/* 추가 */
	glMatrixMode(GL_MODELVIEW); // Mode 활성화
	glLoadIdentity(); // 활성화된 Matrix를 단위행렬로 초기화

	// 역순으로 명령이 실행됨
	glTranslatef(250, 250, 0); // 평행이동 (원래 자리로 돌아감)
	glRotatef(spin, 0, 0, 1); // 회전 각도 spin으로 설정
	glTranslatef(-250, -250, 0); // 회전 중심 (250, 250)을 원점으로 평행이동


	// main menu에서 받은 새로운 전역변수 type -> 화면 출력
	if (type == 1)
	{
		draw_triangle();
	}
	if (type == 2)
	{
		draw_quad();
	}
	if (type == 3)
	{
		draw_polygon();
	}


	/* 그리기 명령을 바로 그래픽 카드로 보냄*/
	glFlush(); // Buffer에 명령을 모아둔 후에 한번에 수행

	/* 애니메이션 구현 */
	glutSwapBuffers(); // Back buffer을 Front buffer로 swap
}


/* GLUT - 메뉴 추가 */
// 메뉴 처리 함수

void main_menu_function(int option)
{
	printf("Main menu %d has been selected\n", option);
	if (option == 999) {
		exit(0);
	}

	if (option == 1)
	{
		draw_triangle();
		type = 1;
	}
	if (option == 2)
	{
		draw_quad();
		type = 2;
	}
	if (option == 3)
	{
		draw_polygon();
		type = 3;
	}

	// Spin 기능 구현
	//if (option == 17)
	//{
	//	idle();
	//}
}



int main(int argc, char** argv)
{
	/* Window 초기화 */
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 애니메이션 구현
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12181761_김현조_Lab05 GL");

	init(); // 사용자 초기화 함수

	/* Popup menu 생성 및 추가 */
	glutCreateMenu(main_menu_function);

	glutAddMenuEntry("Triangle", 1);
	glutAddMenuEntry("Quad", 2);
	glutAddMenuEntry("Polygon", 3);
	// glutAddMenuEntry("Wanna Spin?",17); // Spin 버튼 구현
	glutAddMenuEntry("Quit", 999);

	glutAttachMenu(GLUT_RIGHT_BUTTON);


	/* Callback 함수 정의 */
	glutDisplayFunc(draw); // draw: 실제 그리기 함수
	glutIdleFunc(idle); // 애니메이션 구현 - 컴퓨터의 유휴시간에 호출


	/* Looping 시작 */
	glutMainLoop(); // 가장 마지막에 오도록...!

	return 0;
}
