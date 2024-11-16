#include "Screen.h"

struct RGB
{
    short r;
    short g;
    short b;
};
const struct RGB TEXTURE[][4] = {{{0, 255, 0}, {255, 0, 0}, {128, 128, 128}, {255, 255, 255}},
                                 {{0, 175, 0}, {255, 255, 255}, {110, 110, 110}, {110, 110, 110}}};
// 0 grama, 1 borda rua, 2 estrada, 3- faixa

struct Section
{
    int length;
    short turn_rate;
    short end_x;
    short rate_rate;
};
const struct Section Track[] = {{300, 0, 0, 1}, {200, 2, 0, 2}};

short *ROAD;
int HEIGTH_ROAD;
int WIDTH_ROAD;
int road_z = 0;
int section_index = 0;
int TEXTURE_RATE;

void createRoad(int width, int heigth, int borderSize, int middleLine, int endBorderSize, int endMiddleLine, int textureRate)
{
    HEIGTH_ROAD = heigth;
    WIDTH_ROAD = width;
    TEXTURE_RATE = textureRate;
    ROAD = new short[HEIGTH_ROAD * WIDTH_ROAD];

    const int BORDER_RATIO = HEIGTH_ROAD / (borderSize - endBorderSize);
    const int MIDDLE_RATIO = 2 * HEIGTH_ROAD / (middleLine - endMiddleLine); // Diminui de dois em dois

    borderSize++;    // negar 0 % ratio
    middleLine += 2; // negar 0 % ratio

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

void showRoad(int x_shift, int z_increase) // x é 0 no centro
{
    road_z += z_increase;
    road_z % (TEXTURE_RATE * 2);
    for (int i = 0; i < HEIGTH_ROAD; i++)
    {
        for (int j = 0; j < WIDTH_ROAD; j++)
        {
            int position = (i * WIDTH_ROAD) + j + x_shift;
            int color = (road_z + i) % (TEXTURE_RATE * 2) >= TEXTURE_RATE;
            
            struct RGB values = (j + x_shift < 0 || j + x_shift >= WIDTH_ROAD) ? TEXTURE[color][0] : TEXTURE[color][ROAD[position]];
            setPixel(i, j, values.r, values.g, values.b);
        }
    }
}
