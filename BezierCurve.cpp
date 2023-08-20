#include <iostream>
#include <GL/glut.h>

using namespace std;

// Define some constants
const int winWidth = 600;
const int winHeight = 600;
const float xwcMin = 0.0;
const float xwcMax = 130.0;
const float ywcMin = 0.0;
const float ywcMax = 130.0;

// Define two functions: bino() and computeBezPt()
void bino(int n, int* C) {
    for (int k = 0; k <= n; k++) {
        C[k] = 1;
        for (int j = n; j >= k + 1; j--) {
            C[k] *= j;
            C[k] /= (k - j);
        }
    }
}

void computeBezPt(float u, wcPt3D* bezPt, int nCtrlPts, wcPt3D* ctrlPts, int* C) {
    bezPt->x = bezPt->y = bezPt->z = 0.0;
    for (int k = 0; k < nCtrlPts; k++) {
        float bezBlendFcn = C[k] * pow(u, k) * pow(1 - u, nCtrlPts - k);
        bezPt->x += ctrlPts[k].x * bezBlendFcn;
        bezPt->y += ctrlPts[k].y * bezBlendFcn;
        bezPt->z += ctrlPts[k].z * bezBlendFcn;
    }
}

// Define the bezier() function to draw the Bezier curve
void bezier(wcPt3D* ctrlPts, int nCtrlPts, int nBezCurvePts) {
    wcPt3D bezCurvePt;
    float u;
    int* C = new int[nCtrlPts];
    bino(nCtrlPts - 1, C);
    glBegin(GL_LINE_STRIP);
    for (int k = 0; k <= nBezCurvePts; k++) {
        u = float(k) / float(nBezCurvePts);
        computeBezPt(u, &bezCurvePt, nCtrlPts, ctrlPts, C);
        glVertex2f(bezCurvePt.x, bezCurvePt.y);
    }
    glEnd();
    delete[] C;
}

// Define the displayFcn() function to draw the Bezier curve and control points
void displayFcn() {
    float theta = 0.0;
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5);
    glPushMatrix();
    for (int i = 0; i < 24; i++) {
        glTranslatef(0, -0.8, 0);
        bezier(ctrlPts, nCtrlPts, nBezCurvePts);
    }
    glPopMatrix();
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(20, 100);
    glVertex2f(20, 40);
    glEnd();
    glFlush();
}

// Define the winReshapeFun() function to handle window resize events
void winReshapeFun(int newWidth, int newHeight) {
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
    glClear(GL_COLOR_BUFFER_BIT);
}

void d_menu(int op)
{
    if (op == 1)
        glColor3f(1.0, 0.0, 0.0);
    else if (op == 2)
        glColor3f(0.0, 1.0, 0.0);
    else if (op == 3)
        glColor3f(0.0, 0.0, 1.0);
    else if (op == 4)
        exit(0);
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Bezier Curve");

    glutCreateMenu(d_menu);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Quit", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFun);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}
