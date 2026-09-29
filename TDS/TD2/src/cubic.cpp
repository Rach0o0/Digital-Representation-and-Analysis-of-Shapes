#include "Eigen/Core"
#include <Eigen/Dense>
using Eigen::MatrixXd;

#include "cubic.h"

/*
Initialize system constraints
*/
void CubicInterpolation::init_system()
{
  // complete here

  // [...]
}

CubicInterpolation::CubicInterpolation(const MatrixXd &V1)
{
  // complete here
}

/*
Evaluate tangent at step i
*/
void CubicInterpolation::eval_tangent(int i, MatrixXd &dX, double x)
{
  // complete here
}

/*
Evaluate function at time t
*/
double CubicInterpolation::eval_function(double t)
{
  // complete here
  return 0.;
}
