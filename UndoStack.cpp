
#include "UndoStack.h"
#include <iostream>
using namespace std;

// Constructor
UndoStack::UndoStack() {
    topNode = nullptr;
    stackSize = 0;
}

// Destructor
UndoStack::~UndoStack() {
    while (topNode != nullptr) {
        UndoNode* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }

    stackSize = 0;
}

// Push product into stack
void UndoStack::push(const Product& product) {
    UndoNode* newNode = new UndoNode(product);

    newNode->next = topNode;
    topNode = newNode;

    stackSize++;

    cout << "Action saved in Undo Stack.\n";
}

// Pop latest product from stack
bool UndoStack::pop(Product& product) {
    if (isEmpty()) {
        return false;
    }

    UndoNode* temp = topNode;

    product = temp->data;

    topNode = topNode->next;

    delete temp;
    stackSize--;

    return true;
}

// Display stack
void UndoStack::displayStack() const {
    if (isEmpty()) {
        cout << "Undo Stack is empty.\n";
        return;
    }

    UndoNode* current = topNode;

    cout << "\nLatest actions first:\n";

    while (current != nullptr) {
        cout << "Product ID: " << current->data.id << endl;
        cout << "Product Name: " << current->data.name << endl;
        cout << "Brand: " << current->data.brand << endl;
        cout << "Price: PHP " << current->data.price << endl;
        cout << "-----------------------------\n";

        current = current->next;
    }
}

// Check if stack is empty
bool UndoStack::isEmpty() const {
    return topNode == nullptr;
}

// Get stack size
int UndoStack::getStackSize() const {
    return stackSize;
}
