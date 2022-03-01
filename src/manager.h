//
// Created by Sofia  Murillo on 1/27/22.
//

#ifndef INC_22S_PA01_MATERIAL_GWORLS_MANAGER_H
#define INC_22S_PA01_MATERIAL_GWORLS_MANAGER_H
#include <fstream>
#include <vector>
#include "algos.h"

using namespace std;

class manager {
public:
    manager();

    // Read the file input from the file passed in (which will be read in main through argv)
    void read_input(fstream&, string&);

    // Call the algorithm and output functions from invoking variable passed in
    void call_functions(algos, vector<painting>&, string&);
};


#endif //INC_22S_PA01_MATERIAL_GWORLS_MANAGER_H
