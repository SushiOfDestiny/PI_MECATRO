#ifndef DERIVATIVE_H
#define DERIVATIVE_H

namespace derivative {
    double getFilteredDerivative(double etaPrevious, double deltaYPrevious, double deltaYCurrent, double tau, double deltaT);
}

#endif