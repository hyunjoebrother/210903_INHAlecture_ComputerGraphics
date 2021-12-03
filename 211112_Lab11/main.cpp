// Lect 11. Texture Mapping -  keyboard event

#include <gl/glut.h> //OpenGL을 사용하기 위해 윈도우 시스템과 연결하는 함수들
#include <stdio.h>
#include <iostream>
using namespace std;

#include <string.h> // Character 출력 - strlen 함수


/* 초기화 및 Display Callback 함수 */
string* texName;

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


	// 조명 스위치와 0번 조명 스위치 켜기
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	// Texture Mapping
	glGenTextures(6, texName);


	// Material 속성 추가
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	// Material Mode 설정
	glEnable(GL_COLOR_MATERIAL);
}


/* Callback 함수 정의 */

// Angle 변화시키는 함수
void idle(void)
{
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
	// Texture Binding
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glBegin(GL_QUADS);
	// Left
	glTexCoord2f(0, 0); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1, 0); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1, 1); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0, 1); glVertex3f(-1.0f, 1.0f, 1.0f);

	// Right
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Bottom
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Top
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	// Near
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);


	// Far
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glEnd();
}


// Display Callback 함수
// draw 함수 호출 전에 resize() 호출됨 -> Viewport & Projection TF 끝난 상태
// -> Viewing TF ON
void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // 현재 활성화된 행렬을 단위행렬로 초기화

	// Viewing TF (World -> Camera Coordinate)
	// 시점 고정
	// (20,20,20)에서 (0,0,0) 바라보는 Viewing TF
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);


	draw_axis();


	/* 그리기 명령을 바로 그래픽 카드로 보냄*/
	glFlush(); // Buffer에 명령을 모아둔 후에 한번에 수행
	glutSwapBuffers(); // Double Buffering시 Buffer Swap
}

/*
void drawCube(void)
{
	draw_axis();
	//glRotatef(angle1, 0, 1, 0); // 전역변수 
	
}
*/

/* 한번에 clear하는 함수 -> 메뉴 따로 만들어줌 */
void clear(void)
{
	/* 화면 깨끗하게 지우기 */
	glClear(GL_COLOR_BUFFER_BIT);
}


int main(int argc, char** argv)
{
	/* Window 초기화 */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12181761_김현조_Lab11 GL");

	init(); // 사용자 초기화 함수


	/* Callback 함수 정의 */
	glutIdleFunc(idle); // 조절 함수
	glutDisplayFunc(draw); // draw: 실제 그리기 함수
	glutReshapeFunc(resize); // WM_SIZE 처리하는 Callback 함수 resize 지정

	/* Looping 시작 */
	glutMainLoop(); // 가장 마지막에 오도록...!

	return 0;
}