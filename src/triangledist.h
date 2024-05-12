#pragma once

#include "./walk.h"


class TriangleDist : public Walk {

    /*
    uses a triangle distribution (by that i mean a probability distribution resembling -|x|)
    centered around the median between the lower and upper bound.
    
    if we have lower bound of l and upper bound h, and we let n=h-l, we will have probability distribution
    of
    P(x) = -(2/n)^2 * |x - (h + l)/2| + 2/n
    
    
    we will find a distance to travel that satisfies this probability distribution first uniformly selecting
    a probability p (between 0 and 1), which we will then find a corresponding distance k such that
    the integral of P(x)dx evaluated from lower->k is close to p, since k must be an integer.
    */
    public:

    TriangleDist();
    TriangleDist(unsigned width, unsigned height);


    bool step(); //defaults to between 1 and distance to the goal;

    bool step(unsigned xlower, unsigned xupper, unsigned ylower, unsigned yupper);

    bool step(unsigned xupper, unsigned yupper);


    private:

    double probability(unsigned lower, unsigned higher, unsigned x);
};