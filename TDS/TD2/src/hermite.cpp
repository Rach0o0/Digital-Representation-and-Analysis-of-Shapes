#include "Eigen/Core"
#include <Eigen/Dense>
#include <hermite.h>
#include <iostream>

using Eigen::MatrixXd;

void HermiteInterpolation::solve_x()
{
    solutionx = W.colPivHouseholderQr().solve(solvex);
}

void HermiteInterpolation::solve_y()
{
    solutiony = W.colPivHouseholderQr().solve(solvey);
}

HermiteInterpolation::HermiteInterpolation(const MatrixXd &V1, const Eigen::MatrixXd &slopes_input)
{
    W = MatrixXd::Zero(4, 4);
    // complete here
}

// complete linspace with corrdinates

void HermiteInterpolation::eval_function(Eigen::MatrixXd &linspace)
{
    // complete here
}

/*
Evaluate tangent at step i
*/
void HermiteInterpolation::eval_tangent(int i, MatrixXd &dX, double time)
{
    // complete here for bonus
}
