#include "roots.h"
#include <iostream>

double functionCalculation(double a, double b, double c, double x) {
    return a * x * x + b * x + c;
}

double derivativeCalculation(double a, double b, double x) {
    return 2 * a * x + b;
}

double* rootCalculation(double a, double b, double c, double x1, double x2) {
    double criticalPoint = criticalPointCalculation(a, b);
    double f_CP = functionCalculation(a, b, c, criticalPoint);

    if ((a < 0 && f_CP < 0) || (a > 0 && f_CP > 0)) {
        std::cout << "No roots found in the given interval." << std::endl;
        std::cout << a << ", " << criticalPoint << std::endl;
        return nullptr;
    }

    return new double(1.2);
}

double criticalPointCalculation(double a, double b) {
    return -b / (2.0 * a);
}