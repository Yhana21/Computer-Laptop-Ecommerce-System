#include "ProductBST.h"
#include <iostream>

using namespace std;

// Constructor
ProductBST::ProductBST() {
    root = nullptr;
}

// Destructor
ProductBST::~ProductBST() {
    deleteTree(root);
    root = nullptr;
}

// Insert node into BST
BSTNode* ProductBST::insertNode(BSTNode* node, const Product& product) {

    if (node == nullptr) {
        return new BSTNode(product);
    }

    if (product.id < node->data.id) {
        node->left = insertNode(node->left, product);
    }
    else if (product.id > node->data.id) {
        node->right = insertNode(node->right, product);
    }
    else {
        cout << "Product ID already exists.\n";
    }

    return node;
}

// Insert product
void ProductBST::insertProduct(const Product& product) {
    root = insertNode(root, product);
}

// Search node
BSTNode* ProductBST::searchNode(BSTNode* node, int id) const {

    if (node == nullptr || node->data.id == id) {
        return node;
    }

    if (id < node->data.id) {
        return searchNode(node->left, id);
    }

    return searchNode(node->right, id);
}

// Search product
BSTNode* ProductBST::searchProduct(int id) const {
    return searchNode(root, id);
}

// Inorder traversal
void ProductBST::inorderTraversal(BSTNode* node) const {

    if (node == nullptr) {
        return;
    }

    inorderTraversal(node->left);

    cout << "ID: " << node->data.id << endl;
    cout << "Name: " << node->data.name << endl;
    cout << "Category: " << node->data.category << endl;
    cout << "Brand: " << node->data.brand << endl;
    cout << "Price: " << node->data.price << endl;
    cout << "Stock: " << node->data.stockQuantity << endl;

    cout << "-----------------------------\n";

    inorderTraversal(node->right);
}

// Display products
void ProductBST::displayProducts() const {

    if (root == nullptr) {
        cout << "\nProduct BST is empty.\n";
        return;
    }

    cout << "\n========== PRODUCT BST ==========\n";

    inorderTraversal(root);
}

// Delete all BST nodes
void ProductBST::deleteTree(BSTNode* node) {

    if (node == nullptr) {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}