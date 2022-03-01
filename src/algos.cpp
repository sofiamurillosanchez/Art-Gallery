//
// Created by Sofia  Murillo on 1/27/22.
// References:
// QuickSort Implementation - https://slaystudy.com/c-vector-quicksort/
//

#include "algos.h"
#include <vector>
#include <fstream>
#include <cmath>

// Set paintings and original vector to vector of paintings passed in (which will be created during file reading)
void algos::set_painting_original(vector<painting> p) {
    paintings = p;
    original = p;
}

// Getters and setters for wall width and height
void algos::set_wall_width(int w) {
    wall_width = w;
}

int algos::get_wall_width() {
    return wall_width;
}

void algos::set_wall_height(int h) {
    wall_height = h;
}

int algos::get_wall_height() {
    return wall_height;
}

// Brute force algorithm. Implements recursion to go through all the combinations of paintings.

void algos::brute_force(string& inputFileName) {
    double maxTotalPrice = 0;
    double currPrice = 0;
    int currWidth = 0;
    paintings.clear();
    vector<painting> bestCombination;

    // here, k represents the # of elements you want in this subset
    // thus, to generate all possible subsets, we need to use k <= size of list
    for (int k = 0; k <= original.size(); k++) {
        recursive_combos(maxTotalPrice, currPrice, currWidth, 0, k, bestCombination);
    }

    output_brute(inputFileName, bestCombination, maxTotalPrice);
    reset();
}

// Brute Force Recursive Function to generate combinations
// requires the maximum Total Price found thus far, the current price, the current width, the offset,
// the length of the combination, and the best Combination vector in the parent function
// Referenced Stack Overflow: https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
void algos::recursive_combos(double& maxTotalPrice, double& currPrice, int& currWidth, int offset, int k, vector<painting>& bestCombination) {
    if (k == 0) {
        // if the full combination is smaller than the size of the wall
        // and the new price is greater than the previous,
        // then make this the new best combination and update maxTotalPrice
        if (wall_width > currWidth) {
            if (currPrice > maxTotalPrice) {
                bestCombination = paintings;
                maxTotalPrice = currPrice;
            }
        }

        // removing the price + widths from the parameters
        if (!paintings.empty()) {
            currPrice -= paintings.back().get_price();
            currWidth -= paintings.back().get_width();
        }

        return;
    }

    // here, we track the prices and widths of combinations
    // as well as our recursive calls
    for (int i = offset; i <= original.size() - k; i++) {
        // if we are starting with a newCombination vector that is empty
        // reset the parameters to 0
        if (offset == 0) {
            currPrice = 0;
            currWidth = 0;
        }
        // add paintings + their respective prices and widths
        paintings.push_back(original.at(i));
        currPrice += original.at(i).get_price();
        currWidth += original.at(i).get_width();

        // recursive call, note the offset becomes (i + 1) (start at next element)
        // and the k (length of new subset to generate) becomes (k - 1)
        recursive_combos(maxTotalPrice, currPrice, currWidth, i + 1, k - 1, bestCombination);

        // remove the latest painting
        if (!paintings.empty()) {
            paintings.pop_back();
        }
    }
}

// Brute force output function, to be called by manager class
void algos::output_brute(string& inputFileName, vector<painting>& bestCombination, double& maxTotalPrice) {
    long totalValue = lround(maxTotalPrice); // Total value of the paintings in bestCombination vector
    cout << "Writing Brute Force Output to file" << endl;

    // output to "*inputFileName*-bruteforce.txt"
    ofstream outputFile;
    string outputFileName = inputFileName + "-bruteforce.txt";
    outputFile.open(outputFileName);

    if (outputFile.is_open()) {
        // continue to write to file
        // first line contains a single integer - total $$ value of wall
        outputFile << totalValue << "\n";
        // each additional line has 4 integers, each separated by a space:
        // 1) painting ID, 2) $ of painting, 3) painting width 4) painting height
        for (int i = 0; i < bestCombination.size(); i++) {
            outputFile << bestCombination.at(i).get_id() << " ";
            outputFile << lround(bestCombination.at(i).get_price()) << " ";
            outputFile << bestCombination.at(i).get_width() << " ";
            outputFile << bestCombination.at(i).get_height() << "\n";
        }
        // NOTE: I've implemented some rounding b/c our sample files had doubles as prices
        // and double -> int conversion is prone to errors, to I tried to mitigate them by rounding
        // that way the output file's numbers add up properly
    } else {
        // if outputFile fails to open, don't try to write anything
        // send error message to console
        cout << "Unable to write to " << outputFileName << "!" << endl;
    }

    // close outputFile when finished
    outputFile.close();
}

