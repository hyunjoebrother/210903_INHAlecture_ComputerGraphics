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
	/* ȭ���� �⺻������ dark blue ���� */
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
}

// Display Callback �Լ�
void draw(void)
{
	/* Teapot 1�� �׸��� �ӽ� ��ƾ */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f); // ��
	glutWireTeapot(0.5f); // ������ �ϳ� �׸�
	glFlush();
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
	printf("Mouse button is clicked! (%d, %d, %d, %d) \n",
		button, state, x, y);
}


/* GLUT - ���콺 ������ ó�� */

// Callback �Լ� motion
void motion(int x, int y)
{
	printf("Mouse is moving! (%d, %d) \n", x, y);
}


/* GLUT - Ű���� �Է� ó�� */

// Callback �Լ� keyboard
void keyboard(unsigned char key, int x, int y)
{
	printf("You pressed %c\n", key);
}


/* GLUT - Idle function ó�� */

// Callback �Լ� idle
/*void idle(void)
{
	// ��ü�� ������ animation ������ ����
	printf("%d second has elapsed since the system was started\n",
		GetTickCount() / 1000);
}
*/


/* GLUT - �޴� �߰� */
// �޴� ó�� �Լ�
void sub_menu_function(int option)
{
	printf("Submenu %d has been selected\n", option);
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
	glutCreateWindow("12181761_������_first GL");
	init(); // ����� �ʱ�ȭ �Լ�

	/* Callback �Լ� ���� */
	glutDisplayFunc(draw); // draw: ���� �׸��� �Լ�
	glutMouseFunc(mouse); // mouse �Լ� ���������
	glutMotionFunc(motion); // motion �Լ� ���������
	glutKeyboardFunc(keyboard); // keyboard �Լ� ���������
	//glutIdleFunc(idle); // idle �Լ� ���������

	/* Looping ���� */
	glutMainLoop();

	/* MENU ���� �� �߰� */
	submenu1 = glutCreateMenu(sub_menu_function);
	glutAddMenuEntry("Sub1", 1);
	glutAddMenuEntry("Sub2", 2);
	glutAddMenuEntry("Sub3", 3);

	glutCreateMenu(main_menu_function);
	glutAddMenuEntry("Quit", 999);
	glutAddMenuEntry("Go!", 11);
	glutAddSubMenu("Sub Menu", submenu1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	return 0;
}
