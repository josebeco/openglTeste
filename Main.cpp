#include "Screen.h"
#include "Track.h"
#define WIDTH 480
#define HEIGHT 360
int c = 0;
int f []= {255, 0 , 0};

int main(int argc, char **argv)
{
    init(WIDTH, HEIGHT);
    start(argc, argv);
}

void cycle() 
{
    createRoad(WIDTH, 210, 9, 5, 2, 0);
    showRoad();
}
