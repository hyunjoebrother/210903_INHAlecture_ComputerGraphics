/* 개인 메모용 주석 */
// OpenGL (Graphics Library)
//	: 그래픽 및 이미지를 조작하는데 사용할 수 있는 많은 기능들 제공
//	: API 비슷한데 Khronos 가 개발한 유지 관리하는 설명서
//	: 컴퓨터 그래픽을 하드웨어 가속으로 처리rendering함과 동시에 여러 분야에 사용되도록
//	: State Machine : 각 상태가 정의되고 조건에 따라 상태간의 변이가 정의
//					: 모든 설정이 상태 변수로 저장, 유지됨

#include <gl/glut.h> //OpenGL을 사용하기 위해 윈도우 시스템과 연결하는 함수들
#include <stdio.h>

/* 초기화 및 Display Callback 함수 */

// 사용자 초기화 함수 
void init(void)
{
	/* 화면의 기본색으로 dark blue 설정 */
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
}

// Display Callback 함수
void draw(void)
{
	/* Teapot 1개 그리는 임시 루틴 */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f); // 색
	glutWireTeapot(0.5f); // 주전자 하나 그림
	glFlush();
}


/* GLUT - 마우스 입력 처리 */

// Callback 함수 mouse
// 
// 인자 정보
// button : Left = 0, Middle = 1, Right = 2
// state : Up = 0, Down = 1 (0 -> 1 출력)
// x, y : 마우스 클릭된 좌표

void mouse(int button, int state, int x, int y)
{
	printf("Mouse button is clicked! (%d, %d, %d, %d) \n",
		button, state, x, y);
}


/* GLUT - 마우스 움직임 처리 */

// Callback 함수 motion
void motion(int x, int y)
{
	printf("Mouse is moving! (%d, %d) \n", x, y);
}


/* GLUT - 키보드 입력 처리 */

// Callback 함수 keyboard
void keyboard(unsigned char key, int x, int y)
{
	printf("You pressed %c\n", key);
}


/* GLUT - Idle function 처리 */

// Callback 함수 idle
/*void idle(void)
{
	// 물체의 움직임 animation 구현에 쓰임
	printf("%d second has elapsed since the system was started\n",
		GetTickCount() / 1000);
}
*/


/* GLUT - 메뉴 추가 */
// 메뉴 처리 함수
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
	int submenu1; // 메뉴 만들기

	/* Window 초기화 */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12181761_김현조_first GL");
	init(); // 사용자 초기화 함수

	/* Callback 함수 정의 */
	glutDisplayFunc(draw); // draw: 실제 그리기 함수
	glutMouseFunc(mouse); // mouse 함수 만들어주자
	glutMotionFunc(motion); // motion 함수 만들어주자
	glutKeyboardFunc(keyboard); // keyboard 함수 만들어주자
	//glutIdleFunc(idle); // idle 함수 만들어주자

	/* Looping 시작 */
	glutMainLoop();

	/* MENU 생성 및 추가 */
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
