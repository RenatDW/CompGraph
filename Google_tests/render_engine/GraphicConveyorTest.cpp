#include "gtest/gtest.h"
#include "../../../src/render_engine/headers/GraphicConveyor.h"
#include <cmath>

bool matricesAreEqual(const Matrix4D& m1, const Matrix4D& m2, float epsilon = 1e-5)
{
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			if (std::fabs(m1.get(row, col) - m2.get(row, col)) > epsilon) {
				return false;
			}
		}
	}
	return true;
}

TEST(GraphicConveyorTest, RotateMatrix)
{
	Matrix4D result = GraphicConveyor::get_rotate_matrix(static_cast<float>(M_PI / 2), 0.0f, 0.0f);
	Matrix4D expected({
			{0, 1, 0, 0},
			{-1, 0, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
	});

	EXPECT_TRUE(matricesAreEqual(result, expected));
}


TEST(GraphicConveyorTest, rotateScaleTranslateTest)
{

}
