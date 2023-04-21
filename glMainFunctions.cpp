#pragma once
#include <iostream> 
#include "GL\freeglut.h"
#include <string>       
#include <iostream>     
#include <sstream> 
#include <map>

using std::cout;
using std::endl;

int iter_draw = 0;

extern double Xleft, Xright, Ybottom, Ytop;
extern double Lx, Ly;
extern int N;
extern double H;
extern double * glPosX, * glPosY;
extern int width, height;

#define rgb(r,g,b) (GLclampf)r/255.0, (GLclampf)g/255.0, (GLclampf)b/255.0, (GLclampf)1.0

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	//width = w;
	//height = h;
}
void idle()
{
	//this function is doing something between rendering
	glutReshapeFunc(reshape);
	glutPostRedisplay();
	iter_draw++;
	//if (iter_draw % 100 == 0) cout << iter_draw << endl;
}

void circle(double r, double x0, double y0, int p)
{
	glBegin(GL_POLYGON);
	for (double alpha = 0; alpha <= 6.29185; alpha = alpha + 6.29185 / p) {
		glVertex3d(r * cos(alpha) + x0, r * sin(alpha) + y0, 0.0);
	}
	for (double alpha = 0; alpha <= 6.29185; alpha = alpha + 6.29185 / p) {
		glVertex3d(0.99 * r * cos(alpha) + x0, 0.99 * r * sin(alpha) + y0, 0.0);
	}
	for (double alpha = 0; alpha <= 6.29185; alpha = alpha + 6.29185 / p) {
		glVertex3d(0.98 * r * cos(alpha) + x0, 0.98 * r * sin(alpha) + y0, 0.0);
	}
	glEnd();
}

void display()
{
	glClearColor(rgb(30, 30, 30));
	glClear(GL_COLOR_BUFFER_BIT);

	//____________________________________//
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();



	gluOrtho2D(Xleft, Xright, Ybottom, Ytop);

	//axes
	glBegin(GL_LINES);
	glColor3d(0.0, 0.0, 0.9);
	glVertex3d(Xleft, 0, 0); 	 glVertex3d(Xright, 0, 0);
	glVertex3d(0, Ybottom, 0);  	glVertex3d(0, Ytop, 0);
	glVertex3d(Xleft, Ytop, 0); 	 glVertex3d(Xright, Ytop, 0);
	glVertex3d(Xright, Ybottom, 0);  	glVertex3d(Xright, Ytop, 0);
	glEnd();



	//objects
	glColor3d(0.0, 0.46, 0.89);
	for (int i = 0; i < N; i++)
	{
		//if (mark[i] > 3.0) glColor3f(0.7, 0.7, 0.7);
		circle(H * 0.4, glPosX[i], glPosY[i], 12);
		//glBegin(GL_POINTS);
		//glVertex3f(x[i], y[i], 0.0);
		//glEnd();
	}
	




	glutSwapBuffers();
}


#include "keyboard.h"
#include "mouse.h"
void mainGL(int argc, char** argv)
{
	double aspect = Lx / Ly;
	//height = (int)(width / aspect);
	//width = (int)(height * aspect);

	//cout << "L= " << Lx << " " << Ly << endl;
	
#define d 4
	width = int(ceil(width / (0.0 + d)) * d);
	height = int(ceil(height / (0.0 + d)) * d);

	//init gl functions
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowSize(width, height);
		glutInitWindowPosition(400, 20);
		glutCreateWindow("Window_freeglut");

		glutReshapeFunc(reshape);
		glutDisplayFunc(display);
		glutIdleFunc(idle);

		glutPassiveMotionFunc(mouseMovePassive);
		glutMotionFunc(mouseClickMove);
		glutMouseFunc(mouseClick);
		glutKeyboardFunc(keyboard);
	}
	glutMainLoop();
}

