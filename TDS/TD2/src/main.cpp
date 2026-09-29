// std includes
#include <iostream>
#include <ostream>
#include <memory>
#include <chrono>
#include <vector>
#include <thread>
#include <string>

// libigl includes
#include "igl/readPLY.h"

// Eigen includes
#include "Eigen/Core"

// Polyscope includes
#include "polyscope/polyscope.h"
#include "polyscope/messages.h"
#include "polyscope/point_cloud.h"
#include "polyscope/curve_network.h"

#include <GLFW/glfw3.h>
void emptyGLFWErrorCallback(int, const char *) {}

#include <util.h>
#include <lagrange.h>
#include <linear.h>
#include <cubic.h>
#include <hermite.h>

using Eigen::MatrixXi, Eigen::MatrixXd, Eigen::Vector2d;
MatrixXd V1; // matrix storing vertex coordinates of the input curve
MatrixXi F1;
bool linear = true;
bool cubic = false;
bool lagrange = false;
bool hermite = false;

bool cubic_tangents = false;
bool hermite_tangents = false;

int resolution = 5; // resolution of displayed curve

std::shared_ptr<CurveInterpolation> interp; // pointer to the interpolation method

polyscope::PointCloud *psPoints;

void callback()
{
  static int numPoints = 2000;
  static float param = 3.14;

  ImGui::PushItemWidth(100);

  if (ImGui::SliderInt("Resolution", &resolution, 2, 2000))
  {
  }

  if (ImGui::Checkbox("Linear", &linear))
  {
    cubic = false;
    lagrange = false;
    hermite = false;
    linear = true;
  }
  if (ImGui::Checkbox("Lagrange", &lagrange))
  {
    linear = false;
    cubic = false;
    hermite = false;
    lagrange = true;
  }

  if (ImGui::Checkbox("Cubic", &cubic))
  {
    linear = false;
    lagrange = false;
    hermite = false;
    cubic = true;
  }
  ImGui::SameLine();
  if (ImGui::Checkbox("Cubic Tangents", &cubic_tangents))
  {
  }

  if (ImGui::Checkbox("Hermite", &hermite))
  {
    linear = false;
    cubic = false;
    lagrange = false;
    hermite = true;
  }
  ImGui::SameLine();
  if (ImGui::Checkbox("Hermite Tangents", &hermite_tangents))
  {
  }

  if (ImGui::Button("Interpolate"))
  {

    if (linear)
    {
      interp = std::shared_ptr<CurveInterpolation>(new LinearInterpolation(V1));
      MatrixXd linspace = MatrixXd::Zero(resolution, 2);
      util::build_linspace(linspace, V1); // initialize the X axis of the interpolation
      std::vector<Vector2d> points;
      std::vector<std::array<int, 2>> edges;
      std::vector<std::array<double, 3>> colors;

      for (size_t i = 0; i < resolution; i++)
      {
        double time = linspace(i, 0);
        linspace(i, 1) = interp->eval_function(time);
        Vector2d pt = Vector2d(linspace(i, 0), linspace(i, 1));
        points.push_back(pt);
        if (i < resolution - 1)
        {
          edges.push_back({int(i), int(i + 1)});
          colors.push_back({0.0, 0.0, 1.0});
        }
      }

      polyscope::registerCurveNetwork2D("Linear Interpolation", points, edges);
    }

    if (lagrange)
    {
      interp = std::shared_ptr<CurveInterpolation>(new LagrangeInterpolation(V1));
      MatrixXd linspace = MatrixXd::Zero(resolution, 2);
      util::build_linspace(linspace, V1); // initialize the X axis of the interpolation
      std::vector<Vector2d> points;
      std::vector<std::array<int, 2>> edges;
      std::vector<std::array<double, 3>> colors;

      for (size_t i = 0; i < resolution; i++)
      {
        double time = linspace(i, 0);
        linspace(i, 1) = interp->eval_function(time);
        Vector2d pt = Vector2d(linspace(i, 0), linspace(i, 1));
        points.push_back(pt);
        if (i < resolution - 1)
        {
          edges.push_back({int(i), int(i + 1)});
          colors.push_back({0.0, 0.0, 1.0});
        }
      }

      polyscope::registerCurveNetwork2D("Lagrange Interpolation", points, edges);
    }

    if (cubic)
    {
      MatrixXd linspace = MatrixXd::Zero(resolution, 2);
      interp = std::shared_ptr<CurveInterpolation>(new CubicInterpolation(V1));
      util::build_linspace(linspace, V1); // initialize the X axis of the interpolation
      std::vector<Vector2d> points;
      std::vector<std::array<int, 2>> edges;
      std::vector<std::array<double, 3>> colors;

      for (size_t i = 0; i < resolution; i++)
      {
        double time = linspace(i, 0);
        linspace(i, 1) = interp->eval_function(time);
        Vector2d pt = Vector2d(linspace(i, 0), linspace(i, 1));
        points.push_back(pt);
        if (i < resolution - 1)
        {
          edges.push_back({int(i), int(i + 1)});
          colors.push_back({0.0, 0.0, 1.0});
        }
      }

      polyscope::registerCurveNetwork2D("Cubic Interpolation", points, edges);

      if (cubic_tangents)
      {
        std::vector<Eigen::Vector3d> tangent_vectors;
        tangent_vectors.push_back(Eigen::Vector3d(0, 0, 0));
        for (size_t i = 1; i < V1.rows() - 1; i++)
        {
          MatrixXd dX(V1.rows(), 2);
          interp->eval_tangent(i, dX, V1(i, 0));
          Eigen::Vector3d tangent = Eigen::Vector3d(dX(i, 0), dX(i, 1), 0);
          tangent_vectors.push_back(tangent);
        }
        tangent_vectors.push_back(Eigen::Vector3d(0, 0, 0));

        polyscope::getPointCloud("Input Points")->addVectorQuantity("Tangents", tangent_vectors);
      }
    }

    if (hermite)
    {
      Eigen::MatrixXd slopes = Eigen::MatrixXd::Ones(V1.rows(), 2);

      // Build interpolator
      interp = std::shared_ptr<CurveInterpolation>(new HermiteInterpolation(V1, slopes));

      // Sample points along the curve
      MatrixXd linspace = MatrixXd::Zero(resolution, 2);
      util::build_linspace(linspace, V1); // (keeps your existing convention)
      interp->eval_function(linspace);

      // Convert to Polyscope buffers
      std::vector<Eigen::Vector2d> points;
      points.reserve(linspace.rows());
      for (int i = 0; i < linspace.rows(); ++i)
      {
        points.emplace_back(linspace(i, 0), linspace(i, 1));
      }

      std::vector<std::array<int, 2>> edges;
      edges.reserve(std::max(0, resolution - 1));
      for (int i = 0; i + 1 < resolution; ++i)
      {
        edges.push_back({i, i + 1});
      }

      auto *cn = polyscope::registerCurveNetwork2D("Hermite Interpolation", points, edges);

      // --- Optional: show tangents at the original control points ---
      if (hermite_tangents)
      {
        // TODO for you as a bonus
      }
    }
  }
}

