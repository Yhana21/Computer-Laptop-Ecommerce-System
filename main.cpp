
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

#include "Product.h"
#include "Inventory.h"
#include "ProductBST.h"
#include "SearchSort.h"
#include "ShoppingCart.h"
#include "CheckoutQueue.h"
#include "UndoStack.h"
#include "BrandShowcase.h"

using namespace std;

// Clear invalid input
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Display menu
void displayMenu() {
    cout << "\n============================================\n";
    cout << "       COMPUTER & LAPTOP ONLINE STORE\n";
    cout << "         E-COMMERCE INVENTORY SYSTEM\n";
    cout << "============================================\n";
    cout << "1.  Add Product\n";
    cout << "2.  Display All Products\n";
    cout << "3.  Search Product by ID\n";
    cout << "4.  Add Product to Shopping Cart\n";
    cout << "5.  Display Shopping Cart\n";
    cout << "6.  View Cart Total\n";
    cout << "7.  Add Cart Items to Checkout Queue\n";
    cout << "8.  Process Checkout Queue\n";
    cout << "9.  Display Checkout Queue\n";
    cout << "10. Display Partner Brands\n";
    cout << "11. Display Undo Stack\n";
    cout << "12. Filter Products by Brand\n";
    cout << "13. Sort Products by Price\n";
    cout << "14. Sort Products by Stock\n";
    cout << "15. Sort Products by Brand\n";
    cout << "16. Undo Last Action\n";
    cout << "0.  Exit\n";
    cout << "============================================\n";
    cout << "Enter your choice: ";
}

// Display sorted products
void sortAndDisplay(const Inventory& inventory, int sortChoice) {

    int size = inventory.getProductCount();

    if (size == 0) {
        cout << "\nInventory is empty.\n";
        return;
    }

    Product* products = new Product[size];

    InventoryNode* current = inventory.getHead();

    int index = 0;

    while (current != nullptr && index < size) {
        products[index] = current->data;
        current = current->next;
        index++;
    }

    if (sortChoice == 13) {
        SearchSort::sortByPrice(products, size);
        cout << "\n===== PRODUCTS SORTED BY PRICE =====\n";
    }
    else if (sortChoice == 14) {
        SearchSort::sortByStock(products, size);
        cout << "\n===== PRODUCTS SORTED BY STOCK =====\n";
    }
    else if (sortChoice == 15) {
        SearchSort::sortByBrand(products, size);
        cout << "\n===== PRODUCTS SORTED BY BRAND =====\n";
    }

    for (int i = 0; i < size; i++) {
        cout << "\nProduct ID: " << products[i].id << endl;
        cout << "Product Name: " << products[i].name << endl;
        cout << "Category: " << products[i].category << endl;
        cout << "Brand: " << products[i].brand << endl;
        cout << "Price: PHP " << fixed << setprecision(2)
             << products[i].price << endl;
        cout << "Stock: " << products[i].stockQuantity << endl;
        cout << "------------------------------------\n";
    }

    delete[] products;
}

