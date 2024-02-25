#include "walk.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>

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


    double slope = std::abs(((double)curr_y - double(prev_y))/((double)curr_x - (double)prev_x));
    double fracportion = 0.0;
    std::cout << "slope: " << slope << std::endl;
    std::cout << std::endl;

    HSLAPixel pix(240, 1, 0.5);

    unsigned temp_x = prev_x;
    unsigned temp_y = prev_y;

    //check if you move right or left
    if (curr_x >= prev_x) {//move right, paint from prev_x,prev_y->(curr_x,curr_y)

        bool touchedGoal = false;
        for (unsigned i = prev_x; i < curr_x; i++) {
            fracportion += slope;
            unsigned numpixels = std::floor(fracportion);
            //move up or down
            if (curr_y >= prev_y) {//paint down
                for (unsigned j = 0; j <= numpixels && prev_y + j < curr_y; j++) {
                    //only color if you're still far from the destination pixel
                    if (!touchedGoal) image.getPixel(i, prev_y + j) = pix;
                    if (!touchedGoal && touchNeighbor(i,prev_y + j, curr_x, curr_y)) touchedGoal = true;
                }
                prev_y += numpixels;
                if (prev_y >= image.height()) prev_y = image.height() - 1;
            } else {//paint up
                for (unsigned j = 0; j <= numpixels && prev_y >= j; j++) {
                    if (!touchedGoal) image.getPixel(i, prev_y - j) = pix;
                    if (!touchedGoal && touchNeighbor(i,prev_y-j,curr_x,curr_y)) touchedGoal = true;
                }
                prev_y = prev_y >= numpixels ? prev_y - numpixels : 0;
            }

            fracportion = fracportion - numpixels;
        }

        //take care of the remaining y distance towards the goal
        //we've already drawn pixels until curr_x, so we just need to draw vertical pixels until reaching curr_y

        if (!touchedGoal) {
            if (curr_y >= prev_y) {
                while (prev_y < curr_y) {
                    image.getPixel(curr_x, prev_y) = pix;
                    prev_y++;
                }
            } else {
                while (prev_y > curr_y) {
                    image.getPixel(curr_x, prev_y) = pix;
                    prev_y--;
                }
            }
        }
    } else {//move left
        bool touchedGoal = false;
        for (unsigned i = prev_x; i > curr_x; i--) {
            fracportion += slope;
            unsigned numpixels = std::floor(fracportion);

            if (curr_y >= prev_y) {
                for (unsigned j = 0; j <= numpixels && prev_y + j < curr_y; j++) {
                    if (!touchedGoal) image.getPixel(i, prev_y + j) = pix;
                    if (!touchedGoal && touchNeighbor(i,prev_y + j, curr_x, curr_y)) touchedGoal = true;
                }
                prev_y += numpixels;
                if (prev_y >= image.height()) prev_y = image.height() - 1;
            } else {
                for (unsigned j = 0; j <= numpixels && prev_y >= j; j++) {
                    if (!touchedGoal) image.getPixel(i, prev_y - j) = pix;
                    if (!touchedGoal && touchNeighbor(i,prev_y-j,curr_x,curr_y)) touchedGoal = true;
                }
                prev_y = prev_y >= numpixels ? prev_y - numpixels : 0;
            }

            fracportion -= numpixels;
        }
        if (!touchedGoal) {
            if (curr_y >= prev_y) {
                while (prev_y < curr_y) {
                    image.getPixel(curr_x, prev_y) = pix;
                    prev_y++;
                }
            } else {
                while (prev_y > curr_y) {
                    image.getPixel(curr_x, prev_y) = pix;
                    prev_y--;
                }
            }
        }
    }

    //recolors the start/dest in case they got colored over
    image.getPixel(curr_x, curr_y) = HSLAPixel(100, 1, 0.5);
    image.getPixel(temp_x, temp_y) = HSLAPixel(100, 1, 0.5);
}

bool Walk::check_status() {
    return curr_x == dest_x && curr_y == dest_y;
}


bool Walk::touchNeighbor(int x, int y, int goalx, int goaly) {
    if (x == goalx) {
        return std::abs(y - goaly) <= 1;
    }
    if (y == goaly) {
        return std::abs(x-goalx) <= 1;
    }
    return (std::abs(x-goalx) + std::abs(y-goaly)) <= 2;
}