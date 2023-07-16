#include <stdio.h>
#include <GL/glut.h>

int previousX, previousY;
GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

void myInit(char* progname)
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(progname);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT0);
}

void myDisplay(void)
{
    float ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    float diffuse[] = { 0.3, 0.3, 0.3, 1.0 };
    float specular[] = { 0.9, 0.9, 0.9, 1.0 };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);

    glPushMatrix();
    glRotatef(rotationX, 0.0f, 1.0f, 0.0f);
    glRotatef(rotationY, 1.0f, 0.0f, 0.0f);
    glTranslated(0.0, 0.0, 0.0);
    glScalef(1.2, 0.8, 1.0);
    glutSolidSphere(0.8, 20, 20);
    glPopMatrix();

    glFlush();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
}

void myReshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)width / (double)height, 0.1, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0, 0.0, -3.6);
}

void myMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        previousX = x;
        previousY = y;
    }
}

void myMotion(int x, int y)
{
    rotationX += (x - previousX);
    rotationY += (y - previousY);
    previousX = x;
    previousY = y;
    glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    myInit(argv[0]);
    glutKeyboardFunc(myKeyboard);
    glutReshapeFunc(myReshape);
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutMotionFunc(myMotion);
    glutMainLoop();
    return 0;
}
