#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

#include "Product.h"

// Node for Doubly Linked List
struct CartNode {
    Product data;
    int quantity;

    CartNode* next;
    CartNode* prev;

    CartNode(const Product& product, int qty)
        : data(product), quantity(qty),
          next(nullptr), prev(nullptr) {}
};

// Shopping Cart Management
class ShoppingCart {
private:
    CartNode* head;
    CartNode* tail;
    int itemCount;

public:
    // Constructor and Destructor
    ShoppingCart();
    ~ShoppingCart();

    // Prevent shallow copying
    ShoppingCart(const ShoppingCart&) = delete;
    ShoppingCart& operator=(const ShoppingCart&) = delete;

    // Cart Operations
    void addToCart(const Product& product, int quantity);
    bool removeFromCart(int productID);
    void displayCart() const;

    // Cart Information
    double calculateTotal() const;
    int getItemCount() const;
    bool isEmpty() const;

    // Access cart
    CartNode* getHead() const;
};

#endif