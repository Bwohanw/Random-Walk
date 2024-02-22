#include "walk.h"
#include <stdlib.h>
#include <iostream>

using namespace cs225;


Walk::Walk() {
    start_x = 0;
    start_y = 0;
    dest_x = 0;
    dest_y = 0;
    curr_x = start_x;
    curr_y = start_y;
    image = PNG(100,100);
}


Walk::Walk(unsigned width, unsigned height) : image(PNG(width, height)) {
    start_x = 0;
    start_y = 0;
    dest_x = 0;
    dest_y = 0;
    curr_x = start_x;
    curr_y = start_y;
}


void Walk::setStart(unsigned x, unsigned y) {
    start_x = x;
    start_y = y;
    curr_x = x;
    curr_y = y;

    image.getPixel(x,y) = HSLAPixel(140,1,0.5);
}


void Walk::setDest(unsigned x, unsigned y) {
    dest_x = x;
    dest_y = y;

    image.getPixel(x,y) = HSLAPixel(0,1,0.5);
}


void Walk::draw(std::string fileName) {
    image.writeToFile(fileName);
}


bool Walk::step() {
    if (curr_x == dest_x && curr_y == dest_y) return true;
    unsigned prev_x = curr_x;
    unsigned prev_y = curr_y;
    // curr_x += 9;
    // curr_y += 9;


    // drawPath(prev_x, prev_y);

    // return false;



    //walks towards the destination, taking a random number of steps horizontally and vertically, both between 1 and 10

    unsigned displacex = rand() % 100;
    unsigned displacey = rand() % 100;

    //bounds checking

    if (curr_x < dest_x) {//needs to go to the right
        if (curr_x + displacex >= image.width()) curr_x = image.width() != 0 ? image.width() - 1 : 0;
        else curr_x += displacex;
    }
    else {//going to the left
        if (curr_x < displacex) curr_x = 0;
        else curr_x -= displacex;
    }

    if (curr_y < dest_y) {//going down
        if (curr_y + displacey >= image.height()) curr_y = image.height() != 0 ? image.height() - 1 : 0;
        else curr_y += displacey;
    } else {//going up
        if (curr_y < displacey) curr_y = 0;
        else curr_y -= displacey;
    }

    drawPath(prev_x, prev_y);
    std::cout << std::endl;
    std::cout << "displace: " << displacex << " " << displacey << std::endl;
    std::cout << "current: " << curr_x << " " << curr_y << std::endl;

    return check_status();
}


void Walk::drawPath(unsigned prev_x, unsigned prev_y) {
    if (curr_x == start_x && curr_y == start_y) return;
    if (curr_x == dest_x && curr_y == dest_y) return;

    double slope = ((double)curr_y - double(prev_y))/((double)curr_x - (double)prev_x);
    double fracportion = 0;
    image.getPixel(curr_x, curr_y) = HSLAPixel(240, 1, 0.5);
}

bool Walk::check_status() {
    return curr_x == dest_x && curr_y == dest_y;
}