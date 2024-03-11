#include "triangledist.h"


TriangleDist::TriangleDist() : Walk() {}

TriangleDist::TriangleDist(unsigned width, unsigned height) : Walk(width, height) {}


bool TriangleDist::step() {
    unsigned lower = 1;
    unsigned upper = 10;

    double midpt = (lower + upper) / 2.0;

    double n = upper - lower;

    double prob = (rand() % 100) / 100.0;

    std::cout << "prob: " << prob << std::endl;

    unsigned cbest = lower;
    double probbest = 0;
    probability(lower, upper, 1);
    for (unsigned potential = lower; potential <= upper; potential++) {
        // double cprob = probability(lower, upper, potential);
        // if (std::abs(cprob - prob) < std::abs(probbest - prob)) {
        //     cbest = potential;
        //     probbest = cprob;
        // }
    }


    unsigned prev_x = curr_x;
    unsigned prev_y = curr_y;

    unsigned displacex = cbest;
    unsigned displacey = cbest;


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
    std::cout << exp << std::endl;
    exp *= std::abs(x - midpt);
    std::cout << exp << std::endl;
    exp += 2/n;
    std::cout << exp << std::endl;
    return exp;
}