#include "gtest/gtest.h"
#include "../../../src/render_engine/headers/GraphicConveyor.h"
#include <cmath>

bool matricesAreEqual(const Matrix4D& m1, const Matrix4D& m2, float epsilon = 1e-5)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			if (std::fabs(m1.get(row, col) - m2.get(row, col)) > epsilon)
			{
				return false;
			}
		}
	}
	return true;
}

TEST(GraphicConveyorTest, Rotate)
{
	Matrix4D result = GraphicConveyor::get_rotate_matrix(90, 0, 0);
	Matrix4D expected({
			{0, 1, 0, 0},
			{-1, 0, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
	});

	EXPECT_TRUE(matricesAreEqual(result, expected));
}

TEST(GraphicConveyorTest, RotateZeroDegrees)
{
	Model model;
	model.vertices = {
			{1, 1, 1},
	};

	GraphicConveyor::rotate(model, 0.0f, 0.0f, 0.0f);

	Vector3D expectedVertex(1.0f, 1.0f, 1.0f);
	EXPECT_EQ(model.vertices[0], expectedVertex);
}

TEST(GraphicConveyorTest, Scale)
{
	float sx = 2.0f, sy = 3.0f, sz = 4.0f;

	Matrix4D expected({
			{2, 0, 0, 0},
			{0, 3, 0, 0},
			{0, 0, 4, 0},
			{0, 0, 0, 1}
	});

	Matrix4D result = GraphicConveyor::get_scale_matrix(sx, sy, sz);
	EXPECT_TRUE(matricesAreEqual(result, expected));
}

TEST(GraphicConveyorTest, Translate)
{
	float tx = 5.0f, ty = 6.0f, tz = 7.0f;

	Matrix4D expected({
			{1, 0, 0, 5},
			{0, 1, 0, 6},
			{0, 0, 1, 7},
			{0, 0, 0, 1}
	});

	Matrix4D result = GraphicConveyor::get_translate_matrix(tx, ty, tz);
	EXPECT_TRUE(matricesAreEqual(result, expected));
}

TEST(GraphicConveyorTest, rotateScaleTranslateTest)
{
	Model model;
	model.vertices = {
			{1, 0, 0},
	};
	GraphicConveyor::rotate_scale_translate(
			model, 2.0f, 2.0f, 2.0f, 90.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f);

	Vector3D expectedVertex(5.0f, -2.0f, 0.0f);
	EXPECT_EQ(model.vertices[0], expectedVertex);
}

TEST(GraphicConveyorTest, PerspectiveMatrix)
{
	float fov = static_cast<float>(M_PI / 4);
	float aspect_ratio = 16.0f / 9.0f;
	float near_plane = 1.0f;
	float far_plane = 10.0f;

	Matrix4D result = GraphicConveyor::perspective(fov, aspect_ratio, near_plane, far_plane);

	EXPECT_FLOAT_EQ(result.get(0, 0), 1.0f / (aspect_ratio * std::tan(fov / 2)));
	EXPECT_FLOAT_EQ(result.get(1, 1), 1.0f / std::tan(fov / 2));
	EXPECT_FLOAT_EQ(result.get(2, 2), (far_plane + near_plane) / (far_plane - near_plane));
	EXPECT_FLOAT_EQ(result.get(2, 3), 2 * near_plane * far_plane / (near_plane - far_plane));
	EXPECT_FLOAT_EQ(result.get(3, 2), 1.0f);
}


