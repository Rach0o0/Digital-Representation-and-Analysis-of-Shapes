#include <Transform.h>
#include <iostream>

/*
[R11 R12 R13 Tx]
[R21 R22 R23 Ty]
[R31 R32 R33 Tz]
[  0   0   0  1]

*/


using Eigen::MatrixXd, Eigen::Vector3d, Eigen::RowVector3d, Eigen::Quaterniond;

void Transform::uniform_scale(double s)
{
    //Eigen::MatrixXd::Identity(i,i)
    Eigen::MatrixXd scaleM = Eigen::MatrixXd::Identity(4,4);
    scaleM(0,0) = s;
    scaleM(1,1) = s;
    scaleM(2,2) = s;

    //compose
    M = M * scaleM;
}

void Transform::scale(double s1, double s2, double s3)
{
    //non_uniform
    Eigen::MatrixXd scaleM = Eigen::MatrixXd::Identity(4,4);
    scaleM(0,0) = s1;
    scaleM(1,1) = s2;
    scaleM(2,2) = s3;

    //compose
    M = M * scaleM;
}

void Transform::translate(Eigen::Vector3d t)
{
    /*
    [1  0  0  tx]
    [0  1  0  ty]
    [0  0  1  tz]
    [0  0  0  1 ]
    */
    Eigen::MatrixXd transM = Eigen::MatrixXd::Identity(4,4);
    transM(0,3) = t(0);
    transM(1,3) = t(1);
    transM(2,3) = t(2);

    //compose
    M = M * transM;

}

void Transform::rotate_around_axis(double theta, int axis)
{
    /*
    around X : 
    [1    0       0      0]
    [0  cos(θ) -sin(θ)  0]
    [0  sin(θ)  cos(θ)  0]
    [0    0       0      1]

    around Y : 
    [cos(θ)    0       sin(θ)      0]
    [0         1        0          0]
    [-sin(θ)   0      cos(θ)       0]
    [0         0        0          1]

    around Z : 
    [cos(θ)  -sin(θ)    0          0]
    [sin(θ)   cos(θ)    0          0]
    [0         0        1          0]
    [0         0        0          1]
    */

    Eigen::MatrixXd rotM = Eigen::MatrixXd::Identity(4,4);

    double co = cos(theta);
    double si = sin(theta);

    if (axis == 0){
        rotM(1, 1) = co;
        rotM(1, 2) = -si;
        rotM(2,1) = si;
        rotM(2,2) = co;
    }
    else if (axis == 1){
        rotM(0, 0) = co;
        rotM(0, 2) = si;
        rotM(2,0) = -si;
        rotM(2,2) = co;
    }
    else{
        rotM(0, 0) = co;
        rotM(0, 1) = -si;
        rotM(1,0) = si;
        rotM(1,1) = co;
    }

    M = M * rotM;
}

Eigen::MatrixXd Transform::get_matrix()
{
    //return matrix
    return M;
}

void Transform::set_matrix(Eigen::MatrixXd m)
{
    //set the matrix
    M = m;
}

Transform Transform::operator*(const Transform &T)
{
    Transform res;
    res.M = this->M * T.M;
    return res;
}

Transform Transform::operator=(const Transform &T)
{
    this->M = T.M;
    return *this;
}

Transform Transform::operator*(const Eigen::MatrixXd &M_in)
{
    Transform res;
    res.M = this->M * M_in;
    return res;
}

Transform Transform::operator=(const Eigen::MatrixXd &M)
{
    this->M = M;
    return *this;
}

Transform Transform::compose(const Transform &T)
{
    Transform res;
    res.M = this->M * T.M;
    return res;
}

void Transform::apply_transform(Eigen::MatrixXd &V)
{
    /*
    V : (nx3) matrix -> 3D coordinates of points
    - convert into homogeneous : (nx4)
    - apply transformation
    - reconvert into 3D
    */

    int n = V.rows();
    //homogeneous version
    Eigen::MatrixXd V_hom(n, 4);

    //add column of 1 for homogeneous 
    V_hom.block(0, 0, n, 3) = V;
    V_hom.col(3) = Eigen::VectorXd::Ones(n);

    //apply transform
    V_hom = V_hom * M.transpose();

    //reconvert
    V = V_hom.block(0, 0, n, 3);

}

void Transform::print_quaternion(Quaterniond q)
{
    std::cout << "(" << q.w() << ", " << q.x() << ", " << q.y() << ", " << q.z() << std::endl;
}

void Transform::rotate_with_quaternions(Eigen::MatrixXd &V, Eigen::Vector3d axis, double theta)
{
    // To be COMPLETED

    /*
    V matrix of points v
    quaternion : v = (w,x,y,z) with w scalar
    q = quaternion
    v_rotated = q * v * q*

    */

    axis.normalize();
    //quaternion
    Eigen::Quaterniond q(Eigen::AngleAxisd(theta, axis));

    //apply rotation for each point
    for (int i = 0; i < V.rows(); i++){
        Eigen::Vector3d p = V.row(i);
        //apply rotation
        Eigen::Vector3d p_rot = q * p;

        V.row(i) = p_rot;
    }

}