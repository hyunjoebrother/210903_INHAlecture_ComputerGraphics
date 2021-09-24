#include <gl/glut.h> //OpenGL�� ����ϱ� ���� ������ �ý��۰� �����ϴ� �Լ���
#include <stdio.h>

// Character ��� - strlen �Լ�
#include <string.h>


// �� ��� ��ǥ ��������
int pointX, pointY;

// ī�޶� ��ǥ�� ���� �������� 
int radius, theta, phi;
int cam[3], center[3], up[3];


// ����ǥ�� ON



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
}



/* Callback �Լ� ���� */

/* WM_SIZE�� �޽��� ó���� ���� callback �Լ� */
// ������ ���� �� ũ�� ��ȭ�� WM_SIZE �޽��� �߻�

void resize(int width, int height)
{
	// Viewport TF
	glViewport(0, 0, width, height); // ������ ũ�� ��ȭ�� viewport �缳��
	printf("Window Change! Resize function ON\n"); // �޽��� ��� Ȯ�ο�
	/* ȭ�� ��ǥ ���� ���� */
	glMatrixMode(GL_PROJECTION); // ���� ��ǥ�� ����
	glLoadIdentity(); // ��ǥ�� �ʱ�ȭ

	// Projection TF
	gluPerspective(45, (float)width / (float)height, 1, 500);

	glMatrixMode(GL_MODELVIEW);
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
	printf("Draw function ON\n");
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Viewing TF
	// ī�޶� ��ġ, ī�޶� �ٶ󺸴� �� ��ġ, ī�޶� ������ ���� ��ǥ 
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 0, 1); 
	// -> (10,10,10)���� (0,0,0) �ٶ󺸴� Viewing TF

	glColor3f(1, 1, 0);
	glutWireTeapot(4);
	draw_axis();


	/* �׸��� ����� �ٷ� �׷��� ī��� ����*/
	glFlush(); // Buffer�� ����� ��Ƶ� �Ŀ� �ѹ��� ����
	glutSwapBuffers(); // Double Buffering��
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

// key�� ���� phi, theta �� ���� by Ű���� �Է�
void special_keyboard(int key, int x, int y)
{
	if(key == GLUT_KEY_LEFT)
}

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
	glutDisplayFunc(draw); // draw: ���� �׸��� �Լ�
	glutKeyboardFunc(keyboard); // keyboard �Լ� ���������

	glutReshapeFunc(resize); // WM_SIZE ó���ϴ� resize �Լ�

	glutCreateMenu(main_menu_function);

	glutAddMenuEntry("Clear", 831);
	glutAddMenuEntry("Quit", 999);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	/* Looping ���� */
	glutMainLoop(); // ���� �������� ������...!

	return 0;
}