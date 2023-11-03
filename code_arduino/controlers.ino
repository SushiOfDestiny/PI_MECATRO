// Following code takes measures as inputs and returns controlled tensions values

#include "constants.h"    

double PDSumApprox(double phisr, double  phis, double  phisrPrevious, double  phisPrevious){
    double deltaPhis = phisr - phis;
    double deltaPhisDot; // getDerivative + machin;
    double Us = Usbar + h1 * ( deltaPhis + Tds*deltaPhisDot);

    return Us;
}

double PDDifApprox(double phidr, double phid, double cLFr, double cLF){
    double deltaPhid = phidr - phid;
    double deltaPhidDot; // getDerivative + machin;
    double deltaCLF = cLFr - cLF;
    double Ud = Udbar + k1*(deltaPhid + Tdd*deltaPhidDot) + k5*deltaCLF;
    return Ud;
}