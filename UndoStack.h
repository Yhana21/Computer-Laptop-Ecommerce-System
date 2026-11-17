
#ifndef UNDO_STACK_H
#define UNDO_STACK_H

#include "Product.h"

struct UndoNode {
    Product data;
    UndoNode* next;

    UndoNode(const Product& product)
        : data(product), next(nullptr) {}
};

class UndoStack {
private:
    UndoNode* topNode;
    int stackSize;

public:
    UndoStack();
    ~UndoStack();

    UndoStack(const UndoStack&) = delete;
    UndoStack& operator=(const UndoStack&) = delete;

    void push(const Product& product);
    bool pop(Product& product);
    void displayStack() const;

    bool isEmpty() const;
    int getStackSize() const;
};

#endif
