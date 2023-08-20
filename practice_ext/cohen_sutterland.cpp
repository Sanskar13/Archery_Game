#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

#define opcode int

enum { top = 0x8, bottom = 0x6, right = 0x4, left = 0x2 };
float xmin = 100, ymin = 100, xmax = 300, ymax = 300;
float umin = 400, vmin = 350, umax = 700, vmax = 650;
float x1 = 50, y1 = 80, x2 = 310, y2 = 399;

void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
}

opcode comopcode(float x, float y)
{
    int p = 0;
    if (x < xmin) p |= left;
    else if (x > xmax) p |= right;
    else if (y < ymin) p |= bottom;
    else if (y > ymax) p |= top;

    return p;
}

void cohen()
{
    bool flag = false, done = false;
    int x = 0, y = 0;
    opcode p1, p2, p;

    p1 = comopcode(x1, y1);
    p2 = comopcode(x2, y2);
    float m = (y2 - y1) / (x2 - x1);
    do {
        if (!(p1 | p2)) {
            done = true;
            flag = true;
        }
        else if (p1 & p2) {
            done = true;
        }
        else {

            p = p1 ? p1 : p2;

            if (p & bottom) {
                y = ymin;
                x = x1 + (ymin - y1) / m;
            }
            if (p & top) {
                y = ymax;
                x = x1 + (ymax - y1) / m;
            }
            if (p & right) {
                x = xmax;
                y = y1 + (xmax - x1) * m;
            }
            if (p & left) {
                x = xmin;
                y = y1 + (xmin - x1) * m;
            }

            if (p == p1) {
                x1 = x;
                y1 = y;
                p1 = comopcode(x1, y1);
            }
            if (p == p2) {
                x2 = x;
                y2 = y;
                p2 = comopcode(x2, y2);
            }

        }
    } while (!done);


    if (flag) {
        float sx = (umax - umin) / (xmax - xmin);
        float sy = (vmax - vmin) / (ymax - ymin);

        x1 = sx * x1 + umin - sx * xmin;
        x2 = sx * x2 + umin - sx * xmin;
        y1 = sy * y1 + vmin - sy * ymin;
        y2 = sy * y2 + vmin - sy * ymin;
    }

    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
    glFlush();
}

void display()
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmin, ymax);
    glVertex2f(xmax, ymax);
    glVertex2f(xmax, ymin);
    glEnd();
    glColor3f(1, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
    glColor3f(1, 1, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(umin, vmin);
    glVertex2f(umin, vmax);
    glVertex2f(umax, vmax);
    glVertex2f(umax, vmin);
    glEnd();

    cohen();

    glFlush();


}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("cohen");
    myinit();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}


