#include <gl/glut.h>
#include <stdio.h>

void init(void)
{
	/* ȭ���� �⺻������ dark blue ���� */
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
}

void draw(void)
{
	/* Teapot 1�� �׸��� �ӽ� ��ƾ */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireTeapot(0.5f);
	glFlush();
}




int main(int argc, char** argv)
{
	/* Window �ʱ�ȭ */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12181761_������_first GL");
	init(); // ����� �ʱ�ȭ �Լ�

	/* Callback �Լ� ���� */
	glutDisplayFunc(draw);

	/* Looping ���� */
	glutMainLoop();

	return 0;
}

