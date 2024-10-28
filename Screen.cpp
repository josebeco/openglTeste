#include <GL/glut.h>
#include "Main.h"
using namespace std;
int WIDTH = 0;
int HEIGHT = 0;
GLubyte *pixels = NULL;

void initGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void setPixel(int i, int j, int r, int g, int b)
{
    int position = (i * WIDTH + j) * 3;
    pixels[position++] = r;
    pixels[position++] = g;
    pixels[position] = b;
}

void display()
{
    cycle();
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    }
}

void timer(int extra){
    glutPostRedisplay();
    glutTimerFunc(20, timer, 0); //50 fps 1000 / 20
}



void start(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("aaaaa");
    initGL();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
}

void init(int width, int height)
{
    WIDTH = width;
    HEIGHT = height;
    pixels = new GLubyte[WIDTH * HEIGHT * 3];
}
