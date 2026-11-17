#ifndef PRODUCT_BST_H
#define PRODUCT_BST_H

#include "Product.h"

// Node for Binary Search Tree
struct BSTNode {
    Product data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const Product& product)
        : data(product), left(nullptr), right(nullptr) {}
};

// Product Binary Search Tree
class ProductBST {
private:
    BSTNode* root;

    // Helper functions
    BSTNode* insertNode(BSTNode* node, const Product& product);
    BSTNode* searchNode(BSTNode* node, int id) const;
    void inorderTraversal(BSTNode* node) const;
    void deleteTree(BSTNode* node);

public:
    // Constructor and destructor
    ProductBST();
    ~ProductBST();

    // Prevent accidental shallow copying
    ProductBST(const ProductBST&) = delete;
    ProductBST& operator=(const ProductBST&) = delete;

    // BST operations
    void insertProduct(const Product& product);
    BSTNode* searchProduct(int id) const;
    void displayProducts() const;
};

#endif