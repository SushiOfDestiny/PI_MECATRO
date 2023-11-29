#include "constants.h"

namespace derivative2{
  double auxVarEta(double e, double ePrev, double etaPrev, double N){
      // Return auxiliary var eta at current time
      // e is diff between command output and measured output 
      double eta = 1/(N + 2/deltaT)*(N*(e + ePrev) + (-N + 2/deltaT)*etaPrev);
      return eta;
  }

  double getFilteredDeriv(double eta, double N, double e){
      // Return approximated derivative D of the entry e = yr - ym 
      // (deviation between reference et measured output), such as 
      // output = k*(e - Td*D).
      // Warning, the "-" is not the usual form.
      return Tdd*N*(e - eta);
  }
}