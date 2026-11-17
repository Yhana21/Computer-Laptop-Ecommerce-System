#include "ShoppingCart.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Constructor
ShoppingCart::ShoppingCart() {
    head = nullptr;
    tail = nullptr;
    itemCount = 0;
}

// Destructor
ShoppingCart::~ShoppingCart() {
    CartNode* current = head;

    while (current != nullptr) {
        CartNode* temp = current;
        current = current->next;
        delete temp;
    }

    head = nullptr;
    tail = nullptr;
    itemCount = 0;
}

// Add product to cart
void ShoppingCart::addToCart(const Product& product, int quantity) {

    if (quantity <= 0) {
        cout << "Invalid quantity.\n";
        return;
    }

    if (quantity > product.stockQuantity) {
        cout << "Not enough stock available.\n";
        return;
    }

    CartNode* current = head;

    while (current != nullptr) {
        if (current->data.id == product.id) {

            if (current->quantity + quantity > product.stockQuantity) {
                cout << "Requested quantity exceeds available stock.\n";
                return;
            }

            current->quantity += quantity;
            cout << "Cart quantity updated successfully.\n";
            return;
        }

        current = current->next;
    }

    CartNode* newNode = new CartNode(product, quantity);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    itemCount++;

    cout << "Product added to cart successfully.\n";
}

// Remove product from cart
bool ShoppingCart::removeFromCart(int productID) {

    CartNode* current = head;

    while (current != nullptr) {

        if (current->data.id == productID) {

            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }

            if (current->next != nullptr) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }

            delete current;
            itemCount--;

            cout << "Product removed from cart.\n";
            return true;
        }

        current = current->next;
    }

    cout << "Product not found in cart.\n";
    return false;
}

// Display shopping cart
void ShoppingCart::displayCart() const {

    if (head == nullptr) {
        cout << "\nYour shopping cart is empty.\n";
        return;
    }

    CartNode* current = head;

    cout << "\n========== SHOPPING CART ==========\n";

    while (current != nullptr) {

        cout << "\nProduct ID: " << current->data.id << endl;
        cout << "Name: " << current->data.name << endl;
        cout << "Brand: " << current->data.brand << endl;
        cout << "Quantity: " << current->quantity << endl;
        cout << "Price: " << fixed << setprecision(2)
             << current->data.price << endl;

        cout << "Subtotal: "
             << current->data.price * current->quantity << endl;

        cout << "----------------------------------\n";

        current = current->next;
    }

    cout << "Total: " << fixed << setprecision(2)
         << calculateTotal() << endl;
}

// Calculate total price
double ShoppingCart::calculateTotal() const {

    double total = 0.0;
    CartNode* current = head;

    while (current != nullptr) {
        total += current->data.price * current->quantity;
        current = current->next;
    }

    return total;
}

// Get number of cart items
int ShoppingCart::getItemCount() const {
    return itemCount;
}

// Check if cart is empty
bool ShoppingCart::isEmpty() const {
    return head == nullptr;
}

// Get first cart node
CartNode* ShoppingCart::getHead() const {
    return head;
}