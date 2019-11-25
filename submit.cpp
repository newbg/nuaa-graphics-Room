/*****************************************************************************
		FILE : submit.c (Assignment 1)
		NOTE : you have to implement functions in this file
*****************************************************************************/
/*****************************************************************************
		Student Information
		Student ID:
		Student Name:
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

void init(void);
void display(void);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void idle(void);

void setLight0(bool flag);
void setLight1(bool flag);

/* Global Variables */
GLfloat light_pos0[] = { 0, 25, -10, 1 };
GLfloat light_dir0[] = { 0, -1, 0 };
GLfloat light_cutoff0 = 45;
GLfloat light_amb0[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light_dif0[] = { 0.4, 0.4, 0.4, 1.0 };
GLfloat light_spc0[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat light_pos1[] = { 10, 10, 10, 1 };
GLfloat light_dir1[] = { 0, -1, -1 };
GLfloat light_cutoff1 = 20;
GLfloat light_amb1[] = { 0.1, 0.3, 0.1, 1.0 };
GLfloat light_dif1[] = { 0.1, 0.7, 0.1, 1.0 };
GLfloat light_spc1[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat light_pos2[] = { 0, 10, -10, 1 };
GLfloat light_dir2[] = { 0, -1, 0 };
GLfloat light_cutoff2 = 50;
GLfloat light_amb2[] = { 0.2, 0.15, 0, 1.0 };
GLfloat light_dif2[] = { 0.8, 0.75, 0, 1.0 };
GLfloat light_spc2[] = { 1.0, 1.0, 0, 1.0 };

GLfloat no_mat[] = { 0.00,0.00,0.00,1.0 };
GLfloat mat_ambinet[] = { 0.3,0.2,0.5,1.0 };
GLfloat mat_diffuse[] = { 0.8,0.2,0.5,1.0 };
GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 };
GLfloat high_shininess[] = { 1.0 };

GLfloat no_mat1[] = { 0.0,0.0,0.0,1.0 };
GLfloat mat_ambinet1[] = { 0.7,0.2,0.75,1.0 };
GLfloat mat_diffuse1[] = { 0.3,0.62,0.8,1.0 };
GLfloat mat_specular1[] = { 0.10,1.0,1.0,1.0 };
GLfloat high_shininess1[] = { 10.0 };

GLfloat no_mat2[] = { 0.00,0.20,0.40,1.0 };
GLfloat mat_ambinet2[] = { 0.3,0.62,0.25,1.0 };
GLfloat mat_diffuse2[] = { 0.3,0.8,0.2,1.0 };
GLfloat mat_specular2[] = { 0.280,0.280,0.20,1.0 };
GLfloat high_shininess2[] = { 0.50 };
GLfloat
FanAngle = 0,
TeapotPos = -96,
PostPos = -100,
HolePos = -100,
StoolPos = 50,
Sphereangle = 0,
SphereScale = 6;
GLfloat catinet = 150, circle_ro = 0, circle_ro1 = 0, windows_tr = 5, lightsize = 6, donut_size = 7;
float t_x = 0.0;
enum { stoolstop, stoolmove } Stool;
float angle = 0.0;
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
GLUquadricObj* obj;
bool aRoomLight = true;
bool Stool_dir = true;
bool aAndroid = false;
int aAndroidAng = 0;
bool aAndroidLight = false;
bool aAndroidJumpUp = true;
float aAndroidJumpDis = 0;
float fscale = 1.0;
bool aCeilingLight = false;
bool b_Animation = FALSE;
bool aMice = false;
bool b_direction = TRUE;
bool aMiceEyeBigger = true;
float aMiceEyeScale = 1.0;
float aMiceTrans[] = { 0,0,0 };
const GLfloat PI = 3.141592653f;
enum { fan_turnoff, fan_turnon } Fan;
// 当前时间，时 分 秒
float h = 0.0f;
float m = 0.0f;
float s = 0.0f;
int option = 0;
int  i;
enum { postempty, post_up, post_down } Post;
void setLight0(bool flag)
{
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir0);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, light_cutoff0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_spc0);

	if (flag)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);
}

void setLight1(bool flag)
{
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_dir1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, light_cutoff1);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_amb1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_dif1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_spc1);

	if (flag)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);
}

void setLight2(bool flag)
{
	glLightfv(GL_LIGHT2, GL_POSITION, light_pos2);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_dir2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, light_cutoff2);

	glLightfv(GL_LIGHT2, GL_AMBIENT, light_amb2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_dif2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_spc2);

	if (flag)
		glEnable(GL_LIGHT2);
	else
		glDisable(GL_LIGHT2);
}

void DrawStar(GLfloat px, GLfloat py, GLfloat vx, GLfloat vy, int flag)//位置以及五角星一个外顶点坐标
{
	glBegin(GL_TRIANGLE_FAN);//绘制一系列三角形
	GLfloat vtx[12], vty[12];//1个中心点，10个顶点，顶点的第一个和最后一个相同，其中奇数下标是外顶点，偶数下标是内顶点
	vtx[0] = px;//已知的中心点
	vty[0] = py;
	vtx[1] = vx;//已知的第一个外顶点
	vty[1] = vy;
	GLfloat length1 = sqrt((px - vx) * (px - vx) + (py - vy) * (py - vy));//中心点到外顶点的长度
	GLfloat length2 = length1 * sin(0.1 * PI) / sin(126.0 / 180 * PI);
	//计算剩下的所有顶点
	double init = atan((vty[1] - vty[0]) / (vtx[1] - vtx[0]));//顶点与中心点连线与x轴的角度
	if (flag)
		init = init - PI;
	for (int i = 2; i < 12; i++) {
		init = init - 0.2 * PI;
		if (i % 2 == 0) {//内顶点
			vtx[i] = length2 * cos(init) + vtx[0];
			vty[i] = length2 * sin(init) + vty[0];
		}
		else {//外顶点
			vtx[i] = length1 * cos(init) + vtx[0];
			vty[i] = length1 * sin(init) + vty[0];
		}
	}
	for (int i = 0; i < 12; i++) //设置顶点
		glVertex3f(vtx[i], vty[i], 0.5);
	glEnd();
}

