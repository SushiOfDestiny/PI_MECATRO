#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "constants.h"
#include "derivative.h"

namespace controllers
{
    double phiSumRef(double time);
    
    double etaPDSumApprox(
        double etaPrevious, double deltaPhisCurrent, double deltaPhisPrevious, double epsilon, double deltaT);

    double etaToDerivative(double etaCurrent, double eCurrent, double epsilon);

    double usPDSumApprox(double deltaPhisDot, double deltaPhisCurrent);

    double etaPDDifApprox(
        double etaPrevious, double deltaPhidCurrent, double deltaPhidPrevious,
        double deltaCLFCurrent, double deltaCLFPrevious, double epsilon, double deltaT);

    double udPDDifApprox(double deltaPhidDot, double deltaECurrent);

    double udPLF(double deltacLFCurrent);
}

#endif