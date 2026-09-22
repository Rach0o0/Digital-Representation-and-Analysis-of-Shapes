// std includes
#include <iostream>
#include <ostream>
#include <memory>
#include <chrono>
#include <vector>
#include <thread>
#include <string>

// libigl includes
#include "igl/read_triangle_mesh.h"

// Eigen includes
#include "Eigen/Core"

// Polyscope includes
#include "polyscope/polyscope.h"
#include "polyscope/messages.h"
#include "polyscope/point_cloud.h"
#include "polyscope/surface_mesh.h"
// get rid in windows of this annoying warning
#include <GLFW/glfw3.h>
void emptyGLFWErrorCallback(int, const char *) {}

// Our Includes
#include <Transform.h>

/*
Here we include the necessary Eigen and Polyscope headers. We also include Transform.h, which is a header file that we will create to store the Transform class. We will define the Transform class in Transform.cpp. We also include the necessary igl headers to read in the input mesh.
*/

// Often you will see something like using namespace Eigen or using namespace std. This is generally a bad practice and you should avoid that, since it copies the entire namespace in your file. Since c++17 you can import only certain functions from a namespace, which makes you code cleaner and less error-prone. For example, you can use using Eigen::MatrixXd; to import only the MatrixXd class from the Eigen namespace. This is what we do in the following lines of code. It is like the python command from numpy import XYZ...
using Eigen::MatrixXi, Eigen::MatrixXd, Eigen::Vector3d, Eigen::Vector3i, Eigen::RowVector3d;

MatrixXd V, V_copy; // matrix storing vertex coordinates of the input mesh
MatrixXi F, F_copy; // matrix storing the integer indices of the vertices forming the (triangular) faces of the input mesh

Transform transformer; // we initialize an object from the transform class. For now it is just an empty object with nothing in it.

float unit_scale = 1.0; // we initialize a variable scale with the value 1.0. This variable will be used to scale the mesh.

float scale_x = 1.0;
float scale_y = 1.0;
float scale_z = 1.0;

float translate_x = 0.0; // we initialize a variable translate_x with the value 0.0. This variable will be used to translate the mesh in the x-direction.
float translate_y = 0.0; // we initialize a variable translate_y with the value 0.0. This variable will be used to translate the mesh in the y-direction.
float translate_z = 0.0; // we initialize a variable translate_z with the value 0.0. This variable will be used to translate the mesh in the z-direction.

int rotation_axis = 0;
bool rot_x = true;
bool rot_y = false;
bool rot_z = false;
float theta = 0.;

float dir_x = 1.0;
float dir_y = 0.0;
float dir_z = 0.0;

bool is_rotating = false;

polyscope::SurfaceMesh *psMesh; // we initialize a pointer to a polyscope object of type SurfaceMesh.We will use this object to display the mesh in polyscope.

