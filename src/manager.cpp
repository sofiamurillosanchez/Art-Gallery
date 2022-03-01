//
// Created by Sofia  Murillo on 1/27/22.
//

#include "manager.h"

manager::manager() {}

void manager::read_input(fstream& input, string& inputFileName){
    int width_wall = 0;
    int numpaintings  = 0; // total number of paintings
    int id = 0; // id of painting
    double price = 0;
    int width_painting = 0;
    int height_painting = 0;
    int arbitrary = 0; // While file reading, height is arbitrary, so it will be held in this variable

    algos a; // Invoking object
    vector<painting> paintings; // To set paintings vector in algos class

    input >> width_wall;
    a.set_wall_width(width_wall); // Set width of wall in invoking variable (and height, just in case)
    input >> arbitrary; // Height of wall
    a.set_wall_height(arbitrary);

    input >> numpaintings;

    while(!input.eof()){
        input >> id;
        input >> price;
        input >> width_painting;
        input >> height_painting;

        // Create painting object with the id, width, height, and price
        painting p(id, width_painting, height_painting, price);

        // Add painting object to the vector of paintings
        paintings.emplace_back(p);
    }

    // Once the vector is fully created (file reading is complete), set the vector of paintings in the invoking object
    // equal to the vector recently created
    a.set_painting_original(paintings);

    // Call the functions on the invoking variable to run the algorithms
    call_functions(a, paintings, inputFileName);

    input.close();
}

// Call the algorithm functions from invoking variable passed in

void manager::call_functions(algos a, vector<painting>& paintings, string& inputFileName) {
    //pass in input file name to each function
    if(paintings.size() <= 20){
        a.brute_force(inputFileName);
    }

    a.expensive_first(inputFileName);

    if (paintings.size() > 10) {
        a.heuristic(inputFileName);
    }
}