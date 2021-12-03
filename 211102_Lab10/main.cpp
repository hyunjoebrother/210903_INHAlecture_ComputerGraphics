// Lect 10. Material Properties -  선택된 물체가 emmisive 갖도록 keyboard event

#include <gl/glut.h> //OpenGL을 사용하기 위해 윈도우 시스템과 연결하는 함수들
#include <stdio.h>
#include <iostream>
using namespace std;

#include <string.h> // Character 출력 - strlen 함수

// 태양의 자전을 의미하는 전역변수 
float SunRot = 0;

// 지구의 자전과 공전을 의미하는 전역변수 
float EarthRot = 0;
float EarthOrb = 0;

// 화성의 자전과 공전을 의미하는 전역변수 
float MarsRot = 0;
float MarsOrb = 0;

// 달의 자전과 공전을 의미하는 전역변수 
float MoonRot = 0;
float MoonOrb = 0;

// 목성의 자전과 공전을 의미하는 전역변수 
float JupiterRot = 0;
float JupiterOrb = 0;


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

	// 각도 초기화
	EarthRot = 0;
	EarthOrb = 0;
	MarsRot = 0;
	MarsOrb = 0;
	MoonRot = 0;
	MoonOrb = 0;
	JupiterRot = 0;
	JupiterOrb = 0;

	// Solar System에 광원 추가
	// 0번 조명 관련 설정
	GLfloat light_ambient[] = { 0.4f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 3.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 2.0f, 1.0f, 2.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);


	// 태양의 위치에 조명 설정
	gluLookAt(15, 15, 15, 0, 0, 0, 0, 1, 0);
	GLfloat light_position[] = { 0.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);


	// 조명 스위치와 0번 조명 스위치 켜기
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	
	// Material 반사특성 설정 - 붉은색 반사되도록
	GLfloat ambient_Sun[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuse_Sun[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat specular_Sun[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_Sun);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_Sun);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_Sun);
	glMaterialf(GL_FRONT, GL_SHININESS, 64);


	// Emissive 속성 추가 - 조명 자체를 모델링하여 어두운 외면를 밝힘
	// emmisive light 설정
	GLfloat emission[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glutSolidSphere(3, 30, 30); // 태양 그리기
	emission[0] = 0.0f;
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);

	//// 여러 개의 material property 설정하기
	// Material 속성 추가
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	// Material Mode 설정
	glEnable(GL_COLOR_MATERIAL);
}


/* Callback 함수 정의 */

// Angle 변화시키는 함수
void idle(void)
{
	// 태양 자전
	SunRot = SunRot + .05;
	if (SunRot > 360) SunRot -= 360;

	// 지구 공전과 자전
	EarthOrb = EarthOrb + .01;
	if (EarthOrb > 360) EarthOrb -= 360;
	EarthRot = EarthRot + .03;
	if (EarthRot > 360) EarthRot -= 360;

	// 화성 공전과 자전
	MarsOrb = MarsOrb + 0.008;
	if (MarsOrb > 360) MarsOrb -= 360;
	MarsRot = MarsRot + .015;
	if (MarsRot > 360) MarsRot -= 360;

	// 달 공전과 자전
	MoonOrb = MoonOrb + 0.1;
	if (MoonOrb > 360) MoonOrb -= 360;
	MoonRot = MoonRot + 0.005;
	if (MoonRot > 360) MoonRot -= 360;

	// 목성 공전0.5과 자전 20
	JupiterOrb = JupiterOrb + 0.05;
	if (JupiterOrb > 360) JupiterOrb -= 360;
	JupiterRot = JupiterRot + 0.002;
	if (JupiterRot > 360) JupiterRot -= 360;

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
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // 현재 활성화된 행렬을 단위행렬로 초기화

	// Viewing TF (World -> Camera Coordinate)
	// 시점 고정
	// (20,20,20)에서 (0,0,0) 바라보는 Viewing TF
	gluLookAt(20, 20, 20, 0, 0, 0, 0, 1, 0);

	// 태양 그리기
	glRotatef(SunRot, 0, 1, 0); // 자전

	glColor3f(0.7, 0.3, 0);
	glutWireSphere(5, 50, 50); // 조교님이 2,3번째 인자 알려주심
	draw_axis(); // World 좌표계

	glPushMatrix(); // 현재 Matrix를 Stack에 저장

	// 지구 그리기
	glRotatef(EarthOrb, 0, 1, 0); // 공전
	glTranslatef(8, 0, 0); // 중심으로부터 이동
	glRotatef(EarthRot, 0, 1, 0); // 자전

	glColor3f(0, 0, 1);
	glutWireSphere(1.6, 50, 50);

	// Pop 없이 바로 공전하는 행성을 그림
	// 달 그리기
	glRotatef(MoonOrb, 0, 1, 0); // 공전
	glTranslatef(3, 0, 0);
	glRotatef(MoonRot, 0, 1, 0); // 자전

	glColor3f(0.3, 0.3, 0.3);
	glutWireSphere(0.5, 50, 50);

	glPopMatrix(); // 태양만 그렸던 상태로 행렬 복귀

	// 화성 그리기
	glRotatef(MarsOrb, 0, 1, 0); // 공전
	glTranslatef(15, 0, 0);
	glRotatef(MarsRot, 0, 1, 0); // 자전

	glColor3f(1, 0, 0);
	glutWireSphere(1.2, 50, 50);

	glPopMatrix(); // 태양만 그렸던 상태로 행렬 복귀

	// 목성 그리기
	glRotatef(JupiterOrb, 0, 1, 0); // 공전
	glTranslatef(25, 0, 0);
	glRotatef(JupiterRot, 0, 1, 0); // 자전

	glColor3f(0, 1, 0);
	glutWireSphere(3, 50, 50);

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


int main(int argc, char** argv)
{
	/* Window 초기화 */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12181761_김현조_Lab10 GL");

	init(); // 사용자 초기화 함수


	/* Callback 함수 정의 */
	glutIdleFunc(idle); // 자전과 공전 각도 조절 함수
	glutDisplayFunc(draw); // draw: 실제 그리기 함수
	glutReshapeFunc(resize); // WM_SIZE 처리하는 Callback 함수 resize 지정

	/* Looping 시작 */
	glutMainLoop(); // 가장 마지막에 오도록...!

	return 0;
}