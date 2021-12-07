// Lect 12. GLU Quadric Objects -  change parameter

#pragma once //� �ڵ�, ��������� �ٸ� �ڵ峪 ������� include �ɶ�, �ߺ��������
#define _CRT_SECURE_NO_WARNINGS // sprintf error

#include "bmpfuncs.h"
#include <GL/freeglut.h>
#include <gl/glut.h> //OpenGL�� ����ϱ� ���� ������ �ý��۰� �����ϴ� �Լ���
#include <stdio.h>
#include <iostream>
using namespace std;

#include <stdlib.h>
#include <string.h> // Character ��� - strlen �Լ�
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PI 3.14159265

/* �������� ���� */

volatile double theta = 45.0; // ĳ�̵� data�� ���� �ʰ� �׻� �޸𸮿� ����
volatile double phi = 45.0;
volatile int radius = 18;
volatile double upVector = cos(phi * PI / 180);

volatile double* angle = new double[7]();
volatile double rotateFactor = 1.0;
bool spinEnable = true;
bool display_axis = false;
bool set_materialProperty = true;
int current_width, current_height;

// ���� ���� ���
volatile unsigned char lightMode = 0;

// �þ� ����
volatile double eyex, eyey, eyez;

// Texture Mapping ����
GLuint texName[6]; // make Cube - 6��
GLuint texName2[3]; // make Cylinder - 3�� (��,�Ʒ�,��)
GLuint* texName3 = new GLuint();
GLuint tmp;

// Quadric Object ����
GLUquadricObj* qobj = gluNewQuadric();

// Object Selector
volatile unsigned char selector = 4;


/* Function List */
void init(void);
void resize(int, int);

void draw(void);
void draw_axis(void);
void draw_axis(double);
void draw_textureCube(void);
void draw_cylinder(void);
void draw_sphere(void);
void draw_string(void*, const char*, float, float, float, float, float);
void draw_text(void);

void mouse(int, int, int, int);
void mouseWheel(int but, int dir, int x, int y);
void keyboard(unsigned char, int, int);
void specialKeyboard(int, int, int);

void idle(void);

void popup_menu(void);
void sub_menu_function(int option);
void main_menu_function(int option);

void light_default(void);
void printInstruction(void);
void setDefault(void);

void cubeTextureMapping(void);
void cylinderTextureMapping(void);
void sphereTextureMapping(void);

void light_sel(void);

typedef unsigned char uchar;


int main(int argc, char** argv)
{
	/* Window �ʱ�ȭ */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("12181761_������_Lab12 GL");

	init(); // ����� �ʱ�ȭ �Լ�

	/* Callback �Լ� ���� */

	// CPU ���� �ð� ó��
	glutIdleFunc(idle);

	// quadric object �Ӽ� ����
	//gluQuadricDrawStyle(qobj, GLU_FILL);
	// Lect 12 - ���� change
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluQuadricNormals(qobj, GLU_SMOOTH);

	// draw callback - ���� �׸��� �Լ�
	glutDisplayFunc(draw);
	//glutReshapeFunc(resize); // WM_SIZE ó���ϴ� Callback �Լ� resize ����

	// Ű���� ���ͷ�Ʈ ó��
	glutKeyboardFunc(keyboard);

	// Ư�� Ű���� ����Ű ó��
	glutSpecialFunc(specialKeyboard);

	// ���콺 ó��
	glutMouseFunc(mouse);
	glutMouseWheelFunc(mouseWheel);

	// �޴� ó��
	popup_menu();

	/* Looping ���� */
	glutMainLoop(); // ���� �������� ������...!

	return 0;
}


