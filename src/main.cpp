#include <iostream>
#include "roots/roots.cpp"

int main()
{
    double* root = rootCalculation(1.0, -3.0, 2.0, 0.0, 3.0);
    if (root != nullptr) {
        std::cout << "Root found: " << *root << std::endl;
        delete root;
    } else {
        std::cout << "No root found." << std::endl;
    }
    return 0;
}
