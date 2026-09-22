#include <Transform.h>
#include <iostream>

using Eigen::MatrixXd, Eigen::Vector3d, Eigen::RowVector3d, Eigen::Quaterniond;

void Transform::uniform_scale(double s)
{
}

void Transform::scale(double s1, double s2, double s3)
{
}

void Transform::translate(Eigen::Vector3d t)
{
}

void Transform::rotate_around_axis(double theta, int axis)
{
}

Eigen::MatrixXd Transform::get_matrix()
{
}

void Transform::set_matrix(Eigen::MatrixXd m)
{
}

Transform Transform::operator*(const Transform &T)
{
}

Transform Transform::operator=(const Transform &T)
{
}

Transform Transform::operator*(const Eigen::MatrixXd &M_in)
{
}

Transform Transform::operator=(const Eigen::MatrixXd &M)
{
}

Transform Transform::compose(const Transform &T)
{
}

void Transform::apply_transform(Eigen::MatrixXd &V)
{
}

void Transform::print_quaternion(Quaterniond q)
{
    std::cout << "(" << q.w() << ", " << q.x() << ", " << q.y() << ", " << q.z() << std::endl;
}

void Transform::rotate_with_quaternions(Eigen::MatrixXd &V, Eigen::Vector3d axis, double theta)
{
    // To be COMPLETED
}