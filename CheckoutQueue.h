#ifndef CHECKOUT_QUEUE_H
#define CHECKOUT_QUEUE_H

#include "Product.h"

// Node for Checkout Queue
struct CheckoutNode {
    Product data;
    int quantity;
    CheckoutNode* next;

    CheckoutNode(const Product& product, int qty)
        : data(product), quantity(qty), next(nullptr) {}
};

// Checkout Queue Management
class CheckoutQueue {
private:
    CheckoutNode* front;
    CheckoutNode* rear;
    int queueSize;

public:
    // Constructor and Destructor
    CheckoutQueue();
    ~CheckoutQueue();

    // Prevent shallow copying
    CheckoutQueue(const CheckoutQueue&) = delete;
    CheckoutQueue& operator=(const CheckoutQueue&) = delete;

    // Queue Operations
    void enqueue(const Product& product, int quantity);
    bool dequeue(Product& product, int& quantity);
    void displayQueue() const;

    // Queue Information
    bool isEmpty() const;
    int getQueueSize() const;
};

#endif