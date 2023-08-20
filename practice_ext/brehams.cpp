#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

void myinit()
{
    glMatrixMode(GL_PROJECTION_MATRIX);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);
    glMatrixMode(GL_MODELVIEW);
}

void setPixel(float x, float y) {
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void brehams(float x0, float y0, float xend, float yend)
{
    float x, y;
    if (x0 > xend) {
        x = xend;
        y = yend;
        xend = x0;
        yend = y0;
    }
    else {
        x = x0;
        y = y0;
    }

    int dx = fabs(x0 - xend), dy = fabs(y0 - yend);
    int twody = 2 * dy, twodx = 2 * dx;
    int twodyminusdx = 2 * (dy - dx);
    int twodxminusdy = 2 * (dx - dy);

    if (dx > dy) {
        int p0 = 2 * dy - dx;
        while (x < xend)
        {
            x++;
            if (p0 < 0) p0 += twody;
            else {
                y++;
                p0 += twodyminusdx;
            }

            setPixel(x, y);
        }
    }
    else {
        int p0 = 2 * dx - dy;
        while (y < yend)
        {
            y++;
            if (p0 < 0) p0 += twodx;
            else {
                x++;
                p0 += twodxminusdy;
            }

            setPixel(x, y);
        }
    }
}

void display()
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    brehams(-100, -100, 100, 100);
    glFlush();

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(500, 500);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Breshnans");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
}