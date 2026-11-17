
#ifndef INVENTORY_H
#define INVENTORY_H

#include "Product.h"

// Node for the Singly Linked List
struct InventoryNode {
    Product data;
    InventoryNode* next;

    InventoryNode(const Product& product)
        : data(product), next(nullptr) {}
};

// Inventory management class
class Inventory {
private:
    InventoryNode* head;
    int productCount;

public:
    // Constructor and destructor
    Inventory();
    ~Inventory();

    // Prevent accidental shallow copies
    Inventory(const Inventory&) = delete;
    Inventory& operator=(const Inventory&) = delete;

    // Inventory operations
    void addProduct(const Product& product);
    bool deleteProduct(int id);
    bool updateProduct(int id, const Product& updatedProduct);
    void displayProducts() const;
    void displayProductsByBrand(const string& brand) const;

    // Search operations
    InventoryNode* findProductByID(int id) const;
    int getProductCount() const;

    // Access inventory list
    InventoryNode* getHead() const;
};

#endif