/* �ʱ�ȭ �� Display Callback �Լ� */
// ����� �ʱ�ȭ �Լ� 
void init(void) 
{
	printf("Init function ON\n");

	// ȭ���� �⺻������ Black ����
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Default Object Color
	glColor3f(1.0f, 1.0f, 1.0f);

	// Resize Callback �Լ� ����
	glutReshapeFunc(resize);

	// Light Setting
	light_default();

	// ���۹� ���
	printInstruction();

	/* Texture Mapping ���� */
	gluQuadricTexture(qobj, GL_TRUE);

	cubeTextureMapping();
	cylinderTextureMapping();
	sphereTextureMapping();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	// polygon�� ���� ������ �����ϰ� texture�� ���´�
	glEnable(GL_TEXTURE_2D); // texture�� 2D
}

 
// Display Callback �Լ�
// draw �Լ� ȣ�� ���� resize() ȣ��� -> Viewport & Projection TF ���� ����
// -> Viewing TF ON
void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ��ü�� �յ� ���踦 ���� depth

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // ���� Ȱ��ȭ�� ����� ������ķ� �ʱ�ȭ
	glEnable(GL_DEPTH_TEST);

	eyex = radius * sin(theta * PI / 180) * cos(phi * PI / 180);
	eyey = radius * sin(phi * PI / 180);
	eyez = radius * cos(phi * PI / 180) * cos(phi * PI / 180);
	upVector = cos(phi * PI / 180);

	// Viewing TF (World -> Camera Coordinate)
	// ���� ����
	gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, upVector, 0);
	draw_text();
	glDisable(GL_LIGHT1);
	light_sel();

	// Teuxture Cube
	glPushMatrix();
	if (selector == 4)
		glTranslatef(2, 0, 2);
	if (selector == 1 || selector == 4)
		draw_textureCube();
	glPopMatrix();

	// Cider
	glPushMatrix();
	if (selector == 4)
		glTranslatef(2, 0, -2);
	if (selector == 2 || selector == 4)
		draw_cylinder();
	glPopMatrix();

	// Earth
	glPushMatrix();
	if (selector == 4)
		glTranslatef(-2.82, 0, 0);
	if (selector >= 3)
		draw_sphere();
	glPopMatrix();

	/* �׸��� ����� �ٷ� �׷��� ī��� ����*/
	//glFlush(); // Buffer�� ����� ��Ƶ� �Ŀ� �ѹ��� ����
	glutSwapBuffers(); // Double Buffering�� Buffer Swap
}


/* WM_SIZE�� �޽��� ó���� ���� callback �Լ� */
// ������ ���� �� ũ�� ��ȭ�� WM_SIZE �޽��� �߻�

// Viewport TF�� Projection TF ����
// -> resize �Լ� (WM_SIZE ó��)���� (= glutReshapeFunc)
void resize(int width, int height)
{
	glViewport(0, 0, width, height);
	current_width = width;
	current_height = height;
	printf("WIDTH: %d   HEIGHT : %d\n", width, height);

	// 3D ������ ���� projection ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, (float)width / (float)height, 1, 500);
	glMatrixMode(GL_MODELVIEW);
}


/* ��ǥ�� �׸��� �Լ� */
void draw_axis(void)
{
	if (!display_axis)
		goto out1;
	glLineWidth(1.5);

	glBegin(GL_LINES);
	glColor3f(0.5, 0, 0); // x�� red
	glVertex3f(0, 0, 0);
	glVertex3f(3, 0, 0);

	glColor3f(0, 0.5, 0); // y�� green
	glVertex3f(0, 0, 0);
	glVertex3f(0, 3, 0);

	glColor3f(0, 0, 0.5); // z�� blue
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 3);
	glEnd();

	glLineWidth(1);
out1:
	glutPostRedisplay(); // call draw() callback func
}


void draw_axis(double l)
{
	if (!display_axis)
		goto out2;
	glLineWidth(1.5);

	glBegin(GL_LINES);
	glColor3f(0.5, 0, 0); // x�� red
	glVertex3f(0, 0, 0);
	glVertex3f(l, 0, 0);

	glColor3f(0, 0.5, 0); // y�� green
	glVertex3f(0, 0, 0);
	glVertex3f(0, l, 0);

	glColor3f(0, 0, 0.5); // z�� blue
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, l);
	glEnd();

	glLineWidth(1);
