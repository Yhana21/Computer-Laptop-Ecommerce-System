#include "CheckoutQueue.h"
#include <iostream>
using namespace std;

// Constructor
CheckoutQueue::CheckoutQueue() {
    front = nullptr;
    rear = nullptr;
    queueSize = 0;
}

// Destructor
CheckoutQueue::~CheckoutQueue() {
    while (front != nullptr) {
        CheckoutNode* temp = front;
        front = front->next;
        delete temp;
    }

    rear = nullptr;
    queueSize = 0;
}

// Add checkout request to the queue
void CheckoutQueue::enqueue(const Product& product, int quantity) {
    if (quantity <= 0) {
        cout << "Invalid quantity. Please enter a quantity greater than zero.\n";
        return;
    }

    CheckoutNode* newNode = new CheckoutNode(product, quantity);

    if (isEmpty()) {
        front = newNode;
        rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }

    queueSize++;

    cout << "Checkout request added successfully!\n";
}

// Process the first checkout request
bool CheckoutQueue::dequeue(Product& product, int& quantity) {
    if (isEmpty()) {
        cout << "Checkout queue is empty.\n";
        return false;
    }

    CheckoutNode* temp = front;

    product = temp->data;
    quantity = temp->quantity;

    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    queueSize--;

    return true;
}

// Display pending checkout requests
void CheckoutQueue::displayQueue() const {
    if (isEmpty()) {
        cout << "\nCheckout queue is empty.\n";
        return;
    }

    CheckoutNode* current = front;

    cout << "\n===== CHECKOUT QUEUE =====\n";

    while (current != nullptr) {
        cout << "Product ID: " << current->data.id << endl;
        cout << "Product Name: " << current->data.name << endl;
        cout << "Brand: " << current->data.brand << endl;
        cout << "Quantity: " << current->quantity << endl;
        cout << "--------------------------\n";

        current = current->next;
    }
}

// Check if queue is empty
bool CheckoutQueue::isEmpty() const {
    return front == nullptr;
}

// Get number of checkout requests
int CheckoutQueue::getQueueSize() const {
    return queueSize;
}