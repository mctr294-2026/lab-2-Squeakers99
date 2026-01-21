#include "roots.h"
#include <iostream>

double functionCalculation(double a, double b, double c, double x) {
    return a * x * x + b * x + c;
}

double derivativeCalculation(double a, double b, double x) {
    return 2 * a * x + b;
}

// Calculates roots of a quadratic funciton by using the Newton-Raphson method
double* rootCalculation(double a, double b, double c, double x1, double x2) {
    // Calculate the critical point
    double criticalPoint = criticalPointCalculation(a, b);
    double f_CP = functionCalculation(a, b, c, criticalPoint);

    // Checks if the function has any real roots and returns nullptr if not
    if ((a < 0 && f_CP < 0) || (a > 0 && f_CP > 0)) {
        return nullptr;
    }

    // Checks if the function has any real roots inside the range and returns nullptr if not
    double f_x1 = functionCalculation(a, b, c, x1);
    double f_x2 = functionCalculation(a, b, c, x2);
    
    if ((f_x1 > 0 && f_x2 > 0) || (f_x1 < 0 && f_x2 < 0)) {
        return nullptr;
    }

    double x0 = (x1 + x2) / 2.0; // Initial guess at the midpoint

    double f_x0 = functionCalculation(a, b, c, x0);
    double f_prime_x0 = derivativeCalculation(a, b, x0);

    // Newton-Raphson iteration
    for (int i = 0; i < maxIterations; i++) {
        f_x0 = functionCalculation(a, b, c, x0);
        f_prime_x0 = derivativeCalculation(a, b, x0);

        double x_next = x0 - f_x0 / f_prime_x0;

        // Check for convergence
        if (std::abs(x_next - x0) < tolerance) {
            return new double(x_next);
        }

        x0 = x_next;
    }

    return new double(x0); // Return the best estimate after max iterations
}

double criticalPointCalculation(double a, double b) {
    return -b / (2.0 * a);
}