out2:
	glutPostRedisplay(); // call draw() callback func
}



void idle(void)
{
	double rf = rotateFactor;

	// spin ���� ��ȭ
	if (!spinEnable) goto out3;
	angle[0] += 0.5 * rf;
	angle[1] += 0.05 * rf;
	angle[2] += 0.3 * rf;
	angle[3] += 0.1 * rf;
	angle[4] += 0.5 * rf;
	angle[5] += 0.2 * rf;
	angle[6] += 0.4 * rf;

	if (angle[1] > 360 || angle[0] > 360)
	{
		angle[0] -= 360;
		angle[1] -= 360;
	}
	if (angle[2] > 360) angle[2] -= 360;
	if (angle[3] > 360) angle[3] -= 360;
	if (angle[4] > 360) angle[4] -= 360;
	if (angle[5] > 360) angle[5] -= 360;
	if (angle[6] > 360) angle[6] -= 360;
out3:
	glutPostRedisplay(); // call draw() callback func.
}



/* Callback �Լ� ���� */

void mouse(int button, int state, int x, int y) {};

void mouseWheel(int but, int dir, int x, int y)
{
	if (dir > 0)
	{
		if (radius > 2)
		{
			radius--;
			printf("\'zoom in!\', radius: %d\n", radius);
		}
	}
	else {
		if (radius < 100) {
			radius++;
			printf("\'zoom out!\', radius: %d\n", radius);
		}
	}
	glutPostRedisplay();
}

void popup_menu(void)
{
	int submenu1 = glutCreateMenu(sub_menu_function);
	glutAddMenuEntry("cube", 1);
	glutAddMenuEntry("cylinder", 2);
	glutAddMenuEntry("sphere", 3);
	glutAddMenuEntry("all", 4);

	glutCreateMenu(main_menu_function);
	glutAddMenuEntry("Quit", 999);	
	glutAddMenuEntry("Clear", 900);

	glutAddSubMenu("View Mode", submenu1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void sub_menu_function(int option)
{
	switch (option) {
	case 1:
		lightMode = 0;
		selector = 1;
		break;
	case 2:
		lightMode = 0;
		selector = 2;
		break;
	case 3:
		lightMode = 0;
		selector = 3;
		break;
	case 4:
		lightMode = 0;
		selector = 4;
		break;
	default:
		break;
	}
	printf("object View Mode%d\n", selector);
	glutPostRedisplay();
}

void main_menu_function(int option)
{
	if (option == 999)
	{
		exit(0);
	}
	else if (option == 900)
	{
		setDefault();
	}
	glutPostRedisplay();
}

void light_default() 
{
	glClearColor(0, 0, 0, 1.0f);

	// Light0 ����
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.3f, 1.0f};
	GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat specularLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	// Material ����
	GLfloat ambientMaterial[] = { 0.2f, 0.2f, 0.3f, 1.0f };
	GLfloat diffuseMaterial[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specularMaterial[] = { 0.9f, 0.9f, 0.9f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, 60);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// global Light ����
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// Depth Test Enable
	glFrontFace(GL_CCW); // CW, CCW �ٲ㺸�鼭 front face �����غ���
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;

	case '0':
		lightMode = 0;
		printf("light%d at camera\n", lightMode);
		break;

	case '1':
		lightMode = 1;
		printf("light%d at cube\n", lightMode);
		break;

	case '2':
		lightMode = 2;
		printf("light%d at cylinder\n", lightMode);
		break;

	case '3':
		lightMode = 3;
		printf("light%d at sphere\n", lightMode);
		break;

	case 's':
		spinEnable = !spinEnable;
		if (spinEnable)
			printf("Spin Enabled!\n");
		else
			printf("Spin NOT Enabled!\n");
		break;

	case 'd':
		display_axis = !display_axis;
		if (display_axis)
			printf("Display axis!\n");
		else
			printf("NOT display axis!\n");
		break;

	case 'm':
		set_materialProperty = !set_materialProperty;
		if (set_materialProperty)
			printf("Enable set material Property!\n");
		else
			printf("NOT set material Property!\n");
		break;

	case '+':
		if (rotateFactor < 3.0) {
			rotateFactor += 0.1;
			printf("rotate velocity++ : %lf\n", rotateFactor);
		}
		break;

	case '-':
		if (rotateFactor > 0.2) {
			rotateFactor -= 0.1;
			printf("rotate velocity-- : %lf\n", rotateFactor);
		}
		break;

	default:
		printf("you pressed %c\n", key);
		break;
	}
	glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		theta -= 1;
		if (theta <= -360)
			theta = 0.0;
		break;

	case GLUT_KEY_RIGHT:
		theta += 1;
		if (theta >= 360)
			theta = 0.0;
		break;

	case GLUT_KEY_DOWN:
		phi -= 1;
		if (abs((int)phi) % 360 == 0)
			phi = 0.0;
		break;

	case GLUT_KEY_UP:
		phi += 1;
		if (abs((int)phi) % 360 == 0)
			phi = 0.0;
		break;

	case 5:
		printInstruction();
		setDefault();
		break;

	default:
		printf("%d is pressed\n", key);
		break;
	}
	glutPostRedisplay();
}

