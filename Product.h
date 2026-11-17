
#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
using namespace std;

// Product structure for the E-Commerce Inventory System
struct Product {
    int id;
    string name;
    string category;
    string brand;
    double price;
    int stockQuantity;
};

#endif
