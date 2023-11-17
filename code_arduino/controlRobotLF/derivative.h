#ifndef DERIVATIVE_H
#define DERIVATIVE_H

namespace derivative {
    double getDerivative(double deltaYPrevious, double deltaYCurrent, double deltaT);
    double getFilteredDerivative(double xPrevious, double deltaYPrevious, double deltaYCurrent, double epsilon, double deltaT);
    double etaToDerivative(double etaCurrent, double eCurrent, double epsilon);
}

#endif