void DrawFan()
{
	obj = gluNewQuadric();
	gluQuadricNormals(obj, GLU_SMOOTH);
	gluQuadricTexture(obj, GL_TRUE);
	glPushMatrix();

	glTranslatef(0, 6, 0);
	glRotatef(FanAngle, 0, 1, 0);

	//风扇支架

	glPushMatrix();
	glTranslatef(0, 1, 0);
	glScalef(0.1, 0.1, 0.1);
	glColor3ub(255, 228, 225);

	glRotatef(-90, 1, 0, 0);
	gluCylinder(obj, 2, 2, 15, 30, 30);
	glPopMatrix();

	//风扇圆
	glTranslatef(0, 0.5, 0);
	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);

	glRotatef(-90, 1, 0, 0);
	glColor3ub(139, 139, 131);
	gluCylinder(obj, 6, 6, 3, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);
	glTranslatef(0, 0, 0);
	glRotatef(-90, 1, 0, 0);
	glColor3ub(240, 255, 240);
	gluDisk(obj, 0, 6, 30, 30);

	glTranslatef(0, 0, 0);
	glColor3ub(205, 205, 193);
	gluDisk(obj, 0, 6, 30, 30);
	glPopMatrix();

	//扇叶
	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);
	glColor3ub(240, 255, 255);
	glTranslatef(0, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, 0);
	glVertex3f(40, 0, -5);
	glVertex3f(40, 0, 5);

	glVertex3f(0, 0, 0);
	glVertex3f(-40, 0, -5);
	glVertex3f(-40, 0, 5);

	glVertex3f(0, 0, 0);
	glVertex3f(-5, 0, -40);
	glVertex3f(5, 0, -40);

	glVertex3f(0, 0, 0);
	glVertex3f(-5, 0, 40);
	glVertex3f(5, 0, 40);
	glEnd();
	glPopMatrix();

	glPopMatrix();
	//glFlush();
	//glutSwapBuffers();//交换缓冲区


}

void DrawStool()
{
	obj = gluNewQuadric();
	gluQuadricNormals(obj, GLU_SMOOTH);
	//gluQuadricTexture(obj, GL_TRUE);
	glPushMatrix();

	glColor3ub(238, 197, 145);
	glScalef(0.15, 0.15, 0.15);
	glTranslatef(StoolPos - 10, -60, -60);

	//凳子腿
	glPushMatrix();
	glTranslatef(-5, 0, -5);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(obj, 1, 1, 13, 31, 31);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 0, -5);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(obj, 1, 1, 13, 31, 31);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, 0, 5);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(obj, 1, 1, 13, 31, 31);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 0, 5);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(obj, 1, 1, 13, 31, 31);
	glPopMatrix();


	//凳子面
	glPushMatrix();
	glTranslatef(0, 10, 0);
	glRotatef(-90, 1, 0, 0);
	glColor3ub(205, 170, 125);
	gluCylinder(obj, 8.5, 8.5, 3, 30, 30);
	glPopMatrix();

	glTranslated(0, 13, 0);
	glRotatef(-90, 1, 0, 0);
	gluDisk(obj, 0, 8.6, 20, 20);

	glPopMatrix();
}

void Drawtable()
{
	//glPushMatrix();

	//glTranslatef(7, 1, 0);
	//glScalef(0.3, 0.3, 0.3);
	//木板
	//glColor3ub(139, 115, 85);

	//glScalef(4, 0.3, 5);
	//glutSolidCube(1);
	//glPopMatrix();

	//铁链


	//铁链
	//glPushMatrix();
	////glScalef(0.1, 0.1, 0.1);
	//glColor3ub(0, 0, 0);
	//glTranslatef(10, 3, 10);
	//gluPartialDisk(obj, 2, 3.5, 32, 32, -90, 180);
	//glPopMatrix();

	//glPushMatrix();
	//glScalef(0.3, 0.3, 0.3);	
	////glTranslatef(85, -60, -78);
	//for (int i = 1; i <= 7; i++)
	//{
	//	glTranslatef(10, -1, 0);
	//	gluDisk(obj, 1, 1.5, 32, 32);
	//}
	//glPopMatrix();

	//glPushMatrix();
	//glScalef(0.3, 0.3, 0.3);
	////glTranslatef(85, -60, -78);
	////glTranslatef(0, 0, -45);
	//gluPartialDisk(obj, 2, 3.5, 32, 32, -90, 180);

	//for (int i = 1; i <= 7; i++)
	//{
	//	glTranslatef(10, -1, 10);
	//	gluDisk(obj, 1, 1.5, 32, 32);
	//}
	//glPopMatrix();

	//石柜
	glPushMatrix();
	glColor3ub(139, 139, 122);
	glTranslatef(-4, 1.5, 5);
	glScalef(2, 0.08, 8);
	glutSolidCube(1);

	glTranslatef(0, -30, 0);
	glutSolidCube(1);

	glPopMatrix();

}



