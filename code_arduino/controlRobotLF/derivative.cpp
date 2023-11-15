namespace derivative {
  double getFilteredDerivative(double xPrevious, double deltaYPrevious, double deltaYCurrent, double epsilon, double deltaT) {
    /*This function outputs the xCurrent term of the estimator from the filtered derivative calculation
    based on previous values for x and deltaY (the measured value)
    
    WARNING : xCurrent = eta - deltaY/epsilon so to get etaCurrent, use xCurrent + deltaY/epsilon

    The original equation used is 
    eta_dot = (deltaY_dot - eta)/epsilon
    which is changed to
    x_dot = - eta/epsilon - deltaY/(epsilon^2)
    where x = eta - deltaY/epsilon
    */
    const double alpha = deltaT/(2*epsilon);
    return ((1.0/(1.0+alpha))*(xPrevious*(1.0 - alpha) - (deltaYCurrent + deltaYPrevious)*alpha/epsilon));
  }
  double etaToDerivative(double etaCurrent, double eCurrent, double epsilon)
    {
        // Return filtered derivative from auxiliary variable eta
        return etaCurrent + eCurrent / epsilon;
    }
}