int main() {

    // Initialize data structures
    Inventory inventory;
    ProductBST productTree;
    ShoppingCart cart;
    CheckoutQueue checkoutQueue;
    UndoStack undoStack;
    BrandShowcase brandShowcase;

    // Computer and laptop partner brands
    brandShowcase.addBrand("ASUS");
    brandShowcase.addBrand("Lenovo");
    brandShowcase.addBrand("HP");
    brandShowcase.addBrand("Acer");
    brandShowcase.addBrand("Dell");

    int choice = -1;

    do {

        displayMenu();

        if (!(cin >> choice)) {
            cout << "\nInvalid input. Enter a number only.\n";
            clearInput();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {

        // 1. Add Product
        case 1: {
            Product product;

            cout << "\n========== ADD PRODUCT ==========\n";

            cout << "Product ID: ";
            if (!(cin >> product.id)) {
                cout << "Invalid product ID.\n";
                clearInput();
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (inventory.findProductByID(product.id) != nullptr) {
                cout << "Product ID already exists.\n";
                break;
            }

            cout << "Product Name: ";
            getline(cin, product.name);

            cout << "Category: ";
            getline(cin, product.category);

            cout << "Brand: ";
            getline(cin, product.brand);

            cout << "Price: ";
            if (!(cin >> product.price)) {
                cout << "Invalid price.\n";
                clearInput();
                break;
            }

            cout << "Stock Quantity: ";
            if (!(cin >> product.stockQuantity)) {
                cout << "Invalid stock quantity.\n";
                clearInput();
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (product.id <= 0 ||
                product.name.empty() ||
                product.brand.empty() ||
                product.price < 0 ||
                product.stockQuantity < 0) {

                cout << "Invalid product information.\n";
                break;
            }

            inventory.addProduct(product);
            productTree.insertProduct(product);
            undoStack.push(product);

            cout << "\nProduct added successfully!\n";

            break;
        }

        // 2. Display Products
        case 2:
            inventory.displayProducts();
            break;

        // 3. Search Product by ID
        case 3: {
            int id;

            cout << "\nEnter Product ID: ";

            if (!(cin >> id)) {
                cout << "Invalid ID.\n";
                clearInput();
                break;
            }

            // Search using Binary Search Tree
            BSTNode* result = productTree.searchProduct(id);

            // Verify that product still exists in inventory
            InventoryNode* current =
                inventory.findProductByID(id);

            if (result != nullptr && current != nullptr) {

                cout << "\n========== PRODUCT FOUND ==========\n";
                cout << "ID: " << current->data.id << endl;
                cout << "Name: " << current->data.name << endl;
                cout << "Category: " << current->data.category << endl;
                cout << "Brand: " << current->data.brand << endl;
                cout << "Price: PHP " << current->data.price << endl;
                cout << "Current Stock: "
                     << current->data.stockQuantity << endl;
            }
            else {
                cout << "\nProduct not found.\n";
            }

            break;
        }

        // 4. Add to Shopping Cart
        case 4: {
            int id, quantity;

            cout << "\nEnter Product ID: ";

            if (!(cin >> id)) {
                cout << "Invalid ID.\n";
                clearInput();
                break;
            }

            InventoryNode* productNode =
                inventory.findProductByID(id);

            if (productNode == nullptr) {
                cout << "Product not found.\n";
                break;
            }

            cout << "Product: " << productNode->data.name << endl;
            cout << "Brand: " << productNode->data.brand << endl;
            cout << "Available Stock: "
                 << productNode->data.stockQuantity << endl;

            cout << "Enter Quantity: ";

            if (!(cin >> quantity)) {
                cout << "Invalid quantity.\n";
                clearInput();
                break;
            }

            if (quantity <= 0) {
                cout << "Quantity must be greater than zero.\n";
                break;
            }

            cart.addToCart(productNode->data, quantity);

            break;
        }

        // 5. Display Shopping Cart
        case 5:
            cart.displayCart();
            break;

        // 6. View Cart Total
        case 6:
            cout << fixed << setprecision(2);
            cout << "\nCart Total: PHP "
                 << cart.calculateTotal() << endl;
            break;

        // 7. Add Cart Items to Checkout Queue
        case 7: {

            if (cart.isEmpty()) {
                cout << "\nShopping cart is empty.\n";
                break;
            }

            while (cart.getHead() != nullptr) {

                CartNode* current = cart.getHead();

                checkoutQueue.enqueue(
                    current->data,
                    current->quantity
                );

                cart.removeFromCart(current->data.id);
            }

            cout << "\nProducts successfully added to checkout queue.\n";

            break;
        }

        // 8. Process Checkout
        case 8: {

            if (checkoutQueue.isEmpty()) {
                cout << "\nCheckout queue is empty.\n";
                break;
            }

            Product product;
            int quantity;

            while (checkoutQueue.dequeue(product, quantity)) {

                InventoryNode* found =
                    inventory.findProductByID(product.id);

                if (found == nullptr) {
                    cout << "\nProduct not found: "
                         << product.name << endl;
                    continue;
                }

                if (found->data.stockQuantity >= quantity) {

                    found->data.stockQuantity -= quantity;

                    cout << "\nCheckout Successful!\n";
                    cout << "Product: " << found->data.name << endl;
                    cout << "Brand: " << found->data.brand << endl;
                    cout << "Quantity: " << quantity << endl;
                    cout << "Remaining Stock: "
                         << found->data.stockQuantity << endl;

                }
                else {
                    cout << "\nInsufficient stock for "
                         << found->data.name << ".\n";

                    cout << "Available Stock: "
                         << found->data.stockQuantity << endl;
                }
            }

            cout << "\nCheckout processing completed.\n";

            break;
        }

        // 9. Display Checkout Queue
        case 9:
            checkoutQueue.displayQueue();
            break;

        // 10. Display Partner Brands
        case 10:
            cout << "\n========== PARTNER BRANDS ==========\n";
            brandShowcase.displayBrands();
            break;

        // 11. Display Undo Stack
        case 11:
            cout << "\n========== UNDO STACK ==========\n";
            undoStack.displayStack();
            cout << "Total saved actions: "
                 << undoStack.getStackSize() << endl;
            break;

        // 12. Filter Products by Brand
        case 12: {
            string brand;

            cout << "\nAvailable Brands:\n";
            brandShowcase.displayBrands();

            cout << "\nEnter Brand Name: ";
            getline(cin, brand);

            inventory.displayProductsByBrand(brand);

            break;
        }

        // 13. Sort by Price
        case 13:
            sortAndDisplay(inventory, 13);
            break;

        // 14. Sort by Stock
        case 14:
            sortAndDisplay(inventory, 14);
            break;

        // 15. Sort by Brand
        case 15:
            sortAndDisplay(inventory, 15);
            break;

        // 16. Undo Last Added Product
        case 16: {

            Product undoneProduct;

            if (undoStack.isEmpty()) {
                cout << "\nNothing to undo!\n";
                break;
            }

            if (undoStack.pop(undoneProduct)) {

                if (inventory.deleteProduct(undoneProduct.id)) {

                    cout << "\n========== UNDO SUCCESSFUL ==========\n";
                    cout << "The last added product has been removed.\n";
                    cout << "Product ID: "
                         << undoneProduct.id << endl;
                    cout << "Product Name: "
                         << undoneProduct.name << endl;
                    cout << "Brand: "
                         << undoneProduct.brand << endl;

                }
                else {

                    // Restore the action if deletion fails
                    undoStack.push(undoneProduct);

                    cout << "\nUndo failed.\n";
                    cout << "Product was not found in inventory.\n";
                    cout << "Undo action has been restored to the stack.\n";
                }
            }

            break;
        }

        // 0. Exit
        case 0:
            cout << "\nThank you for using the Computer & Laptop Store!\n";
            break;

        default:
            cout << "\nInvalid menu choice.\n";
        }

    } while (choice != 0);

    return 0;
}