// Expensive first algorithm. Quick sorts all the paintings by price and places them on the wall until they
// exceed the width of the wall (on the first case where it does). Then, it will remove the most recently placed painting
// since that's the one that "broke" the wall.
void algos::expensive_first(string& inputFileName) {
    // Quicksort requires the end parameter to be size - 1 (needs an index)
    QuickSort(paintings, 0, paintings.size() - 1);
    determineLayout(paintings); // Set paintings equal to the vector returned after determining layout
    output_expensive(inputFileName);
    reset();
}

// Referenced: https://slaystudy.com/c-vector-quicksort/ for QuickSort implementation
void algos::QuickSort(vector<painting>& p, int start, int end) {
    if(start<end){
        int part = partition(p,start,end);
        QuickSort(p,start,part-1);
        QuickSort(p,part+1,end);
    }
}

int algos::partition(vector<painting> & p, int start, int end) {
    int pivot = end;
    int j = start;
    for(int i=start;i<end;++i){
        if(p[i].get_price() > p[pivot].get_price()){
            swap(p[i],p[j]);
            ++j;
        }
    }
    swap(p[pivot],p[j]);
    return j;
}



// Expensive first output functions, to be called by manager class
void algos::output_expensive(string& inputFileName) {
    cout << "Writing Most-Expensive-First Output to file" << endl;

    // output to "*inputFileName*-highvalue.txt"
    ofstream outputFile;
    string outputFileName = inputFileName + "-highvalue.txt";
    outputFile.open(outputFileName);

    if (outputFile.is_open()) {
        // continue to write to file
        // first line contains a single integer - total $$ value of wall
        double totalValue = 0;
        for (int i = 0; i < paintings.size(); i++) {
            totalValue += paintings.at(i).get_price();
        }

        outputFile << lround(totalValue) << "\n";
        // each additional line has 4 integers, each separated by a space:
        // 1) painting ID, 2) $ of painting, 3) painting width 4) painting height
        for (int i = 0; i < paintings.size(); i++) {
            outputFile << paintings.at(i).get_id() << " ";
            outputFile << lround(paintings.at(i).get_price()) << " ";
            outputFile << paintings.at(i).get_width() << " ";
            outputFile << paintings.at(i).get_height() << "\n";
        }
        // NOTE: I've implemented some rounding b/c our sample files had doubles as prices
        // and double -> int conversion is prone to errors, to I tried to mitigate them by rounding
        // that way the output file's numbers add up properly
    } else {
        // if outputFile fails to open, don't try to write anything
        // send error message to console
        cout << "Unable to write to " << outputFileName << "!" << endl;
    }

    // close outputFile when finished
    outputFile.close();
}

