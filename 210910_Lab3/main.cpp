/* ���� �޸�� �ּ� */
// OpenGL (Graphics Library)
//	: �׷��� �� �̹����� �����ϴµ� ����� �� �ִ� ���� ��ɵ� ����
//	: API ����ѵ� Khronos �� ������ ���� �����ϴ� ����
//	: ��ǻ�� �׷����� �ϵ���� �������� ó��rendering�԰� ���ÿ� ���� �о߿� ���ǵ���
//	: State Machine : �� ���°� ���ǵǰ� ���ǿ� ���� ���°��� ���̰� ����
//					: ��� ������ ���� ������ ����, ������

#include <gl/glut.h> //OpenGL�� ����ϱ� ���� ������ �ý��۰� �����ϴ� �Լ���
#include <stdio.h>

/* �ʱ�ȭ �� Display Callback �Լ� */

// ����� �ʱ�ȭ �Լ� 
void init(void)
{
	/* ȭ���� �⺻������ Blue ���� */
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

	/* ȭ�� ��ǥ ���� ���� */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// (0,0) ~ (500,500) 2���� viewport ����
	gluOrtho2D(0.0f, 500.0f, 0.0f, 500.0f);
}



/* Callback �Լ� ���� */

// �� �׸���
void draw_point(void)
{
	/* �� ���� ������ */
	glColor3f(1.0f, 0.0f, 0.0f);
	/* ���� ũ�� (�ʱⰪ�� 1.0) */
	glPointSize(4.0f);

	glBegin(GL_POINTS);
	glVertex2i(5, 5);
	glVertex2i(200, 200);
	glVertex2i(450, 300);
	glEnd();
}

// �� �׸���
void draw_line(void)
{
	/* �� ���� ����� */
	glColor3f(1.0f, 1.0f, 0.0f);

	/* �� �Ӽ� */
	glLineWidth(2.0f); // �� �β�
	glEnable(GL_LINE_STIPPLE); // �� ���� �����ϱ� ���� STATE ON ��Ŵ
	glLineStipple(3, 0xAAAA); // �� ����

	glBegin(GL_LINES);
	glVertex2i(50, 50);
	glVertex2i(250, 450);
	glVertex2i(300, 450);
	glVertex2i(400, 100);
	glEnd();
}

// ��(Triangle) �׸���
void draw_triangle(void)
{
	/* �� ���� ����� */
	glColor3f(1.0f, 1.0f, 0.0f);


	glBegin(GL_TRIANGLES);
	glVertex2i(50, 50);
	glVertex2i(250, 450);
	glVertex2i(400, 100);
	glEnd();
}


// Polygon �׸���
void draw_polygon(void)
{
	/* ���� */
	glColor3f(0.3f, 0.2f, 1.0f);

	glBegin(GL_POLYGON);
	glVertex2i(10, 10);
	glVertex2i(40, 10);
	glVertex2i(120, 70);
	glVertex2i(200, 150);
	glVertex2i(300, 150);
	glEnd();
}

// Display Callback �Լ�
void draw(void)
{
	/* ȭ�� �����ϰ� ����� */
	glClear(GL_COLOR_BUFFER_BIT);


	glFlush();
}


/* GLUT - �޴� �߰� */
// �޴� ó�� �Լ�
void sub_menu_function(int option)
{
	printf("Submenu %d has been selected\n", option);
	
	if (option == 1)
	{
		draw_point();
	}
	if (option == 2)
	{
		draw_line();
	}
	if (option == 3)
	{
		draw_triangle();
	}
	if (option == 4)
	{
		draw_polygon();
	}
	
}

void main_menu_function(int option)
{
	printf("Main menu %d has been selected\n", option);
	if (option == 999) {
		exit(0);
	}
}



int main(int argc, char** argv)
{
	int submenu1; // �޴� �����

	/* Window �ʱ�ȭ */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12181761_������_Lab03 GL");

	init(); // ����� �ʱ�ȭ �Լ�

	/* Callback �Լ� ���� */
	glutDisplayFunc(draw); // draw: ���� �׸��� �Լ�
	//glutIdleFunc(idle); // idle �Լ� ���������


	/* Popup menu ���� �� �߰� */
	submenu1 = glutCreateMenu(sub_menu_function);
	glutAddMenuEntry("Point", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Triangle", 3);
	glutAddMenuEntry("Polygon", 4);

	glutCreateMenu(main_menu_function);

	glutAddSubMenu("Wanna Draw?", submenu1);
	glutAddMenuEntry("Quit", 999);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	/* Looping ���� */
	glutMainLoop(); // ���� �������� ������...!

	return 0;
}
