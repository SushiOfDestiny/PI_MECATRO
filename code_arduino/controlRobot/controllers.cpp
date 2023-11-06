// Following code takes measures as inputs and returns controlled tensions values
#include "controllers.h"

#include "constants.h"
#include "derivative.h"

namespace controllers
{
    double phiSumRef(double time)
    {
        // Return reference for phiSum at given time
        return alpha * ur * time;
    }

    // double phiDifRef(double time){
    //     // Return reference for phiDif at given time
    //     return 0;
    // }

    double etaPDSumApprox(
        double etaPrevious, double deltaPhisCurrent, double deltaPhisPrevious, double epsilon, double deltaT)
    {
        // Return auxiliary variable eta for PD of Sum subsystem
        // deltaPhis = phir + phil;
        double etaCurrent = derivative::getFilteredDerivative(
            etaPrevious, deltaPhisPrevious, deltaPhisCurrent, epsilon, deltaT); // getDerivative + machin;

        return etaCurrent;
    }

    double etaToDerivative(double etaCurrent, double eCurrent, double epsilon)
    {
        // Return filtered derivative from auxiliary variable eta
        return etaCurrent + eCurrent / epsilon;
    }

    double usPDSumApprox(double deltaPhisDot, double deltaPhisCurrent)
    {
        // Return command sum of voltage for sum subsystem
        double Us = Usbar + h1 * (deltaPhisCurrent + Tds * deltaPhisDot);
        return Us;
    }

    double etaPDDifApprox(
        double etaPrevious, double deltaPhidCurrent,
        double deltaPhidPrevious, double epsilon, double deltaT)
    {
        // Return auxiliary variable eta for PD+P of Dif subsystem
        // E is total entry phid + cLF
        // deltaPhis = phir - phil;
        double etaCurrent = derivative::getFilteredDerivative(
            etaPrevious, deltaPhidPrevious, deltaPhidCurrent, epsilon, deltaT); // getDerivative + machin;

        return etaCurrent;
    }

    double udPDDifApprox(double deltaPhidDot, double deltaECurrent)
    {
        double Ud = Udbar + k1 * (deltaECurrent + Tdd * deltaPhidDot);
        return Ud;
    }
}
