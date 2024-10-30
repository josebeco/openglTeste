
struct RGB
{
    int r;
    int g;
    int b;
};
const struct RGB TEXTURE[][4] = {{{0, 255, 0}, {255, 0, 0}, {128, 128, 128}, {255, 255, 255}}, {{0, 175, 0}, {255, 255, 255}, {75, 75, 75}, {75, 75, 75}}}; // 0 grama, 1 borda rua, 2 estrada, 3- faixa
int *ROAD;
int HEIGTH;
int WIDTH;

void createRoad(int h, int w, int endLength, int borderSize)
{
    HEIGTH = h;
    WIDTH = w;
    ROAD = new int[HEIGTH * WIDTH];
    for (int i = 0; i < HEIGTH; i++)
    {
        for (int j = 0; j <= WIDTH / 2; j++)
        {
            int position = (i * WIDTH) + j;
            if (i <= j - borderSize)
            {
                ROAD[position] = 0;
            }
            else if (i > j)
            {
                ROAD[position] = 2;
            }
            else if (i > j - borderSize && i <= j)
            {
                ROAD[position] = 1;
            }
            else
            {
                ROAD[position] = 3;
            }

            ROAD[(i * WIDTH) + WIDTH - j - 1] = ROAD[position];
        }
    }
}
