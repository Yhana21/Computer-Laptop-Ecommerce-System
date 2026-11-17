#ifndef BRAND_SHOWCASE_H
#define BRAND_SHOWCASE_H

#include <iostream>
#include <string>
using namespace std;

// Node for Brand Showcase
struct BrandNode {
    string brandName;
    BrandNode* next;

    BrandNode(const string& name)
        : brandName(name), next(nullptr) {}
};

// Brand Showcase Management
class BrandShowcase {
private:
    BrandNode* head;

public:
    // Constructor and Destructor
    BrandShowcase();
    ~BrandShowcase();

    // Prevent shallow copying
    BrandShowcase(const BrandShowcase&) = delete;
    BrandShowcase& operator=(const BrandShowcase&) = delete;

    // Brand Operations
    void addBrand(const string& brandName);
    bool removeBrand(const string& brandName);
    void displayBrands() const;
    bool searchBrand(const string& brandName) const;
};

#endif