/*
The callback function in polyscope is a function that is called every frame. This is useful if you want to update the visualization based on some parameters. In this case we will use the callback function to update the mesh in polyscope based on the transformation matrix that we will implement in the Transform class. We will also use the callback function to update the transformation matrix based on the user input in polyscope.

*/
void callback()
{
	static int numPoints = 2000;
	static float param = 3.14;

	ImGui::PushItemWidth(100);
	if (ImGui::Button("Reset"))
	{
		V = V_copy;
		psMesh->updateVertexPositions(V);
		Eigen::MatrixXd id = MatrixXd::Identity(4, 4);
		transformer.set_matrix(id);
	}

	ImGui::Text("Uniform Scaling");
	if (ImGui::SliderFloat("Uniform Scale Factor", &unit_scale, 0, 5))
	{
		transformer.uniform_scale(double(unit_scale));
	}
	if (ImGui::Button("Uniform Scale"))
	{
		transformer.apply_transform(V);
		psMesh->updateVertexPositions(V);
	}

	ImGui::Text("Non-Uniform Scaling");
	if (ImGui::SliderFloat("Scale X", &scale_x, 0, 5))
	{
	};
	ImGui::SameLine();
	if (ImGui::SliderFloat("Scale Y", &scale_y, 0, 5))
	{
	};
	ImGui::SameLine();
	if (ImGui::SliderFloat("Scale Z", &scale_z, 0, 5))
	{
	};
	if (ImGui::Button("Scale"))
	{
		transform.scale(double(scale_x), double(scale_y), double(scale_z));
		transform.apply_transform(V);
		psMesh->updateVertexPositions(V);
	}

	ImGui::Text("Translation");
	if (ImGui::SliderFloat("Translate X", &translate_x, -5, 5))
	{
	};
	ImGui::SameLine();
	if (ImGui::SliderFloat("Translate Y", &translate_y, -5, 5))
	{
	};
	ImGui::SameLine();
	if (ImGui::SliderFloat("Translate Z", &translate_z, -5, 5))
	{
	};

	if (ImGui::Button("Translate"))
	{
		transformer.translate(Eigen::Vector3d(double(translate_x), double(translate_y), double(translate_z)));
		transformer.apply_transform(V);
		psMesh->updateVertexPositions(V);
	}

	ImGui::Text("Rotation around axis");
	if (ImGui::RadioButton("X-axis", &rotation_axis, 0))
	{
		rot_x = true;
		rot_y = false;
		rot_z = false;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("Y-axis", &rotation_axis, 1))
	{
		rot_x = false;
		rot_y = true;
		rot_z = false;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("Z-axis", &rotation_axis, 2))
	{
		rot_x = false;
		rot_y = false;
		rot_z = true;
	}
	ImGui::SameLine();
	if (ImGui::SliderFloat("Angle", &theta, -2 * 3.14, 2 * 3.14))
	{
	};

	if (ImGui::Button("Rotate"))
	{
		if (rot_x)
		{
			rotation_axis = 0;
		}
		else if (rot_y)
		{
			rotation_axis = 1;
		}
		else
		{
			rotation_axis = 2;
		}
		transformer.rotate_around_axis(double(theta), rotation_axis);
		transformer.apply_transform(V);
		psMesh->updateVertexPositions(V);
	}

	ImGui::Text("Rotation around axis with Quaternions");

	if (ImGui::SliderFloat("Direction X", &dir_x, -5, 5))
	{
	};
	ImGui::SameLine();
	if (ImGui::SliderFloat("Direction Y", &dir_y, -5, 5))
	{
	};
	ImGui::SameLine();
	if (ImGui::SliderFloat("Direction Z", &dir_z, -5, 5))
	{
	};
	if (ImGui::SliderFloat("Angle Rotation", &theta, -2 * 3.14, 2 * 3.14))
	{
	}
	if (ImGui::Button("Rotate with Quaternions"))
	{
		Eigen::Vector3d axis(dir_x, dir_y, dir_z);
		transformer.rotate_with_quaternions(V, axis, double(theta));
		psMesh->updateVertexPositions(V);
	}
	if (ImGui::Checkbox("Animating", &is_rotating))
	{
	}

	if (is_rotating)
	{
		Eigen::Vector3d axis(dir_x, dir_y, dir_z);
		transformer.rotate_with_quaternions(V, axis, 0.05);
		psMesh->updateVertexPositions(V);
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}

	ImGui::PopItemWidth();
}

int main(int argc, char *argv[])
{

	// --- Load the meshes ---
	//------------------------

	// We use the command line argument to load a mesh into our program.

	// we check first if the command line argument is empty or not. If it is not empty, we load the mesh from the file specified in the command line argument. If it is empty, we load a default mesh.

	std::string path_to_source = std::string(PROJECT_SOURCE_DIR);

	if (argc > 1)
	{

		std::string filename = std::string(argv[1]);
		std::string full_path = path_to_source + filename;
		std::cout << "Full path to file: " << full_path << std::endl;

		std::cout << "Loading mesh from file: " << filename << std::endl;
		igl::read_triangle_mesh(full_path, V, F);
		std::cout << "loading: " << full_path << std::endl;
	}
	else
	{

		// If you prefer you can also load here directly the mesh by specifying the path to the file. However, in this case if you want to change the mesh you have to recompile the code.
		std::cout << " psth to source: " << path_to_source << std::endl;
		std::string filename = "/data/star.off";
		std::string full_path = path_to_source + filename;

		igl::read_triangle_mesh(full_path, V, F);
		std::cout << "loading: " << full_path << std::endl;
		// Load default meshes
	}

	V_copy = V;
	F_copy = F;

	std::cout << " -- Transformation of Meshes -- " << std::endl;

	// --- Visualize the mesh using Polyscope ---
	//--------------------------------------------

	// Options
	polyscope::options::autocenterStructures = true;
	polyscope::view::windowWidth = 1024;
	polyscope::view::windowHeight = 1024;

	// Initialize polyscope
	polyscope::init();

	psMesh = polyscope::registerSurfaceMesh("Input Mesh", V, F);

	polyscope::state::userCallback = callback;

	// Show the gui
	polyscope::show();

	return 0;
}