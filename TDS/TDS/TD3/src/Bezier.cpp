#include "Bezier.h"
#include "Eigen/Geometry"

using Eigen::MatrixXd, Eigen::RowVector3d, Eigen::Vector3d;

using namespace Eigen;

MatrixXd Bezier::de_casteljau(const MatrixXd &V, double t)
{
  // TODO: Recursive implementation of the de casteljeau method
  return V;
}

MatrixXd Bezier::de_casteljau_intermediate(const MatrixXd &V, double t)
{

  // TODO: one de casteljeau recursion step
  return V;
}

/**
 * Plot the curve, for t=0, dt, 2*dt, ..., 1, with a given 'resolution' <br>
 * where dt=1/(resolution-1)
 *
 * @param resolution  number of points to be evaluated on the curve
 */
MatrixXd Bezier::plot_curve(const MatrixXd &V, int resolution)
{
  // TODO: use de_casteljau function to compute the visualization
  MatrixXd points(resolution, 3);
  return points;
}

MatrixXd Bezier::plot_curve(const MatrixXd &V, int resolution, double t)
{
  assert(t <= 1.);
  assert(t >= 0);
  // TODO: draw the bezier curve until t\in [0,1]
  return V;
}

/**
 * Perform the subdivision (once) of the Bezier curve (with parameter t) <br>
 * Return two Bezier curves (with 'n' control points each)
 */
std::vector<MatrixXd> Bezier::subdivide(const MatrixXd &V, double t)
{
  std::vector<MatrixXd> curves{};
  // TODO
  return curves;
}

/**
 * Plot the curve using recursive subdivision <br>
 *
 * @param levels  number of levels of subdivisions
 * @return  a polyline representing the curve to be rendered: this is obtained by concantenation of
 * the control points of all subdivided curves
 */
MatrixXd Bezier::subdivision_plot(const MatrixXd &V, int levels)
{
  // TODO
  Eigen::MatrixXd newV;
  return newV;
}

/**
 * Compute the tangent of a given curve c(t) for a given parameter t0
 *
 * @param V  the vertices of the control polygon
 * @param t0   an input parameter in [0, 1]
 *
 * @return    the tangent at c(t0)
 **/
MatrixXd Bezier::compute_tangent(const MatrixXd &V, double t0)
{
  // TODO
  Eigen::MatrixXd tangent;
  return tangent;
}

/**
 * Compute the normal vector of a given curve c(t) for a given parameter t0
 *
 * @param V  the vertices of the control polygon
 * @param t0   an input parameter in [0, 1]
 *
 * @return    the normal at c(t0)
 **/
MatrixXd Bezier::compute_normal(const MatrixXd &V, double t0)
{
  // TODO
  Eigen::MatrixXd normal;
  return normal;
}

/**
 * Compute a loop of points around a curve c(t) for a given parameter t0
 * The points belongs on a circle lying the hyperplane passing through c(t0) and orthogonal to tangent(t0)
 *
 * @param V  the vertices of the control polygon
 * @param t0   an input parameter in [0, 1]
 *
 * @return    a loop of vertices on the hyperplane passing through c(t0) and orthogonal to tangent(t0)
 **/
MatrixXd Bezier::compute_loop_of_vertices(const MatrixXd &V, double t0, int k, double radius)
{
  // TODO
  Eigen::MatrixXd points;
  return points;
}