// ���۹� console ���
void printInstruction() {
	printf("\n----------keyboard navigation----------\n");
	printf("\'x\' : zoom in\n");
	printf("\'z\' : zoom out\n");
	printf("����Ű : camera ��ġ\n");
	printf("\'d\' : print/remove draw_axis\n");
	printf("\'+\' : rotate velocity up\n");
	printf("\'-\' : rotate velocity down\n");
	printf("0~4 : ���� ���� (object 3�� ��� ���� ����)\n");
	printf("F5 : ���ΰ�ħ\n\n");
}

void setDefault()
{
	radius = 18;
	selector = 4;
	lightMode = 0;
	theta = 45.0;
	phi = 45.0;
	rotateFactor = 1.0;

	spinEnable = true;
	display_axis = false;
	set_materialProperty = true;
}

void draw_string(void* font, const char* str, float x_position, float y_position, float red, float green, float blue)
{
	glPushAttrib(GL_LIGHTING_BIT);// Lect 12
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10); // ȭ�� ��ǥ
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(red, green, blue);   
	glRasterPos3f(x_position, y_position, 0);
	for (unsigned int i = 0; i < strlen(str); i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}

void draw_text()
{
	char* str = (char*)"Light (camera)";

	switch (lightMode) {
	case 0:
		str = (char*)"Light (camera)";
		break;
	case 1:
		str = (char*)"Light (cube)";
		break;
	case 2:
		str = (char*)"Light (cylinder)";
		break;
	case 3: 
		str = (char*)"Light (sphere)";
		break;
	default:
		break;
	}
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, str, -9.5, 8.7, 1, 1, 0);
}

void cubeTextureMapping() 
{
	glGenTextures(6, texName);
	int imgWidth, imgHeight, channels;
	
	for (int i = 0; i < 6; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texName[i]);
		char buf[100];
		sprintf(buf, "img/TexImage%d.bmp", i);
		buf[strlen(buf)] = 0;
		uchar* img = readImageData(buf, &imgWidth, &imgHeight, &channels);

		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
}

