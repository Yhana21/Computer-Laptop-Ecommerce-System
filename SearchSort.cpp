#include "SearchSort.h"
#include <iostream>
#include <string>

using namespace std;

// Linear Search
int SearchSort::linearSearch(Product products[], int size, int id) {

    for (int i = 0; i < size; i++) {
        if (products[i].id == id) {
            return i;
        }
    }

    return -1;
}

// Binary Search
// Products must be sorted by ID first.
int SearchSort::binarySearch(Product products[], int size, int id) {

    int left = 0;
    int right = size - 1;

    while (left <= right) {

        int mid = left + (right - left) / 2;

        if (products[mid].id == id) {
            return mid;
        }

        if (products[mid].id < id) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return -1;
}

// Insertion Sort by Price
void SearchSort::sortByPrice(Product products[], int size) {

    for (int i = 1; i < size; i++) {

        Product key = products[i];
        int j = i - 1;

        while (j >= 0 && products[j].price > key.price) {
            products[j + 1] = products[j];
            j--;
        }

        products[j + 1] = key;
    }
}

// Insertion Sort by Stock
void SearchSort::sortByStock(Product products[], int size) {

    for (int i = 1; i < size; i++) {

        Product key = products[i];
        int j = i - 1;

        while (j >= 0 &&
               products[j].stockQuantity > key.stockQuantity) {

            products[j + 1] = products[j];
            j--;
        }

        products[j + 1] = key;
    }
}

// Quick Sort helper
static int partitionByBrand(Product products[], int low, int high) {

    string pivot = products[high].brand;
    int i = low - 1;

    for (int j = low; j < high; j++) {

        if (products[j].brand <= pivot) {

            i++;

            Product temp = products[i];
            products[i] = products[j];
            products[j] = temp;
        }
    }

    Product temp = products[i + 1];
    products[i + 1] = products[high];
    products[high] = temp;

    return i + 1;
}

// Quick Sort implementation
static void quickSortByBrand(Product products[], int low, int high) {

    if (low < high) {

        int pivot = partitionByBrand(products, low, high);

        quickSortByBrand(products, low, pivot - 1);
        quickSortByBrand(products, pivot + 1, high);
    }
}

// Sort products by Brand
void SearchSort::sortByBrand(Product products[], int size) {

    if (size > 1) {
        quickSortByBrand(products, 0, size - 1);
    }
}