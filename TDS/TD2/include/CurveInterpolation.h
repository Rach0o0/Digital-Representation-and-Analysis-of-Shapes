#pragma once
#include <Eigen/Core>
class CurveInterpolation
{
public:
    virtual double operator()(double x){
        throw std::logic_error("operator() not supported by this interpolation.");
    }
    virtual double eval_function(double time){
        throw std::logic_error("eval_function not supported by this interpolation.");
    }
    // default: not supported
    virtual void eval_tangent(int, Eigen::MatrixXd&, double)
    {
        throw std::logic_error("eval_tangent not supported by this interpolation.");
    }
    virtual void eval_function(Eigen::MatrixXd&) 
    {
        throw std::logic_error("eval_function not supported by this interpolation.");
    }
    virtual ~CurveInterpolation() = default;
};