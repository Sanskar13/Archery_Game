#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#include<conio.h>

void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100, 200, -100, 200, -200, 200);
    glMatrixMode(GL_MODELVIEW);
}

void drawtable()
{
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(50, 40, -50);
    glScalef(50, 5, 50);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(30, 20, -30);
    glScalef(5, 35, 6);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(67, 20, -30);
    glScalef(5, 35, 6);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(40, 20, -50);
    glScalef(5, 35, 6);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(70, 20, -60);
    glScalef(5, 35, 6);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(50, 0, -40);
    glScalef(100, 5, 100);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 0);
    glRotatef(90, 0, 0, 1);
    glTranslatef(50, 0, -50);
    glScalef(100, 5, 100);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(50, 50, -100);
    glScalef(100, 100, 5);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(50, 60, -30);
    glRotatef(30, 0, 1, 0);
    glutSolidTeapot(10);
    glPopMatrix();


}

void display()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat mat_ambient[] = { .7, .7, .7, 1 };
    GLfloat mat_diffuse[] = { .5, .5, .5, 1 };
    GLfloat mat_spec[] = { 1, 1, 1, 1 };
    GLfloat mat_shininess[] = { 50 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    GLfloat light_pos[] = { 100, 100, 100 };
    GLfloat mat_light[] = { .7, .7, .7, 1 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_light);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(25, 25, 50, 0, 0, -25, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);

    drawtable();
    glFlush();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    // glutInitWindowPosition(100, 100);
    glutCreateWindow("Tea Pot");
    myinit();
    glutDisplayFunc(display);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}