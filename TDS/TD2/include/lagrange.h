#pragma once
#include "CurveInterpolation.h"

class LagrangeInterpolation : public CurveInterpolation
{
    Eigen::MatrixXd V;
    Eigen::MatrixXd W;
    Eigen::MatrixXd a;

    void Vandermonde();

public:
    LagrangeInterpolation() = default;
    ~LagrangeInterpolation() = default;

    LagrangeInterpolation(const Eigen::MatrixXd &V0);

    // evaluate interpolated function at time t
    double eval_function(double t) override;
    double operator()(double x) override { return this->eval_function(x); }

};