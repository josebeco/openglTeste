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

void createRoad(int width, int heigth, int borderSize, int middleLine, int endBorderSize, int endMiddleLine)
{
    HEIGTH_ROAD = heigth;
    WIDTH_ROAD = width;
    ROAD = new short[HEIGTH_ROAD * WIDTH_ROAD];

    const int BORDER_RATIO = HEIGTH_ROAD / (borderSize - endBorderSize);
    const int MIDDLE_RATIO = 2 * HEIGTH_ROAD / (middleLine - endMiddleLine); // Diminui de dois em dois

    borderSize++; // negar 0 % ratio
    middleLine +=2; // negar 0 % ratio

    for (int i = 0; i < HEIGTH_ROAD; i++)
    {
        if (i % BORDER_RATIO == 0)
            borderSize--;

        if (i % MIDDLE_RATIO == 0)
            middleLine -= 2;

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

        ROAD[(i * WIDTH_ROAD) + WIDTH_ROAD / 2] = 3; // set middle line center

        for (int j = 1; j <= middleLine / 2; j++)
        {
            ROAD[(i * WIDTH_ROAD) + WIDTH_ROAD / 2 - j] = 3;
            ROAD[(i * WIDTH_ROAD) + WIDTH_ROAD / 2 + j] = 3;
        }
    }
}

void showRoad()
{
    int c = 1;
    for (int i = 0; i < HEIGTH_ROAD; i++)
    {
        if(i % 15 == 0){
            c ^= 1;
        }

        for (int j = 0; j < WIDTH_ROAD; j++)
        {
            struct RGB values = TEXTURE[c][ROAD[(i * WIDTH_ROAD) + j]];
            setPixel(i, j, values.r, values.g, values.b);
        }
    }
}
