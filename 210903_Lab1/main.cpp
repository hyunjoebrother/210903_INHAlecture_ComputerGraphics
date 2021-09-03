#include <gl/glut.h>
#include <stdio.h>

void init(void)
{
	/* 화면의 기본색으로 dark blue 설정 */
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
}

void draw(void)
{
	/* Teapot 1개 그리는 임시 루틴 */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireTeapot(0.5f);
	glFlush();
}




int main(int argc, char** argv)
{
	/* Window 초기화 */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12181761_김현조_first GL");
	init(); // 사용자 초기화 함수

	/* Callback 함수 정의 */
	glutDisplayFunc(draw);

	/* Looping 시작 */
	glutMainLoop();

	return 0;
}

