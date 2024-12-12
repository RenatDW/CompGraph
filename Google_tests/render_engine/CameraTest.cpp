#include "gtest/gtest.h"
#include "../../../src/render_engine/src/Camera.cpp"
// #include <QPainter>
#include "../../../src/render_engine/src/GraphicConveyor.cpp"
#include "../../../src/math/headers/Matrix4D.h"
#include "../../../src/math/headers/Point3D.h"
#include "../../../src/math/headers/Vector3D.h"
// #include "../../render_engine/headers/RenderEngine.h"
// #include "../../render_engine/headers/RenderEngine.h"

TEST(CameraTest, set_position_test)
{
    Camera cam(Vector3D(1,1,1),Vector3D(1,1,1),10, 10, 10, 10);
    Camera cam2(Vector3D(2,2,2),Vector3D(1,1,1),10, 10, 10, 10);
	cam.move_position(Vector3D(1, 1, 1));
    EXPECT_EQ(cam == cam2, true);
}

TEST(CameraTest, move_target_test)
{
    Camera cam(Vector3D(1,1,1),Vector3D(1,1,1),10, 10, 10, 10);
    Camera cam2(Vector3D(1,1,1),Vector3D(2,2,2),10, 10, 10, 10);
	cam.move_target(Vector3D(1, 1, 1));
    EXPECT_EQ(cam == cam2, true);

}

TEST(CameraTest, get_view_matrix_test)
{
    Camera cam(Vector3D(1,2,3),Vector3D(4,5,6),10, 10, 10, 10);
    Matrix4D view_matrix = cam.get_view_matrix();
    const Matrix4D ans({{0.707,-0.408,0.577,0},{0,0.816,0.577,0},{-0.707,-0.408,0.577,0},{1.414,0,-3.462,1}});
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            EXPECT_NEAR(ans.get(i,j), view_matrix.get(i,j), 0.01);

        }
    }
}

TEST(CameraTest, get_projection_matrix_test)
{
    Camera cam(Vector3D(1,2,3),Vector3D(4,5,6),7, 8, 9, 10);
    Matrix4D projection_matrix = cam.get_projection_matrix();
    Matrix4D ans({{0.3337, 0 ,0 ,0},{0, 2.6696, 0,0},{0, 0, 19, 1},{0, 0, -180, 0}});
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            EXPECT_NEAR(ans.get(i,j), projection_matrix.get(i,j), 0.01);

        }
    }
}

TEST(EngineTest, edge_function)
{
    Point3D d(1,0,0);
    Point3D b(0,1,0);
    Point3D a(0,0,1);
    Point3D c(1/2,0,1/2);
    // ASSERT_EQ (RenderEngine::edge_function(d,b,c), 0);
}

TEST(EngineTest, transpoort)
{
	// Original matrix
	Matrix4D original({
		{ 1.0f, 2.0f, 3.0f, 4.0f },
		{ 5.0f, 6.0f, 7.0f, 8.0f },
		{ 9.0f, 10.0f, 11.0f, 12.0f },
		{ 13.0f, 14.0f, 15.0f, 16.0f }
	});

	// Ожидаемая транспонированная матрица
	Matrix4D expected({
		{ 1.0f, 5.0f, 9.0f, 13.0f },
		{ 2.0f, 6.0f, 10.0f, 14.0f },
		{ 3.0f, 7.0f, 11.0f, 15.0f },
		{ 4.0f, 8.0f, 12.0f, 16.0f }
	});

	// Выполняем транспонирование
	Matrix4D result = original.transposition();

	// Проверяем, что результат совпадает с ожидаемым
	EXPECT_EQ(result, expected);
}

TEST(EngineTest, transpoorted_featues)
{
	Camera camera(Vector3D(0, 0, 100), Vector3D(0, 0, 0),
		1.0f, 1, 0.01f, 100);
	//normal
	Matrix4D model_matrix = Matrix4D::create_identity_matrix();
	Matrix4D view_matrix = camera.get_view_matrix();
	Matrix4D projection_matrix = camera.get_projection_matrix();
	Matrix4D model_view_projection_matrix(model_matrix);
	model_view_projection_matrix = model_view_projection_matrix * projection_matrix * view_matrix;

	//trans
	Matrix4D tr_model_matrix = Matrix4D::create_identity_matrix().transposition();
	Matrix4D tr_view_matrix = camera.get_view_matrix().transposition();
	Matrix4D tr_projection_matrix = camera.get_projection_matrix().transposition();
	Matrix4D tr_model_view_projection_matrix(tr_model_matrix);
	tr_model_view_projection_matrix = tr_model_view_projection_matrix * tr_view_matrix * tr_projection_matrix;

	ASSERT_EQ(view_matrix, tr_view_matrix.transposition());
	ASSERT_EQ(model_matrix, tr_model_matrix.transposition());
	ASSERT_EQ(projection_matrix, tr_projection_matrix.transposition());
	ASSERT_EQ(model_view_projection_matrix,  tr_model_view_projection_matrix.transposition());
}

