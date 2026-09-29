#pragma once
#include "CurveInterpolation.h"

class CubicInterpolation : public CurveInterpolation
{
    Eigen::MatrixXd M; // coefficients
    Eigen::MatrixXd a; // solution
    Eigen::MatrixXd V; // points to interpolate
    Eigen::MatrixXd y; // left size of linear system
public:
    CubicInterpolation() = default;
    ~CubicInterpolation() = default;

    CubicInterpolation(const Eigen::MatrixXd &V0);
    void init_system();
    // evaluate function at time t
    double eval_function(double t) override;
    void eval_tangent(int i, Eigen::MatrixXd &dX, double x) override;
    double operator()(double x) override{return this->eval_function(x);};
};