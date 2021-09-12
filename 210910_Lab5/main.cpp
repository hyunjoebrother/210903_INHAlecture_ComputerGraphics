#include <gl/glut.h> //OpenGL�� ����ϱ� ���� ������ �ý��۰� �����ϴ� �Լ���
#include <stdio.h>


double spin; // ȸ�� ���� ���� �� �ʱ�ȭ


/* �ʱ�ȭ �� Display Callback �Լ� */

// ����� �ʱ�ȭ �Լ� 
void init(void)
{
	/* ȭ���� �⺻�� ���� */
	glClearColor(0.4f, 0.0f, 0.4f, 0.0f);

	/* ȭ�� ��ǥ ���� ���� */
	glMatrixMode(GL_PROJECTION); // ���� ��ǥ�� ����
	glLoadIdentity(); // ��ǥ�� �ʱ�ȭ

	// (0,0) ~ (500,500) 2���� viewport ����
	gluOrtho2D(0.0f, 500.0f, 0.0f, 500.0f);
}


/* Callback �Լ� ���� */

void idle(void) // �ִϸ��̼� ���� - ��ǻ���� ���޽ð��� �� ��
{
	spin = spin + 0.1; // ȸ�� ���� + 0.1
	if (spin > 360) {
		spin -= 360;
	}

	glutPostRedisplay();
}

// Triangle �׸���
void draw_triangle(void)
{
	/* �� ���� ����� */
	glColor3f(1.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	glVertex2i(50, 50);
	glVertex2i(150, 400);
	glVertex2i(350, 100);
	glEnd();
}

// Quad �׸���
void draw_quad(void)
{
	/* ���� */
	glColor3f(0, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glVertex2i(10, 100);
	glVertex2i(70, 170);
	glVertex2i(170, 200);
	glVertex2i(230, 170);
	glEnd();
}

// Polygon �׸���
void draw_polygon(void)
{
	/* ���� */
	glColor3f(1.0f, 0, 1.0f);

	glBegin(GL_POLYGON);
	glVertex2i(10, 10);
	glVertex2i(40, 10);
	glVertex2i(120, 120);
	glVertex2i(200, 150);
	glVertex2i(300, 150);
	glEnd();
}

// Display Callback �Լ�
void draw(void)
{
	/* ȭ�� �����ϰ� ����� */
	glClear(GL_COLOR_BUFFER_BIT);

	// draw_point();
	/* �߰� */
	glMatrixMode(GL_MODELVIEW); // Mode Ȱ��ȭ
	glLoadIdentity(); // Ȱ��ȭ�� Matrix�� ������ķ� �ʱ�ȭ

	// �������� ������ �����
	glTranslatef(250, 250, 0); // �����̵� (���� �ڸ��� ���ư�)
	glRotatef(spin, 0, 0, 1); // ȸ�� ���� spin���� ����
	glTranslatef(-250, -250, 0); // ȸ�� �߽� (250, 250)�� �������� �����̵�


	/* �׸��� ������ �ٷ� �׷��� ī��� ����*/
	glFlush(); // Buffer�� ������ ��Ƶ� �Ŀ� �ѹ��� ����

	/* �ִϸ��̼� ���� */
	glutSwapBuffers(); // Back buffer�� Front buffer�� swap
}


/* GLUT - �޴� �߰� */
// �޴� ó�� �Լ�

void main_menu_function(int option)
{
	printf("Main menu %d has been selected\n", option);
	if (option == 999) {
		exit(0);
	}

	if (option == 1)
	{
		draw_triangle();
	}
	if (option == 2)	
	{
		draw_quad();
	}
	if (option == 3)
	{
		draw_polygon();
	}

	// Spin ��� ����
	//if (option == 17)
	//{
	//	idle();
	//}
}



int main(int argc, char** argv)
{
	/* Window �ʱ�ȭ */
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // �ִϸ��̼� ����
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12181761_������_Lab05 GL");

	init(); // ����� �ʱ�ȭ �Լ�

	/* Popup menu ���� �� �߰� */
	glutCreateMenu(main_menu_function);

	glutAddMenuEntry("Triangle", 1);
	glutAddMenuEntry("Quad", 2);
	glutAddMenuEntry("Polygon", 3);
	// glutAddMenuEntry("Wanna Spin?",17); // Spin ��ư ����
	glutAddMenuEntry("Quit", 999);

	glutAttachMenu(GLUT_RIGHT_BUTTON);


	/* Callback �Լ� ���� */
	glutDisplayFunc(draw); // draw: ���� �׸��� �Լ�
	glutIdleFunc(idle); // �ִϸ��̼� ���� - ��ǻ���� ���޽ð��� ȣ��


	/* Looping ���� */
	glutMainLoop(); // ���� �������� ������...!

	return 0;
}
