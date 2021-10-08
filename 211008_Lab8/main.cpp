#include <gl/glut.h> //OpenGL�� ����ϱ� ���� ������ �ý��۰� �����ϴ� �Լ���
#include <stdio.h>
#include <iostream>
using namespace std;


// �������� ����
double m_RotateAngle;



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

	// Ȱ��ȭ
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	glClearDepth(1.0f);


	// Shaded Rendering �ʱ�ȭ
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
	glFrontFace(GL_CW); // Teapot�� CW�� ���ǵ�
	glEnable(GL_DEPTH_TEST);
}


/* Callback �Լ� ���� */

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

void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	/* �߰� */
	glMatrixMode(GL_MODELVIEW); // Mode Ȱ��ȭ
	glLoadIdentity(); // Ȱ��ȭ�� Matrix�� ������ķ� �ʱ�ȭ

	// (20,20,20)���� (0,0,0) �ٶ󺸴� Viewing TF
	gluLookAt(20, 20, 20, 0, 0, 0, 0, 1, 0);

	glColor3f(1.0f, 0, 0);
	glutWireTeapot(0.5f);

	draw_axis();

	/* �׸��� ����� �ٷ� �׷��� ī��� ����*/
	glFlush(); // Buffer�� ����� ��Ƶ� �Ŀ� �ѹ��� ����

	/* �ִϸ��̼� ���� */
	glutSwapBuffers(); // Back buffer�� Front buffer�� swap
}


/* �ѹ��� clear�ϴ� �Լ� -> �޴� ���� ������� */
void clear(void)
{
	/* ȭ�� �����ϰ� ����� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


int main(int argc, char** argv)
{
	/* Window �ʱ�ȭ */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12181761_������_Lab08 GL");

	init(); // ����� �ʱ�ȭ �Լ�


	/* Callback �Լ� ���� */
	//glutIdleFunc(idle); // �Լ�
	glutDisplayFunc(draw); // draw: ���� �׸��� �Լ�
	glutReshapeFunc(resize); // WM_SIZE ó���ϴ� Callback �Լ� resize ����

	/* Looping ���� */
	glutMainLoop(); // ���� �������� ������...!

	return 0;
}