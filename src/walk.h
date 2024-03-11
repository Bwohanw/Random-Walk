#pragma once



#include "../lib/cs225/PNG.h"
#include <iostream>


using namespace cs225;

class Walk {
    public:
    Walk();//creates a walk on a default canvas (100x100)
    
    Walk(unsigned width, unsigned height);//creates a walk on a canvas with the specified size;

    //Only use setStart and setDest once
    void setStart(unsigned x, unsigned y);//specifies where the start point is
    //if not used, startpoint defaults to (0,0)

    void setDest(unsigned x, unsigned y);//specifies where the destination point is
    //if not used, endpoint defaults to (0,0)



    bool check_status();//returns true if at destination, false otherwise
    
    bool step();//one iteration of the random walk, and updates the canvas with its path taken
    //can walk in any direction, returns true if the walk reaches the destination, false otherwise


    void draw(std::string fileName);



    protected:
    void drawPath(unsigned prev_x, unsigned prev_y);//draws in the path taken from the previous point to the new curr_x, curr_y

    // private:
    unsigned start_x;
    unsigned start_y;
    unsigned dest_x;
    unsigned dest_y;

    unsigned curr_x;
    unsigned curr_y;

    PNG image;



    bool touchNeighbor(int x, int y, int goalx, int goaly);
};