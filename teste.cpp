#include "Screen.h"
#define WIDTH 400
#define HEIGHT 400

int main(int argc, char **argv)
{
    init(WIDTH, HEIGHT);
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            if (i == j)
            {
                continue;
            }
            setPixel(i, j, 255, 0, 0);
        }
    }
    start(argc, argv);
}
