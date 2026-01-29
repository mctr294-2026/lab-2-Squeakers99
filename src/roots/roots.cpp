#include <functional>
#include <cmath>

double tolerance = 1e-6;
double max_iterations = 1e6;

// Bisection Method Execution
bool bisection(std::function<double(double)> f,
                double a, double b,
                double *root) {
    // Check that f(a) and f(b) have opposite signs and returns false if not
    if (f(a) * f(b) >= 0)
    {
        return false;
    }

    // Defines a variable to track iterations
    int iterations = 0;

    // Calculatres the midpoint c
    double c = (a + b) / 2.0;

    // Iteratively refines the bracket [a, b] until the root is found within tolerance or max iterations reached
    while(std::abs(f(c)) > tolerance && iterations < max_iterations) {
        // Refines the bracket [a, b] based on the sign of f(c)
        if (f(a) * f(c) < 0) {
            b = c;
        } else {
            a = c;
        }

        // Recalculates the midpoint c
        c = (a + b) / 2.0;

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

// Regula Falsi Method Execution
bool regula_falsi(std::function<double(double)> f,
                  double a, double b,
                  double *root) {
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

// Newton-Raphson Method Execution
bool newton_raphson(std::function<double(double)> f,
                    std::function<double(double)> g,
                    double a, double b, double c,
                    double *root) {
    // Defines a variable to track iterations
    int iterations = 0;

    // Iteratively refines the guess c until the root is found within tolerance or max iterations reached
    while(std::abs(f(c)) > tolerance && iterations < max_iterations) {
        double g_c = g(c);
        if (g_c == 0) {
            return false; // Derivative is zero, cannot proceed
        }
        c = c - f(c) / g_c;

        // Check if c is still within [a, b]
        if (c < a || c > b) {
            return false; // Out of bounds
        }

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