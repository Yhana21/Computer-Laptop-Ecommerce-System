#ifndef SEARCH_SORT_H
#define SEARCH_SORT_H

#include "Product.h"

// Searching and Sorting class
class SearchSort {
public:

    // Linear Search
    static int linearSearch(
        Product products[],
        int size,
        int id
    );

    // Binary Search
    static int binarySearch(
        Product products[],
        int size,
        int id
    );

    // Sort products by price
    static void sortByPrice(
        Product products[],
        int size
    );

    // Sort products by stock quantity
    static void sortByStock(
        Product products[],
        int size
    );

    // Sort products by brand
    static void sortByBrand(
        Product products[],
        int size
    );
};

#endif