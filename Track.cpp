#include "Screen.h"
struct RGB
{
    short r;
    short g;
    short b;
};
const struct RGB TEXTURE[][4] = {{{0, 255, 0}, {255, 0, 0}, {128, 128, 128}, {255, 255, 255}}, {{0, 175, 0}, {255, 255, 255}, {75, 75, 75}, {75, 75, 75}}}; // 0 grama, 1 borda rua, 2 estrada, 3- faixa
short *ROAD;
int HEIGTH_ROAD;
int WIDTH_ROAD;

void createRoad(int w, int h, int borderSize, int middleLine)
{
    HEIGTH_ROAD = h;
    WIDTH_ROAD = w;
    ROAD = new short[HEIGTH_ROAD * WIDTH_ROAD];
    for (int i = 0; i < HEIGTH_ROAD; i++)
    {
        for (int j = 0; j < WIDTH_ROAD / 2 - middleLine / 2; j++)
        {
            int position = (i * WIDTH_ROAD) + j;
            if (i <= j - borderSize)
            {
                ROAD[position] = 2;
            }
            else if (i > j)
            {
                ROAD[position] = 0;
            }
            else if (i > j - borderSize && i <= j)
            {
                ROAD[position] = 1;
            }

            ROAD[(i * WIDTH_ROAD) + WIDTH_ROAD - j - 1] = ROAD[position];
        }
        for (int j = 0; j <= middleLine / 2; j++)
        {
            ROAD[(i * WIDTH_ROAD) + WIDTH_ROAD / 2 - j] = 3;
            ROAD[(i * WIDTH_ROAD) + WIDTH_ROAD / 2 + j] = 3;
        }
    }
}

void showRoad()
{
    for (int i = 0; i < HEIGTH_ROAD; i++)
    {
        for (int j = 0; j < WIDTH_ROAD; j++)
        {
            struct RGB values = TEXTURE[0][ROAD[(i * WIDTH_ROAD) + j]];
            setPixel(i, j, values.r, values.g, values.b);
        }
    }
}
