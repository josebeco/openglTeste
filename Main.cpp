#include "Screen.h"
#define WIDTH 400
#define HEIGHT 400
int c = 0;
int f []= {255, 0 , 0};

int main(int argc, char **argv)
{
    init(WIDTH, HEIGHT);
    start(argc, argv);
}

void cycle()
{
    c++;
    c %= 3;
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            if (i == j)
            {
                continue;
            }
            setPixel(i, j, f[c], f[(c + 1) % 3], f[(c + 2) % 3]);
        }
    }
}
