#include <gl/glut.h> //OpenGL�� ����ϱ� ���� ������ �ý��۰� �����ϴ� �Լ���
#include <stdio.h>
#include <iostream>
using namespace std;

#include <string.h> // Character ��� - strlen �Լ�
#include <math.h>

// �� ��� ��ǥ ��������
int pointX, pointY;

// ī�޶� ��ǥ -> ����ǥ�踦 ���� �������� 
double radius = 10;
double theta = 45, phi = 45;

double cam[3]; // ī�޶� ��ġ
double center[3] = { 0, 0, 0 }; // �ٶ󺸴� ��
double up[3] = { 0, 1, 0 }; // ī�޶��� Up vector

// ����ǥ�� ����
int x, y, z;

// ������ ������ ������ �ǹ��ϴ� �������� 
float EarthAngle1 = 0;
float EarthAngle2 = 0;

// ȭ���� ������ ������ �ǹ��ϴ� �������� 
float MarsAngle1 = 0;
float MarsAngle2 = 0;

// ���� ������ ������ �ǹ��ϴ� �������� 
float MoonAngle1 = 0;
float MoonAngle2 = 0;



/* �ʱ�ȭ �� Display Callback �Լ� */

// ����� �ʱ�ȭ �Լ� 
void init(void)
{
	printf("Init function ON\n");
	/* ȭ���� �⺻������ Black ���� */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// (0,0) ~ (500,500) 2���� viewport ����
	gluOrtho2D(0.0f, 500.0f, 0.0f, 500.0f);

	// Alpha-Blendign OFF
	glDisable(GL_BLEND);

	// ���� �ʱ�ȭ
	EarthAngle1 = 0;
	EarthAngle2 = 0;
	MarsAngle1 = 0;
	MarsAngle2 = 0;
	MoonAngle1 = 0;
	MoonAngle2 = 0;
}


/* Callback �Լ� ���� */

// Angle ��ȭ��Ű�� �Լ�
void idle(void)
{
	// ����
	EarthAngle1 = EarthAngle1 + 0.1;
	if (EarthAngle1 > 360) EarthAngle1 -= 360;
	EarthAngle2 = EarthAngle2 + 3;
	if (EarthAngle2 > 360) EarthAngle2 -= 360;

	// ȭ��
	MarsAngle1 = MarsAngle1 + 0.5;
	if (MarsAngle1 > 360) MarsAngle1 -= 360;
	MarsAngle2 = MarsAngle2 + 6;
	if (MarsAngle2 > 360) MarsAngle2 -= 360;

	// ��
	MoonAngle1 = MoonAngle1 + 0.1;
	if (MoonAngle1 > 360) MoonAngle1 -= 360;
	MoonAngle2 = MoonAngle2 + 0.5;
	if (MoonAngle2 > 360) MoonAngle2 -= 360;

	glutPostRedisplay();
}

// key�� ���� phi, theta �� ���� by Ű���� �Է�
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

	// ȭ�� ����� - �ǽð� �ݿ�
	glutPostRedisplay();
}


/* WM_SIZE�� �޽��� ó���� ���� callback �Լ� */
// ������ ���� �� ũ�� ��ȭ�� WM_SIZE �޽��� �߻�

// Viewport TF�� Projection TF ����
// -> resize �Լ� (WM_SIZE ó��)���� (= glutReshapeFunc)
void resize(int width, int height)
{
	// Viewport TF
	glViewport(0, 0, width, height); // ������ ũ�� ��ȭ�� viewport �缳��
	printf("Window Change! Resize function ON\n"); // �޽��� ��� Ȯ�ο�
	/* ȭ�� ��ǥ ���� ���� */
	glMatrixMode(GL_PROJECTION); // ���� ��ǥ�� ���� -> Projection TF �����ϵ���
	glLoadIdentity(); // ��ǥ�� �ʱ�ȭ

	// Projection TF
	gluPerspective(45, (float)width / (float)height, 1, 500);

	glMatrixMode(GL_MODELVIEW); // Projection ���� �� ȯ��
}

