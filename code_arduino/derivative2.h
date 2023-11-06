#ifndef DERIVATIVE2_H
#define DERIVATIVE2_H

#include "constants.h"

double auxVarEta(double e, double ePrev, double etaPrev, double N);
double getFilteredDeriv(double eta, double N, double e);

#endif