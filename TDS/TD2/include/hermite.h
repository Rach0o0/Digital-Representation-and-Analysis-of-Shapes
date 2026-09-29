#pragma once

#include "CurveInterpolation.h"

class HermiteInterpolation : public CurveInterpolation
{
    Eigen::MatrixXd solutionx; // solution for x
    Eigen::MatrixXd solutiony; // solution for y
    Eigen::MatrixXd steps;     // points to interpolate
    Eigen::MatrixXd solvey;    // left size of linear system
    Eigen::MatrixXd solvex;    // left size of linear system
    Eigen::MatrixXd slopes;
    Eigen::MatrixXd W;

    void solve_x();

    void solve_y();

public:
    HermiteInterpolation() = default;
    ~HermiteInterpolation() = default;
    HermiteInterpolation(const Eigen::MatrixXd &V1, const Eigen::MatrixXd &slopes_input);

    void eval_function(Eigen::MatrixXd &linspace) override;

    void eval_tangent(int i, Eigen::MatrixXd &dX, double time) override;
};
