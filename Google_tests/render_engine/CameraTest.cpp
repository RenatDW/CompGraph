#include "gtest/gtest.h"
#include "../../render_engine/src/Camera.cpp"
#include "../../render_engine/src/GraphicConveyor.cpp"
#include "../../math/headers/Matrix4D.h"
#include "../../math/headers/Vector3D.h"

TEST(CameraTest, set_position_test)
{
    Camera cam(Vector3D(1,1,1),Vector3D(1,1,1),10, 10, 10, 10);
    Camera cam2(Vector3D(2,2,2),Vector3D(1,1,1),10, 10, 10, 10);
    cam.movePosition(Vector3D(1,1,1));
    EXPECT_EQ(cam == cam2, true);
}

TEST(CameraTest, move_target_test)
{
    Camera cam(Vector3D(1,1,1),Vector3D(1,1,1),10, 10, 10, 10);
    Camera cam2(Vector3D(1,1,1),Vector3D(2,2,2),10, 10, 10, 10);
    cam.moveTarget(Vector3D(1,1,1));
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