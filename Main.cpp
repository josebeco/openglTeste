#include "Screen.h"
#include "Track.h"
#define WIDTH 480
#define HEIGHT 360


int main(int argc, char **argv)
{
    createRoad(WIDTH, 210, 9, 5, 2, 1, 15);
    init(WIDTH, HEIGHT);
    start(argc, argv); 
}

void cycle() 
{
    showRoad(0, 5);
}
