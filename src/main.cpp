//
// Created by Eileen Garcia on 1/24/2022.
//

#include <iostream>
#include <fstream>
#include "manager.h"
#include <string>

int main(int argc, char** argv) {

    if (argc < 2) {
        cout << "Error: Too Few Arguments. Please enter one input file." << endl;
        cout << "For example: input.txt" << endl;
        return 1;
    } else if (argc > 2) {
        cout << "Error: Too Many Arguments. Please enter ONLY one input file." << endl;
        cout << "For example: input.txt" << endl;
        return 1;
    }

    fstream input(argv[1]); // Create fstream object from program argument

    // Store input file name for output file creation
    // Reference: https://stackoverflow.com/questions/8520560/get-a-file-name-from-a-path
    // Referenced for substr() use in storing the file name without the file extension
    string inputFilePath(argv[1]);
//    string inputFileName = inputFilePath.substr(inputFilePath.find_last_of('/') + 1);
    inputFilePath = inputFilePath.substr(0, inputFilePath.find_last_of('.'));

    manager manage; // Invoking variable
    cout << "Reading input" << endl;
    // Pass inputFileName to read_input() since the function calls the algorithms
    // which in turn, call the output functions for each algorithm
    manage.read_input(input, inputFilePath);

    cout << "Done!" << endl;

    return 0;
}