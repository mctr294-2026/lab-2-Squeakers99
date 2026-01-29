#include <functional>
#include <cmath>

double tolerance = 1e-6;
double max_iterations = 1e6;

bool bisection(std::function<double(double)> f, double a, double b, double *root) {
    // Check that f(a) and f(b) have opposite signs and returns false if not
    if (f(a) * f(b) >= 0)
    {
        return false;
    }

    // Defines a variable to track iterations
    int iterations = 0;

    // Calculates the midpoint c
    double c = a - (f(a) * (b - a)) / (f(b) - f(a));

    // Iteratively refines the bracket [a, b] until the root is found within tolerance or max iterations reached
    while(std::abs(f(c)) > tolerance && iterations < max_iterations) {
        if (f(a) * f(c) < 0) {
            b = c;
        } else {
            a = c;
        }
        c = a - (f(a) * (b - a)) / (f(b) - f(a));
        iterations++;
    }
    
    // If the root is found within tolerance, assigns it to the output parameter and returns true
    if (std::abs(f(c)) < tolerance) {
        *root = c;
        return true;
    } else {
        return false;
    }
}