int main(int argc, char *argv[])
{

  // --- Load the meshes ---
  //------------------------
  std::string path_to_source = std::string(PROJECT_SOURCE_DIR);
  if (argc < 2)
  {
    std::string filename = "/data/curve.ply";
    std::string full_path = path_to_source + filename;
    std::cout << "loading: " << full_path << std::endl;
    Eigen::MatrixXd V_load;
    Eigen::MatrixXi F_load;
    igl::readPLY(full_path, V_load, F_load);
    V1 = Eigen::MatrixXd::Zero(V_load.rows(), 2);
    V1.col(0) = V_load.col(0);
    V1.col(1) = V_load.col(1);
  }
  else
  {
    std::string filename = std::string(argv[1]);

    std::string full_path = path_to_source + filename;
    if (filename.size() >= 3 && filename.substr(filename.size() - 3) == "ply")
    {
      Eigen::MatrixXd V_load;
      Eigen::MatrixXi F_load;
      igl::readPLY(full_path, V_load, F_load);
      V1 = Eigen::MatrixXd::Zero(V_load.rows(), 2);
      V1.col(0) = V_load.col(0);
      V1.col(1) = V_load.col(1);
      std::cout << "reading input file: " << full_path << std::endl;
    }
    else
    {
      std::cout << "Error: input file must be a .ply file" << std::endl;
      return 0;
    }
  }

  //  print the number of mesh elements
  std::cout << "Points: \n"
            << V1 << std::endl;

  std::cout << " -- Interpolation of Curves -- " << std::endl;

  // --- Visualize the mesh using Polyscope ---
  //--------------------------------------------

  // Options
  polyscope::view::windowWidth = 1024;
  polyscope::view::windowHeight = 1024;

  // Initialize polyscope
  polyscope::init();

  psPoints = polyscope::registerPointCloud2D("Input Points", V1);

  polyscope::state::userCallback = callback;

  // Show the gui
  polyscope::show();

  return 0;

  return (0);
}
