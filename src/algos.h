//
// Created by Sofia  Murillo on 1/27/22.
//

#ifndef INC_22S_PA01_MATERIAL_GWORLS_ALGOS_H
#define INC_22S_PA01_MATERIAL_GWORLS_ALGOS_H

#include <iostream>
#include <vector>
#include <map>
#include "painting.h"

using namespace std;

class algos {
private:
    vector<painting> paintings;
    map<double, vector<painting>> heuristic_groups;

    // Same as paintings vector, simply used as a way to preserve the original vector's order
    vector<painting> original;
    int wall_width;
    int wall_height;

public:
    void set_painting_original(vector<painting>);
    void set_wall_width(int);
    int get_wall_width();
    void set_wall_height(int); // TODO: Arbitrary, but might be needed for output purposes
    int get_wall_height();

    void brute_force(string&);
    void recursive_combos(double&, double& currPrice, int& currWidth, int, int, vector<painting>&);
    void output_brute(string&, vector<painting>&, double&);

    void expensive_first(string&);
    int partition(vector<painting>&, int, int);
    void QuickSort(vector<painting>&, int, int);
    void output_expensive(string&);

    void heuristic(string&);
    void output_heuristic(string&);


    void determineLayout(vector<painting>&);
    // Resets the paintins vector to its original form after sorting
    void reset();
};


#endif //INC_22S_PA01_MATERIAL_GWORLS_ALGOS_H
