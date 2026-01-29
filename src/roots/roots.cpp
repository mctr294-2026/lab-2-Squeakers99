#include <functional>
#include <cmath>
#include <iostream>

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

    // Ensures a is less than b
    if (a > b) {
        throw std::invalid_argument("a must be less than b");
    }

    // Ensures c is within [a, b]
    if (c < a || c > b) {
        throw std::invalid_argument("c must be within [a, b]");
    }

    // Defines a variable to track iterations
    int iterations = 0;

    // Checks if the guess is the root
    if (std::abs(f(c)) < tolerance) {
        *root = c;
        return true;
    }

    // Iteratively refines the guess c until the root is found within tolerance or max iterations reached
    while(iterations < max_iterations) {
        // Creates a variable to store the derivative at c
        double g_c = g(c);

        // Prevents division by zero
        if (g_c == 0) {
            return false;
        }

        // Gets the new c value using the Newton-Raphson formula
        double c_new = c - f(c) / g_c;

        // Checks if the change between c and c_new is within tolerance
        if (std::abs(c - c_new) < tolerance) {
            *root = c_new;
            return true;
        } else{
            c = c_new;
        }

        iterations++;
    }

    // If the root is not found within max iterations, returns false
    return false;
}

// Secant Method Execution
bool secant(std::function<double(double)> f,
            double a, double b, double c,
            double *root) {

    // Defines a variable to track iterations
    int iterations = 0;

    // Defined c_next to store the next approximation
    double c_next;

    // Ensures a is less than b
    if (a > b) {
        throw std::invalid_argument("a must be less than b");
    }

    // Ensures c is within [a, b]
    if (c < a || c > b) {
        throw std::invalid_argument("c must be within [a, b]");
    }

    // Chooses the 2nd point
    if (c == a) {
        c_next = a + (b - a) * 0.1; // Moves into the interval
    } else if (c == b) {
        c_next = b - (b - a) * 0.1; // Moves into the interval
    } else {
        // Tries to get it on opposite sides if possible
        double f_a = f(a);
        double f_b = f(b);

        if (f(a) * f(c) < 0) {
            c_next = a; // Uses a if it's on the opposite side
        } else if (f(b) * f(c) < 0) {
            c_next = b; // Uses b if it's on the opposite side
        } else {
            // No sign change, chooses a point near c
            double dx = (b - a) * 0.1;
            c_next = c + dx;
            if (c_next > b) c_next = c - dx;
        }
    }

    // Ensures within bounds and different from c
    if (c_next < a) c_next = a;
    if (c_next > b) c_next = b;

    // Checks faliure case that the points are essentially the same
    if (std::abs(c_next - c) < tolerance) {
        return false;
    }

    // Checks if either guess is a root
    if (std::abs(f(c)) < tolerance) {
        *root = c;
        return true;
    } else if (std::abs(f(c_next)) < tolerance) {
        *root = c_next;
        return true;
    }

    // Iteratively refines the guesses c and c_next until the root is found within tolerance or max iterations reached
    while(iterations < max_iterations) {
        double f_c = f(c);
        double f_c_next = f(c_next);

        // Prevents division by zero
        if (f_c - f_c_next == 0) {
            return false;
        }

        // Gets the new c value using the Secant formula
        double c_new = c - f_c * (c - c_next) / (f_c - f_c_next);

        // Checks if the change between c_next and c_new is within tolerance
        if (std::abs(c_next - c_new) < tolerance) {
            *root = c_new;
            return true;
        } else{
            c = c_next;
            c_next = c_new;
        }

        iterations++;
    }

    // If the root is not found within max iterations, returns false
    return false;
}