void init(void) // All Setup For OpenGL Goes Here
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void display(void) // Here's Where We Do All The Drawing
{
	// TODO:
	// Place light source here
	setLight0(aRoomLight);
	setLight1(aAndroidLight);
	setLight2(aCeilingLight);

	// TODO:
	// Draw walls and objects here
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat matBlack[] = { 0, 0, 0, 1 };
	GLfloat matWhite[] = { 1, 1, 1, 1 };
	GLfloat matPink[] = { 1, 0.8, 0.2, 1 };
	GLfloat matBrown[] = { 1, 0.6, 0.3, 1 };
	GLfloat matYellowGreen[] = { 0.5, 1, 0.5, 1 };
	GLfloat matRed[] = { 1, 0, 0, 1 };
	GLfloat matGreen[] = { 0, 1, 0, 1 };
	GLfloat matBlue[] = { 0, 0, 1, 1 };
	GLfloat matYellow[] = { 1, 1, 0, 1 };
	GLfloat matShininess[] = { 50 };

	//Room x:10 to -10; y:10 to -10; z:0 to -20
	glColor3f(1, 1, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matWhite);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matWhite);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glBegin(GL_QUADS);					//back wall
	glVertex3f(10, 10, -20);
	glVertex3f(-10, 10, -20);
	glVertex3f(-10, -10, -20);
	glVertex3f(10, -10, -20);
	glEnd();

	glColor3f(0.6, 1, 1);  // 顶部
	glMaterialfv(GL_FRONT, GL_AMBIENT, matRed);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matRed);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glBegin(GL_QUADS);
	glVertex3f(10, 10, -20);
	glVertex3f(10, 10, 0);
	glVertex3f(-10, 10, 0);
	glVertex3f(-10, 10, -20);
	glEnd();

	glColor3f(0.56, 0.93, 0.56);  // 左边
	glMaterialfv(GL_FRONT, GL_AMBIENT, matGreen);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matGreen);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glBegin(GL_QUADS);
	glVertex3f(-10, 10, -20);
	glVertex3f(-10, 10, 0);
	glVertex3f(-10, -10, 0);
	glVertex3f(-10, -10, -20);
	glEnd();

	glColor3f(0.8, 0.88, 1);  // 底面
	glMaterialfv(GL_FRONT, GL_AMBIENT, matBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matBlue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glBegin(GL_QUADS);
	glVertex3f(-10, -10, -20);
	glVertex3f(-10, -10, 0);
	glVertex3f(10, -10, 0);
	glVertex3f(10, -10, -20);
	glEnd();

	glColor3f(0.56,0.93,0.56);  //右墙
	glMaterialfv(GL_FRONT, GL_AMBIENT, matYellow);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matYellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glBegin(GL_QUADS);
	glVertex3f(10, -10, -20);
	glVertex3f(10, -10, 0);
	glVertex3f(10, 10, 0);
	glVertex3f(10, 10, -20);
	glEnd();

	//demo
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glScalef(2, 2, 2);
	glTranslated(-2.0f, -2, -7.0f);
	glTranslated(t_x, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambinet1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess1);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat1);
	glutSolidSphere(0.5, 30, 30);		/* draw a sphere in GLUT	*/
	glPopMatrix();

	/*Draw Calender START*/
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(5, 3.5, 0.5);
	glVertex3f(5, 3.5, 3.5);
	glVertex3f(5, 2, 3.5);
	glVertex3f(5, 2, 0.5);

	glEnd();




	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0.8);
	glVertex3f(5, 2, 0.5);
	glVertex3f(5, 2, 3.5);
	glVertex3f(5, 0, 3.5);
	glVertex3f(5, 0, 0.5);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0,0,0);
	//for (i = 2; i >= 0.1; i -= 0.2) {
	//	glVertex3f(5, i, 3.5);
	//	glVertex3f(5, i, 0.5);
	//}
	glVertex3f(5, 1.6, 3.5);
	glVertex3f(5, 1.6, 0.5);
	glVertex3f(5, 1.2, 3.5);
	glVertex3f(5, 1.2, 0.5);
	glVertex3f(5, 0.8, 3.5);
	glVertex3f(5, 0.8, 0.5);
	glVertex3f(5, 0.4, 3.5);
	glVertex3f(5, 0.4, 0.5);

	//for (i = 3.5; i >= 0.5; i -= 0.3) {
	//	glVertex3f(5, 2, i);
	//	glVertex3f(5, 0, i);
	//}
	glVertex3f(5, 2, 0.8);
	glVertex3f(5, 0, 0.8);
	glVertex3f(5, 2, 1.3);
	glVertex3f(5, 0, 1.3);
	glVertex3f(5, 2, 1.8);
	glVertex3f(5, 0, 1.8);
	glVertex3f(5, 2, 2.3);
	glVertex3f(5, 0, 2.3);
	glVertex3f(5, 2, 2.8);
	glVertex3f(5, 0, 2.8);
	glVertex3f(5, 2, 3.3);
	glVertex3f(5, 0, 3.3);

	glEnd();



	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(0.5f, 0.5f, 0.f);
	glVertex3f(5, 0.2, 3.1);
	glVertex3f(5, 0.2, 1);
	glVertex3f(5, 0.65, 2.6);
	glVertex3f(5, 1.5, 2);
	glVertex3f(5, 1.1, 1.5);
	glVertex3f(5, 1.8, 1);
	glVertex3f(5, 1.5, 2.6);
	glVertex3f(5, 1.1, 2);


	glEnd();

	//glBegin(GL_TRIANGLES);
	//glColor3f(0.5f, 0.5f, 0.5f);
	//glVertex3f(5, 80.0, -199.f);
	//glVertex3f(5, 90.0, -199.f);
	//glVertex3f(5, 82.0, -199.f);
	//glEnd();

	//glBegin(GL_TRIANGLES);
	//glColor3f(0.5f, 0.5f, 0.5f);
	//glVertex3f(-45.0, 80.0, -199.f);
	//glVertex3f(-25.0, 90.0, -199.f);
	//glVertex3f(-23.0, 82.0, -199.f);
	//glEnd();

	//glBegin(GL_POLYGON);
	//glColor3f(0.45f, 0.45f, 0.45f);
	//glVertex3f(5, 2.8, 1);
	//glVertex3f(5, 3, 2);
	//glVertex3f(5, 2.8, 1);
	//glVertex3f(5, 3, 2);
	//glEnd();
	/*Draw Calender END*/

	// 窗户
	/*windows*/
	int m = 360;
	glPushMatrix();
	glColor4f(0, 0, 1, 1);
	glTranslatef(2.2, 4, -2);
	glRotatef(270.f, 0.f, 0.f, 30.f);
	glScalef(0.2, 6.0f, 1.f);
	glutSolidCube(0.8f);
	glPopMatrix();

	glPushMatrix();
	glColor4f(0, 0, 1, 1);
	glTranslatef(2.2, 0, -2);
	glRotatef(90.f, 0.f, 0.f, 30.f);
	glScalef(0.2, 6.0f, 1.f);
	glutSolidCube(0.8f);
	glPopMatrix();

	//glPushMatrix();
	//glBegin(GL_TRIANGLE_FAN);
	//glTranslatef(2, -2, -2);
	////glScalef(50, 5, 5);
	//glColor4f(1,0,1,0.1);
	//glVertex3f(0.5, 3.4, 0);
	//glVertex3f(0.5, windows_tr - 4.9, 0);
	//glVertex3f(3.5, windows_tr - 4.9, 0);
	//glVertex3f(3.5, 3.4, 0);
	//glEnd();
	//glPopMatrix();

	glPushMatrix();
	glBegin(GL_LINES);
	glTranslatef(2.2, 0, -2);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(0.5, 3.4, 0);
	glVertex3f(0.5, windows_tr - 4.9, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(1.5, 3.4, 0);
	glVertex3f(1.5, windows_tr - 4.9, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(2.5, 3.4, 0);
	glVertex3f(2.5, windows_tr - 4.9, 0);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(3.5, 3.4, 0);
	glVertex3f(3.5, windows_tr - 4.9, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);
	glTranslatef(2, -2, -2);
	//glScalef(50, 5, 5);
	glColor3f(0.9, 0.9, 1);
	glVertex3f(0.5, 3.4, 0);
	glVertex3f(0.5, windows_tr - 4.9, 0);
	glVertex3f(3.5, windows_tr - 4.9, 0);
	glVertex3f(3.5, 3.4, 0);
	glEnd();
	glPopMatrix();

	// ============================
	glPushMatrix();
	glTranslatef(2.5, 2.5, 0);
	//glScalef(0.005, 0.005, 0.005);
	glRotated(circle_ro1, 0, 1, 0);
	glBegin(GL_POLYGON);
	glColor4f(100, 100, 100, 1);
	for (int i = 0; i < m; i++)
	{
		glVertex2f(0.5 * cos(2 * PI * i / m), 0.5 * sin(2 * PI * i / m));
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, 2, 0);
	glRotated(circle_ro1, 0, 1, 0);
	glBegin(GL_POLYGON);
	glColor4f(100, 100, 100, 1);
	for (int i = 0; i < m; i++)
	{
		glVertex2f(0.05 * cos(2 * PI * i / m), 0.05 * sin(2 * PI * i / m));
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 1.5, 0);
	glRotated(circle_ro1, 0, 1, 0);
	glBegin(GL_POLYGON);
	glColor4f(100, 100, 100, 1);
	for (int i = 0; i < m; i++)
	{
		glVertex2f(0.05 * cos(2 * PI * i / m), 0.05 * sin(2 * PI * i / m));
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.2, 1.2, 0);
	glRotated(circle_ro1, 0, 1, 0);
	glBegin(GL_POLYGON);
	glColor4f(100, 100, 100, 1);
	for (int i = 0; i < m; i++)
	{
		glVertex2f(0.05 * cos(2 * PI * i / m), 0.05 * sin(2 * PI * i / m));
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5, 1, 0);
	glRotated(circle_ro1, 0, 1, 0);
	glBegin(GL_POLYGON);
	glColor4f(100, 100, 100, 1);
	for (int i = 0; i < m; i++)
	{
		glVertex2f(0.05 * cos(2 * PI * i / m), 0.05 * sin(2 * PI * i / m));
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.6, 2.3, 0);
	glRotated(circle_ro1, 0, 1, 0);
	glBegin(GL_POLYGON);
	glColor4f(100, 100, 100, 1);
	for (int i = 0; i < m; i++)
	{
		glVertex2f(0.05 * cos(2 * PI * i / m), 0.05 * sin(2 * PI * i / m));
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.9, 2.8, 0);
	glRotated(circle_ro1, 0, 1, 0);
	glBegin(GL_POLYGON);
	glColor4f(100, 100, 100, 1);
	for (int i = 0; i < m; i++)
	{
		glVertex2f(0.05 * cos(2 * PI * i / m), 0.05 * sin(2 * PI * i / m));
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.f, 0.12f, 2.f);

	glVertex3f(0.5, 3.4, 0);
	glVertex3f(0.5, 0.1, 0);
	glVertex3f(3.5, 0.1, 0);
	glVertex3f(3.5, 3.4, 0);
	glEnd();
	glPopMatrix();




	// 小桌子
	//glTranslatef(0, 2, -5);
	glPushMatrix();
	//glScalef(50, 50, 50);
	glColor3f(0.4f, 0.20f, 0.f);
	glTranslatef(-3.5, -2.5, 2);
	//glTranslatef(2, 6, -3);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(-90.f, 1.f, 0.f, 0.f);
	glutSolidTorus(donut_size, donut_size, 110.f, 110.f);
	glPopMatrix();

	//Bed on the conner
	glColor3f(1, 0.8, 0.2);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matBrown);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matBrown);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);

	glPushMatrix();
	glTranslatef(-6, -6, -19.5);
	glScalef(8, 8, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-6, -7, -11.5);
	glScalef(8, 1, 16);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-6, -8.5, -4);
	glScalef(8, 3, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();

	glColor3f(1, 0.8, 0.8);		//pink
	glMaterialfv(GL_FRONT, GL_AMBIENT, matPink);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matPink);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);

	glTranslatef(-6, -6, -11.5);
	glScalef(8, 2, 16);
	glutSolidCube(1);
	glPopMatrix();

	//Brown closet in the conner
	//glColor3f(1, 0.6, 0.3);

	//glMaterialfv(GL_FRONT, GL_AMBIENT, matBrown);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, matBrown);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	//glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	//glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);

	//glPushMatrix();
	//glRotatef(90, 1, 0, 0);
	//glTranslatef(6, 0, -12);
	////glTranslatef(6, 0, -18);
	//glScalef(8, 20, 4);
	//glutSolidCube(1);
	//glPopMatrix();

	//Brown desk
	glColor3f(1, 0.6, 0.3);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matBrown);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matBrown);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);


	glPushMatrix();
	//glRotated(90, 0, 1, 0);
	glTranslatef(8, -4.5, -6);
	glScalef(4, 1, 12);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(9.5, -7, -6);
	glScalef(1, 6, 12);
	glutSolidCube(1);
	glPopMatrix();

	//  小凳子
	DrawStool();


	// 小人
	// 头
	glPushMatrix();
	glColor3f(1, 0.6, 0.3);
	glTranslatef(2, -3, -12);
	glScalef(0.5,0.5,0.5);
	glutSolidSphere(1.5, 20, 20);
	glPopMatrix();

	//身体
	glPushMatrix();
	glColor3f(1, 1, 0.8);
	glTranslatef(2, -5.5, -12);
	glScalef(0.5, 0.5, 1.0);
	glutSolidSphere(3.5, 20, 20);
	glPopMatrix();

	//左胳膊
	glPushMatrix();
	glRotatef(150., 0., 1., 0.);
	glColor3f(1, 0.6, 0.3);
	glTranslatef(-2.5, -2, -4.5);
	glScalef(0.25, 0.25, 0.85);
	glutSolidSphere(1, 2, 5);
	glPopMatrix();

	//右胳膊
	glPushMatrix();
	glRotatef(-150., 0., 1., 0.);
	glColor3f(1, 0.6, 0.3);
	glTranslatef(0.5, -2, -4.5);
	glScalef(0.25, 0.25, 0.85);
	glutSolidSphere(1, 2, 5);
	glPopMatrix();

	//左腿
	glPushMatrix();
	glRotatef(170., 0., 1., 0.);
	glTranslatef(0.5, -7, 8);
	glScalef(0.25, 1, 0.85);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();

	//右腿

	glPushMatrix();
	glRotatef(-170., 0., 1., 0.);
	glTranslatef(-4, -7, 8.5);
	glScalef(0.25, 1, 0.85);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();

	glPushMatrix();					//Celling Light
	glColor3f(1, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matYellow);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matYellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	if (aCeilingLight) glMaterialfv(GL_FRONT, GL_EMISSION, matYellow);
	glTranslatef(8, 9.5, -15);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(1, 1, 16, 16);
	glPopMatrix();


	glPushMatrix();					//Celling Light
	glColor3f(1, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matYellow);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matYellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	if (aCeilingLight) glMaterialfv(GL_FRONT, GL_EMISSION, matYellow);
	glTranslatef(-8, 9.5, -15);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(1, 1, 16, 16);
	glPopMatrix();


	glPushMatrix();					//Celling Light
	glColor3f(1, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matYellow);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matYellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	if (aCeilingLight) glMaterialfv(GL_FRONT, GL_EMISSION, matYellow);
	glTranslatef(8, 9.5, -5);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(1, 1, 16, 16);
	glPopMatrix();


	glPushMatrix();					//Celling Light
	glColor3f(1, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matYellow);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matYellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	if (aCeilingLight) glMaterialfv(GL_FRONT, GL_EMISSION, matYellow);
	glTranslatef(-8, 9.5, -5);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(1, 1, 16, 16);
	glPopMatrix();


	// TODO:
	// Add animation here
	//绘制风扇
	DrawFan();


	//绘制钟表
	//glColor3f(0 ,255 ,127); // 黑色
	glPushMatrix();

	// 1 绘制外围同心圆
	int cx = 0; //中心点
	int cy = 0;
	int R = 25; // 半径长
	int n = 100;
	glTranslatef(-2, 1.05, -3);
	glScalef(0.05, 0.05, 0.05);

	glRotatef(180, 0, 1, 0);
	glColor3f(0.94 ,1 ,1);
	glBegin(GL_LINE_LOOP); // 绘制多边形，n足够大就会变成圆形
	for (i = 0; i < n; i++)
	{
		glVertex2f(cx + (R + 2) * cos(2 * PI / n * i), cy + (R + 2) * sin(2 * PI / n * i));
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (i = 0; i < n; i++)
	{
		//glVertex2f(cx + R*cos(2 * PI / n * i), cy + R*sin(2 * PI / n * i));
		glVertex2f(cx + (R + 5) * cos(2 * PI / n * i), cy + (R + 5) * sin(2 * PI / n * i));
	}
	glEnd();


	// 2 绘制时钟 圆上的刻度，刻度粗细，长度不一样
	int lines = 60;
	float ship1 = 10;
	float ship2 = 5;
	for (i = 0; i < lines; i++)
	{
		if (i % 5 == 0)    //  0（12）-11的短线
		{
			glLineWidth(2);
			//glColor3f(0.0, 1.0, 0.0);
			glBegin(GL_LINES);
			glVertex2f(cx + (R - ship1) * sin(2 * PI / lines * i), cy + (R - ship1) * cos(2 * PI / lines * i));
			glVertex2f(cx + R * sin(2 * PI / lines * i), cy + R * cos(2 * PI / lines * i));
			glEnd();
		}
		else
		{
			glLineWidth(1);  //其他的刻度
			//glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_LINES);
			glVertex2f(cx + (R - ship2) * sin(2 * PI / lines * i), cy + (R - ship2) * cos(2 * PI / lines * i));
			glVertex2f(cx + R * sin(2 * PI / lines * i), cy + R * cos(2 * PI / lines * i));
			glEnd();
		}
	}

	// 3 绘制时 分 秒结合的中心的小黑点
	glBegin(GL_POLYGON);
	for (i = 0; i < n; ++i)
		glVertex2i(cx + 5 * cos(2 * PI / n * i), cy + 5 * sin(2 * PI / n * i));
	glEnd();

	// 4 绘制时 分 秒针，三条直线，长短粗细不一样
	int h_len = R - 3 * ship1;
	int m_len = R - ship1;
	int s_len = R - ship1 + 2 * ship1;

	float s_Angle = s / 60.0;
	float m_Angle = (m * 60 + s) / 3600.0;
	float h2 = h >= 12 ? (h - 12) : h;
	float h_Angle = (h2 * 60 * 60 + m * 60 + s) / (12 * 60 * 60);

	glColor3f(0, 0, 0);//指针色
	glLineWidth(0.5); // 秒
	glBegin(GL_LINES);
	glVertex2f(cx - 2 * ship1 * sin(2 * PI * s_Angle), cy - 2 * ship1 * cos(2 * PI * s_Angle));
	glVertex2f(cx + (R - ship2) * sin(2 * PI * s_Angle), cy + (R - ship2) * cos(2 * PI * s_Angle));
	glEnd();

	glLineWidth(3); // 时
	glBegin(GL_LINES);
	glVertex2f(cx, cy);
	glVertex2f(cx + h_len * sin(2 * PI * h_Angle), cy + h_len * cos(2 * PI * h_Angle));
	glEnd();

	glLineWidth(2); // 分
	glBegin(GL_LINES);
	glVertex2f(cx, cy);
	glVertex2f(cx + m_len * sin(2 * PI * m_Angle), cy + m_len * cos(2 * PI * m_Angle));
	glEnd();

	glPopMatrix();

	glPushMatrix();				//Teapot
	glColor3f(0.55, 0.14, 0.14);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matWhite);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matWhite);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glTranslatef(7.5, -3, -10);
	glRotatef(120, 0, 1, 0);
	glutSolidTeapot(1.5);
	glPopMatrix();

	//Android
	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	gluQuadricTexture(quadratic, GL_TRUE);

	glPushMatrix();
	glTranslatef(-15, 2.7, 0);
	glColor4f(0.9 ,0.9 ,1,0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matYellowGreen);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matYellowGreen);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glTranslatef(8, -2, -2);
	glTranslatef(0, aAndroidJumpDis, 0);		//Jump animation
	glRotatef(aAndroidAng, 0, 1, 0);	//Rotate animation
	glPushMatrix();
	glRotatef(90, 1, 0, 0);				//Body
	gluCylinder(quadratic, 1, 1, 1.5, 16, 16);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);				//Hand
	glTranslatef(1.2, 0, 0.3);
	gluCylinder(quadratic, 0.2, 0.2, 1, 16, 16);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);				//Hand
	glTranslatef(-1.2, 0, 0.3);
	gluCylinder(quadratic, 0.2, 0.2, 1, 16, 16);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);				//Foot
	glTranslatef(0.5, 0, 1.5);
	gluCylinder(quadratic, 0.2, 0.2, 0.5, 16, 16);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);				//Foot
	glTranslatef(-0.5, 0, 1.5);
	gluCylinder(quadratic, 0.2, 0.2, 0.5, 16, 16);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.7, 1.2, 0);			//Antenna
	glRotatef(90, 3, -1.5, 0);
	gluCylinder(quadratic, 0.1, 0.1, 0.5, 16, 16);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.7, 1.2, 0);			//Antenna
	glRotatef(90, 3, 1.5, 0);
	gluCylinder(quadratic, 0.1, 0.1, 0.5, 16, 16);
	glPopMatrix();
	glPushMatrix();
	glutSolidSphere(1, 16, 16);			//Head
	glPopMatrix();
	glPopMatrix();

	// 绘制小汽车

	glPushMatrix();

	glTranslatef(2, 6, -3);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);  //绕x轴旋转  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);  //绕y轴旋转  
	glTranslatef(-2, -6, 3);
	//车下半部  


	glTranslatef(2, -8, -5);
	glRotatef(180, 0, 1, 0);
	glScalef(0.05, 0.05, 0.05);
	glBegin(GL_POLYGON);


	glColor3f(0.1, 0.1, 0.8);
	glVertex3f(-40.0f, 0.0f, 15.0f);
	glVertex3f(40.0f, 0.0f, 15.0f);
	glColor3f(1, 0.5, 0.8);
	glVertex3f(40.0f, -15.0f, 15.0f);
	glVertex3f(-40.0f, -15.0f, 15.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.2, 0.5);
	glVertex3f(40.0f, 0.0f, -15.0f);
	glVertex3f(40.0f, 0.0f, 15.0f);
	glVertex3f(40.0f, -15.0f, 15.0f);
	glVertex3f(40.0f, -15.0f, -15.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.1, 0.3);
	glVertex3f(-40.0f, 0.0f, -15.0f);
	glVertex3f(-40.0f, 0.0f, 15.0f);
	glVertex3f(-40.0f, -15.0f, 15.0f);
	glVertex3f(-40.0f, -15.0f, -15.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.1, 0.1, 0.8);
	glVertex3f(-40.0f, 0.0f, -15.0f);
	glVertex3f(40.0f, 0.0f, -15.0f);
	glColor3f(1, 0.5, 0.8);
	glVertex3f(40.0f, -15.0f, -15.0f);
	glVertex3f(-40.0f, -15.0f, -15.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 1);
	glVertex3f(-40.0f, 0.0f, 15.0f);
	glVertex3f(-40.0f, 0.0f, -15.0f);
	glVertex3f(40.0f, 0.0f, -15.0f);
	glVertex3f(40.0f, 0.0f, 15.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.5, 0.2);
	glVertex3f(-40.0f, -15.0f, 15.0f);
	glVertex3f(-40.0f, -15.0f, -15.0f);
	glVertex3f(40.0f, -15.0f, -15.0f);
	glVertex3f(40.0f, -15.0f, 15.0f);
	glEnd();
	//车上半部  
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 1);
	glVertex3f(-20.0f, 0.0f, 15.0f);
	glVertex3f(-10.0f, 10.0f, 15.0f);
	glVertex3f(20.0f, 10.0f, 15.0f);
	glVertex3f(25.0f, 0.0f, 15.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 1);
	glVertex3f(-20.0f, 0.0f, -15.0f);
	glVertex3f(-10.0f, 10.0f, -15.0f);
	glVertex3f(20.0f, 10.0f, -15.0f);
	glVertex3f(25.0f, 0.0f, -15.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0, 1, 1);
	glVertex3f(-10.0f, 10.0f, 15.0f);
	glVertex3f(-10.0f, 10.0f, -15.0f);
	glVertex3f(20.0f, 10.0f, -15.0f);
	glVertex3f(20.0f, 10.0f, 15.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.8, 0.8);
	glVertex3f(-10.0f, 10.0f, 15.0f);
	glVertex3f(-20.0f, 0.0f, 15.0f);
	glVertex3f(-20.0f, 0.0f, -15.0f);
	glVertex3f(-10.0f, 10.0f, -15.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0, 0.5, 0.5);
	glVertex3f(20.0f, 10.0f, 15.0f);
	glVertex3f(20.0f, 10.0f, -15.0f);
	glVertex3f(25.0f, 0.0f, -15.0f);
	glVertex3f(25.0f, 0.0f, 15.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 1);
	glVertex3f(-30.0f, -15.0f, 15.0f);
	glVertex3f(-30.0f, -15.0f, -15.0f);
	glVertex3f(30.0f, -15.0f, -15.0f);
	glVertex3f(30.0f, -15.0f, 15.0f);
	glEnd();
	//车轮  
	glColor3f(1, 0, 0);

	glTranslated(-20.0f, -15.0f, 15.0f);
	glutSolidTorus(2, 5, 5, 100);
	glTranslated(0.0f, 0.0f, -30.0f);
	glutSolidTorus(2, 5, 5, 100);
	glTranslated(45.0f, 0.0f, 0.0f);
	glutSolidTorus(2, 5, 5, 100);
	glTranslated(0.0f, 0.0f, 30.0f);
	glutSolidTorus(2, 5, 5, 100);
	glPopMatrix();


	// 弹簧小板子
	Drawtable();

	// 绘制国旗
	//glPushMatrix();
	glScalef(2, 2, 2);
	glTranslatef(-1.3, 1.5, 0);
	//绘制星星
	glColor3f(1.0, 1.0, 0.0);//设置颜色为黄色
	GLfloat px[5] = { -1.5 / 3,-0.75 / 3,-0.75 / 5,-0.75 / 5,-0.75 / 3 };
	GLfloat py[5] = { 0.25,0.4,0.3,0.15,0.05 };
	GLfloat vx[5] = { -1.5 / 3 };
	GLfloat vy[5] = { 0.4 };//五星的中心点和其中指定顶点
	//计算其余四星的顶点
	for (int i = 1; i < 5; i++) {
		vx[i] = px[i] - 0.05 * cos(atan((py[0] - py[i]) / (px[0] - px[i])));
		vy[i] = py[i] - 0.05 * sin(atan((py[0] - py[i]) / (px[0] - px[i])));
	}
	//绘制
	DrawStar(px[0], py[0], vx[0], vy[0], 0);
	DrawStar(px[1], py[1], vx[1], vy[1], 1);
	DrawStar(px[2], py[2], vx[2], vy[2], 1);
	DrawStar(px[3], py[3], vx[3], vy[3], 1);
	DrawStar(px[4], py[4], vx[4], vy[4], 1);

	//绘制红旗
	glColor3f(1, 0, 0);//确定绘制物体时使用的颜色:红色
	glBegin(GL_QUADS);
	glVertex3f(-0.75, 0.5, 0.5);//位于z=0.5平面的矩形 0.5是相对值
	glVertex3f(0.75, 0.5, 0.5);
	glVertex3f(0.75, -0.5, 0.5);
	glVertex3f(-0.75, -0.5, 0.5);
	glEnd();
	//glutSwapBuffers();//交换缓冲区
	//glPopMatrix();
	glFlush();
	glutSwapBuffers();

}

