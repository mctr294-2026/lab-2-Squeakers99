#pragma once

#define x1
#define x2
#define x3
#define tolerance 1e-6
#define maxIterations 1e6
#define currentIteration 0

double* rootCalculation(double a, double b, double c, double x1, double x2);
double functionCalculation(double a, double b, double c, double x);
double derivativeCalculation(double a, double b, double x);
double criticalPointCalculation(double a, double b);