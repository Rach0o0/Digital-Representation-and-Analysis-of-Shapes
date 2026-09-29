#include <linear.h>

using Eigen::MatrixXd;

// evaluate function at time t
double LinearInterpolation::eval_function(double t)
{
  // To be completed
  return 0.;
}

double LinearInterpolation::operator()(double t)
{
  return this->eval_function(t);
}
