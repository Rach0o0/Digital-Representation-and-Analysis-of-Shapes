#pragma once
#include "CurveInterpolation.h"

class LinearInterpolation: public CurveInterpolation{
  Eigen::MatrixXd V;
  public:
    LinearInterpolation() = default;
    ~LinearInterpolation() = default;

    LinearInterpolation(const Eigen::MatrixXd &V0){
      this->V = V0;
    }

    // evaluate function at time t
    double eval_function(double t) override; 
    double operator()(double x) override;

};