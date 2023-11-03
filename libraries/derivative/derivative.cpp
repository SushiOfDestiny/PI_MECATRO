namespace derivative {
    double getFilteredDerivative(double yPrevious, double psiPrevious, double psiCurrent, double tau, double deltaT) {
  /*This function outputs the yCurrent term of the estimator from the filtered derivative calculation
  based on previous values for y and psi (the measured value)
  The original equation used is 
  omega_dot = (psi_dot - omega)/tau
  which is changed to
  y_dot = - y/tau - psi/(tau^2)
  where y = omega - psi/tau
  */
  const double alpha = deltaT/(2*tau);
  return ((1.0/(1.0+alpha))*(yPrevious*(1.0 - alpha) - (psiCurrent + psiPrevious)*alpha/tau));
};
}