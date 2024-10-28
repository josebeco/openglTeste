#include <GL/glut.h>
using namespace std;
int WIDTH = 0;
int HEIGHT = 0;
GLubyte *pixels = NULL;

void initGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    /*for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            cout << int(pixels[i * WIDTH + j]) << " " << endl;
        }
    }*/

    glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    glutSwapBuffers();
    glutPostRedisplay();
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

void setPixel(int i, int j, int r, int g, int b)
{
    int position = (i * WIDTH + j) * 3;
    pixels[position++] = r;
    pixels[position++] = g;
    pixels[position] = b;
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
    glutMainLoop();
}

void init(int width, int height)
{
    WIDTH = width;
    HEIGHT = height;
    pixels = new GLubyte[WIDTH * HEIGHT * 3];
}
