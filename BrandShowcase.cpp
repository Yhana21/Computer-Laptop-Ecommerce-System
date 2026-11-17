#include "BrandShowcase.h"
using namespace std;

// Constructor
BrandShowcase::BrandShowcase() {
    head = nullptr;
}

// Destructor
BrandShowcase::~BrandShowcase() {
    while (head != nullptr) {
        BrandNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Add a brand
void BrandShowcase::addBrand(const string& brandName) {
    if (brandName.empty()) {
        cout << "Brand name cannot be empty.\n";
        return;
    }

    if (searchBrand(brandName)) {
        cout << "Brand already exists.\n";
        return;
    }

    BrandNode* newNode = new BrandNode(brandName);

    if (head == nullptr) {
        head = newNode;
    } else {
        BrandNode* current = head;

        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = newNode;
    }

    cout << "Brand added successfully!\n";
}

// Remove a brand
bool BrandShowcase::removeBrand(const string& brandName) {
    if (head == nullptr) {
        return false;
    }

    if (head->brandName == brandName) {
        BrandNode* temp = head;
        head = head->next;
        delete temp;

        cout << "Brand removed successfully.\n";
        return true;
    }

    BrandNode* current = head;

    while (current->next != nullptr &&
           current->next->brandName != brandName) {
        current = current->next;
    }

    if (current->next == nullptr) {
        cout << "Brand not found.\n";
        return false;
    }

    BrandNode* temp = current->next;
    current->next = temp->next;
    delete temp;

    cout << "Brand removed successfully.\n";
    return true;
}

// Display all brands
void BrandShowcase::displayBrands() const {
    if (head == nullptr) {
        cout << "\nNo brands available.\n";
        return;
    }

    BrandNode* current = head;

    cout << "\n===== PARTNER BRANDS =====\n";

    while (current != nullptr) {
        cout << "- " << current->brandName << endl;
        current = current->next;
    }
}

// Search for a brand
bool BrandShowcase::searchBrand(const string& brandName) const {
    BrandNode* current = head;

    while (current != nullptr) {
        if (current->brandName == brandName) {
            return true;
        }

        current = current->next;
    }

    return false;
}