/* xyz ��ǥ�� �׸��� �Լ� */
void draw_axis(void)
{
	// ��ǥ�� �β�
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); // X���� red
	glVertex3f(0, 0, 0);
	glVertex3f(4, 0, 0);

	glColor3f(0, 1, 0); // Y���� green
	glVertex3f(0, 0, 0);
	glVertex3f(0, 4, 0);

	glColor3f(0, 0, 1); // Z���� blue
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 4);
	glEnd();
	// �β� �ٽ� ȯ��
	glLineWidth(1);
}

// Display Callback �Լ�
// draw �Լ� ȣ�� ���� resize() ȣ��� -> Viewport & Projection TF ���� ����
// -> Viewing TF ON
void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // ������ķ� 

	// Viewing TF (World -> Camera Coordinate)
	// cam, center, up -> Ű���� �Է��� ����
	// ���� ����
	// (10,10,10)���� (0,0,0) �ٶ󺸴� Viewing TF
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);

	// �¾� �׸���
	glColor3f(0.7, 0.3, 0);
	glutWireSphere(5,50,50); // �������� 2,3��° ���� �˷��ֽ�
	draw_axis(); // World ��ǥ��

	glPushMatrix(); // ���� Matrix�� Stack�� ����

	// ���� �׸���
	glRotatef(EarthAngle1, 0, 1, 0); // ����
	glTranslatef(5, 0, 0); // �߽����κ��� �̵�
	glRotatef(EarthAngle2, 0, 1, 0); // ����

	glColor3f(0, 0, 1);
	glutWireSphere(2,50,50);

	// Pop ���� �ٷ� �����ϴ� �༺�� �׸�
	// �� �׸���
	glRotatef(MoonAngle1, 0, 1, 0);
	glTranslatef(2, 0, 0);
	glRotatef(MoonAngle2, 0, 1, 0);

	glColor3f(0.3, 0.3, 0.3);
	glutWireSphere(0.5, 50, 50);

	glPopMatrix(); // �¾縸 �׷ȴ� ��ä�� ��� ����

	// ȭ�� �׸���
	glRotatef(MarsAngle1, 0, 1, 0);
	glTranslatef(8, 0, 0);
	glRotatef(MarsAngle2, 0, 1, 0);

	glColor3f(1, 0, 0);
	glutWireSphere(1.2, 50, 50);

	/* �׸��� ����� �ٷ� �׷��� ī��� ����*/
	glFlush(); // Buffer�� ����� ��Ƶ� �Ŀ� �ѹ��� ����
	glutSwapBuffers(); // Double Buffering�� Buffer Swap
}


/* �ѹ��� clear�ϴ� �Լ� -> �޴� ���� ������� */
void clear(void)
{
	/* ȭ�� �����ϰ� ����� */
	glClear(GL_COLOR_BUFFER_BIT);
}


/* GLUT - Ű���� �Է� ó�� */

// Callback �Լ� keyboard
void keyboard(unsigned char key, int x, int y)
{
	printf("You pressed %c\n", key);

	// ȭ�� ����� - �ǽð� �ݿ�
	glutPostRedisplay();
}


// ���콺 �� ��ȭ Callback �Լ�


/* GLUT - �޴� �߰� */

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

	// ȭ�� ����� - �ǽð� �ݿ�
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	int submenu1; // �޴� �����

	/* Window �ʱ�ȭ */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12181761_������_Lab06 GL");

	init(); // ����� �ʱ�ȭ �Լ�


	/* Callback �Լ� ���� */
	glutIdleFunc(idle); // ������ ���� ���� ���� �Լ�
	glutDisplayFunc(draw); // draw: ���� �׸��� �Լ�
	glutKeyboardFunc(keyboard); // keyboard �Լ� ���������

	glutReshapeFunc(resize); // WM_SIZE ó���ϴ� Callback �Լ� resize ����
	glutSpecialFunc(special_keyboard); // Ű���� �Է����� ���� ����

	glutCreateMenu(main_menu_function);

	glutAddMenuEntry("Clear", 831);
	glutAddMenuEntry("Quit", 999);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	/* Looping ���� */
	glutMainLoop(); // ���� �������� ������...!

	return 0;
}