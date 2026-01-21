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

    return new double(1.2);
}

double criticalPointCalculation(double a, double b) {
    return -b / (2.0 * a);
}