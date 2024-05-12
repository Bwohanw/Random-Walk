#include "triangledist.h"


TriangleDist::TriangleDist() : Walk() {}

TriangleDist::TriangleDist(unsigned width, unsigned height) : Walk(width, height) {}


bool TriangleDist::step() {
    unsigned lower = 1;
    unsigned xupper = std::abs((int)(dest_x) - (int)(curr_x));

    double xmidpt = (lower + xupper) / 2.0;

    double n = xupper - lower;

    double prob = (rand() % 100) / 100.0;


    unsigned cbest = lower;
    double probbest = 0;
    for (unsigned potential = lower; potential <= xupper; potential++) {
        double cprob = probability(lower, xupper, potential);
        if (std::abs(cprob - prob) < std::abs(probbest - prob)) {
            cbest = potential;
            probbest = cprob;
        }
    }


    unsigned displacex = cbest;
    //displace y

    unsigned yupper = std::abs((int)(dest_y) - (int)(curr_y));
    double ymidpt = (lower + yupper) / 2.0;
    n = yupper - lower;

    prob = (rand() % 100) / 100.0;



    cbest = lower;
    probbest = 0;
    for (unsigned potential = lower; potential <= yupper; potential++) {
        double cprob = probability(lower, yupper, potential);
        if (std::abs(cprob - prob) < std::abs(probbest - prob)) {
            cbest = potential;
            probbest = cprob;
        }
    }


    unsigned displacey = cbest;


    unsigned prev_x = curr_x;
    unsigned prev_y = curr_y;



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


    return check_status();

}


double TriangleDist::probability(unsigned lower, unsigned upper, unsigned x) {
    double midpt = (lower + upper) / 2.0;
    double n = (double)upper - lower;
    double exp = -1 * 4.0 / (n*n);
    exp *= std::abs(x - midpt);
    exp += 2.0/n;
    //exp is the value of p(x) at the given point x
    //now we need to get the actual area under p(x) from lower->x


    if (x <= midpt) {//on the left side of the triangle
        double dist = x - lower;
        return exp * dist / 2;
    }

    //right side, we can calculate the probability by subtracting
    double dist = upper-x;
    return 1-(exp * dist/2);
    return exp;
}