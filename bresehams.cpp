#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

void setPixel(int x, int y)
{
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}
void myinit()
{
    glMatrixMode(GL_PROJECTION_MATRIX);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);
    glMatrixMode(GL_MODELVIEW);
}
void breshnans(int x0, int y0, int xend, int yend)
{
    int dx = abs(xend - x0);
    int dy = abs(yend - y0);
    int p = 2 * dy - dx;
    int twody = 2 * dy, twoDyminusdx = 2 * (dy - dx);
    int twodx = 2 * dx, twoDxminusdy = 2 * (dx - dy);
    int x, y;
    if (x0 > xend)
    {
        x = xend;
        y = yend;
        xend = x0;
        yend = y0;
    }
    else
    {
        x = x0;
        y = y0;
    }
    //glColor3f(1, 0, 0);
    setPixel(x, y);
    if (dx > dy)
    {
        while (x < xend)
        {
            x++;
            if (p < 0)
            {
                p += twody;
            }
            else
            {
                y++;
                p += twoDyminusdx;
            }
            setPixel(x, y);
        }
    }
    else
    {
        p = 2 * dx - dy;
        while (y < yend)
        {
            y++;
            if (p < 0)
            {
                p += twodx;
            }
            else
            {
                x++;
                p += twoDxminusdy;
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
    breshnans(-200, -200, 200, 200);
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