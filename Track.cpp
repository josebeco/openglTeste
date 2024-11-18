#include "Screen.h"
#include <iostream>
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
    int end_z;
    short turn_rate;
    short end_x;
};
const struct Section Track[] = {{1000, 0, 0}, {1500, 1, 0}};
const int track_length = 2;

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
    if (road_z > Track[section_index].end_z)
    {
        if (section_index + 1 >= track_length)
        {
            // acabo a pista TODO
            return;
        }

        section_index++;
    }

    int med_section_index = section_index;
    struct Section current_section = Track[med_section_index];

    int turn_shift = 0;
    int mid_point = ((med_section_index > 0) ? Track[med_section_index - 1].end_z : 0) + (current_section.end_z - ((med_section_index > 0) ? Track[med_section_index - 1].end_z : 0)) / 2;

    for (int i = 0; i < HEIGTH_ROAD; i++)
    {
        if (med_section_index >= track_length)
        {
            turn_shift = 0;
            current_section = {0, 0, 0};
        }
        else if (road_z + i > current_section.end_z)
        {
            med_section_index++;
            turn_shift = 0;
            current_section = Track[med_section_index];
            mid_point = ((med_section_index > 0) ? Track[med_section_index - 1].end_z : 0) + ((current_section.end_z - (med_section_index > 0) ? Track[med_section_index - 1].end_z : 0) / 2);
        }

        turn_shift += current_section.turn_rate * ((road_z + i < mid_point) ? 1 : -1);
        std::cout << turn_shift << std::endl;
        for (int j = 0; j < WIDTH_ROAD; j++)
        {
            int x_cordinate = j + x_shift + turn_shift;
            int color = (road_z + i) % (TEXTURE_RATE * 2) >= TEXTURE_RATE;

            struct RGB values = (x_cordinate < 0 || x_cordinate >= WIDTH_ROAD || med_section_index >= track_length) ? TEXTURE[color][0] : TEXTURE[color][ROAD[(i * WIDTH_ROAD) + x_cordinate]];
            setPixel(i, j, values.r, values.g, values.b);
        }
    }
}
