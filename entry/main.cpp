#include <iostream>
#include "../src/walk.h"
#include "../lib/cs225/PNG.h"


//for myself: c++ entry/main.cpp lib/cs225/HSLAPixel.cpp lib/cs225/PNG.cpp lib/lodepng/lodepng.cpp ./src/walk.cpp
//you might have to delete the executable

using namespace cs225;

int main() {

    Walk walk;
    walk.setStart(0,0);
    walk.setDest(49,49);

    for (unsigned i = 0; i < 3; i++) walk.step();

    walk.draw("output.png");

    // png.writeToFile("./output.png");
    return 0;
}