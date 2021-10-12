#include <gl/glut.h> //OpenGL을 사용하기 위해 윈도우 시스템과 연결하는 함수들
#include <stdio.h>
#include <iostream>
using namespace std;


// 전역변수 선언
double m_RotateAngle = 0;


/* 초기화 및 Display Callback 함수 */

// 사용자 초기화 함수 
void init(void)
{
	printf("Init function ON\n");
	/* 화면의 기본색으로 Black 설정 */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// (0,0) ~ (500,500) 2차원 viewport 생성
	gluOrtho2D(0.0f, 500.0f, 0.0f, 500.0f);

	// Alpha-Blending OFF
	glDisable(GL_BLEND);


	// Polygon Back-Face Culling 활성화
	//glEnable(GL_CULL_FACE); // 한쪽면 표시를 유효하도록
	glCullFace(GL_BACK); // 뒷면을 그리지 않도록

	// Teapot 내부 WireFrame으로 표현
	glPolygonMode(GL_BACK, GL_LINE);


	m_RotateAngle = 0;

	// Shaded Rendering 초기화
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat specularLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat specularMaterial[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
	glMateriali(GL_FRONT, GL_SHININESS, 20);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	// Depth-Test Enable
	glClearDepth(1.0f); // Buffering Clearing 값

	glFrontFace(GL_CW); // Teapot은 CW로 정의됨
	glEnable(GL_DEPTH_TEST); // Depth Buffer 활성화
}


/* Callback 함수 정의 */

/* Rotate Angle 변화시키는 함수 */
void idle(void)
{
	m_RotateAngle = m_RotateAngle + .1;
	if (m_RotateAngle > 360)
		m_RotateAngle -= 360;

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


	//printf("Draw_Axis function ON\n");
}


// Display Callback 함수

void draw(void)
{
	// Scene drawing 직전에 color buffer + depth buffer clearing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* 추가 */
	glMatrixMode(GL_MODELVIEW); // Mode 활성화
	glLoadIdentity(); // 활성화된 Matrix를 단위행렬로 초기화

	// (10,10,10)에서 (0,0,0) 바라보는 Viewing TF
	gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);

	// Step 2. Additional Clipping Plane
	// 시간에 따라 y축 중심으로 회전하도록 하고 평면의 음의 영역을 clipping out한다
	glPushMatrix();

	glRotatef(m_RotateAngle, 0, 1, 0); // idle 함수에서 값 증가시키기
	GLdouble eq[4] = { 1.0, 0.0, 0.0, 0.0 };
	glClipPlane(GL_CLIP_PLANE0, eq);
	glEnable(GL_CLIP_PLANE0);

	glPopMatrix();

	// Teapot Drawing
	glColor3f(1.0f, 0, 0);
	glutSolidTeapot(0.5f); // Wire이 아닌 면으로 출력

	draw_axis();

	/* 그리기 명령을 바로 그래픽 카드로 보냄*/
	glFlush(); // Buffer에 명령을 모아둔 후에 한번에 수행

	/* 애니메이션 구현 */
	glutSwapBuffers(); // Back buffer을 Front buffer로 swap

	//printf("Draw function ON\n");
}


int main(int argc, char** argv)
{
	/* Window 초기화 */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Depth Buffer 사용 선언
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12181761_김현조_Lab08 GL");

	init(); // 사용자 초기화 함수


	/* Callback 함수 정의 */
	glutIdleFunc(idle); // 함수
	glutDisplayFunc(draw); // draw: 실제 그리기 함수
	glutReshapeFunc(resize); // WM_SIZE 처리하는 Callback 함수 resize 지정

	/* Looping 시작 */
	glutMainLoop(); // 가장 마지막에 오도록...!

	return 0;
}