// The heuristic algorithm, basically groups all of the paintings into different "walls"
// then takes the top 3 walls (by value) and compares them and makes switches between their paintings
// until the optimal solution is reached
void algos::heuristic(string& inputFileName) {
    // instantiate variables
    int size_wall = 0;
    double price_wall = 0;
    vector<painting> wall;
    double most_expensive = 0;
    double second_most = 0;
    double third_most = 0;

    // Loop through the paintings
    for(int i = 0; i<paintings.size(); i++){
        // Create each wall
        if(size_wall + paintings.at(i).get_width() < wall_width){
            wall.push_back(paintings.at(i));
            size_wall += paintings.at(i).get_width();
            price_wall += paintings.at(i).get_price();
        } else{
            // Insert the wall into a map where the key is the value of the wall
            heuristic_groups.insert(pair<double, vector<painting>>(price_wall, wall));
            // Create logic for determining the top wall
            if(price_wall > most_expensive){
                double temp1 = most_expensive;
                double temp2 = second_most;

                // adjust the other walls accordingly
                most_expensive = price_wall;

                second_most = temp1;

                third_most = temp2;
            } else if(price_wall > second_most){ // Logic for determining second most expensive wall
                double temp1 = second_most;

                // adjust the other walls accordingly
                second_most = price_wall;

                third_most = temp1;
            } else if(price_wall > third_most){ // Logic for determining third most expensive wall
                third_most = price_wall;
            }

            wall.clear(); // Clear the wall vector to make room for a new wall to be created
            size_wall = 0;
            price_wall = 0;
        }
    }

    // Create the vectors containing the top three walls by finding their values from the map (using the stored values)
    vector<painting> first_most_paintings = heuristic_groups.find(most_expensive)->second;
    vector<painting> second_most_paintings = heuristic_groups.find(second_most)->second;
    vector<painting> third_most_paintings = heuristic_groups.find(third_most)->second;

    // QuickSort these walls into descending order (won't be as time consuming as quicksorting all of the paintings)
    QuickSort(first_most_paintings, 0, first_most_paintings.size()-1);
    QuickSort(second_most_paintings, 0, second_most_paintings.size()-1);
    QuickSort(third_most_paintings, 0, third_most_paintings.size() -1);

    // To keep track of paintings already checked in the comparison
    int trackTopSecond = 0;
    int trackTopThird = 0;

    // Compare the most expensive paintings in second and third to least expensive of first
    for(int i = first_most_paintings.size() - 1; i > 0; i--){
        painting tempFirst = first_most_paintings.at(i);
        painting tempSecond = second_most_paintings.at(trackTopSecond);
        painting tempThird = third_most_paintings.at(trackTopThird);

        // Check to see if price is greater and size is smaller, if so, then replace with that painting
        if(tempSecond.get_price() > tempFirst.get_price() && trackTopSecond < second_most_paintings.size()-1){
            if(tempSecond.get_width() <= tempFirst.get_width()){
                first_most_paintings.at(i) = tempSecond;
                trackTopSecond++;
            }
        } else if(tempThird.get_price() > tempFirst.get_price() && trackTopThird < third_most_paintings.size() - 1){ // do the same for third
            if(tempThird.get_width() <= tempFirst.get_width()){
                first_most_paintings.at(i) = tempThird;
                trackTopThird++;
            }
        } else{
            i = 1; // Break the loop because if the most expensive paintings of the second and third aren't greater
                    // than the least expensive of the first, then there is no longer a need to compare.
        }
    }

    // set global paintings to the top paintings vector produced
    paintings = first_most_paintings;
    output_heuristic(inputFileName); // call output
    reset();
}

// output function for heuristic algorithm
void algos::output_heuristic(string& inputFileName) {
    cout << "Writing Heuristic Output to file" << endl;

    // output to "*inputFileName*-highvalue.txt"
    ofstream outputFile;
    string outputFileName = inputFileName + "-heuristic.txt";
    outputFile.open(outputFileName);

    if (outputFile.is_open()) {
        // continue to write to file
        // first line contains a single integer - total $$ value of wall
        double totalValue = 0;
        for (int i = 0; i < paintings.size(); i++) {
            totalValue += paintings.at(i).get_price();
        }

        outputFile << lround(totalValue) << "\n";
        // each additional line has 4 integers, each separated by a space:
        // 1) painting ID, 2) $ of painting, 3) painting width 4) painting height
        for (int i = 0; i < paintings.size(); i++) {
            outputFile << paintings.at(i).get_id() << " ";
            outputFile << lround(paintings.at(i).get_price()) << " ";
            outputFile << paintings.at(i).get_width() << " ";
            outputFile << paintings.at(i).get_height() << "\n";
        }
        // NOTE: I've implemented some rounding b/c our sample files had doubles as prices
        // and double -> int conversion is prone to errors, to I tried to mitigate them by rounding
        // that way the output file's numbers add up properly
    } else {
        // if outputFile fails to open, don't try to write anything
        // send error message to console
        cout << "Unable to write to " << outputFileName << "!" << endl;
    }

    // close outputFile when finished
    outputFile.close();
}

// Takes the vector of paintings and goes through them to make sure that they fit the wall. The resulting vector is the wall
void algos::determineLayout(vector<painting> & p) {
    vector<painting> result;
    int sum_width = 0;
    int idx = 0;

    // TODO: add check to skip paintings and try adding the next most expensive if a painting doesn't fit
    while(sum_width < wall_width){
        result.emplace_back(p.at(idx));
        idx++;
        // Add the width of the painting just added to the sum (keeping track of the paintings added to the wall)
        sum_width += p.at(idx).get_width();
    }
    p = result;
}

// Resets paintings algorithm to its original form. Called at the end of each algorithm function.
void algos::reset() {
    paintings = original;
}