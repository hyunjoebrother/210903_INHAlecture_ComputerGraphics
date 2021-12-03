// Lect 11. Texture Mapping -  keyboard event

#include <gl/glut.h> //OpenGL�� ����ϱ� ���� ������ �ý��۰� �����ϴ� �Լ���
#include <stdio.h>
#include <iostream>
using namespace std;

#include <string.h> // Character ��� - strlen �Լ�


/* �ʱ�ȭ �� Display Callback �Լ� */
string* texName;

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


	// ���� ����ġ�� 0�� ���� ����ġ �ѱ�
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	// Texture Mapping
	glGenTextures(6, texName);


	// Material �Ӽ� �߰�
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	// Material Mode ����
	glEnable(GL_COLOR_MATERIAL);
}


/* Callback �Լ� ���� */

// Angle ��ȭ��Ű�� �Լ�
void idle(void)
{
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
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);


	draw_axis();


	/* �׸��� ����� �ٷ� �׷��� ī��� ����*/
	glFlush(); // Buffer�� ����� ��Ƶ� �Ŀ� �ѹ��� ����
	glutSwapBuffers(); // Double Buffering�� Buffer Swap
}

/*
void drawCube(void)
{
	draw_axis();
	//glRotatef(angle1, 0, 1, 0); // �������� 
	
}
*/

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
	glutCreateWindow("12181761_������_Lab11 GL");

	init(); // ����� �ʱ�ȭ �Լ�


	/* Callback �Լ� ���� */
	glutIdleFunc(idle); // ���� �Լ�
	glutDisplayFunc(draw); // draw: ���� �׸��� �Լ�
	glutReshapeFunc(resize); // WM_SIZE ó���ϴ� Callback �Լ� resize ����

	/* Looping ���� */
	glutMainLoop(); // ���� �������� ������...!

	return 0;
}