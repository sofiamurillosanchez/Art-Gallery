//
// Created by Sofia  Murillo on 1/27/22.
//

#include "painting.h"

painting::painting() {
    id = 0;
    width = 0;
    height = 0;
    price = 0;
}

painting::painting(int i, int w, int h, double p) {
    id = i;
    width = w;
    height = h;
    price = p;
}

void painting::set_id(int i) {
    id = i;
}

int painting::get_id() {
    return id;
}

void painting::set_price(double p) {
    price = p;
}

double painting::get_price() {
    return price;
}

void painting::set_width(int w) {
    width = w;
}

int painting::get_width() {
    return width;
}

void painting::set_height(int h) {
    height = h;
}

int painting::get_height() {
    return height;
}