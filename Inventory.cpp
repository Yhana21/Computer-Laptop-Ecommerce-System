#include "Inventory.h"
#include <iostream>
using namespace std;

// Constructor
Inventory::Inventory() {
    head = nullptr;
    productCount = 0;
}

// Destructor - prevents memory leaks
Inventory::~Inventory() {
    InventoryNode* current = head;

    while (current != nullptr) {
        InventoryNode* temp = current;
        current = current->next;
        delete temp;
    }

    head = nullptr;
    productCount = 0;
}

// Add a new product
void Inventory::addProduct(const Product& product) {

    if (findProductByID(product.id) != nullptr) {
        cout << "Product ID already exists.\n";
        return;
    }

    InventoryNode* newNode = new InventoryNode(product);

    if (head == nullptr) {
        head = newNode;
    } else {
        InventoryNode* current = head;

        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = newNode;
    }

    productCount++;

    cout << "Product added successfully!\n";
}

// Delete a product using its ID
bool Inventory::deleteProduct(int id) {

    if (head == nullptr) {
        cout << "Inventory is empty.\n";
        return false;
    }

    if (head->data.id == id) {
        InventoryNode* temp = head;
        head = head->next;

        delete temp;
        productCount--;

        cout << "Product deleted successfully!\n";
        return true;
    }

    InventoryNode* current = head;

    while (current->next != nullptr &&
           current->next->data.id != id) {
        current = current->next;
    }

    if (current->next == nullptr) {
        cout << "Product not found.\n";
        return false;
    }

    InventoryNode* temp = current->next;
    current->next = temp->next;

    delete temp;
    productCount--;

    cout << "Product deleted successfully!\n";
    return true;
}

// Update product information
bool Inventory::updateProduct(
    int id,
    const Product& updatedProduct
) {

    InventoryNode* current = findProductByID(id);

    if (current == nullptr) {
        cout << "Product not found.\n";
        return false;
    }

    Product newData = updatedProduct;
    newData.id = id;

    current->data = newData;

    cout << "Product updated successfully!\n";
    return true;
}

// Display all products
void Inventory::displayProducts() const {

    if (head == nullptr) {
        cout << "\nInventory is empty.\n";
        return;
    }

    InventoryNode* current = head;

    cout << "\n========== INVENTORY ==========\n";

    while (current != nullptr) {

        cout << "Product ID: " << current->data.id << endl;
        cout << "Product Name: " << current->data.name << endl;
        cout << "Category: " << current->data.category << endl;
        cout << "Brand: " << current->data.brand << endl;
        cout << "Price: " << current->data.price << endl;
        cout << "Stock Quantity: "
             << current->data.stockQuantity << endl;

        cout << "-------------------------------\n";

        current = current->next;
    }

    cout << "Total Products: " << productCount << endl;
}

// Display products by brand
void Inventory::displayProductsByBrand(
    const string& brand
) const {

    InventoryNode* current = head;
    bool found = false;

    cout << "\n===== PRODUCTS BY BRAND: "
         << brand << " =====\n";

    while (current != nullptr) {

        if (current->data.brand == brand) {

            cout << "Product ID: " << current->data.id << endl;
            cout << "Product Name: " << current->data.name << endl;
            cout << "Category: " << current->data.category << endl;
            cout << "Brand: " << current->data.brand << endl;
            cout << "Price: " << current->data.price << endl;
            cout << "Stock Quantity: "
                 << current->data.stockQuantity << endl;

            cout << "-------------------------------\n";

            found = true;
        }

        current = current->next;
    }

    if (!found) {
        cout << "No products found for brand: "
             << brand << endl;
    }
}

// Find product using ID
InventoryNode* Inventory::findProductByID(int id) const {

    InventoryNode* current = head;

    while (current != nullptr) {

        if (current->data.id == id) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

// Get total number of products
int Inventory::getProductCount() const {
    return productCount;
}

// Get the head of the inventory list
InventoryNode* Inventory::getHead() const {
    return head;
}