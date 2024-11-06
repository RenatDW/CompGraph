# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name

add_executable(Google_Tests_run
        math_tests/Vector2DTest.cpp
        render_engine/CameraTest.cpp
        obj_reader/ObjReaderTest.cpp
        Math_tests/Vector3DTest.cpp
        math_tests/Point2DTest.cpp
        math_tests/Matrix3DTest.cpp
        math_tests/Matrix4DTest.cpp
        math_tests/Vector4DTest.cpp
        math_tests/Point3DTest.cpp
)

target_link_libraries(Google_Tests_run gtest gtest_main)
