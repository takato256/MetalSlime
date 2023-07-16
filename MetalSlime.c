#include <stdio.h>
#include <GL/glut.h>

void myInit(char *progname)
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
    float ambient[] = {0.25, 0.25, 0.25, 1.0};  // 環境光の設定
    float diffuse[] = {0.75, 0.75, 0.75, 1.0};  // 拡散反射の設定
    float specular[] = {0.9, 0.9, 0.9, 1.0};   // 鏡面反射の設定

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);  // シャイニング度を増加

    glPushMatrix();
    glTranslated(0.0, 0.0, 0.0);
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

void myKeyboard(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    myInit(argv[0]);
    glutKeyboardFunc(myKeyboard);
    glutReshapeFunc(myReshape);
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}
