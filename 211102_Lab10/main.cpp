// Lect 10. Material Properties -  ���õ� ��ü�� emmisive ������ keyboard event

#include <gl/glut.h> //OpenGL�� ����ϱ� ���� ������ �ý��۰� �����ϴ� �Լ���
#include <stdio.h>
#include <iostream>
using namespace std;

#include <string.h> // Character ��� - strlen �Լ�

// �¾��� ������ �ǹ��ϴ� �������� 
float SunRot = 0;

// ������ ������ ������ �ǹ��ϴ� �������� 
float EarthRot = 0;
float EarthOrb = 0;

// ȭ���� ������ ������ �ǹ��ϴ� �������� 
float MarsRot = 0;
float MarsOrb = 0;

// ���� ������ ������ �ǹ��ϴ� �������� 
float MoonRot = 0;
float MoonOrb = 0;

// ���� ������ ������ �ǹ��ϴ� �������� 
float JupiterRot = 0;
float JupiterOrb = 0;


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
	EarthRot = 0;
	EarthOrb = 0;
	MarsRot = 0;
	MarsOrb = 0;
	MoonRot = 0;
	MoonOrb = 0;
	JupiterRot = 0;
	JupiterOrb = 0;

	// Solar System�� ���� �߰�
	// 0�� ���� ���� ����
	GLfloat light_ambient[] = { 0.4f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 3.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 2.0f, 1.0f, 2.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);


	// �¾��� ��ġ�� ���� ����
	gluLookAt(15, 15, 15, 0, 0, 0, 0, 1, 0);
	GLfloat light_position[] = { 0.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);


	// ���� ����ġ�� 0�� ���� ����ġ �ѱ�
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	
	// Material �ݻ�Ư�� ���� - ������ �ݻ�ǵ���
	GLfloat ambient_Sun[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuse_Sun[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat specular_Sun[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_Sun);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_Sun);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_Sun);
	glMaterialf(GL_FRONT, GL_SHININESS, 64);


	// Emissive �Ӽ� �߰� - ���� ��ü�� �𵨸��Ͽ� ��ο� �ܸ鸦 ����
	// emmisive light ����
	GLfloat emission[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glutSolidSphere(3, 30, 30); // �¾� �׸���
	emission[0] = 0.0f;
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);

	//// ���� ���� material property �����ϱ�
	// Material �Ӽ� �߰�
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	// Material Mode ����
	glEnable(GL_COLOR_MATERIAL);
}


/* Callback �Լ� ���� */

// Angle ��ȭ��Ű�� �Լ�
void idle(void)
{
	// �¾� ����
	SunRot = SunRot + .05;
	if (SunRot > 360) SunRot -= 360;

	// ���� ������ ����
	EarthOrb = EarthOrb + .01;
	if (EarthOrb > 360) EarthOrb -= 360;
	EarthRot = EarthRot + .03;
	if (EarthRot > 360) EarthRot -= 360;

	// ȭ�� ������ ����
	MarsOrb = MarsOrb + 0.008;
	if (MarsOrb > 360) MarsOrb -= 360;
	MarsRot = MarsRot + .015;
	if (MarsRot > 360) MarsRot -= 360;

	// �� ������ ����
	MoonOrb = MoonOrb + 0.1;
	if (MoonOrb > 360) MoonOrb -= 360;
	MoonRot = MoonRot + 0.005;
	if (MoonRot > 360) MoonRot -= 360;

	// �� ����0.5�� ���� 20
	JupiterOrb = JupiterOrb + 0.05;
	if (JupiterOrb > 360) JupiterOrb -= 360;
	JupiterRot = JupiterRot + 0.002;
	if (JupiterRot > 360) JupiterRot -= 360;

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
	glLoadIdentity(); // ���� Ȱ��ȭ�� ����� ������ķ� �ʱ�ȭ

	// Viewing TF (World -> Camera Coordinate)
	// ���� ����
	// (20,20,20)���� (0,0,0) �ٶ󺸴� Viewing TF
	gluLookAt(20, 20, 20, 0, 0, 0, 0, 1, 0);

	// �¾� �׸���
	glRotatef(SunRot, 0, 1, 0); // ����

	glColor3f(0.7, 0.3, 0);
	glutWireSphere(5, 50, 50); // �������� 2,3��° ���� �˷��ֽ�
	draw_axis(); // World ��ǥ��

	glPushMatrix(); // ���� Matrix�� Stack�� ����

	// ���� �׸���
	glRotatef(EarthOrb, 0, 1, 0); // ����
	glTranslatef(8, 0, 0); // �߽����κ��� �̵�
	glRotatef(EarthRot, 0, 1, 0); // ����

	glColor3f(0, 0, 1);
	glutWireSphere(1.6, 50, 50);

	// Pop ���� �ٷ� �����ϴ� �༺�� �׸�
	// �� �׸���
	glRotatef(MoonOrb, 0, 1, 0); // ����
	glTranslatef(3, 0, 0);
	glRotatef(MoonRot, 0, 1, 0); // ����

	glColor3f(0.3, 0.3, 0.3);
	glutWireSphere(0.5, 50, 50);

	glPopMatrix(); // �¾縸 �׷ȴ� ���·� ��� ����

	// ȭ�� �׸���
	glRotatef(MarsOrb, 0, 1, 0); // ����
	glTranslatef(15, 0, 0);
	glRotatef(MarsRot, 0, 1, 0); // ����

	glColor3f(1, 0, 0);
	glutWireSphere(1.2, 50, 50);

	glPopMatrix(); // �¾縸 �׷ȴ� ���·� ��� ����

	// �� �׸���
	glRotatef(JupiterOrb, 0, 1, 0); // ����
	glTranslatef(25, 0, 0);
	glRotatef(JupiterRot, 0, 1, 0); // ����

	glColor3f(0, 1, 0);
	glutWireSphere(3, 50, 50);

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


int main(int argc, char** argv)
{
	/* Window �ʱ�ȭ */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12181761_������_Lab10 GL");

	init(); // ����� �ʱ�ȭ �Լ�


	/* Callback �Լ� ���� */
	glutIdleFunc(idle); // ������ ���� ���� ���� �Լ�
	glutDisplayFunc(draw); // draw: ���� �׸��� �Լ�
	glutReshapeFunc(resize); // WM_SIZE ó���ϴ� Callback �Լ� resize ����

	/* Looping ���� */
	glutMainLoop(); // ���� �������� ������...!

	return 0;
}