void timerFunc(int value)
{
	s += 1;
	int carry1 = 0;
	if (s >= 60)
	{
		s = 0;
		carry1 = 1;
	}
	m += carry1;
	int carry2 = 0;
	if (m >= 60)
	{
		m = 0;
		carry2 = 1;
	}
	h += carry2;
	if (h >= 24)
		h = 0;

	glutPostRedisplay(); // 重画

	glutTimerFunc(1000, timerFunc, 1); // 每一秒中执行一次
}

/*
初始化函数
设置背景，获取时间
*/
void SetupRC(void)
{
	// 设置窗口为白色
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// 获取本地当前时间
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	h = sys.wHour;
	m = sys.wMinute;
	s = sys.wSecond;
}

void reshape(int w, int h) // Resize the GL Window. w=width, h=height
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(65, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	gluLookAt(0.0, 0.0, 15.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) // Handle the keyboard events here
{
	switch (key)
	{
	case'\033'://press 'esc' to quit
		exit(0);
		break;

	case'1':
		aRoomLight = !aRoomLight;
		printf("Press key '1'.\n");
		break;
	case'2':
		aCeilingLight = !aCeilingLight;
		printf("Press key '2'.\n");
		break;
	case'3':
		aAndroidLight = !aAndroidLight;
		if (!aAndroidLight) aAndroidJumpDis = 0;
		printf("Press key '3'.\n");
		break;
	case '4':	//风扇旋转/停下
		if (Fan == fan_turnoff)
			Fan = fan_turnon;
		else Fan = fan_turnoff;
		break;
	case '6':	//凳子移动
		Stool = stoolmove;
		break;
	case 'w':
		xRot -= 5.0f;
		glutPostRedisplay(); // 刷新窗口  
		break;
	case 's':
		xRot += 5.0f;
		glutPostRedisplay(); // 刷新窗口  
		break;
	case 'a':
		yRot -= 5.0f;
		glutPostRedisplay(); // 刷新窗口  
		break;
	case 'd':
		yRot += 5.0f;
		glutPostRedisplay(); // 刷新窗口  
		break;
	case'5':
		b_Animation = !b_Animation;
		break;
	case '7':
		option = 7;
		break;
	case '8':
		option = 8;
		break;
	case'9':
		aAndroid = !aAndroid;
		if (!aAndroid) aAndroidJumpDis = 0;
		printf("Press key '4'.\n");
		break;
	case 'z':
		option = 5;
		break;
	case 'x':
		option = 6;
		break;
	}

	if (aRoomLight || aCeilingLight || aAndroidLight)
		aMice = false;

	//printf("Pos:%f %f %f %f\n",light_pos0[0], light_pos0[1], light_pos0[2], light_pos0[3]);
	//printf("Dir:%f %f %f\n", light_dir0[0], light_dir0[1], light_dir0[2]);
	//printf("Cutoff:%f\n",light_cutoff0);

	//printf("Amb:%f %f %f\n",light_amb0[0],light_amb0[1],light_amb0[2]);
	//printf("Dif:%f %f %f\n",light_dif0[0],light_dif0[1],light_dif0[2]);
	//printf("Spc:%f %f %f\n\n",light_spc0[0],light_spc0[1],light_spc0[2]);
}

void idle(void)
{
	if (aAndroid) {
		if (!aAndroidLight)
			aAndroidAng = ++aAndroidAng % 360;
		else {
			if (aAndroidJumpUp) {
				aAndroidJumpDis += 0.1;
				if (aAndroidJumpDis >= 1) aAndroidJumpUp = false;
			}
			else {
				aAndroidJumpDis -= 0.1;
				if (aAndroidJumpDis <= 0) aAndroidJumpUp = true;
			}
		}
	}
	if (option == 7)
	{
		if (donut_size < 10)
			donut_size += 1;
	}

	else if (option == 8)
	{
		if (donut_size >= 6)
			donut_size -= 1;
	}
	else if (option == 5)
	{
		if (windows_tr >= 5.1)
			windows_tr -= 0.2;
	}
	else if (option == 6)
	{
		if (windows_tr <= 8.18)
			windows_tr += 0.2;
	}

	if (b_Animation)
	{



		if (b_direction == TRUE)
		{
			t_x += 0.01;
			if (t_x > 0.7) // control the shift range
			{
				b_direction = FALSE;
			}
		}
		else
		{
			t_x += -0.01;
			if (t_x < -2) // control the shift range
			{
				b_direction = TRUE;
			}
		}


	}
	if (Stool == stoolmove)
	{
		if (Stool_dir)
		{
			StoolPos -= 1;
			if (StoolPos <= -10)
			{
				Stool = stoolstop;
				Stool_dir = false;
			}
		}
		else
		{
			StoolPos += 1;
			if (StoolPos >= 10)
			{
				Stool = stoolstop;
				Stool_dir = true;
			}

		}
	}
	if (circle_ro <= 10000)

	{

		circle_ro += 0.05;

	}
	if (Fan == fan_turnon)
	{
		if (FanAngle <= -360)
		{
			FanAngle = 0;
		}
		FanAngle--;
	}
	if (!aMice) {
		if (aMiceEyeBigger) {
			aMiceEyeScale += 0.2;
			if (aMiceEyeScale >= 3) aMiceEyeBigger = false;
		}
		else {
			aMiceEyeScale -= 0.2;
			if (aMiceEyeScale <= 0) aMiceEyeBigger = true;
		}
		aMiceTrans[0] = aMiceTrans[1] = aMiceTrans[2] = 0;
	}
	else {
		aMiceEyeScale = 1;
		aMiceTrans[2] += 0.5;
		if (aMiceTrans[2] < 10)
			aMiceTrans[0] += 0.2;
		else
			aMiceTrans[0] -= 0.2;
		if (aMiceTrans[2] > 25)
			aMiceTrans[0] = aMiceTrans[1] = aMiceTrans[2] = 0;
	}
	Sleep(10);
	glutPostRedisplay();
}

void main(int argc, char** argv)
{

	/*Initialization of GLUT Library */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	/*Create a window with title specified */
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Assignment 1");

	init();	/*not GLUT call, initialize several parameters */

	/*Register different CALLBACK function for GLUT to response
	with different events, e.g. window sizing, mouse click or
	keyboard stroke */
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutTimerFunc(1000, timerFunc, 1);

	/*Enter the GLUT event processing loop which never returns.
	it will call different registered CALLBACK according
	to different events. */
	glutMainLoop();

}