void draw_textureCube()
{
	glColor3f(1.0, 1.0, 1.0); // #fff�� set�ؾ��� texture ���� ����� ����

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// polygon�� ���� ����� texture ������ ���Ͽ� ����
	// texture�� ������ ǥ�鿡 ���� ȿ�� ���� ����

	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0, 0); // -x��
	glTexCoord2f(0, 0); glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(1, 0); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(0, 1); glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(1, 1); glVertex3f(-1.0, 1.0, 1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texName[1]);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0, 0); // x��
	glTexCoord2f(0, 0); glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(1, 0); glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(0, 1); glVertex3f(1.0, -1.0, -1.0);
	glTexCoord2f(1, 1); glVertex3f(1.0, 1.0, -1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texName[2]);
	glBegin(GL_QUADS);
	glNormal3f(0, -1.0, 0); // -y��
	glTexCoord2f(0, 0); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(1, 0); glVertex3f(1.0, -1.0, -1.0);
	glTexCoord2f(0, 1); glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(1, 1); glVertex3f(-1.0, -1.0, 1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texName[3]);
	glBegin(GL_QUADS);
	glNormal3f(0, 1.0, 0); // y��
	glTexCoord2f(0, 0); glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(1, 0); glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(0, 1); glVertex3f(1.0, 1.0, -1.0);
	glTexCoord2f(1, 1); glVertex3f(-1.0, 1.0, -1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texName[4]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1.0); // z��
	glTexCoord2f(0, 0); glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(1, 0); glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(0, 1); glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(1, 1); glVertex3f(1.0, -1.0, 1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texName[5]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1.0); // -z��
	glTexCoord2f(0, 0); glVertex3f(1.0, 1.0, -1.0);
	glTexCoord2f(1, 0); glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(0, 1); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(1, 1); glVertex3f(1.0, -1.0, -1.0);
	glEnd();

	draw_axis();
}

void draw_cylinder()
{
	glRotatef(-90, 1, 0, 0); // ���� �����
	glTranslatef(0, 0, -1); // �ٸ� object�� y������ ���߱�
	glColor3f(1.0, 1.0, 1.0);

	// TOP view
	glPushMatrix();
	glTranslatef(0, 0, 2);
	glBindTexture(GL_TEXTURE_2D, texName2[0]);
	gluPartialDisk(qobj, 0, 0.7, 30, 3, 0, 360);
	glPopMatrix();

	// MIDDLE view
	glBindTexture(GL_TEXTURE_2D, texName2[1]);
	gluCylinder(qobj, 0.7, 0.7, 2, 20, 20);

	// BOTTOM view
	glPushMatrix();
	glRotatef(180, 1, 0, 0); // normal vector ������ ����
	glBindTexture(GL_TEXTURE_2D, texName2[2]);
	gluPartialDisk(qobj, 0, 0.7, 30, 3, 0, 360);
	glPopMatrix();

	draw_axis();
}

void draw_sphere()
{
	glRotatef(-90, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);

	glBindTexture(GL_TEXTURE_2D, *texName3);
	gluSphere(qobj, 0.7, 100, 100);

	draw_axis();
}

void light_sel()
{
	if (lightMode == 0)
	{
		GLfloat light_position[] = { eyex, eyey, eyez, 1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}

	else if (lightMode == 1)
	{
		GLfloat light_position[] = { 3.5, 0, 3.5, 1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}

	else if (lightMode == 2)
	{
		GLfloat light_position[] = { 2, 0, -2, 1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}

	else if (lightMode == 3)
	{
		GLfloat light_position[] = { -2.8, 0, 0, 1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}
}

void cylinderTextureMapping()
{
	glGenTextures(3, texName2);
	glBindTexture(GL_TEXTURE_2D, texName2[0]);
	int width, height, channels;

	uchar* img = readImageData("img/CIDER_T.bmp", &width, &height, &channels);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, texName2[1]);
	img = readImageData("img/coke.bmp", &width, &height, &channels);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	glBindTexture(GL_TEXTURE_2D, texName2[2]);
	img = readImageData("img/CIDER_B.bmp", &width, &height, &channels);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}


void sphereTextureMapping()
{
	glGenTextures(1, texName3);
	//uchar* img;
	int width, height, channels;

	glBindTexture(GL_TEXTURE_2D, texName2[0]);


	uchar* img = readImageData("img/CIDER_T.bmp", &width, &height, &channels);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}



