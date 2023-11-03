#ifndef DERIVATIVE_H
#define DERIVATIVE_H

namespace derivative {
    double getFilteredDerivative(double yPrevious, double psiPrevious, double psiCurrent, double tau, double deltaT);
}

#endif