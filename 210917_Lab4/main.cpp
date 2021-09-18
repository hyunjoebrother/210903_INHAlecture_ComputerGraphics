
#include <gl/glut.h> //OpenGL�� ����ϱ� ���� ������ �ý��۰� �����ϴ� �Լ���
#include <stdio.h>

// �� ��� ��ǥ ��������
float pointX, pointY;


/* �ʱ�ȭ �� Display Callback �Լ� */

// ����� �ʱ�ȭ �Լ� 
void init(void)
{
	/* ȭ���� �⺻������ Black ���� */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	/* ȭ�� ��ǥ ���� ���� */
	glMatrixMode(GL_PROJECTION); // ���� ��ǥ�� ����
	glLoadIdentity(); // ��ǥ�� �ʱ�ȭ

	// (0,0) ~ (500,500) 2���� viewport ����
	gluOrtho2D(0.0f, 500.0f, 0.0f, 500.0f);

	// Alpha-Blendign OFF
	glDisable(GL_BLEND);
}



/* Callback �Լ� ���� */

// �� �׸���
void draw_point()
{
	/* �� ���� ������ */
	glColor3f(1.0f, 0.0f, 0.0f);
	/* ���� ũ�� (�ʱⰪ�� 1.0) */
	glPointSize(5.0f);

	glBegin(GL_POINTS);
	glVertex2i(pointX, pointY);
	printf("point X, Y : (%d, %d)\n", pointX, pointY);
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
	glLineStipple(3, 0xAAAA); // �� ���� (fatctor �ֱ�, pattern ����)

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
	// glClear(GL_COLOR_BUFFER_BIT); -> ���� ��� ������

	/* �׸��� ����� �ٷ� �׷��� ī��� ����*/
	glFlush(); // Buffer�� ����� ��Ƶ� �Ŀ� �ѹ��� ����
}

/* Alpha-Blending */
void blend_function(void)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.0, 1.0, 1.0, 0.75);
}

/* Antialiasing */
void antialiasing_function(void)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
}

/* �ѹ��� clear�ϴ� �Լ� -> �޴� ���� ������� */
void clear(void)
{
	/* ȭ�� �����ϰ� ����� */
	glClear(GL_COLOR_BUFFER_BIT);
}


/* GLUT - ���콺 �Է� ó�� */

// Callback �Լ� mouse
// 
// ���� ����
// button : Left = 0, Middle = 1, Right = 2
// state : Up = 0, Down = 1 (0 -> 1 ���)
// x, y : ���콺 Ŭ���� ��ǥ

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN) // ���� ����
		{
			printf("Mouse button is clicked! (%d, %d) \n", x, y);
			pointX = x;
			pointY = y;
		}
	}
}


/* GLUT - Ű���� �Է� ó�� */

// Callback �Լ� keyboard
void keyboard(unsigned char key, int x, int y)
{
	printf("You pressed %c\n", key);

	if (key == 'b')
	{
		printf("You want Alpha-Blending\n");
		blend_function();
	}
	if (key == 'a')
	{
		printf("You want Antialiasing\n");
		antialiasing_function();
	}
}


/* GLUT - �޴� �߰� */
// �޴� ó�� �Լ�
void sub_menu_function(int option)
{
	printf("Submenu %d has been selected\n", option);

	switch (option)
	{
	case 1 :
		draw_point();
		break;

	case 2:
		draw_line();
		break;

	case 3:
		draw_triangle();
		break;
		
	case 4:
		draw_polygon();
		break;
	}
}

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
}


int main(int argc, char** argv)
{
	int submenu1; // �޴� �����

	/* Window �ʱ�ȭ */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12181761_������_Lab04 GL");

	init(); // ����� �ʱ�ȭ �Լ�


	/* Callback �Լ� ���� */
	glutDisplayFunc(draw); // draw: ���� �׸��� �Լ�
	glutMouseFunc(mouse); // mouse �Լ� ���������
	glutKeyboardFunc(keyboard); // keyboard �Լ� ���������


	/* Popup menu ���� �� �߰� */
	submenu1 = glutCreateMenu(sub_menu_function);
	glutAddMenuEntry("Point", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Triangle", 3);
	glutAddMenuEntry("Polygon", 4);

	glutCreateMenu(main_menu_function);

	glutAddSubMenu("Wanna Draw? Choose Mode", submenu1);
	glutAddMenuEntry("Clear", 831);
	glutAddMenuEntry("Quit", 999);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	/* Looping ���� */
	glutMainLoop(); // ���� �������� ������...!

	return 0;
}