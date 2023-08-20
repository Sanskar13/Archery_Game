
#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#define opcode int
enum { top = 0x8, bottom = 0x4, left = 0x2, right = 0x1 };
float x1 = 50, y1 = 100, x2 = 350, y2 = 599; // Line segment endpoints
float xmin = 100, ymin = 100, xmax = 300, ymax = 300; // Clipping window boundaries
float umin = 400, vmin = 400, umax = 700, vmax = 700; // Display window boundaries


void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
}
opcode compopcode(float x, float y)
{
    int p = 0;
    if (x < xmin)
        p |= left;
    else if (x > xmax)
        p |= right;
    else if (y < ymin)
        p |= bottom;
    else if (y > ymax)
        p |= top;
    return p;
}
void cohensutherlan()
{
    bool flag = false, done = false;
    int x = 0, y = 0;
    opcode p1, p2, p;
    p1 = compopcode(x1, y1);
    p2 = compopcode(x2, y2);
    float m = (y2 - y1) / (x2 - x1);
    do {
        if (!(p1 | p2))
        {
            done = true;
            flag = true;
        }
        else if (p1 & p2)
        {
            done = true;
        }
        else
        {
            p = p1 ? p1 : p2;
            if (p & bottom)
            {
                y = ymin;
                x = x1 + (ymin - y1) / m;
            }
            else if (p & top)
            {
                y = ymax;
                x = x1 + (ymax - y1) / m;
            }
            else if (p & right)
            {
                x = xmax;
                y = y1 + (xmax - x1) * m;
            }
            else
            {
                x = xmin;
                y = y1 + (xmin - x1) * m;
            }
            if (p == p1)
            {
                x1 = x;
                y1 = y;
                p1 = compopcode(x1, y1);
            }
            if (p == p2)
            {
                x2 = x;
                y2 = y;
                p2 = compopcode(x2, y2);
            }
        }
    } while (!done);
    if (flag)
    {
        float sx = (umax - umin) / (xmax - xmin);
        float sy = (vmax - vmin) / (ymax - ymin);
        x1 = sx * x1 + umin - sx * xmin;
        y1 = sy * y1 + vmin - sy * ymin;
        x2 = sx * x2 + umin - sx * xmin;
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

    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();

    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(umin, vmin);
    glVertex2f(umin, vmax);
    glVertex2f(umax, vmax);
    glVertex2f(umax, vmin);
    glEnd();
    cohensutherlan();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("CLIPPING ALGORITHM");
    myinit();

    glutDisplayFunc(display);
    glutMainLoop();
}