//
// Created by Sofia  Murillo on 1/27/22.
//

#ifndef INC_22S_PA01_MATERIAL_GWORLS_PAINTING_H
#define INC_22S_PA01_MATERIAL_GWORLS_PAINTING_H

using namespace std;

class painting {
private:
    // Track the ID of the painting
    int id;

    // Width and Height of the painting
    int width;
    int height;

    // Price of the painting
    double price;

public:
    painting();
    painting(int, int, int, double);

    // Getters and setters for the paintings
    void set_id(int);
    int get_id();

    void set_width(int);
    int get_width();

    void set_height(int);
    int get_height();

    void set_price(double);
    double get_price();
};


#endif //INC_22S_PA01_MATERIAL_GWORLS_PAINTING_H
