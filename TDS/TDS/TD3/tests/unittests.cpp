#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "Bezier.h"

using Eigen::MatrixXd;
using Eigen::RowVector3d;
using Eigen::Vector3d;

static void ExpectMatricesNear(const MatrixXd &A, const MatrixXd &B, double eps = 1e-10)
{
    ASSERT_EQ(A.rows(), B.rows());
    ASSERT_EQ(A.cols(), B.cols());
    for (int i = 0; i < A.rows(); ++i)
        for (int j = 0; j < A.cols(); ++j)
            EXPECT_NEAR(A(i, j), B(i, j), eps) << "Mismatch at (" << i << "," << j << ")";
}

class BezierTest : public ::testing::Test
{
protected:
    // Quadratic control polygon (planar for some analytic checks)
    MatrixXd V2; // 3 control points
    // Cubic control polygon
    MatrixXd V3; // 4 control points

    void SetUp() override
    {
        V2.resize(3, 3);
        V2 << 0, 0, 0,
            1, 2, 0,
            2, 0, 0;

        V3.resize(4, 3);
        V3 << 0, 0, 0,
            1, 1, 0,
            2, -1, 0,
            3, 0, 0;
    }
};
Bezier bezier;

TEST_F(BezierTest, DeCasteljau_Endpoints)
{
    MatrixXd p0 = bezier.de_casteljau(V3, 0.0);
    MatrixXd p1 = bezier.de_casteljau(V3, 1.0);
    ExpectMatricesNear(p0, V3.topRows(1));
    ExpectMatricesNear(p1, V3.bottomRows(1));
}

TEST_F(BezierTest, DeCasteljau_AffineInvariance)
{
    Vector3d t(10.0, -3.5, 2.0);
    double s = 2.5;

    MatrixXd Vt = V2.rowwise() + t.transpose();
    MatrixXd Vs = V2 * s; // uniform scale

    double u = 0.37;

    MatrixXd c = bezier.de_casteljau(V2, u);
    MatrixXd ct = bezier.de_casteljau(Vt, u);
    MatrixXd cs = bezier.de_casteljau(Vs, u);

    ExpectMatricesNear(ct, c.rowwise() + t.transpose(), 1e-12);
    ExpectMatricesNear(cs, c * s, 1e-12);
}

TEST_F(BezierTest, DeCasteljau_MatchesBernstein_Quadratic)
{
    // Quadratic Bernstein: B(t) = (1-t)^2 P0 + 2(1-t)t P1 + t^2 P2
    double t = 0.42;
    MatrixXd dc = bezier.de_casteljau(V2, t);

    double b0 = (1 - t) * (1 - t);
    double b1 = 2 * (1 - t) * t;
    double b2 = t * t;

    RowVector3d bern = b0 * V2.row(0) + b1 * V2.row(1) + b2 * V2.row(2);
    ExpectMatricesNear(dc, bern);
}

TEST_F(BezierTest, DeCasteljauIntermediate_ShapeAndValues)
{
    double t = 0.25;
    MatrixXd mid = bezier.de_casteljau_intermediate(V3, t);
    ASSERT_EQ(mid.rows(), V3.rows() - 1);
    ASSERT_EQ(mid.cols(), 3);
    // Check linear blends for first/last segment
    ExpectMatricesNear(mid.row(0), (1 - t) * V3.row(0) + t * V3.row(1));
    ExpectMatricesNear(mid.bottomRows(1), (1 - t) * V3.row(2) + t * V3.row(3));
}

TEST_F(BezierTest, PlotCurve_SizesAndEnds)
{
    int res = 25;
    MatrixXd graph = bezier.plot_curve(V3, res);
    ASSERT_EQ(graph.rows(), res);
    ASSERT_EQ(graph.cols(), 3);
    ExpectMatricesNear(graph.row(0), bezier.de_casteljau(V3, 0.0));
    ExpectMatricesNear(graph.bottomRows(1), bezier.de_casteljau(V3, 1.0));
}

TEST_F(BezierTest, Subdivide_BasicProperties)
{
    double t = 0.6;
    auto parts = bezier.subdivide(V3, t);
    ASSERT_EQ(parts.size(), 2u);
    const MatrixXd &L = parts[0];
    const MatrixXd &R = parts[1];
    ASSERT_EQ(L.rows(), V3.rows());
    ASSERT_EQ(R.rows(), V3.rows());
    ASSERT_EQ(L.cols(), 3);
    ASSERT_EQ(R.cols(), 3);

    // Endpoints preserved
    ExpectMatricesNear(L.row(0), V3.row(0));
    ExpectMatricesNear(R.bottomRows(1), V3.bottomRows(1));

    // Meeting point equals curve point at t
    MatrixXd ct = bezier.de_casteljau(V3, t);
    ExpectMatricesNear(L.bottomRows(1), ct);
    ExpectMatricesNear(R.topRows(1), ct);
}

TEST_F(BezierTest, Tangent_LinearCurve)
{
    // For degree-1: tangent is constant and equals P1 - P0 (up to normalization if you normalize)
    MatrixXd V(2, 3);
    V << 1, 2, 3,
        4, 6, 9;
    MatrixXd tan0 = bezier.compute_tangent(V, 0.0);
    MatrixXd tan5 = bezier.compute_tangent(V, 0.5);
    MatrixXd tan1 = bezier.compute_tangent(V, 1.0);

    RowVector3d expected = V.row(1) - V.row(0);
    ExpectMatricesNear(tan0, expected);
    ExpectMatricesNear(tan5, expected);
    ExpectMatricesNear(tan1, expected);
}
