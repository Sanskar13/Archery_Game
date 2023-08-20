#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

int xx = 20, yy = 30, xend = 80, yend = 90;

void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}

void setPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}

void Bresenhamline()
{
    int p, x, y;

    // Check for the direction of the line
    if (xx > xend)
    {
        x = xend;
        y = yend;
        xend = xx;
        yend = yy;
    }
    else
    {
        x = xx;
        y = yy;
    }

    int dx = abs(xend - x), dy = abs(yend - y);
    int twody = 2 * dy, twodyMinustwodx = 2 * (dy - dx);
    int twodx = 2 * dx, twodxMinustwody = 2 * (dx - dy);

    glColor3f(1, 0, 0); // Set color to red.
    glPointSize(2);    // Set point size to 2.

    if (dx > dy)
    {
        // For slope |m| < 1
        p = 2 * dy - dx;
        setPixel(x, y);

        while (x < xend)
        {
            x = x + 1;

            if (p < 0)
                p = p + twody;
            else
            {
                y = y + 1;
                p = p + twodyMinustwodx;
            }

            setPixel(x, y);
        }
    }
    else
    {
        // For slope |m| >= 1
        p = 2 * dx - dy;
        setPixel(x, y);

        while (y < yend)
        {
            y = y + 1;

            if (p < 0)
                p = p + twodx;
            else
            {
                x = x + 1;
                p = p + twodxMinustwody;
            }

            setPixel(x, y);
        }
    }
}

void display()
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 500, 500);
    Bresenhamline();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenham's Line Drawing Algorithm");
    myinit();
    printf("Enter coordinates of the first point: ");
    scanf("%d %d", &xx, &yy);
    printf("Enter coordinates of the second point: ");
    scanf("%d %d", &xend, &yend);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
