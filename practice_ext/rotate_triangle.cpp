#include<stdio.h>
#include<gl/glut.h>
#include<math.h>

float p[3][2] = { {20, 20}, {40, 40}, {60, 20} };
float xp = 0, yp = 0, theta = 30, rtheta;
void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    float x, y;
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 0);

    glBegin(GL_TRIANGLES);
    glVertex2fv(p[0]);
    glVertex2fv(p[1]);
    glVertex2fv(p[2]);
    glEnd();

    rtheta = (theta * 3.142) / 180;
    for (int i = 0; i < 3; i++) {
        x = p[i][0];
        y = p[i][1];

        p[i][0] = xp + (x - xp) * cos(rtheta) - (y - yp) * sin(rtheta);
        p[i][1] = yp + (x - xp) * sin(rtheta) + (y - yp) * cos(rtheta);
    }

    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2fv(p[0]);
    glVertex2fv(p[1]);
    glVertex2fv(p[2]);
    glEnd();

    glFlush();

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("rotate triangle");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
}