#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

float v[8][3] = { {-1,-1,1},{-1,1,1},{1,1,1},{1,-1,1},{-1,-1,-1},{-1,1,-1},{1,1,-1},{1,-1,-1} };
float p[8][3] = { {0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1} };
float theta[3] = { 0,0,0 };
int flag = 2;

void idle()
{
    theta[flag] = theta[flag] + 0.009;
    if (theta[flag] > 360) theta[flag] = 0;
    glutPostRedisplay();
}

void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int b, int s, int x, int y)
{
    if (b == GLUT_RIGHT_BUTTON && s == GLUT_DOWN) flag = 0;
    if (b == GLUT_MIDDLE_BUTTON && s == GLUT_DOWN) flag = 1;
    if (b == GLUT_LEFT_BUTTON && s == GLUT_DOWN) flag = 2;
}

void drawpoly(int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);
    glColor3fv(p[a]);
    glVertex3fv(v[a]);
    glColor3fv(p[b]);
    glVertex3fv(v[b]);
    glColor3fv(p[c]);
    glVertex3fv(v[c]);
    glColor3fv(p[d]);
    glVertex3fv(v[d]);
    glEnd();
}


void colorcube()
{
    drawpoly(0, 1, 2, 3);
    drawpoly(0, 1, 5, 4);
    drawpoly(1, 5, 6, 2);
    drawpoly(4, 5, 6, 7);
    drawpoly(3, 2, 6, 7);
    drawpoly(0, 4, 7, 3);
}

void display()
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glRotatef(theta[0], 1, 0, 0);
    glRotatef(theta[1], 0, 1, 0);
    glRotatef(theta[2], 0, 0, 1);
    colorcube();
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("cube rotation");
    myinit();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}