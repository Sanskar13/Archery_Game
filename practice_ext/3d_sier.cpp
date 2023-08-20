#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float v[4][3] = { {0,0,1}, {-1, -0.5, 0}, {0,1,0}, {1, -0.5, 0} };
int c = 5;

void myinit() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
}

void disp_tri(float a[], float b[], float c[])
{
    glBegin(GL_POLYGON);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glEnd();
}

void div_tri(float* a, float* b, float* c, int n)
{
    float v1[3], v2[3], v3[3];
    int i = 0;
    if (n > 0) {
        for (i = 0; i < 3; i++) {
            v1[i] = (a[i] + b[i]) / 2;
            v2[i] = (a[i] + c[i]) / 2;
            v3[i] = (c[i] + b[i]) / 2;
        }
        div_tri(a, v1, v2, n - 1);
        div_tri(v1, b, v3, n - 1);
        div_tri(v2, v3, c, n - 1);
    }
    else disp_tri(a, b, c);
}

void display() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);

    div_tri(v[0], v[1], v[2], c);
    glColor3f(1, 1, 0);
    div_tri(v[1], v[2], v[3], c);
    glColor3f(1, 0, 1);
    div_tri(v[0], v[2], v[3], c);
    glColor3f(0, 1, 0);
    div_tri(v[0], v[1], v[3], c);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("3D sierpinski Gasked");
    myinit();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}